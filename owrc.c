#include "ow.h"
#include "owrc.h"
#include "comm.h"
#include  "msp430g2352.h"

void owrc_read_rom()
{
    DBG_ON();
    OWWriteByte(0x33);
    DBG_OFF();
}
