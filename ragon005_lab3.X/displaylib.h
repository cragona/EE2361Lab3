/* 
 * File:   display.h
 * Author: Jennifer
 *
 * Created on February 21, 2018, 5:22 PM
 */

#ifndef DISPLAY_H
#define	DISPLAY_H "displaylib.h"


#ifdef	__cplusplus
extern "C" {
#endif
enum SIDE{
    left = 0b0000010000000000, //rA10
    right = 0b0000100000000000, //RA11
    two = 0b100, //RB2
    three = 0b1000, //RB3
    four = 0b10000, //etc...
    five = 0b100000,
    six = 0b1000000,
    seven = 0b10000000,
    eight = 0b100000000,
    nine = 0b1000000000
};
//function prototypes
void show7seg(char myChar, enum SIDE mySide);
void init7seg(void);
unsigned char getL(void);
unsigned char getR (void);
int dualShow(int myDelay);

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */