#ifndef __MAIN_H__
#define __MAIN_H__

#include"app/states.h"
#include"HAL/NFC_13_56MHZ.h"
#include"HAL/LCD.h"
#include <avr/eeprom.h>

#define Debug_APP 1
#define SHOW_SCREEN_DELAY _delay_ms(2000)


#define MACHINE_POINTS_E2PROM_ADD      0x01
#define TOTAL_LOAD_POINTS_E2PROM_ADD   0x04

#define MASTER_CARD_ID           0xFFFFFFFF
#define LOAD_CARD_ID             0xEEEEEEEE

st_recieved_tag_data tag_data_struct;
U32 Machine_points;
U32 total_load_points;
U32 Company_ID;


#endif
































