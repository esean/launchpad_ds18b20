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

void InitializeClocks();


void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  P1DIR = 0xFF; // All P1.x outputs
  P1OUT = 0; // All P1.x reset
  P2DIR = 0xFF; // All P2.x outputs
  P2OUT = 0; // All P2.x reset

  InitializeClocks();
  owInit();

  while(1)
  {
    P1OUT ^= 0x01; // Toggle P1.0 using exclusive-OR

    if (OWTouchReset() > 0)
        P1OUT |= BIT6;
    else
        P1OUT &= ~BIT6;

    //_BIS_SR(LPM3_bits + GIE); // Enter LPM3 w/interrupt
    __delay_cycles(8000000);
  }
}


void InitializeClocks(void)
{
//  BCSCTL3 |= XCAP_3;              //12.5pF cap- setting for 32768Hz crystal
//  BCSCTL2 &= ~(DIVS_3);                         // SMCLK = DCO / 8 = 1MHz  
  BCSCTL1 = CALBC1_16MHZ;                    // Set range/
  DCOCTL = CALDCO_16MHZ;
}

