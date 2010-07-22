void
mspi_write (mspi_t this, void *buffer, uint16_t size)
{
    uint16_t i;

    if (this->blast)
    {
        mspi_channel_cs_select (this->channel);
        
        if (this->size <= 8)
        {
            uint8_t *buf = buffer;
            
            for (i = 0; i < size; i++)
                spi_putc (*buf++);
        }
        else
        {
            uint16_t *buf = buffer;
            
            for (i = 0; i < size; i++)
                spi_put16 (*buf++);
        }
        mspi_channel_cs_deselect (this->channel);
    }
    else
    {
        if (this->size <= 8)
        {
            uint8_t *buf = buffer;
            
            for (i = 0; i < size; i++)
            {
                mspi_channel_cs_select (this->channel);
                spi_putc (*buf++);
                mspi_channel_cs_deselect (this->channel);
            }
        }
        else
        {
            uint16_t *buf = buffer;
            
            for (i = 0; i < size; i++)
            {
                mspi_channel_cs_select (this->channel);
                spi_put16 (*buf++);
                mspi_channel_cs_deselect (this->channel);
            }
        }
    }
}
