/* 
 * File:   keypad.h
 * Author: user
 *
 * Created on February 5, 2015, 11:42 AM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H


void initKeypad(void);
char scanKeypad(void);

#define INPUT 1
#define OUTPUT 0
#define ROWS 4
#define COLUMNS 3


#endif	/* KEYPAD_H */

