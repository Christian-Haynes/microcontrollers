#include <c8051f120.h>           // Get SFR declarations
#include "types.h"
#include "spi.h"
#include "lcd.h"
#include "sd.h"
#include "dac.h"
#include "readdir.h"

//#pragma code                        // Include ASM in .LST file
void kbinit ( void );
uint8_t kbcheck ( void );
void dacinit ( void );

int main(void){
    SD_data xdata dat;

    //init procedures
    SFRPAGE = 0x0F;
    WDTCN = 0xDE;                   // Disable watchdog timer
    WDTCN = 0xAD;
    OSCICN = 0xC2;
    XBR2 |= 0x40;                   // Enable crossbar and weak pull-up
    EA = 1;                         // Enable all interrupts
    spi_set_divisor(0);
    spiinit();
    lcdinit();
    kbinit();
    dacinit();
    dac2init();
    dacrate(11025);
    dacstereo(0);                   // Set number of channels to mono

/*
	while(1) {
		uint8_t temp[1];
		PCON |= 1;
		temp[0] = kbcheck();
		if (temp[0] == 13) {
			lcdclear();
            lcdpos(0,0);
		}
		else if (temp[0] == 8) {
			_lcdcmd(0x10);
			lcdwrite(" ");
			_lcdcmd(0x10);
		}
		else if (temp[0] != 255)
			lcdwrite(temp);
	}
*/

    while(1){
        while(!spicardpresent());   // Wait until card is detected
        if(!microSDinit()){         // If initialization fails, print error.
            lcdclear();
            lcdpos(0,0);
            lcdwrite("ERROR: microSD");
            lcdpos(1,0);
            lcdwrite("failure.");
        } else {
            spi_set_divisor(1);     // Set to max speed after initialisation
	
			readdir();
			lcdwrite("do");

            microSDread(0x112358, (uint8_t *) &dat);
            lcdclear();
            lcdpos(0,0);
            lcdwrite(dat.string);
            while(spicardpresent()){
                PCON |= 1;
                if(!dacbusy()){
                    dacplay(dat.len, dat.wavedata); //output to DAC
                }
            }
        }
    }
    return 0;
}
