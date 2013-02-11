#include  "msp430g2352.h"
#include "comm.h"

#define MIN_ENTRY_TIME_US       1 // us
#define NUM_CLOCKS_IN_TICK      4   // at 16MHz, 4clocks = 0.25us

// send 'databyte' to 'port'
int outp(unsigned port, int databyte)
{
    if (databyte > 0)
        P1OUT |= BIT7;
    else
        P1OUT &= ~BIT7;
    P1DIR |= BIT7;
    return 0;
}

// read byte from 'port'
int inp(unsigned port)
{
    P1DIR &= ~BIT7;
    __no_operation();   // let it settle
    return (P1IN & BIT7) ? 0x01 : 0;
}

// one tick = 0.25us
void tickDelay(int tick)
{
    // just coming into fxn here, is 1us
    if (tick <= (MIN_ENTRY_TIME_US*4))
        return;

    CCR0 = (tick * 4) - (MIN_ENTRY_TIME_US * 4);    // @ 16MHz SMCLK = 0.0625us/clk
    TACTL = TASSEL_2 + MC_1 + TACLR; // SMCLK, contmode
    while ((TACTL & TAIFG) == 0);
    TACTL = MC_0;
}

