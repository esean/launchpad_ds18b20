
#define DBG_ON()  { P2OUT |= BIT5; }
#define DBG_OFF() { P2OUT &= ~BIT5; }

// send 'databyte' to 'port'
int outp(unsigned port, int databyte);

// read byte from 'port'
int inp(unsigned port);

// at 8MHz, 2clocks = 0.25us + some overhead of iter loop call
void tickDelay(int tick);

