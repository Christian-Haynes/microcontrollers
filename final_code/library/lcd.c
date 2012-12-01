#include "lcd.h"
#include "delay.h"
#include "itoa.h"
#include <c8051f120.h>          // get SFR declarations

// hackros
#define lcdwstr()    while (*str) {_lcddata(*str); ++str;}

// timings in us
#define T_AS        0.06
#define PW_EH       0.5
#define T_DSW       0.2
#define T_AH        0.02
#define T_DDR       0.4

// utility functions
void _mpuwdata(uint8_t d);          // write data to MPU
void _mpuwcmd(uint8_t cmd);
uint8_t _mpurdata();                // read data from MPU
uint8_t _mpurcmd();
//void _lcddata(uint8_t d);           // write data to MPU, wait for busy state to complete
//void _lcdcmd(uint8_t d);
void _busy();                       // wait on busy flag

// global vars
uint8_t lcdrs;
uint8_t lcdrw;
uint8_t pdata *lcdbase;
uint8_t pdata *lcdwdata;
uint8_t pdata *lcdwcmd;
uint8_t pdata *lcdrdata;
uint8_t pdata *lcdrcmd;

// public functions
void lcdinit() {
    // external memory config
    SFRPAGE = 0;
    EMI0CF = 0x34;                   //external interface on pins P7-P4
    EMI0CN  = 0xFF;                   //8-bit address reference off-chip memory
    SFRPAGE = 0x0F;
    P4MDOUT = 0xC0;                   //read and write control
    P6MDOUT = 0xFF;                   //address lines
    P7MDOUT = 0xFF;                   //data lines
    lcdrs = 0x02;
    lcdrw = 0x01;
    // external pointer config
    lcdbase  = 0xB4;
    lcdwdata = lcdbase + lcdrs;
    lcdwcmd  = lcdbase;
    lcdrdata = lcdbase + lcdrw + lcdrs;
    lcdrcmd  = lcdbase + lcdrw;

    // huh?
    _mpuwcmd(0x3C);
    delay_us(37);
    _mpuwcmd(0x0E);

    // set display on/off, cursor, and blinking.
    _lcdcmd(0x06);
    lcdclear();
}

void lcdwrite(uint8_t *str) {
    lcdwstr();
}

void lcdwritec(uint8_t code *str) {
    lcdwstr();
}

void lcdwritex(uint8_t xdata *str) {
    lcdwstr();
}

void lcdwritei8(uint8_t i) {
    char a[] = "\0\0\0\0";
    itoa8(i, a);
    lcdwrite(a);
}

void lcdwritei16(uint16_t i) {
    char a[] = "\0\0\0\0\0\0";
    itoa16(i, a);
    lcdwrite(a);
}


void lcdpos(uint8_t row, uint8_t col) {
    _lcdcmd((0x80 | ((row & 0x01) << 6) | (col & 0x0F))); //lulz
}

void lcdcursor(uint8_t mode) {
    _lcdcmd((0x0C | (mode & 0x0F))); //trololol
}

void lcdclear() {
    _lcdcmd(0x01);
}

// utility function definitions
void _mpuwdata(uint8_t d) {
    *lcdwdata = d;
}

void _mpuwcmd(uint8_t cmd) {
    *lcdwcmd = cmd;
}

uint8_t _mpurdata() {
    return *lcdrdata;
}

uint8_t _mpurcmd() {
    return *lcdrcmd;
}

void _lcddata(uint8_t d) {
    _busy();
    _mpuwdata(d);
}

void _lcdcmd(uint8_t d) {
    _busy();
    _mpuwcmd(d);
}

void _busy() {
    while (_mpurcmd() & 0x80); //win
}
