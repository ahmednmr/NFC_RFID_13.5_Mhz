#ifndef __MAIN_H__
#define __MAIN_H__

#include"app/states.h"
#include"HAL/NFC_13_56MHZ.h"
#include"HAL/LCD.h"
#include"HAL/keypad.h"
#include"HAL/buzzer.h"
#include <avr/eeprom.h>

#define Debug_APP 1
#define SHOW_SCREEN_DELAY _delay_ms(2000)


#define MACHINE_POINTS_E2PROM_ADD      0x01
#define TOTAL_LOAD_POINTS_E2PROM_ADD   0x04
#define COMPANY_ID_NUMBER_E2PROM_ADD   0x08

#define MASTER_CARD_ID           0xFFFFFFFF     //4294967295
#define LOAD_CARD_ID             0xEEEEEEEE     //4008636142
#define SETTINGS_CARD_ID             0xDDDDDDDD     //4008636142

#define ENTER_KEY  'E'
#define CANCELLE_KEY  'D'

st_recieved_tag_data tag_data_struct;
U32 Machine_points;
U32 total_load_points;
U32 Company_ID;


#endif
































