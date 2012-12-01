#include "itoa.h"

#define NUM5 10000
#define NUM4 1000
#define NUM3 100
#define NUM2 10
#define NUM1 1

#define TEST(k)  if ( i / NUM##k ) { s = k; }
#define TRUNC(n) do { a[p++] = i / n + 0x30; i %= n; } while(0)
#define MCASE(k) case k: TRUNC(NUM##k) 

void itoa8(uint8_t i, char *a) {
    uint8_t p = 0;
    uint8_t s = 3;

    // DOCJK
    TEST(3) else
    TEST(2) else
    TEST(1)

    switch(s) {
        MCASE(3);
        MCASE(2);
        MCASE(1);
    }
}

void itoa16(uint16_t i, char *a) {
    uint8_t p = 0;
    uint8_t s = 5;
    // max is 65,535

    // DOCJK
    TEST(5) else
    TEST(4) else
    TEST(3) else
    TEST(2) else
    TEST(1)

    switch(s) {
        MCASE(5);
        MCASE(4);
        MCASE(3);
        MCASE(2);
        MCASE(1);
    }
}