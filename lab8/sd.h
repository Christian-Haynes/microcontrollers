#ifndef _SD_H
#define _SD_H

/*  initializes the SD card.  It is called after you have initialized the SPI
    interface, as it uses the bus to prepare the card for reading.  It first calls spi_set_divisor() to set 
    the SPI clock to the rate needed for initialization.   If the initialization fails, it returns 0.  
    Otherwise it calls spi_set_divisor() for full-speed operation and returns a 1. */
uint8 microSDinit();

/*  this is the primary procedure 
    you will use – repeatedly.  It is passed a sector number on the SD card and a pointer to a 512-
    byte buffer.  It will attempt to read a sector from the SD card.  If the read is successful it will 
    return a non-zero value, otherwise it returns a zero. */
uint8 microSDread(uint32 blockaddr, uint8 xdata *buffer);

#endif