#include "lcd.h"
#include "delay.h"

// useful macros
#define SET_RS()    (lcdrs = 0x02)
#define SET_RW()    (lcdrw = 0x01)

#define CLEAR_RS()  (lcdrs = 0x00)
#define CLEAR_RW()  (lcdrw = 0x00)

#define SET_DATA(d) (*(lcdrs | lcdrw | lcdbase) = (d))
#define GET_DATA()  (*(lcdrs | lcdrw | lcdbase))

// hackros
#define lcdwstr()    while (*str != '\0') {_lcdw(0, *str); str++;}

// timings in us
#define T_AS        0.06
#define PW_EH       0.5
#define T_DSW       0.2
#define T_AH        0.02
#define T_DDR       0.4

// utility functions
void _mpuw(uint8_t rs, uint8_t data); // write data to MPU
uint8_t _mpur(uint8_t rs);            // read data from MPU
void _lcdw(uint8_t rs, uint8_t data); // write data to MPU, wait for busy state to complete
void _busy();                         // wait on busy flag

// global vars
uint8_t xdata *lcdbase;
uint8_t lcdrs;
uint8_t lcdrw;

// public functions
void lcdinit() {
    const uint8_t setup_flags = 0x38; // function set: 8-bit mode, 2 lines, 5x8 font

    // external memory

    // huh?
    _mpuw(1, setup_flags);
    delay_us(37);

    //anoeu
    lcdclear();

    _busy();
}

void lcdwritec(uint8_t code *str) {
    lcdwstr();
}

void lcdwritex(uint8_t xdata *str) {
    lcdwstr();
}

void lcdpos(uint8_t row, uint8_t col) {
    _lcdw(1, (0x80 | (row & 0x40) | col));  //lulz
}

void lcdcursor(uint8_t mode) {
    switch(mode) {
        case 0:
            _lcdw(1, 0x0C);
            break;
        case 1:
            _lcdw(1, 0x0D);
            break;
        case 2:
            _lcdw(1, 0x0E);
            break;
        case 3:
            _lcdw(1, 0x0F);
            break;
        default:
    }
}

void lcdclear() {
    _lcdw(1, 0x01);
}

// utility function definitions
void _mpuw(uint8_t rs, uint8_t data) {
    if (rs == 1) {
        SET_RS();
    }
    else {
        CLEAR_RS();
    }
    CLEAR_RW();
    
    SET_DATA(data);
}

uint8_t _mpur(uint8_t rs) {
    if (rs == 1) {
        SET_RS();
    }
    else {
        CLEAR_RS();
    }
    SET_RW();

    uint8_t data = GET_DATA();
    return data;
}

void _lcdw(uint8_t rs, uint8_t data) {
    _busy();
    _mpuw(rs, data);
}

void _busy() {
    uint8_t data;
    do {
        data = _mpur(0); // read data with RS = 0
    } while (data & 0x80); // we only care about the MSB (busy flag), loop while busy
}