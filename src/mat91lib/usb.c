#include "config.h"
#include "usb.h"


/* CDC communication device class. 
   UDP USB device port.

   There are two communication endpoints and endpoint 0 is used for
   the enumeration process.  Endpoint 1 is a 64-byte Bulk OUT endpoint
   and endpoint 2 is a 64-byte Bulk IN endpoint.

   The Vendor ID is Atmel's vendor ID 0x03EB.  The product ID is
   0x6124

*/


#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define AT91C_EP_OUT 1
#define AT91C_EP_OUT_SIZE 0x40
#define AT91C_EP_IN  2
#define AT91C_EP_IN_SIZE 0x40


static const char devDescriptor[] =
{
    /* Device descriptor */
    0x12,   // bLength
    0x01,   // bDescriptorType
    0x10,   // bcdUSBL
    0x01,   //
    0x02,   // bDeviceClass:    CDC class code
    0x00,   // bDeviceSubclass: CDC class sub code
    0x00,   // bDeviceProtocol: CDC Device protocol
    0x08,   // bMaxPacketSize0
    0xEB,   // idVendorL
    0x03,   //
    0x24,   // idProductL
    0x61,   //
    0x10,   // bcdDeviceL
    0x01,   //
    0x00,   // iManufacturer    // 0x01
    0x00,   // iProduct
    0x00,   // SerialNumber
    0x01    // bNumConfigs
};


static const char cfgDescriptor[] = 
{
    /* ============== CONFIGURATION 1 =========== */
    /* Configuration 1 descriptor */
    0x09,   // CbLength
    0x02,   // CbDescriptorType
    0x43,   // CwTotalLength 2 EP + Control
    0x00,
    0x02,   // CbNumInterfaces
    0x01,   // CbConfigurationValue
    0x00,   // CiConfiguration
    0xC0,   // CbmAttributes 0xA0
    0x00,   // CMaxPower
    
    /* Communication Class Interface Descriptor Requirement */
    0x09, // bLength
    0x04, // bDescriptorType
    0x00, // bInterfaceNumber
    0x00, // bAlternateSetting
    0x01, // bNumEndpoints
    0x02, // bInterfaceClass
    0x02, // bInterfaceSubclass
    0x00, // bInterfaceProtocol
    0x00, // iInterface
    
    /* Header Functional Descriptor */
    0x05, // bFunction Length
    0x24, // bDescriptor type: CS_INTERFACE
    0x00, // bDescriptor subtype: Header Func Desc
    0x10, // bcdCDC:1.1
    0x01,
    
    /* ACM Functional Descriptor */
    0x04, // bFunctionLength
    0x24, // bDescriptor Type: CS_INTERFACE
    0x02, // bDescriptor Subtype: ACM Func Desc
    0x00, // bmCapabilities
    
    /* Union Functional Descriptor */
    0x05, // bFunctionLength
    0x24, // bDescriptorType: CS_INTERFACE
    0x06, // bDescriptor Subtype: Union Func Desc
    0x00, // bMasterInterface: Communication Class Interface
    0x01, // bSlaveInterface0: Data Class Interface
    
    /* Call Management Functional Descriptor */
    0x05, // bFunctionLength
    0x24, // bDescriptor Type: CS_INTERFACE
    0x01, // bDescriptor Subtype: Call Management Func Desc
    0x00, // bmCapabilities: D1 + D0
    0x01, // bDataInterface: Data Class Interface 1
    
    /* Endpoint 1 descriptor */
    0x07,   // bLength
    0x05,   // bDescriptorType
    0x83,   // bEndpointAddress, Endpoint 03 - IN
    0x03,   // bmAttributes      INT
    0x08,   // wMaxPacketSize
    0x00,
    0xFF,   // bInterval
    
    /* Data Class Interface Descriptor Requirement */
    0x09, // bLength
    0x04, // bDescriptorType
    0x01, // bInterfaceNumber
    0x00, // bAlternateSetting
    0x02, // bNumEndpoints
    0x0A, // bInterfaceClass
    0x00, // bInterfaceSubclass
    0x00, // bInterfaceProtocol
    0x00, // iInterface
    
    /* First alternate setting */
    /* Endpoint 1 descriptor */
    0x07,   // bLength
    0x05,   // bDescriptorType
    0x01,   // bEndpointAddress, Endpoint 01 - OUT
    0x02,   // bmAttributes      BULK
    AT91C_EP_OUT_SIZE,   // wMaxPacketSize
    0x00,
    0x00,   // bInterval
    
    /* Endpoint 2 descriptor */
    0x07,   // bLength
    0x05,   // bDescriptorType
    0x82,   // bEndpointAddress, Endpoint 02 - IN
    0x02,   // bmAttributes      BULK
    AT91C_EP_IN_SIZE,   // wMaxPacketSize
    0x00,
    0x00    // bInterval
};


/* USB standard request code */
#define STD_GET_STATUS_ZERO           0x0080
#define STD_GET_STATUS_INTERFACE      0x0081
#define STD_GET_STATUS_ENDPOINT       0x0082

#define STD_CLEAR_FEATURE_ZERO        0x0100
#define STD_CLEAR_FEATURE_INTERFACE   0x0101
#define STD_CLEAR_FEATURE_ENDPOINT    0x0102

#define STD_SET_FEATURE_ZERO          0x0300
#define STD_SET_FEATURE_INTERFACE     0x0301
#define STD_SET_FEATURE_ENDPOINT      0x0302

#define STD_SET_ADDRESS               0x0500
#define STD_GET_DESCRIPTOR            0x0680
#define STD_SET_DESCRIPTOR            0x0700
#define STD_GET_CONFIGURATION         0x0880
#define STD_SET_CONFIGURATION         0x0900
#define STD_GET_INTERFACE             0x0A81
#define STD_SET_INTERFACE             0x0B01
#define STD_SYNCH_FRAME               0x0C82

/* CDC Class Specific Request Code */
#define GET_LINE_CODING               0x21A1
#define SET_LINE_CODING               0x2021
#define SET_CONTROL_LINE_STATE        0x2221


typedef struct 
{
    unsigned int dwDTERRate;
    char bCharFormat;
    char bParityType;
    char bDataBits;
} AT91S_CDC_LINE_CODING, *AT91PS_CDC_LINE_CODING;


AT91S_CDC_LINE_CODING line =
{
    115200, // baudrate
    0,      // 1 Stop Bit
    0,      // None Parity
    8
};     // 8 Data bits


static usb_dev_t usb_dev;


static void 
usb_control_write (usb_t usb, const char *data, usb_size_t length)
{
    AT91PS_UDP pUDP = usb->pUDP;
    uint32_t cpt;
    AT91_REG csr;

    do {
        cpt = MIN (length, 8);
        length -= cpt;

        while (cpt--)
            pUDP->UDP_FDR[0] = *data++;

        if (pUDP->UDP_CSR[0] & AT91C_UDP_TXCOMP)
        {
            pUDP->UDP_CSR[0] &= ~AT91C_UDP_TXCOMP;
            while (pUDP->UDP_CSR[0] & AT91C_UDP_TXCOMP);
        }

        pUDP->UDP_CSR[0] |= AT91C_UDP_TXPKTRDY;
        do {
            csr = pUDP->UDP_CSR[0];

            // Data IN stage has been stopped by a status OUT
            if (csr & AT91C_UDP_RX_DATA_BK0) 
            {
                pUDP->UDP_CSR[0] &= ~AT91C_UDP_RX_DATA_BK0;
                return;
            }
        } while (! (csr & AT91C_UDP_TXCOMP));

    } while (length);

    if (pUDP->UDP_CSR[0] & AT91C_UDP_TXCOMP)
    {
        pUDP->UDP_CSR[0] &= ~AT91C_UDP_TXCOMP;
        while (pUDP->UDP_CSR[0] & AT91C_UDP_TXCOMP)
            continue;
    }
}


void usb_control_write_zlp (usb_t usb)
{
    AT91PS_UDP pUDP = usb->pUDP;

    pUDP->UDP_CSR[0] |= AT91C_UDP_TXPKTRDY;
    while (! (pUDP->UDP_CSR[0] & AT91C_UDP_TXCOMP))
        continue;

    pUDP->UDP_CSR[0] &= ~AT91C_UDP_TXCOMP;
    while (pUDP->UDP_CSR[0] & AT91C_UDP_TXCOMP)
        continue;
}


void usb_control_stall (usb_t usb)
{
    AT91PS_UDP pUDP = usb->pUDP;

    pUDP->UDP_CSR[0] |= AT91C_UDP_FORCESTALL;
    while (! (pUDP->UDP_CSR[0] & AT91C_UDP_ISOERROR))
        continue;

    pUDP->UDP_CSR[0] &= ~(AT91C_UDP_FORCESTALL | AT91C_UDP_ISOERROR);
    while (pUDP->UDP_CSR[0] & (AT91C_UDP_FORCESTALL | AT91C_UDP_ISOERROR))
        continue;
}


void
usb_enumerate (usb_t usb)
{
    AT91PS_UDP pUDP = usb->pUDP;
    uint8_t request_type;
    uint8_t request;
    uint16_t value;
    uint16_t index;
    uint16_t length;
    uint16_t status;

    if (! (pUDP->UDP_CSR[0] & AT91C_UDP_RXSETUP))
        return;

    request_type = pUDP->UDP_FDR[0];
    request = pUDP->UDP_FDR[0];

    value = (pUDP->UDP_FDR[0] & 0xFF);
    value |= (pUDP->UDP_FDR[0] << 8);

    index = (pUDP->UDP_FDR[0] & 0xFF);
    index |= (pUDP->UDP_FDR[0] << 8);

    length = (pUDP->UDP_FDR[0] & 0xFF);
    length |= (pUDP->UDP_FDR[0] << 8);

    if (request_type & 0x80)
    {
        pUDP->UDP_CSR[0] |= AT91C_UDP_DIR;
        while (! (pUDP->UDP_CSR[0] & AT91C_UDP_DIR))
            continue;
    }
    pUDP->UDP_CSR[0] &= ~AT91C_UDP_RXSETUP;

    while ((pUDP->UDP_CSR[0]  & AT91C_UDP_RXSETUP))
        continue;

    // Handle supported standard device request Cf Table 9-3 in USB
    // specification Rev 1.1
    switch ((request << 8) | request_type) 
    {
    case STD_GET_DESCRIPTOR:
        if (value == 0x100)       // Return Device Descriptor
            usb_control_write (usb, devDescriptor, 
                               MIN (sizeof (devDescriptor), length));
        else if (value == 0x200)  // Return Configuration Descriptor
            usb_control_write (usb, cfgDescriptor, 
                               MIN (sizeof (cfgDescriptor), length));
        else
            usb_control_stall (usb);
        break;

    case STD_SET_ADDRESS:
        usb_control_write_zlp (usb);
        pUDP->UDP_FADDR = (AT91C_UDP_FEN | value);
        pUDP->UDP_GLBSTATE  = (value) ? AT91C_UDP_FADDEN : 0;
        break;

    case STD_SET_CONFIGURATION:
        usb->currentConfiguration = value;
        usb_control_write_zlp (usb);
        pUDP->UDP_GLBSTATE  = (value) ? AT91C_UDP_CONFG : AT91C_UDP_FADDEN;
        pUDP->UDP_CSR[1] = (value) ? (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_BULK_OUT) : 0;
        pUDP->UDP_CSR[2] = (value) ? (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_BULK_IN)  : 0;
        pUDP->UDP_CSR[3] = (value) ? (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_ISO_IN)   : 0;
        break;

    case STD_GET_CONFIGURATION:
        usb_control_write (usb, (char *) &usb->currentConfiguration,
                           sizeof (usb->currentConfiguration));
        break;

    case STD_GET_STATUS_ZERO:
        status = 0;
        usb_control_write (usb, (char *) &status, sizeof (status));
        break;

    case STD_GET_STATUS_INTERFACE:
        status = 0;
        usb_control_write (usb, (char *) &status, sizeof (status));
        break;

    case STD_GET_STATUS_ENDPOINT:
        status = 0;
        index &= 0x0F;
        if ((pUDP->UDP_GLBSTATE & AT91C_UDP_CONFG) && (index <= 3))
        {
            status = (pUDP->UDP_CSR[index] & AT91C_UDP_EPEDS) ? 0 : 1;
            usb_control_write (usb, (char *) &status, sizeof (status));
        }
        else if ((pUDP->UDP_GLBSTATE & AT91C_UDP_FADDEN) && (index == 0))
        {
            status = (pUDP->UDP_CSR[index] & AT91C_UDP_EPEDS) ? 0 : 1;
            usb_control_write (usb, (char *) &status, sizeof (status));
        }
        else
            usb_control_stall (usb);
        break;

    case STD_SET_FEATURE_ZERO:
        usb_control_stall (usb);
        break;
    case STD_SET_FEATURE_INTERFACE:
        usb_control_write_zlp (usb);
        break;
    case STD_SET_FEATURE_ENDPOINT:
        index &= 0x0F;
        if ((value == 0) && index && (index <= 3))
        {
            pUDP->UDP_CSR[index] = 0;
            usb_control_write_zlp (usb);
        }
        else
            usb_control_stall (usb);
        break;

    case STD_CLEAR_FEATURE_ZERO:
        usb_control_stall (usb);
        break;

    case STD_CLEAR_FEATURE_INTERFACE:
        usb_control_write_zlp (usb);
        break;

    case STD_CLEAR_FEATURE_ENDPOINT:
        index &= 0x0F;
        if ((value == 0) && index && (index <= 3)) 
        {
            if (index == 1)
                pUDP->UDP_CSR[1] = (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_BULK_OUT);
            else if (index == 2)
                pUDP->UDP_CSR[2] = (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_BULK_IN);
            else if (index == 3)
                pUDP->UDP_CSR[3] = (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_ISO_IN);

            usb_control_write_zlp (usb);
        }
        else
            usb_control_stall (usb);
        break;

        // handle CDC class requests
    case SET_LINE_CODING:
        while (! (pUDP->UDP_CSR[0] & AT91C_UDP_RX_DATA_BK0));
        pUDP->UDP_CSR[0] &= ~AT91C_UDP_RX_DATA_BK0;
        usb_control_write_zlp (usb);
        break;

    case GET_LINE_CODING:
        usb_control_write (usb, (char *) &line, MIN (sizeof (line), length));
        break;

    case SET_CONTROL_LINE_STATE:
        usb->currentConnection = value;
        usb_control_write_zlp (usb);
        break;

    default:
        usb_control_stall (usb);
        break;
    }
}


usb_size_t
usb_read (usb_t usb, char *data, usb_size_t length)
{
    AT91PS_UDP pUDP = usb->pUDP;
    uint32_t packetSize;
    uint32_t nbBytesRcv = 0;
    uint32_t currentReceiveBank = usb->currentRcvBank;

    while (length)
    {
        if (! usb_configured_p (usb))
            break;

        if (pUDP->UDP_CSR[AT91C_EP_OUT] & currentReceiveBank) 
        {
            packetSize = MIN (pUDP->UDP_CSR[AT91C_EP_OUT] >> 16, length);
            length -= packetSize;
            if (packetSize < AT91C_EP_OUT_SIZE)
                length = 0;

            while (packetSize--)
                data[nbBytesRcv++] = pUDP->UDP_FDR[AT91C_EP_OUT];

            pUDP->UDP_CSR[AT91C_EP_OUT] &= ~currentReceiveBank;

            if (currentReceiveBank == AT91C_UDP_RX_DATA_BK0)
                currentReceiveBank = AT91C_UDP_RX_DATA_BK1;
            else
                currentReceiveBank = AT91C_UDP_RX_DATA_BK0;
        }
    }
    usb->currentRcvBank = currentReceiveBank;
    return nbBytesRcv;
}


usb_size_t
usb_write (usb_t usb, const char *data, usb_size_t length)
{
    AT91PS_UDP pUDP = usb->pUDP;
    usb_size_t cpt = 0;

    // Send the first packet
    cpt = MIN (length, AT91C_EP_IN_SIZE);
    length -= cpt;

    while (cpt--) 
        pUDP->UDP_FDR[AT91C_EP_IN] = *data++;

    pUDP->UDP_CSR[AT91C_EP_IN] |= AT91C_UDP_TXPKTRDY;

    while (length)
    {
        // Fill the second bank
        cpt = MIN (length, AT91C_EP_IN_SIZE);
        length -= cpt;
        while (cpt--)
            pUDP->UDP_FDR[AT91C_EP_IN] = *data++;

        // Wait for the the first bank to be sent
        while (! (pUDP->UDP_CSR[AT91C_EP_IN] & AT91C_UDP_TXCOMP))
            if (! usb_configured_p (usb))
                return length;

        pUDP->UDP_CSR[AT91C_EP_IN] &= ~AT91C_UDP_TXCOMP;
        while (pUDP->UDP_CSR[AT91C_EP_IN] & AT91C_UDP_TXCOMP);
        pUDP->UDP_CSR[AT91C_EP_IN] |= AT91C_UDP_TXPKTRDY;
    }

    // Wait for the end of transfer
    while (! (pUDP->UDP_CSR[AT91C_EP_IN] & AT91C_UDP_TXCOMP))
        if (! usb_configured_p (usb))
            return length;

    pUDP->UDP_CSR[AT91C_EP_IN] &= ~AT91C_UDP_TXCOMP;
    while (pUDP->UDP_CSR[AT91C_EP_IN] & AT91C_UDP_TXCOMP)
        continue;

    return length;
}


bool
usb_configured_p (usb_t usb)
{
    AT91PS_UDP pUDP = usb->pUDP;
    AT91_REG isr = pUDP->UDP_ISR;
    
    if (isr & AT91C_UDP_ENDBUSRES) 
    {
        pUDP->UDP_ICR = AT91C_UDP_ENDBUSRES;
        // reset all endpoints
        pUDP->UDP_RSTEP  = ~0;
        pUDP->UDP_RSTEP  = 0;
        // Enable the function
        pUDP->UDP_FADDR = AT91C_UDP_FEN;
        // Configure endpoint 0
        pUDP->UDP_CSR[0] = (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_CTRL);
        usb->currentConfiguration = 0;
    }
    else if (isr & AT91C_UDP_EPINT0)
    {
        pUDP->UDP_ICR = AT91C_UDP_EPINT0;
        usb_enumerate (usb);
    }

    return usb->currentConfiguration;
}


usb_t
usb_init (void)
{
    usb_t usb = &usb_dev;

    /* Set the PLL USB Divider (PLLCK / 2).  */
    AT91C_BASE_CKGR->CKGR_PLLR |= AT91C_CKGR_USBDIV_1 ;

    /* Enable the 48 MHz USB clock UDPCK.  */
    AT91C_BASE_PMC->PMC_SCER = AT91C_PMC_UDP;

    /* Enable System Peripheral USB Clock.  */
    AT91C_BASE_PMC->PMC_PCER = BIT (AT91C_ID_UDP);

    // Enable UDP PullUp (USB_DP_PUP) : enable and clear of the
    // corresponding PIO.  Set in PIO mode and configure as output.
    *AT91C_PIOA_PER = AT91C_PIO_PA16;

    // Clear to enable Pullup resistor
    *AT91C_PIOA_CODR = AT91C_PIO_PA16;

    usb->pUDP = AT91C_BASE_UDP;
    usb->currentConfiguration = 0;
    usb->currentConnection = 0;
    usb->currentRcvBank = AT91C_UDP_RX_DATA_BK0;

    return usb;
}
