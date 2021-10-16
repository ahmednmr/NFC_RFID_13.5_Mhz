/*
 * keypad.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Nmr
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../Helpers/STD_TYPES.h"
#include "../Helpers/Utils.h"
#include "../MCAL/DIO.h"

#define KEYBAD_ROW_PORT     PORT_A
#define FIRST_ROW_PIN        4
#define SECOND_ROW_PIN       5
#define THIRD_ROW_PIN        6
#define FORTH_ROW_PIN        7

#define KEYBAD_COLUMN_PORT  PORT_A
#define FIRST_COLUMN_PIN     0
#define SECOND_COLUMN_PIN    1
#define THIRD_COLUMN_PIN     2
#define FORTH_COLUMN_PIN     3

#define NOT_PRESSED          0x1F
#define BOUNCING_DELAY       _delay_ms(60)

void KeyPad_Init (void);
U8 KeyPad_Scan (void);


#endif /* KEYPAD_H_ */
