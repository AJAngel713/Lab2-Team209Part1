// ******************************************************************************************* //
// File:         lab2p1.c
// Date:         
// Authors:      
//
// Description: 
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

          typedef enum states{
    wait, keyFind, writeLCD
}states;

volatile states curState;

int main(void)
{
    initKeypad();
    initLCD();
    initTimer1();

    curState = wait;

    while(1){
        switch (curState)
        {
            case wait:
            break;

            case keyFind:
                scanKeypad();
                break;

        }
        
    }
    
    return 0;
}

void _ISR _CNInterrupt(){
    _CNIF = 0;

    if (curState == wait){
        curState = keyFind;
    }

}
