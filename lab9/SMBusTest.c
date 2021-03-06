#include <c8051F120.h>

typedef unsigned char uint8;
typedef unsigned short uint16;

void kbinit(void);
void dacinit(void);
void dac2init(void);

void smbus_setup (void);
void smbus_send (uint16 eepromaddr, uint8 len, uint8 xdata * buffer);
void smbus_receive (uint16 eepromaddr, uint8 len, uint8 xdata * buffer);

static uint8 xdata SMBbuf[16];
static uint8 xdata str1[] = "test string #1";
static uint8 xdata str2[] = "smbus test";

void smbus_init( void )
{
// YOUR INITIALIZATION CODE GOES HERE
  SFRPAGE = 0x0F; // enable SMBus on crossbar
  XBR0 |= 1;
  SFRPAGE = 0x00;
  SMB0CR = 0xC0;  // setup SMBus clock
  ENSMB = 1;      // enable SMBus module
  EIE1 |= 2;      // enable SMBus interrupt
}

void main(void)
{

// enable other hardware
  WDTCN = 0xde;
  WDTCN = 0xad;
  SFRPAGE = 0x0f;
  XBR2 = 0x40;
  XBR0 = 0x02;
  OSCICN = 0xc2;
  SFRPAGE = 0x00;
  SPI0CFG = 0x40;
  NSSMD1 = NSSMD0 = 0;

// enable your other modules
//  kbinit(  );
//  dacinit(  );
//  dac2init(  );
  smbus_init(  );
  smbus_setup( );

  EA = 1;

  // write two strings to FLASH, then read them back into buffer
  smbus_send (0x107, sizeof(str1), str1);
  smbus_send (0x9eb, sizeof(str2), str2);
  smbus_receive (0x107, sizeof(SMBbuf), SMBbuf);
  smbus_receive (0x9eb, sizeof(SMBbuf), SMBbuf);
  while (1) {}
}
