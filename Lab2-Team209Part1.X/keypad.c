#include "p24FJ64GA002.h"
#include "keypad.h"
#include "timer.h"

/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void){

    // Rows
    TRISAbits.TRISA0 = OUTPUT; //  row 1, output
    TRISAbits.TRISA1 = OUTPUT; // row 2 , output
    TRISBbits.TRISB9 = OUTPUT; // row 3 , output
    TRISBbits.TRISB8 = OUTPUT; // row 4 output

    ODCAbits.ODA0 = 1; // Open Drain collecctor for pins 2, 3, 6, 7 
    ODCAbits.ODA1 = 1;
    ODCBbits.ODB2 = 1;
    ODCBbits.ODB3 = 1;
    
    // Columns
    TRISAbits.TRISA0 = 1; // column 1, input
    TRISAbits.TRISA1 = 1; // column 2 , input
    TRISBbits.TRISB2 = 1; // column 3 , input

    CNPU2bits.CN21PUE = 1; // pull up resistor for columns
    CNPU2bits.CN16PUE = 1;
    CNPU1bits.CN15PUE = 1;

}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed.
 */
char scanKeypad(void){
    char key = -1;
    char keys[ROWS][COLUMNS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
    };

    

    return key;
}
