/** @file spi_dataflash.h
 *  @author Michael Hayes
 *  @date 06/08/03
 * 
 *  @brief Routines to communicate with a SPI DATAFLASH.
 */
 
#ifndef SPI_DATAFLASH_H
#define SPI_DATAFLASH_H


#include "config.h"
#include "port.h"
#include "spi.h"


typedef struct
{
    spi_cfg_t spi;
    port_cfg_t wp;
    uint16_t pages;
    uint16_t page_size;
} spi_dataflash_cfg_t;    

#define SPI_DATAFLASH_CFG(CHANNEL, DIVISOR, CS_PORT, CS_BIT, WP_PORT, WP_BIT, PAGES, PAGE_SIZE) \
    {{(CHANNEL), (DIVISOR), {CS_PORT, BIT (CS_BIT)}}, {WP_PORT, BIT (WP_BIT)}, PAGES, PAGE_SIZE}


typedef struct
{
    spi_t spi;
    uint8_t page_bits;
    uint32_t size;
    const spi_dataflash_cfg_t *cfg;
} spi_dataflash_obj_t;



typedef spi_dataflash_obj_t *spi_dataflash_t;

typedef enum
{
    SPI_FLASH_OK,
    SPI_FLASH_TIMEOUT,
    SPI_FLASH_SECTOR_INVALID,
    SPI_FLASH_BLOCK_INVALID,
} spi_flash_err_t;


typedef uint32_t spi_dataflash_addr_t;
typedef uint32_t spi_dataflash_size_t;
typedef int32_t spi_dataflash_ret_t;

extern spi_dataflash_ret_t
spi_dataflash_read (spi_dataflash_t dev, spi_dataflash_addr_t addr,
                    uint8_t *buffer, spi_dataflash_size_t len);


extern spi_dataflash_ret_t
spi_dataflash_write (spi_dataflash_t dev, spi_dataflash_addr_t addr,
                     const void *buffer, spi_dataflash_size_t len);

extern spi_dataflash_t
spi_dataflash_init (spi_dataflash_obj_t *obj, const spi_dataflash_cfg_t *cfg);

#endif
