/** @file   led.c
    @author M. P. Hayes, UCECE
    @date   08 June 2002
    @brief  Simple LED driver.
*/

#include "led.h"

/* These routines are for controlling a LED, piezoelectric tweeter, or
   any other 1 bit device.  The flashing code is now in flasher.c.  It
   is assumed that the LEDs are wired to ground so turn on with a
   logic high output level.  */


/* Create a new LED device.  */
led_t
led_init (const led_cfg_t *cfg)
{
    /* Configure port as output.  */
    port_pins_config_output (cfg->port, cfg->bitmask);

    return cfg;
}
