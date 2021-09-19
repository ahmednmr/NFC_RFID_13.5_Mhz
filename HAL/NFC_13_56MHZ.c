/*
 * NFC_13_56MHZ.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Nmr
 */

#include "NFC_13_56MHZ.h"




char Rec_Data[DEFAULT_BUFFER_SIZE];
char Counter=0;

//U8 NFC_Fixed_Company_ID_array[4]           ={0xE9,0xE8,0xE7,0xE6};
unsigned char config_arr[]                 ={0x14,0x01,0x14,0x01};
unsigned char response_config_arr[]        ={0X00,0X00,0XFF,0X00,0XFF,0X00,0X00,0X00,0XFF,0X02,0XFE,0XD5,0X15,0X16,0X00};

unsigned char read_tag_arr[]               ={0x4A,0x01,0x00};
unsigned char response_read_tag_arr[]      ={0x00,0x00,0xFF,0x00,0xFF,0x00,0x00,0x00,0xFF,0X0F,0XF1,0XD5,0X4B,0X01};
unsigned char NFC_Recieved_Data[13]        ={0};

unsigned char read_tag_data[]              ={0x40,0x01,0x30,0x04};
unsigned char response_read_tag_data[]     ={0x00,0x00,0xFF,0x00,0xFF,0x00,0x00,0x00,0xFF,0X13,0XED,0XD5,0X41,0X00};


unsigned char write_page_frame[8]          ={0x40,0x01,0xA2};
unsigned char response_write_page[]        ={0x00,0x00,0xFF,0x00,0xFF,0x00,0x00,0x00,0xFF,0X03,0XFD,0XD5,0X41,0X00,0xEA,0x00};







void NFC_Recieving_interrupt(void)
{
	uint8_t oldsrg = SREG;
	cli();
	Rec_Data[Counter] = UDR;
	Counter++;
	if(Counter == DEFAULT_BUFFER_SIZE){
		Counter = 0; //pointer = 0;
	}
	SREG = oldsrg;
}





char Check_Respond(unsigned char * Expected_Respond,unsigned char Respond_Length)
{

	//	uart_TX_string("Respond\r\n");    //For Debug only

	for(unsigned char i=0;i<Respond_Length;i++)
	{
		if((Rec_Data[i])==(Expected_Respond[i])) continue;
		else
		{
#if Debug_NFC_Driver
			uart_TX_string("Respond Not matched\r\n");   //For Debug only
#endif
			return FALSE;
		}
	}
#if Debug_NFC_Driver
	uart_TX_string("Respond matched\r\n");   //For Debug only
#endif
	return TRUE;

}



void Clear_Rec_buffer(void)
{
	memset(Rec_Data,0,DEFAULT_BUFFER_SIZE);
	Counter=0;

}

void NFC_fixed_data(void)
{
	UART_SendChar(0x55);
	UART_SendChar(0x55);
	UART_SendChar(0x00);
	UART_SendChar(0x00);
	UART_SendChar(0x00);
	UART_SendChar(0x00);
	UART_SendChar(0x00);
	UART_SendChar(0xFF);
}

void NFC_send_frame(unsigned char *data,unsigned char size_of_data)
{
	unsigned char check_sum=0xD4;
	size_of_data+=1;

	NFC_fixed_data();
	UART_SendChar(size_of_data);
	UART_SendChar(~size_of_data+1);
	UART_SendChar(0xD4);

	for(char i=0;i<size_of_data-1;i++)
	{
		UART_SendChar((char)data[i]);
		check_sum+=data[i];

	}
	UART_SendChar(~check_sum+1);
	UART_SendChar(0x00);
}

en_tag_status NFC_init(void)
{
	en_tag_status status;

	uart_init();    // for debug
	sei();

	init_UART_115200();
	UART_set_call_back_function(NFC_Recieving_interrupt);
	Clear_Rec_buffer();
	NFC_send_frame(config_arr,sizeof(config_arr) / sizeof(config_arr[0]));
	_delay_ms(100);
	if(Check_Respond(response_config_arr,response_config_length))
	{
		status=NFC_Connected;
	}
	else
	{
		status=NFC_NOT_Connected;

	}

	return status;
}


en_tag_status NFC_read_tag(void)
{
	en_tag_status status;

	Clear_Rec_buffer();
	NFC_send_frame(read_tag_arr,sizeof(read_tag_arr) / sizeof(read_tag_arr[0]));
	_delay_ms(100);
	if (Check_Respond(response_read_tag_arr,response_read_tag_length))
	{
		status=Tag_exist;;
	}
	else
	{
		status=Tag_not_exist;


	}


	return status;
}



en_tag_status NFC_write_page(U8 page_number,U8* Data)
{

	en_tag_status status;

	write_page_frame[3]=page_number;
	for(char i=0;i<PAGE_SIZE;i++)
	{
		write_page_frame[4+i]=Data[i];
	}

	Clear_Rec_buffer();
	NFC_send_frame(write_page_frame,sizeof(write_page_frame) / sizeof(write_page_frame[0]));
	_delay_ms(100);
	if(Check_Respond(response_write_page,response_write_data_length))
	{
		status=TAG_operation_done;
	}
	else
	{
		status=TAG_operation_Not_done;
	}

	return status;
}


en_tag_status NFC_write_company_id(U8* Company_id)
{

	en_tag_status status;

status=NFC_write_page(COMPANY_ID_PAGE_NUMBER,Company_id);

return status;
}

en_tag_status NFC_write_company_id_number(U32 Company_id_number)
{

	en_tag_status status;
	U8 tag_id[4]={0};

	for(U8 i=0;i<PAGE_SIZE;i++)
	{
		tag_id[3-i]=(unsigned char )(Company_id_number);
		Company_id_number>>=8;
	}


status=NFC_write_page(COMPANY_ID_PAGE_NUMBER,tag_id);

return status;
}



en_tag_status NFC_write_tag_ID(U32 tag_number)
{
	en_tag_status status;
	U8 tag_id[4]={0};

	for(U8 i=0;i<PAGE_SIZE;i++)
	{
		tag_id[3-i]=(unsigned char )(tag_number);
		tag_number>>=8;
	}

	status=NFC_write_page(TAG_ID_PAGE_NUMBER,tag_id);

	return status;

}

en_tag_status NFC_write_Tag_Points(U32 points)
{
	en_tag_status status;
		U8 tag_points[4]={0};

	for(char i=0;i<PAGE_SIZE;i++)
	{
		tag_points[3-i]=(unsigned char )(points);
		points>>=8;
	}

	status=NFC_write_page(TAG_POINTS_PAGE_NUMBER,tag_points);

	return status;

	return 0;
}


//en_tag_status NFC_write_load_Points(U32 points)
//{
//	en_tag_status status;
//		U8 tag_points[4]={0};
//
//	for(char i=0;i<PAGE_SIZE;i++)
//	{
//		tag_points[3-i]=(unsigned char )(points);
//		points>>=8;
//	}
//
//	status=NFC_write_page(LOAD_POINTS_PAGE_NUMBER,tag_points);
//
//	return status;
//
//	return 0;
//}
//


U8 NFC_read_tag_data(st_recieved_tag_data* recieved_struct)
{
	en_tag_status status;

	unsigned long company_id_array_byte[4]={0};
	unsigned long tag_id_array_byte[4]={0};
	unsigned long points_number_array_byte[4]={0};


	Clear_Rec_buffer();
	NFC_send_frame(read_tag_data,sizeof(read_tag_data) / sizeof(read_tag_data[0]));
	_delay_ms(100);
	status=Check_Respond(response_read_tag_data,response_read_tag_data_length);

	for(char i=0;i<DATA_LENGTH;i++)
	{
		NFC_Recieved_Data[i]=Rec_Data[response_read_tag_data_length+i];
	}


	recieved_struct->tag_company_id=0;
	for(char i=0;i<PAGE_SIZE;i++)
	{
		company_id_array_byte[i]=(unsigned long )(NFC_Recieved_Data[Company_ID_index+3-i]);
		company_id_array_byte[i]<<=8*i;
		recieved_struct->tag_company_id |=company_id_array_byte[i];
	}
#if Debug_NFC_Driver
	uart_TX_string("\r\n Company ID  ");    //For Debug only
	uart_TX_long_number(recieved_struct->tag_company_id);
#endif

	recieved_struct->tag_id=0;
	for(char i=0;i<PAGE_SIZE;i++)
	{
		tag_id_array_byte[i]=(unsigned long )(NFC_Recieved_Data[Tag_ID_index+3-i]);
		tag_id_array_byte[i]<<=8*i;
		recieved_struct->tag_id |=tag_id_array_byte[i];
	}

#if Debug_NFC_Driver
	uart_TX_string("\r\n Tag ID  ");    //For Debug only
	uart_TX_long_number(recieved_struct->tag_id);
#endif


	recieved_struct->tag_points_number=0;
	for(char i=0;i<PAGE_SIZE;i++)
	{
		points_number_array_byte[i]=(unsigned long )(NFC_Recieved_Data[Points_Number_index+3-i]);
		points_number_array_byte[i]<<=8*i;
		recieved_struct->tag_points_number |=points_number_array_byte[i];
	}

#if Debug_NFC_Driver
	uart_TX_string("\r\n Points Number ");    //For Debug only
	uart_TX_long_number(recieved_struct->tag_points_number);
#endif



	if(status==TRUE)   return TAG_operation_done;

	else if(status==FALSE) return TAG_operation_Not_done;


}




