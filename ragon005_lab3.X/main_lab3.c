#include "xc.h"
#include <p24Fxxxx.h>
#include <stdio.h>

#include "keypadlib.h"
#include "displaylib.h"


// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1 // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME // Clock Switching and Monitor (Clock switching is enabled,


// Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

#define notFound = '17';

unsigned char taDemo[17] = {'1', '2', '3', 'a', '4', '5', '6', 'b', '7', '8', '9', 'c', '*', '0', '#', 'd', 'x'};
unsigned int tempKey = 16;
unsigned int leftkey = 16;
int buttonPressed = 0;

void delay(int myDelay)
{
    while(myDelay > 0)
    {
        while (!IFS0bits.T1IF) ;
        IFS0bits.T1IF = 0;
        myDelay--;
    }
}

int main(void)
{
    init7seg();
    initKeypad();

    while(1)
    {
        //pre-lab function
//        int dualDelay = 333; //.333ms + .666ms from loop = 1 sec
//        int index = 0;
//        while(index < 16)//left
//        {
//            show7seg(taDemo[index], left);
//            delay(1000); //1 sec
//            index++;
//        }
//
//        index = 0;
//        while(index < 16)//right
//        {
//            show7seg(taDemo[index], right);
//            delay(1000); //1 sec
//            index++;
//        }
//
//        index = 0;
//
//        while(index < 16)//both
//        {
//            int dualDelay = 333; //.333ms + .666ms from loop = 1 sec
//
//            while(dualShow(dualDelay))
//            {
//                show7seg(taDemo[index], left);
//                delay(1);
//                show7seg(taDemo[index], right);
//                delay(1);
//                dualDelay--;
//            }
//            index++;
//        }
//           
        //lab function
        readKeyPad();
        
        if(buttonPressed)
        {
            delay(2);
        }
        
        show7seg(getL(), left);
        delay(1);
        show7seg(getR(), right);
        delay(1);
    }
    return 0;
}