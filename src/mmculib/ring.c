/** @file   ring.c
    @author M. P. Hayes, UCECE
    @date   15 May 2000
    @brief  Ring buffer implementation.
*/

#include <string.h>
#include "ring.h"

/** Define some useful macros for determining number of entries in
   a ring buffer.  Macros are used for run-time speed.  */

/** Ring buffer full predicate.  */
#define RING_FULL_P(RING, TMP) (RING_WRITE_NUM (RING, TMP) == 0)

/** Ring buffer empty predicate.  */
#define RING_EMPTY_P(RING) ((RING)->in == (RING)->out)


/** Return non-zero if the ring buffer is empty.  */
bool
ring_empty_p (ring_t *ring)
{
    return RING_EMPTY_P (ring);
}


/** Determine number of bytes in ring buffer ready for reading.
    @param ring pointer to ring buffer structure
    @return number of bytes in ring buffer ready for reading.  */
ring_size_t
ring_read_num (ring_t *ring)
{
    int tmp;

    return RING_READ_NUM (ring, tmp);
}


/** Determine number of bytes in ring buffer free for writing.
    @param ring pointer to ring buffer structure
    @return number of bytes in ring buffer free for writing.  */
ring_size_t
ring_write_num (ring_t *ring)
{
    int tmp;

    return RING_WRITE_NUM (ring, tmp);
}


/** Initialise a ring buffer structure to use a specified buffer.
    @param ring pointer to ring buffer structure
    @param buffer pointer to memory buffer
    @param size size of memory buffer in bytes
    @return size size of memory buffer in bytes or zero if error.  */
ring_size_t 
ring_init (ring_t *ring, void *buffer, ring_size_t size)
{
    if (!ring || !buffer)
        return 0;

    ring->in = ring->out = ring->top = buffer;
    ring->end = (char *)buffer + size;
    return size;
}


/** Read from a ring buffer.
    @param ring pointer to ring buffer structure
    @param buffer pointer to memory buffer
    @param size maximum number of bytes to read
    @return number of bytes actually read.  */
ring_size_t
ring_read (ring_t *ring, void *buffer, ring_size_t size)
{
    ring_size_t count;
    int tmp;
    char *buf = buffer;

    /* Determine number of entries in ring buffer.  */
    count = RING_READ_NUM (ring, tmp);
    if (size > count)
        size = count;

    /* Return if nothing to read.  */
    if (!size)
        return 0;

    if (ring->out + size >= ring->end)
    {
        int semi_num;

        /* The data is split into two portions, so first read the
           portion to the end of the ring buffer and transfer to the
           user's buffer.  */
        semi_num = ring->end - ring->out;
        memcpy (buf, ring->out, semi_num);

        /* Transfer data to user buffer from top of ring
           buffer.  */
        memcpy (buf + semi_num, ring->top, size - semi_num);

        /* Update output pointer.  */
        ring->out = ring->top + (size - semi_num);
    }
    else
    {
        /* Transfer data to user buffer.  */
        memcpy (buf, ring->out, size);

        /* Update output pointer.  */
        ring->out += size;
    }
    return size;
}


/** Write to a ring buffer.
    @param ring pointer to ring buffer structure
    @param buffer pointer to memory buffer
    @param size number of bytes to write
    @return number of bytes actually written.  */
ring_size_t
ring_write (ring_t *ring, const void *buffer, ring_size_t size)
{
    ring_size_t count;
    int tmp;
    const char *buf = buffer;

    /* Determine number of free entries in ring buffer.  */
    count = RING_WRITE_NUM (ring, tmp);
    if (size > count)
        size = count;

    /* Return if buffer full.  */
    if (!size)
        return 0;

    if (ring->in + size >= ring->end)
    {
        int semi_num;

        /* The data is split into two portions, so first write the
           portion to the end of the ring buffer from the user's
           buffer.  */
        semi_num = ring->end - ring->in;
        memcpy (ring->in, buf, semi_num);

        /* Transfer data from user buffer to top of ring
           buffer.  */
        memcpy (ring->top, buf + semi_num, size - semi_num);

        /* Update input pointer.  */
        ring->in = ring->top + (size - semi_num);
    }
    else
    {
        /* Transfer data to user buffer.  */
        memcpy (ring->in, buf, size);

        /* Update input pointer.  */
        ring->in += size;
    }
    return size;
}

