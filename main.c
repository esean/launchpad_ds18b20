//******************************************************************************
// One-wire test program for Launchpad w/ MSP430G2352.
// Reads temperature from DS18B20.
//
// seanharre@gmail.com
// 02/11/2013
//******************************************************************************
#include  "msp430g2352.h"
#include "ow.h"
#include "comm.h"
#include "owrc.h"

void InitializeClocks();

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  P1DIR = 0xFF; // All P1.x outputs
  P1OUT = 0; // All P1.x reset
  P2DIR = 0xFF; // All P2.x outputs
  P2OUT = 0; // All P2.x reset

  // 1-wire pin set as input
  P1DIR &= ~BIT7;

  // P2.4 controls Q power to DS18B20 power
  P2OUT &= ~BIT4;

  InitializeClocks();
  owInit();

  while(1)
  {
    int temp;

    P1OUT ^= 0x01; // Toggle P1.0 using exclusive-OR

    // returns -1 if no devices found
    P1OUT &= ~BIT6; // light P1.6 if device found
    if ( OWTouchReset() > 0)
    //if ( (temp = owrc_read_temp()) != -1)
        P1OUT |= BIT6;  // found!

    __delay_cycles(HW_CLK/2);
  }
}

void InitializeClocks(void)
{
//  BCSCTL3 |= XCAP_3;              //12.5pF cap- setting for 32768Hz crystal
#if HW_CLK == 16000000
  BCSCTL1 = CALBC1_16MHZ;                    // Set range/
  DCOCTL = CALDCO_16MHZ;
#else
#error "HW_CLK can only be defined as 16MHz"
#endif
}

