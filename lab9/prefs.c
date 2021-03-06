#include "c8051F120.h"
#include <smbus.h>              // SMBus interface routines
#include <prefs.h>              // preference routines and definitions

static bit backupPending;
static uint8 idata count;

#define COUNTINIT 78            // timer 3 overflow counter

// Initialize Flash EEPROM for project.  This only need to be called once, or
// if things get messed up.
void blockInit(void)
{
  uint8 i;
  {
    prefData xdata tmp;
    uint8 xdata *ptr = (uint8 xdata *)&tmp;
    for(i = sizeof(prefData); i--; *ptr++ = 0);
    smbus_send (0, sizeof(prefData), (uint8 *)&tmp);
  }
  {
    backupData xdata tmp;
    uint8 xdata *ptr = (uint8 xdata *)&tmp;
    for(i = sizeof(backupData); i--; *ptr++ = 0);
    smbus_send (sizeof(prefData), sizeof(backupData), (uint8 *)&tmp);
  }
}

// read preferences to Flash EEPROM
void prefRead(prefData xdata *ptr)
{
  smbus_send (0, sizeof(prefData), (uint8 *)ptr);
}
 
// write preferences from Flash EEPROM
void prefWrite(prefData xdata *ptr)
{
  smbus_receive (0, sizeof(prefData), (uint8 *)ptr);
}

// interrupt to track 5 second intervals
void timer3ISR( void ) interrupt 14 {
  TF3 = 0;                      // reset the overflow bit
  if( backupPending == 0 ) {    // if not already pending
    --count;                    // adjust the count
    if( !count ) {              // when it's time, set the pending flag
      count = COUNTINIT;
      backupPending = 1;
    }
  }
}

// read backup data from block
void backupRead(uint16 block, backupData xdata* buffer)
{
  smbus_receive (sizeof(prefData)+block*sizeof(block), 
        sizeof(backupData), (uint8 *)buffer);
}

// Write backup data to block.  The internal write counts are updated and
// if 0x80000 (~525,000) writes have occurred it skips to the next block.
// Wiring will only occur if the backup timer has overflowed; when the write
// does occur, it will reset the overflow flag
//
// returns:
//  0 if backup block number has not changed
//  1 if backup block number has changed
uint8 backupWrite(uint16 block, backupData xdata* buffer)
{ 
  if( backupPending ) {         // if timer has expired, do a write
    uint8 status = 0;           // default status == no change
    buffer->backupCount++;      // update write count
    if( buffer->backupCount == 0) {
      buffer->backupCount2++;
      if(buffer->backupCount2 & 0x08) {
        status = 1;             // write count has overflowed
        block += 1;
        buffer->backupCount = 0;
        buffer->backupCount2 = 0;
      }
    }
    smbus_send (sizeof(prefData)+block*sizeof(block), sizeof(backupData), 
        (uint8 *)buffer);
    backupPending = 0;
    return status;
  }
  return 0;
}

// Turn the backup timer on and off.  Turning on will fully configure the
// Timer 3 to overflow; at 12.25MHz and RCAP3=0, it will overflow at about
// 15.6Hz.  So in a 5 second period, there will be just under 78 interrupts.
void backupTimer(uint8 enable)
{
  SFRPAGE = 1;
  if( enable ) {
    backupPending = 0;          // clear pending flag
    count = COUNTINIT;          // reset overflow counter
    EIE2 |= 1;                  // enable interrupt
    TR3 = 1;                    // start timer
  } else {
    TR3 = 0;                    // stop timer (can leave interrupt enabled)
  }
  SFRPAGE = 0;
}
