/** @file   glcd.h
    @author M. P. Hayes, UCECE
    @date   28 January 2008
    @brief  Simple GLCD driver.
*/
#ifndef GLCD_H
#define GLCD_H

#include "config.h"
#include "port.h"
#include "spi.h"

#define GLCD_WIDTH 128
#define GLCD_HEIGHT 64
#define GLCD_PIXEL_BITS 1

#define GLCD_CFG(PORT, PORTBIT) {(PORT), BIT (PORTBIT)}


/* Do not use the following definitions.  They should be considered
   private but are needed to statically allocate the display
   memory.  */
#define GLCD_PAGE_PIXELS 8
#define GLCD_PAGES (GLCD_HEIGHT / GLCD_PAGE_PIXELS)
#define GLCD_PIXEL_BYTES (GLCD_PAGES * GLCD_WIDTH * GLCD_PIXEL_BITS)


typedef struct
{
} glcd_cfg_t;


/** Private glcd structure.  */
typedef struct
{
    const glcd_cfg_t *cfg;
    spi_t spi;
    uint16_t modified;
    uint8_t screen[GLCD_PIXEL_BYTES];
} glcd_private_t;


typedef glcd_private_t glcd_obj_t;
typedef glcd_obj_t *glcd_t;


extern void 
glcd_pixel_set (glcd_t glcd, uint16_t x, uint16_t y, uint8_t val);


extern void 
glcd_update (glcd_t glcd);


extern void 
glcd_clear (glcd_t glcd);


extern void 
glcd_contrast_set (glcd_t glcd, uint8_t contrast);


/* CFG is points to configuration data specified by GLCD_CFG to
   define the port the GLCD is connected to.  The returned handle is
   passed to the other glcd_xxx routines to denote the GLCD to
   operate on.  */
extern glcd_t
glcd_init (glcd_obj_t *obj, const glcd_cfg_t *cfg);


extern void
glcd_shutdown (glcd_obj_t *obj);

#endif
