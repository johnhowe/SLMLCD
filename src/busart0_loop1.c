#include "config.h"
#include "delay.h"
#include "port.h"
#include "busart.h"


int main (void)
{
    char txbuffer[32];
    char rxbuffer[32];
    busart_t busart;

    busart = busart_init (0, BUSART_BAUD_DIVISOR (9600),
			  txbuffer, sizeof (txbuffer),
			  rxbuffer, sizeof (rxbuffer));
    
    busart_puts (busart, "Hello world\n");

    while (1)
    {
	char buffer[32];
	int ret;

	ret = busart_read (busart, &buffer, sizeof (buffer));
	if (ret)
	    busart_write (busart, &buffer, ret);
    }
}
