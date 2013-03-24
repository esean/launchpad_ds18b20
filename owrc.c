#include "ow.h"
#include "owrc.h"
#include "comm.h"
#include  "msp430g2352.h"

// returns temp, or -1 if no devices found
int owrc_read_temp()
{
    // reset
    if (OWTouchReset() == 0)
        return -1;

    // skip rom
    OWWriteByte(0xCC);

    // read temp
    OWWriteByte(0x44);

    // turn on power trans
    P2OUT |= BIT4;

    // wait 750ms for 12bit
    __delay_cycles(3*HW_CLK/4);

    // turn off power trans
    P2OUT &= ~BIT4;

    DBG_ON();

    // read scratchpad
    OWWriteByte(0xBE);
    DBG_OFF();

    int lsb = OWReadByte();
    int msb = OWReadByte();

    // done reading, reset device
    (void)OWTouchReset();

    return (msb << 8) | lsb;
}

// issues 'read rom' and returns one device info struct
ow_dev owrc_read_rom()
{
    ow_dev ret;

    // issue 'read rom'
    OWWriteByte(0x33);

    // read response
    ret.family_code = OWReadByte();
    for (int i = 0; i < 6; i++)
        ret.sn[i] = OWReadByte();
    ret.crc = OWReadByte();

    return ret;
}



#if 0
static int num_devices = 0xff;

// returns the number of devices found
int owrc_search_rom()
{
    // if bus has already been searched, return num we found before
    if (num_devices != 0xff)
        return num_devices;

    // reset, if no devices found return 0
    if (OWTouchReset() == 0)
        return 0;

    // issue 'search rom'
    OWWriteByte(0xF0);

    // 00 – bus conflict (some zeros retuned; some ones returned) 
    // 01 – all devices have a zero in this bit position 
    // 10 – all devices have a one in this bit position 
    // 11 – there are no devices present 

    // record and return number devices found
    num_devices = 0;
    return num_devices;
}
#endif
