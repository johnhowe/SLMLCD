/** @file   piezo.h
    @author M. P. Hayes, UCECE
    @date   12 March 2003
    @brief 
*/

#ifndef PIEZO_H
#define PIEZO_H

#include "config.h"
#include "delay.h"
#include "port.h"


#define PIEZO_CFG(PORT, PORTBIT) {(PORT), BIT (PORTBIT)}


typedef struct
{
    port_t port;
    port_mask_t bitmask;
} piezo_cfg_t;


typedef const piezo_cfg_t piezo_obj_t;

typedef piezo_obj_t *piezo_t;


/* CFG is points to configuration data specified by PIEZO_CFG to
   define the port the PIEZO is connected to.  The returned handle is
   passed to the other piezo_xxx routines to denote the PIEZO to
   operate on.  */
extern piezo_t
piezo_init (const piezo_cfg_t *cfg);


/* Perhaps we only need a toggle routine.  This would
   be faster and save memory.  */
static inline void
piezo_set (piezo_t piezo, uint8_t val)
{
    port_pins_set (piezo->port, piezo->bitmask, val);
}
        
#endif
