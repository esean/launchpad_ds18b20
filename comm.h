
#define HW_CLK    16000000

#define DBG_ON()  { P2OUT |= BIT5; }
#define DBG_OFF() { P2OUT &= ~BIT5; }

// send 'databyte' to 'port'
int outp(unsigned port, int databyte);

// read byte from 'port'
int inp(unsigned port);

// at 16MHz, 4clocks = 0.25us/tick
void tickDelay(int tick);

