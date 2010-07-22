/** @file   glcd.c
    @author M. P. Hayes, UCECE
    @date   28 January 2008
    @brief  Simple graphical GLCD driver.
*/

#include "config.h"
#include "glcd.h"
#include "delay.h"
#include "spi.h"

#include <stdlib.h>

/* This driver controls an S6B1713 GLCD controller via SPI.  The
   S6B1713 is a 65 com / 132 seg driver and controller for STN GLCD.
*/


#ifndef GLCD_SPI_DIVISOR
#define GLCD_SPI_DIVISOR 2
#endif


/* The following macros must be defined:

   GLCD_SPI_CHANNEL if the SPI controller supports multiple channels
   otherwise GLCD_CS_PORT and GLCD_CS_BIT.

   GLCD_RS_PORT and GLCD_RS_BIT to specify the port controlling the RS signal.

*/

enum {
    GLCD_CMD_DISPLAY_OFF = 0xAE,
    GLCD_CMD_DISPLAY_ON = 0xAF,
    GLCD_CMD_REF_VOLTAGE_MODE = 0x81,
    GLCD_CMD_PAGE_ADDRESS_SET = 0xB0,
    GLCD_CMD_COL_ADDRESS_MSB_SET = 0x10,
    GLCD_CMD_COL_ADDRESS_LSB_SET = 0x00,
    GLCD_CMD_SEGOUTPUT_NORMAL = 0xA0,
    GLCD_CMD_SEGOUTPUT_REVERSE = 0xA1,
    GLCD_CMD_COMOUTPUT_NORMAL = 0xC0,
    GLCD_CMD_COMOUTPUT_REVERSE = 0xC8,
    GLCD_CMD_DISPLAY_NORMAL = 0xA6,
    GLCD_CMD_DISPLAY_REVERSE = 0xA7,
    GLCD_CMD_DISPLAY_ENTIRE_OFF = 0xA4,
    GLCD_CMD_DISPLAY_ENTIRE_ON = 0xA5,
    GLCD_CMD_BIAS0 = 0xA2,
    GLCD_CMD_BIAS1 = 0xA3,
    GLCD_CMD_MODIFY_READ_ON = 0xE0,
    GLCD_CMD_MODIFY_READ_OFF = 0xEE,
    GLCD_CMD_POWER = 0x28,
    GLCD_CMD_INITIAL_LINE_SET = 0x40,
    GLCD_CMD_REG_RESISTOR = 0x20,
    /* Reset the controller.  */
    GLCD_CMD_RESET = 0xE2,
};


/* Power control circuits.  Or the necessary GLCD_VOLT_* constants
   with GLCD_CMD_POWER, e.g., (GLCD_CMD_POWER | GLCD_VOLT_REGULATOR)
   will turn the regulator on and the converter and follower off.  */
#define GLCD_VOLT_CONVERTER                0x04
#define GLCD_VOLT_REGULATOR                0x02
#define GLCD_VOLT_FOLLOWER                 0x01

/* Set the internal voltage regulator resistor ratio 1 + (Rb / Ra)
   or with the desired value:
   000 = 1.90    001 = 2.19     010 = 2.55
   011 = 3.02    100 = 3.61     101 = 4.35
   110 = 5.29    111 = 6.48
*/



static inline void
glcd_command_mode (void)
{
    port_pin_set_low (GLCD_RS_PORT, GLCD_RS_BIT);
}


static inline void
glcd_data_mode (void)
{
    port_pin_set_high (GLCD_RS_PORT, GLCD_RS_BIT);
}


static inline void
glcd_send (glcd_t glcd, char ch)
{
    spi_putc (glcd->spi, ch);
}


static void
glcd_config (glcd_t glcd)
{
    /* Configure the RS pin as an output.  */
    port_pin_config_output (GLCD_RS_PORT, GLCD_RS_BIT);
    
    /* Enter command mode.  */
    glcd_command_mode ();

    /* Set segment and common lines to normal direction.  */
    glcd_send (glcd, GLCD_CMD_SEGOUTPUT_NORMAL);
    glcd_send (glcd, GLCD_CMD_COMOUTPUT_NORMAL);

    /* Set the GLCD bias to 1/9.  With a duty ratio of 1/65 the GLCD
       bias is 1/7 or 1/9.  */
    glcd_send (glcd, GLCD_CMD_BIAS1);

    /* Bring the power circuits online in stages, pausing between each.  */
    glcd_send (glcd, GLCD_CMD_POWER | GLCD_VOLT_CONVERTER);
    delay_ms (1);

    glcd_send (glcd, GLCD_CMD_POWER | GLCD_VOLT_CONVERTER | GLCD_VOLT_REGULATOR);
    delay_ms (1);

    glcd_send (glcd, GLCD_CMD_POWER | GLCD_VOLT_CONVERTER 
              | GLCD_VOLT_REGULATOR | GLCD_VOLT_FOLLOWER);
    delay_ms (1);
    
    /* Set the reference voltage parameter alpha to 24 and the
       resistor regulator ratio to 4.35. 
       
       Vo = (1 + Rb / Ra) * Vev
       
       Vev = (1 - (63 - alpha) / 300) * Vref

       Now Vref = 2 V so with alpha = 24,
       Vev = (1 - (63 - 24) / 300) * 2 = 1.74 V
       Vo = 4.35 * 1.74 = 7.57 V
       
       require Vo < Vout (where Vout is set by external capacitor
       configuration)  */    
    glcd_send (glcd, GLCD_CMD_REF_VOLTAGE_MODE);
    glcd_send (glcd, 50);
    glcd_send (glcd, GLCD_CMD_REG_RESISTOR | 5);
    
    /* Set initial display line to zero.  */
    glcd_send (glcd, GLCD_CMD_INITIAL_LINE_SET | 0);

    glcd_send (glcd, GLCD_CMD_DISPLAY_NORMAL);
    
    /* Turn the GLCD on.  */
    glcd_send (glcd, GLCD_CMD_DISPLAY_ON);
}


void 
glcd_contrast_set (glcd_t glcd __UNUSED__, uint8_t contrast)
{
    int alpha;

#if 0
    alpha = (3 * contrast_percent) - 300 + 63;
#else
    alpha = contrast;
#endif
    if (alpha > 63)
        alpha = 63;

    glcd_command_mode ();
    glcd_send (glcd, GLCD_CMD_REF_VOLTAGE_MODE);
    glcd_send (glcd, alpha);
    glcd_send (glcd, GLCD_CMD_REG_RESISTOR | 5);
}


glcd_t
glcd_init (glcd_obj_t *obj, const glcd_cfg_t *cfg)
{
    glcd_t glcd;
    const spi_cfg_t spi_cfg = SPI_CFG (GLCD_SPI_CHANNEL, 
                                       GLCD_SPI_DIVISOR,
                                       GLCD_CS_PORT, GLCD_CS_BIT);

    glcd = obj;
    glcd->cfg = cfg;

    glcd->spi = spi_init (&spi_cfg);

#ifdef GLCD_RESET_BIT
    port_pin_set_high (GLCD_RESET_PORT, GLCD_RESET_BIT);
    port_pin_set_low (GLCD_RESET_PORT, GLCD_RESET_BIT);
    /* Minimum reset pulse is 900 ns.  */
    DELAY_US (2);
    port_pin_set_high (GLCD_RESET_PORT, GLCD_RESET_BIT);
#endif

    glcd_config (glcd);

    glcd->modified = 0;
    glcd_clear (glcd);

    return glcd;
}


void 
glcd_pixel_set (glcd_t glcd, uint16_t x, uint16_t y, uint8_t val)
{
    uint8_t page;
    uint8_t col;
    uint8_t mask;
    uint8_t oldval;
    uint8_t newval;

    if (x >= GLCD_WIDTH || y >= GLCD_HEIGHT)
        return;

    col = x;
    page = y / GLCD_PAGE_PIXELS;
    
    mask = BIT (y % GLCD_PAGE_PIXELS);

    oldval = glcd->screen[page * GLCD_WIDTH + col];

    if (val)
        newval = oldval | mask;
    else
        newval = oldval & ~mask;

    glcd->screen[page * GLCD_WIDTH + col] = newval;

    /* Record which page modified.  */
    if (oldval != newval)
        glcd->modified |= BIT (page);
}


static void 
glcd_update_page (glcd_t glcd, uint8_t page)
{
    uint8_t col;

    glcd_command_mode ();

    /* Move to start of selected page.  */
    glcd_send (glcd, GLCD_CMD_PAGE_ADDRESS_SET | page);
    /* Without the following delay, the bottom page of the
       display is often selected instead of the top page.  */
    DELAY_US (1);

    glcd_send (glcd, GLCD_CMD_COL_ADDRESS_MSB_SET | 0);
    glcd_send (glcd, GLCD_CMD_COL_ADDRESS_LSB_SET | 0);

    DELAY_US (1);

    glcd_data_mode ();            

    for (col = 0; col < GLCD_WIDTH; col++)
    {
        glcd_send (glcd, glcd->screen[page * GLCD_WIDTH + col]);
    }

    glcd->modified &= ~BIT (page);
}


void 
glcd_update (glcd_t glcd)
{
    uint8_t page;

    /* Transfer backing image to GLCD but only for pages modified.  */
    for (page = 0; glcd->modified && page < GLCD_PAGES; page++)
    {
        if (glcd->modified & BIT (page))
            glcd_update_page (glcd, page);
    }
}


void 
glcd_clear (glcd_t glcd)
{
    uint8_t page;
    uint8_t col;

    for (page = 0; page < GLCD_PAGES; page++)
    {
        for (col = 0; col < GLCD_WIDTH; col++)
        {
            glcd->screen[page * GLCD_WIDTH + col] = 0;
        }
        glcd->modified |= BIT (page);
    }

    glcd_update (glcd);
}


void
glcd_shutdown (glcd_t glcd)
{
    spi_shutdown (glcd->spi);

    port_pin_config_output (GLCD_CS_PORT, GLCD_CS_BIT);

    port_pin_set_low (GLCD_CS_PORT, GLCD_CS_BIT);
    port_pin_set_low (GLCD_RS_PORT, GLCD_RS_BIT);

#ifdef GLCD_RESET_BIT
    port_pin_set_low (GLCD_RESET_PORT, GLCD_RESET_BIT);
#endif
}
