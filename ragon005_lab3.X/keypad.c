#include "xc.h"
#include <p24Fxxxx.h>
#include <stdio.h>

#include "keypadlib.h"

void initKeypad(void)
{
    TRISA = 0b1111;
    CNPU1bits.CN2PUE = 1;
    CNPU1bits.CN3PUE = 1;
    CNPU2bits.CN30PUE = 1;
    CNPU2bits.CN29PUE = 1;
}

//sets and stores key pad entries
void set(int passedKey)
{
    unsigned int clockDisplay[2] = {16, 16};
    if(clockDisplay[0] == 16 && clockDisplay[1] == 16)
    {
        clockDisplay[0] = passedKey;
    }
    else if(clockDisplay[0] != 16 && clockDisplay[1] == 16)
    {
        clockDisplay[1] = passedKey;
    }
    else
    {
        clockDisplay[0] = clockDisplay[1];
        clockDisplay[1] = passedKey;
    }  
}

//scans columns for press
unsigned char scan(unsigned int row)
{
    unsigned char col;
    
    col = PORTA & 0b1111;
    if(col == 7)
        col = 3;
    else if(col == 11)
        col = 2;
    else if(col == 13)
        col = 3;
    else if(col == 14)
        col = 4;
    else
        return col;
    
    return row*4 + col;
}

//just a wait function to let gates latch
void keypadWait(void){
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
}

void readKeyPad(void)
{
    int buttonPressed = 0;
    int columnCheck;
    unsigned int keyToCheck = 17;
    unsigned int row;
    static unsigned int lastKey[] = {17,17,17,17};
    LATB = 0xf000;
    keypadWait();
        //row 1
        //clear old column check
    
    LATBbits.LATB12 = 0;
    LATBbits.LATB13 = 1;
    LATBbits.LATB14 = 1;
    LATBbits.LATB15 = 1;
    keypadWait();
    row = 0;

    columnCheck = PORTA & 0b1111;

    if(columnCheck == 0b0111)
    {
        keyToCheck = 0;
        buttonPressed = 1;
    }
    else if(columnCheck == 0b1011)
    {
        keyToCheck = 1;
        buttonPressed = 1;
    }
    else if(columnCheck == 0b1101)
    {
        keyToCheck = 2;
        buttonPressed = 1;
    }
    else if(columnCheck == 0b1110)
    {
        keyToCheck = 3;
        buttonPressed = 1;
    }

    //row 2
    //clear old column check
        LATBbits.LATB12 = 1;
        LATBbits.LATB13 = 0;
        LATBbits.LATB14 = 1;
        LATBbits.LATB15 = 1;
        keypadWait();
        row = 1;
        columnCheck = PORTA & 0b1111;

    if(columnCheck == 0b0111)
    {
        keyToCheck = 4;
        buttonPressed = 1;
    }
    else if(columnCheck == 0b1011)
    {
        keyToCheck = 5;
        buttonPressed = 1;
    }
    else if(columnCheck == 0b1101)
    {
        keyToCheck = 6;
        buttonPressed = 1;
    }
    else if(columnCheck == 0b1110)
    {
        keyToCheck = 7;
        buttonPressed = 1;
    }

    //row 3
    //clear old column check
        LATBbits.LATB12 = 1;
        LATBbits.LATB13 = 1;
        LATBbits.LATB14 = 0;
        LATBbits.LATB15 = 1;
        keypadWait();
        row = 2;
        columnCheck = PORTA & 0b1111;
    if(columnCheck == 0b0111)
    {
        keyToCheck = 8;
        buttonPressed = 1;
    }
    else if(columnCheck == 0b1011)
    {
        keyToCheck = 9;
        buttonPressed = 1;
    }
    else if(columnCheck == 0b1101)
    {
        keyToCheck = 10;
        buttonPressed = 1;
    }
    else if(columnCheck == 0b1110)
    {
        keyToCheck = 11;
        buttonPressed = 1;
    }

    //row 4
    //clear old column check
    LATBbits.LATB12 = 1;
    LATBbits.LATB13 = 1;
    LATBbits.LATB14 = 1;
    LATBbits.LATB15 = 0;
    keypadWait();
    row = 3;
    columnCheck = PORTA & 0b1111;
    if(columnCheck == 0b0111)
    {
        keyToCheck = 12;
        buttonPressed = 1;
    }
    else if(columnCheck == 0b1011)
    {
        keyToCheck = 13;
        buttonPressed = 1;
    }
    else if(columnCheck == 0b1101)
    {
        keyToCheck = 14;
        buttonPressed = 1;
    }
    else if(columnCheck == 0b1110)
    {
        keyToCheck = 15;
        buttonPressed = 1;
    }
    
    if(keyToCheck != lastKey[row])
    {
        lastKey[row] = keyToCheck;
        if(keyToCheck != 17)
        {
            set(keyToCheck);
        }
    } 
}