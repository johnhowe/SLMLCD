# 1 "Cstartup.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "Cstartup.S"
# 18 "Cstartup.S"
     .equ IRQ_Stack_Size, 0x00000060



 .equ AIC_IVR, (256)
 .equ AIC_FVR, (260)
 .equ AIC_EOICR, (304)
 .equ AT91C_BASE_AIC, (0xFFFFF000)

#;------------------------------------------------------------------------------
#;- Section Definition
#;-----------------
#;- Section
#;- .internal_ram_top Top_Stack: used by the cstartup for vector initalisation
#;- management defined by ld and affect from ldscript
#;------------------------------------------------------------------------------
 .section .internal_ram_top
 .code 32
 .align 0
 .global Top_Stack
Top_Stack:





        .section .reset
        .text
        .global _startup
        .func _startup
_startup:
reset:
# 60 "Cstartup.S"
                B InitReset
undefvec:
                B undefvec
swivec:
                B swivec
pabtvec:
                B pabtvec
dabtvec:
                B dabtvec
rsvdvec:
                B rsvdvec
irqvec:
                B IRQ_Handler_Entry
fiqvec:






FIQ_Handler_Entry:





            mov r9,r0
         ldr r0 , [r8, #AIC_FVR]
            msr CPSR_c,#I_BIT | F_BIT | ARM_MODE_SVC


            stmfd sp!, { r1-r3, r12, lr}


            mov r14, pc
            bx r0


            ldmia sp!, { r1-r3, r12, lr}


            msr CPSR_c, #I_BIT | F_BIT | ARM_MODE_FIQ


            mov r0,r9


            subs pc,lr,#4
 .align 0
.RAM_TOP:
 .word Top_Stack

InitReset:



             .extern AT91F_LowLevelInit



            ldr r13,.RAM_TOP

         ldr r0,=AT91F_LowLevelInit
            mov lr, pc
         bx r0
# 145 "Cstartup.S"
   .EQU IRQ_STACK_SIZE, (3*8*4)
          .EQU ARM_MODE_FIQ, 0x11
          .EQU ARM_MODE_IRQ, 0x12
          .EQU ARM_MODE_SVC, 0x13

          .EQU I_BIT, 0x80
          .EQU F_BIT, 0x40




                mov r0,r13


                msr CPSR_c, #ARM_MODE_FIQ | I_BIT | F_BIT

             ldr r8, =AT91C_BASE_AIC


                msr CPSR_c, #ARM_MODE_IRQ | I_BIT | F_BIT
                mov r13, r0
                sub r0, r0, #IRQ_Stack_Size

                msr CPSR_c, #ARM_MODE_SVC
                mov r13, r0



# Relocate .data section (Copy from ROM to RAM)
                LDR R1, =_etext
                LDR R2, =_data
                LDR R3, =_edata
LoopRel: CMP R2, R3
                LDRLO R0, [R1], #4
                STRLO R0, [R2], #4
                BLO LoopRel

# Clear .bss section (Zero init)
                MOV R0, #0
                LDR R1, =__bss_start__
                LDR R2, =__bss_end__
LoopZI: CMP R1, R2
                STRLO R0, [R1], #4
                BLO LoopZI

  ldr lr,=exit
  ldr r0,=main
  bx r0

        .size _startup, . - _startup
        .endfunc




        .global exit
        .func exit
exit:
        b .
 .size exit, . - exit
        .endfunc
# 219 "Cstartup.S"
        .global IRQ_Handler_Entry
        .func IRQ_Handler_Entry

IRQ_Handler_Entry:



            sub lr, lr, #4
            stmfd sp!, {lr}


            mrs r14, SPSR
            stmfd sp!, {r14}


            stmfd sp!, {r0}




            ldr r14, =AT91C_BASE_AIC
     ldr r0 , [r14, #AIC_IVR]
     str r14, [r14, #AIC_IVR]


            msr CPSR_c, #ARM_MODE_SVC


            stmfd sp!, { r1-r3, r12, r14}


            mov r14, pc
            bx r0

            ldmia sp!, { r1-r3, r12, r14}


            msr CPSR_c, #I_BIT | ARM_MODE_IRQ


            ldr r14, =AT91C_BASE_AIC
            str r14, [r14, #AIC_EOICR]


            ldmia sp!, {r0}


            ldmia sp!, {r14}
            msr SPSR_cxsf, r14


            ldmia sp!, {pc}^

        .size IRQ_Handler_Entry, . - IRQ_Handler_Entry
        .endfunc




        .global AT91F_Default_FIQ_handler
        .func AT91F_Default_FIQ_handler
AT91F_Default_FIQ_handler:
            b AT91F_Default_FIQ_handler
        .size AT91F_Default_FIQ_handler, . - AT91F_Default_FIQ_handler
        .endfunc

        .global AT91F_Default_IRQ_handler
        .func AT91F_Default_IRQ_handler
AT91F_Default_IRQ_handler:
            b AT91F_Default_IRQ_handler
        .size AT91F_Default_IRQ_handler, . - AT91F_Default_IRQ_handler
        .endfunc

        .global AT91F_Spurious_handler
        .func AT91F_Spurious_handler
AT91F_Spurious_handler:
            b AT91F_Spurious_handler
        .size AT91F_Spurious_handler, . - AT91F_Spurious_handler
        .endfunc


        .end
