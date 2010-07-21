#ifndef _LINUX_CRC_CCITT_H
#define _LINUX_CRC_CCITT_H
#ifdef __KERNEL__

//#include <linux/types.h>
#include "linuxtypes.h"

extern u16 const crc_ccitt_table[256];

extern u16 crc_ccitt(u16 crc, const u8 *buffer, size_t len);

static inline u16 crc_ccitt_byte(u16 crc, const u8 c)
{
	return (crc >> 8) ^ crc_ccitt_table[(crc ^ c) & 0xff];
}

#endif /* __KERNEL__ */
#endif /* _LINUX_CRC_CCITT_H */

