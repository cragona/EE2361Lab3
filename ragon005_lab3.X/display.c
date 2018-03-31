#include "xc.h"
#include <p24Fxxxx.h>
#include <stdio.h>


#include "displaylib.h"

void init7seg(void)
{
    CLKDIVbits.RCDIV = 0; //Set RCDIV=1:1 (default 2:1) 32mhz or fcy/2=16mhz)
    AD1PCFG = 0x9fff;   //all analog set to digital
    TRISB = 0b0000000000000011; // set RB as such so RB<15:12> are keypad checks, RB<11:2> are out puts, reserver RB<0:1> for chipkit input
    LATB = 0xf000;

    //TIMER SETUP
    T1CON = 0;
    PR1 = 15999;
    TMR1 = 0;
    IFS0bits.T1IF = 0;
    T1CONbits.TON = 1;
}

void waitDisplay(void)
{
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
}

void show7seg(char myChar, enum SIDE mySide)
{
    LATB = 0xf000;
    waitDisplay();
    
    if(myChar == 48) // 0
    {
        LATB = mySide | three | two;
    }
    else if(myChar == 49) //1
    {
        LATB = mySide | nine | three | four | five | six | two;
    }
    else if(myChar == 50) //2
    {
        LATB = mySide | four | seven | two;
    }
    else if(myChar == 51) //3
    {
        LATB = mySide | four | five | two;
    }
    else if(myChar == 52) //4
    {
        LATB = mySide | nine | five | six | two;
    }
    else if(myChar == 53) //5
    {
        LATB = mySide | eight | five | two;
    }
    else if(myChar == 54)//6
    {
        LATB = mySide | eight | two;
    }
    else if(myChar == 55) //7
    {
        LATB = mySide | four | five | six | three | two;
    }
    else if(myChar == 56) //8
    {
        LATB = mySide | two;
    }
    else if(myChar == 57) //9
    {
        LATB = mySide | five | two;
    }
    else if(myChar == 97) //a
    {
        LATB = mySide | nine | four | eight;
    }
    else if(myChar == 98) //b
    {
        LATB = mySide | nine | eight | two;
    }
    else if(myChar == 99) //c
    {
        LATB = mySide | nine | four | eight | seven | two;
    }
    else if(myChar == 100)//d
    {
        LATB = mySide | four | nine | two;
    }
    else if(myChar == 42) //*
    {
        LATB = mySide | nine | four | eight | two;
    }
    else if(myChar == 35) //#
    {
        LATB = mySide | nine | four | eight | three | two;
    }

    waitDisplay();
}

int dualShow(int myDelay)
{
    while (!IFS0bits.T1IF);
    IFS0bits.T1IF = 0;
    return myDelay;
}

unsigned char getL(void)
{  
    unsigned char taDemo[17] = {'1', '2', '3', 'a', '4', '5', '6', 'b', '7', '8', '9', 'c', '*', '0', '#', 'd', 'x'};
    unsigned int clockDisplay[2] = {16, 16};
    return taDemo[clockDisplay[0]];
}

unsigned char getR (void)
{
    unsigned char taDemo[17] = {'1', '2', '3', 'a', '4', '5', '6', 'b', '7', '8', '9', 'c', '*', '0', '#', 'd', 'x'};
    unsigned int clockDisplay[2] = {16, 16};
    return taDemo[clockDisplay[1]];
}
