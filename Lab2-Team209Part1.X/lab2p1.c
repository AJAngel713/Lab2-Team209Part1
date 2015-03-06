// ******************************************************************************************* //
// File:         lab2p1.c
// Date:         March 13 2015
// Authors:      Angel Lopez, Arminda Estrada, Rubi Ballesteros, Miguel Garcia, Phillip Showers.
//
// Description: Write the key presses of the user to the LCD.
//              Keypadranges from 0 to 9 and *, #.
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "lcd.h"
#include "timer.h"
#include "keypad.h"
#include <stdio.h>

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

typedef enum stateTypeEnum
{
    wait,
    keyFind,
    writeLCDs
}stateType;

volatile stateType curState; // stores the current state.
volatile char keys[17] = {'\0','\0','\0','\0','\0','\0','\0','\0',    // stores all the key presses by the user.
                '\0','\0','\0','\0','\0','\0','\0','\0','\0'};
volatile int keysIndex = 0;    // keeps track of the current keys index that needs to be updated.

int main(void)
{
    initKeypad();   // initialize keypad.
    initLCD();      // initialice LCD.
    clearLCD();     // Clear the screen. This will also set the cursor at pos (0,0) in the LCD.
    curState = wait;// The first state is wait for a keypress.
    

    while(1){
        switch (curState)
        {
            case wait:
                // Nothing to do here.
                break;

            case keyFind:
                keys[keysIndex] = scanKeypad(); // store the result of scanning tthe keys.
                keysIndex++;                    // increment the keys index.
                curState = writeLCDs;           // Go to next state.
                break;

            case writeLCDs:
                if (keys[keysIndex-1] != -1){  // check if value to be written is valid (invalid means it is -1)
                    clearPrintStringLCD(keys); // this function clears the LCD and prints the new string formed by the keys pressed by the user.
                    if (keysIndex == 16) keysIndex = 0;  // check if the keys array is full. If it is, reset the Index.
                }
                else{   // When the last keypress was not valid.
                    if (keysIndex != 0) // When keysIndex is already zero dont decrement it anymore.
                    keysIndex--;        // if keysIndex is more han zero then decrement it
                }
                curState = wait; // go to wait state again.
                break;

        } // switch
    } // while
    
    return 0;
}

void _ISR _CNInterrupt(){
    _CNIF = 0;   // Always put the flag down first.
    delayMs(10); //press/release delay

 
    if (curState == wait){   // check what is the current state. if wait go ahead and scan keys.
        if (COL1 == 0 || COL2 == 0 || COL3 == 0){
//        curState = keyFind;
            /*
             NOTE: I can use the statement right above this, but the program breaks more often by pressing keys fast and simultaneously.
             * By scanning the keys here in the interrupt it no longer breaks.
             */
            keys[keysIndex] = scanKeypad();   // Scan keys.
                keysIndex++;                  // increment Index.
                curState = writeLCDs;         // Go to WriteLCD state.
        } // if (COL...
    }  // if (CurState...

} // _CNInterrupt
