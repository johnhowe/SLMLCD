/** @file   irq.h
    @author M. P. Hayes, UCECE
    @date   04 June 2007
    @brief 
*/
#ifndef IRQ_H
#define IRQ_H

#include "config.h"
#include "bits.h"

#ifndef AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE
#define AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL
#endif

typedef void (* irq_vector_t) (void);

typedef uint32_t irq_id_t;

typedef uint32_t irq_type_t;

typedef uint32_t irq_priority_t;


/* NB, The first interrupt vector is for FIQ.  */
enum {IRQ_ID_MIN = 0, IRQ_ID_MAX = 31};


__inline void irq_type_set (irq_id_t id, irq_type_t type)
{
    BITS_INSERT (AT91C_BASE_AIC->AIC_SMR[id], type, 5, 6);
}


__inline void irq_priority_set (irq_id_t id, irq_priority_t priority)
{
    BITS_INSERT (AT91C_BASE_AIC->AIC_SMR[id], priority, 0, 2);
}


__inline void irq_clear (irq_id_t id)
{
    AT91C_BASE_AIC->AIC_ICCR = BIT (id);
}


__inline void irq_enable (irq_id_t id)
{
    AT91C_BASE_AIC->AIC_IECR = BIT (id);
}


__inline bool irq_enabled_p (irq_id_t id)
{
    return (AT91C_BASE_AIC->AIC_IECR & BIT (id)) != 0;
}


__inline void irq_disable (irq_id_t id)
{
    AT91C_BASE_AIC->AIC_IDCR = BIT (id);
}


__inline void irq_trigger (irq_id_t id)
{
    AT91C_BASE_AIC->AIC_ISCR = BIT (id);
}


__inline void irq_vector_set (irq_id_t id, irq_vector_t isr)
{
    AT91C_BASE_AIC->AIC_SVR[id] = (uint32_t) isr;
}


/* This sets up a vector for an IRQ interrupt.  Note that the IRQ vectors
   are stored in special memoy-mapped registers and thus do not depend
   on RAM or ROM model.  */
__inline void irq_config (irq_id_t id, irq_priority_t priority,
                          uint32_t type, irq_vector_t isr)
{
    irq_disable (id);
    irq_priority_set (id, priority);
    irq_type_set (id, type);
    irq_vector_set (id, isr);
    irq_clear (id);
}
#endif /* IRQ_H  */
