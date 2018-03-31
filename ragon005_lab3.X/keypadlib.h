/* 
 * File:   keypad.h
 * Author: Jennifer
 *
 * Created on February 21, 2018, 4:22 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H "keypadlib.h"

//#define extern unsigned int clockDisplay[2] = {16, 16};


#ifdef	__cplusplus
extern "C" {
#endif
    
    void readKeyPad(void);
    void initKeypad(void);
    unsigned char scan(unsigned int row);
    void keypadWait(void);

#ifdef	__cplusplus
}
#endif

#endif	/* KEYPAD_H */
