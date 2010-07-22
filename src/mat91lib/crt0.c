/** @file   crt0.c
    @author M. P. Hayes, UCECE
    @date   10 June 2007
    @brief  C run time initialisation for the Atmel AT91 series 
            of ARM7 TDMI microprocessors. 
*/

#include "config.h"
#include "cpu.h"

/* This requires cpu.h and irq.h of mat91lib. 

   The user application is run in Supervisor Mode.  This allows full
   privileges.  The top 72 bytes of SRAM are used as the IRQ Mode
   stack.  The Supervisor Mode stack sits below this.  FIQ Mode has no
   allocated stack.  

   Usually this is written in assembler; I have been bloody minded and
   wrote it in C using a fair bit of inline assembler when necessary.
*/


#ifndef IRQ_STACK_SIZE
/* Store 3 registers R0, LR, and SPSR during IRQ.  */
#define IRQ_STACK_SIZE  (3 * 8 * 4)
#endif

#define AIC_FVR_OFFSET 264
#define AIC_IVR_OFFSET 260
//#define AIC_FVR_OFFSET ((char *)&AT91C_BASE_AIC->AIC_FVR - (char *)AT91C_BASE_AIC)
//#define AIC_IVR_OFFSET ((char *)&AT91C_BASE_AIC->AIC_IVR - (char *)AT91C_BASE_AIC)


/** Symbols defined by linker script.  */
extern char __stack_start__;    /** Top of stack.  */
extern char __data_load__;      /** Start of initial values for .data (in flash).  */
extern char __data_start__;     /** Start of data (in SRAM).  */
extern char __data_end__;       /** End of data (in SRAM).  */
extern char __ramtext_load__;   /** Start of initial values for .ramtext (in flash).  */
extern char __ramtext_start__;  /** Start of ramtext (in SRAM).  */
extern char __ramtext_end__;    /** End of ramtext (in SRAM).  */
extern char __bss_start__;      /** Start of uninitialised variables.  */
extern char __bss_end__;        /** End of uninitialised variables.  */


extern int main (int, char *);


void exit (int status __attribute ((unused)))
{
    while (1)
        continue;
}


extern void start (void) __attribute__ ((section (".vectors")))
    __attribute__ ((naked));

/** Startup function.  */
void start (void)
{
    /* Vector table.  */

    /* Reset  0x00 */
    __asm__ ("\tb _reset_handler");
    /* Hang if decoded undefined instruction  0x04 */
    __asm__ ("\tb ."); 
    /* Hang if software interrupt 0x08 */
    __asm__ ("\tb .");
    /* Hang if fetching instruction from invalid address (Prefetch Abort) 0x0c */ 
    __asm__ ("\tb .");
    /* Hang if reading data from invalid address (Data Abort) 0x10 */ 
    __asm__ ("\tb .");
    /* Reserved  0x14 */
    __asm__ ("\tb .");
    /* IRQ 0x18 */
    __asm__ ("\tb _irq_handler");

    /* Fall through to FIQ handler.  */

    /* In FIQ Mode we have banked registers R8--R14 and thus can hold
       values between fast interrupts.  R13 is reserved for the stack
       pointer and R14 is reserved for the link register.

       We use R8 to point to the base of the AIC.  */

    /* Save r0 in FIQ_Register.  */
    __asm__ ("\tmov r9, r0");

    
    __asm__ ("\tldr r0, [r8, %0]" : : "i" (AIC_FVR_OFFSET));
         
    
    /* Switch to Supervisor Mode to allow stack access for C code
       because the FIQ is not yet acknowledged.  */
    cpu_cpsr_c_set_const (CPU_I_BIT | CPU_F_BIT | CPU_MODE_SVC);

    /* Save scratch/used registers and LR on Supervisor Mode stack.  */
    __asm__ ("\tstmfd sp!, {r1-r3, r12, lr}");

    /* Branch to the routine pointed by the AIC_FVR.  */
    __asm__ ("\tmov r14, pc");
    __asm__ ("\tbx r0");

    /* Restore scratch/used registers and LR from Supervisor Mode stack.  */
    __asm__ ("\tldmia sp!, {r1-r3, r12, lr}");

    /* Leave interrupts disabled and switch back to FIQ Mode.  */
    cpu_cpsr_c_set_const (CPU_I_BIT | CPU_F_BIT | CPU_MODE_FIQ);

    /* Restore the R0 CPU_MODE_SVC register.  */
    __asm__ ("\tmov r0, r9");

    /* Restore the Program Counter using the LR_FIQ directly in the PC.  */
    __asm__ ("\tsubs pc, lr, #4");
}


extern void _reset_handler (void)
    __attribute__ ((section (".vectors")))
    __attribute__ ((naked));

void _reset_handler (void)
{
    register char *p = &__stack_start__;
#if 1
    /* Set up temporary stack in top of internal RAM.   */
    register uint32_t sp __asm__ ("sp") = (uint32_t)p;
    register uint32_t fp __asm__ ("fp") = (uint32_t)p;

    /* Create dummy uses.  */
    __asm__ ("" : : "r" (sp));
    __asm__ ("" : : "r" (fp));
#else
    /* This does not work without optimisation since it requires the
       stack and frame pointer to be set up.  */       
    cpu_sp_set ((uint32_t) p);
#endif

    /* Start clocks, map SRAM, etc.  */
    cpu_init ();

    /* Select FIQ Mode.  */
    cpu_cpsr_c_set_const (CPU_I_BIT | CPU_F_BIT | CPU_MODE_FIQ);

    /* Initialise the FIQ register to the AIC.  */
    {
        register uint32_t r8 __asm__ ("r8") = (uint32_t) AT91C_BASE_AIC;

        /* Create a dummy use.  */
        __asm__ ("" : : "r" (r8));
    }

    /* Select IRQ Mode and set IRQ Mode stack.  */
    cpu_cpsr_c_set_const (CPU_I_BIT | CPU_F_BIT | CPU_MODE_IRQ);
    cpu_sp_set ((uint32_t) p);

    /* Select Supervisor Mode and set Supervisor Mode stack.  */
    cpu_cpsr_c_set_const (CPU_MODE_SVC);
    cpu_sp_set ((uint32_t) (p - IRQ_STACK_SIZE));

    {
        char *src;
        char *dst;

        /* Initialise initialised global variables in .data.  */
        for (src = &__data_load__, dst = &__data_start__; dst < &__data_end__; )
            *dst++ = *src++;
        
        /* Zero uninitialised global variables in .bss.  */
        for (dst = &__bss_start__; dst < &__bss_end__; )
            *dst++ = 0;

        /* Relocate .ramtext section.  This is only required for
           functions in the ROM model that need to execute out of RAM
           for speed.  */
        if (__ramtext_load__ != __ramtext_start__)
            for (src = &__ramtext_load__, dst = &__ramtext_start__; dst < &__ramtext_end__; )
                *dst++ = *src++;
    }

    /* Call main using absolute addressing through the interworking.  */
    __asm__ ("\tldr lr, =exit");
    __asm__ ("\tldr r0, =main");
    __asm__ ("\tbx  r0");
}


/** IRQ handler.  This must run in ARM mode.  Note this will not
    compile in Thumb mode because of some of the inline ARM assembler
    instructions.  */
extern void _irq_handler (void)
    __attribute__ ((section (".vectors")))
    __attribute__ ((naked));

void _irq_handler (void)
{
    /* In IRQ mode we have banked registers R13--R14.  R13 is reserved
       for the stack pointer and R14 is reserved for the link
       register.  */


    /* Adjust and save LR_irq in IRQ stack.  */
    __asm__ ("\tsub lr, lr, #4");
    __asm__ ("\tstmfd sp!, {lr}");

    /* Save SPSR for nested interrupt.  */
    __asm__ ("\tmrs r14, SPSR");
    __asm__ ("\tstmfd sp!, {r14}");

    /* Save r0 in IRQ stack.  */
    __asm__ ("\tstmfd sp!, {r0}");

    /* De-assert the NIRQ and clear the source in Protect Mode.  This
       has no effect in Normal Mode.  */
    {
        /* Use r14 since it is saved.  */
        register uint32_t r14 __asm__ ("r14") = (uint32_t) AT91C_BASE_AIC;

        __asm__ ("\tldr r0, [%1, %0]" : : "i" (AIC_IVR_OFFSET), "r" (r14));
        __asm__ ("\tstr %1, [%1, %0]" : : "i" (AIC_IVR_OFFSET), "r" (r14));
    }

    /* Enable interrupt and switch in Supervisor Mode.  */
    cpu_cpsr_c_set_const (CPU_MODE_SVC);

    /* Save scratch/used registers and LR on Supervisor Mode stack.  */
    __asm__ ("\tstmfd sp!, {r1-r3, r12, r14}");

    /* Branch to the routine pointed by the AIC_IVR.  */
    __asm__ ("\tmov r14, pc");
    __asm__ ("\tbx r0");

    /* Restore scratch/used registers and LR from Supervisor Mode stack.  */
    __asm__ ("\tldmia sp!, {r1-r3, r12, r14}");

    /* Disable interrupt and switch back in IRQ Mode.  */
    cpu_cpsr_c_set_const (CPU_I_BIT | CPU_MODE_IRQ);

    /* Mark the End of Interrupt on the AIC.  */
    {
        register uint32_t * r14 __asm__ ("r14") 
            = (uint32_t *) &AT91C_BASE_AIC->AIC_EOICR;

        /* Write anything to AIC_EOICR to indicate interrupt handling
           complete.  */
        __asm__ ("\tstr %0, [%0, #0]" : : "r" (r14));
    };

    /* Restore SPSR_irq and r0 from IRQ Mode stack.  */
    __asm__ ("\tldmia sp!, {r0}");
    __asm__ ("\tldmia sp!, {r14}");
    __asm__ ("\tmsr SPSR_cxsf, r14");

    /* Restore adjusted LR_irq from IRQ Mode stack directly in the PC.  */
    __asm__ ("\tldmia sp!, {pc}^");
}


/** Dummy ISR for unexpected interrupts.  */
void
_irq_unexpected_handler (void)
{
    /* Hang.  */
    while (1)
        continue;
}


/** Dummy ISR for spurious interrupts.  */
void
_irq_spurious_handler (void)
{
    /* Hang.  */
    while (1)
        continue;
}




