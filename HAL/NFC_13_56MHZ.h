/*
 * NFC_13_56MHZ.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Nmr
 */

#ifndef NFC_13_56MHZ_H_
#define NFC_13_56MHZ_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include "../MCAL/UART.h"
#include <avr/interrupt.h>
#include "../uart.h"
#include "../Utils.h"
#include "../STD_TYPES.h"



#define Debug_NFC_Driver 0
#define DEFAULT_BUFFER_SIZE 100


#define response_config_length         15
#define response_read_tag_length       14  //only check first 14 bytes
#define response_read_tag_data_length  14  //only check first 14 bytes
#define DATA_LENGTH                    12
#define response_write_data_length        16

#define PAGE_SIZE                      4
#define Company_ID_index                      0
#define Tag_ID_index                      4
#define Points_Number_index                      8

#define COMPANY_ID_PAGE_NUMBER            4
#define TAG_ID_PAGE_NUMBER                5
#define TAG_POINTS_PAGE_NUMBER            6

typedef struct
{
	unsigned long tag_company_id[4];
	unsigned long tag_id;
	unsigned long tag_points_number;

}st_recieved_tag_data;

typedef enum
{
NFC_NOT_Connected,
NFC_Connected,
Tag_not_exist,
Tag_exist,
Tag_exist_Not_valid,
Tag_exist_valid,
TAG_operation_Not_done,
TAG_operation_done
}en_tag_status;



void NFC_fixed_data(void);
void NFC_send_frame(unsigned char *data,unsigned char size_of_data);
char Check_Respond(unsigned char * Expected_Respond,unsigned char Respond_Length);
void Clear_Rec_buffer(void);
en_tag_status NFC_init(void);
void NFC_Recieving_interrupt(void);
en_tag_status NFC_read_tag(void);
en_tag_status NFC_write_page(U8 page_number,U8* Data);
en_tag_status NFC_write_company_id(U8* Company_id);
en_tag_status NFC_write_tag_ID(U32 tag_number);
en_tag_status NFC_write_Tag_Points(U32 points);
U8 NFC_read_tag_data(st_recieved_tag_data* recieved_struct);




#endif /* NFC_13_56MHZ_H_ */
