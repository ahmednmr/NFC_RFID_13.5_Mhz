/*
 * main.c
 *
 *  Created on: 5 Oct 2015
 *      Author: EmbeddedFab
 */

#include "HAL/NFC_13_56MHZ.h"
#include "HAL/LCD.h"
#define Debug_APP 0
/*
NFC_NOT_Connected,
NFC_Connected,
Tag_not_exist,
Tag_exist_Not_valid,
Tag_exist_valid,
TAG_operation_Not_done,
TAG_operation_done
 */

int main()
{

	st_recieved_tag_data tag_data_struct;
	en_tag_status init_status,read_tag_status,operation_status;
	U8 Machine_points=20;


	LCD_VidInit();
	LCD_vidsendword("welcome");

	init_status=NFC_init();
	if(init_status==NFC_NOT_Connected)
	{
#if Debug_APP
		uart_TX_string(" NFC Not Connected \r\n");   //For Debug only
#endif


	}
	else if (init_status==NFC_Connected)
	{
#if Debug_APP
		uart_TX_string(" NFC Connected \r\n");   //For Debug only
#endif

		while(1)
		{
			read_tag_status=Tag_not_exist;
			LCD_vidClear();
			LCD_vidsendword("Please Scan Tag");

			while(read_tag_status!=Tag_exist)
			{
				read_tag_status=NFC_read_tag();
				if(read_tag_status==Tag_not_exist)
				{
#if Debug_APP
					uart_TX_string(" Tag Not exist \r\n");   //For Debug only
#endif
				}
				_delay_ms(400);
			}
			if(read_tag_status==Tag_exist)
			{
#if Debug_APP
				uart_TX_string(" Tag  exist \r\n");   //For Debug only
#endif

				operation_status=NFC_read_tag_data(&tag_data_struct);



				if(operation_status==TAG_operation_done)
				{
#if Debug_APP

					uart_TX_string("\r\n Company ID  ");    //For Debug only

					for(U8 i=0;i<PAGE_SIZE;i++)
					{
						uart_TX_hex_number(tag_data_struct.tag_company_id[i]);
					}

					uart_TX_string("\r\n Tag ID  ");    //For Debug only
					uart_TX_long_number(tag_data_struct.tag_id);

					uart_TX_string("\r\n Points Number ");    //For Debug only
					uart_TX_long_number(tag_data_struct.tag_points_number);

#endif


					if(tag_data_struct.tag_points_number<Machine_points)
					{

						LCD_vidClear();
						LCD_vidGoTo(0,0);
						LCD_vidsendword("Tag ID : ");
						LCD_SEND_number(tag_data_struct.tag_id);
						LCD_vidGoTo(0,14);
						LCD_SEND_number(Machine_points);
						LCD_vidGoTo(1,0);
						LCD_vidsendword("Points : ");
						LCD_SEND_number(tag_data_struct.tag_points_number);
						_delay_ms(1000);
						LCD_vidClear();
						LCD_vidsendword("Not Enough Points");
						_delay_ms(3000);


					}
					else
					{

						LCD_vidClear();
						LCD_vidGoTo(0,0);
						LCD_vidsendword("Tag ID : ");
						LCD_SEND_number(tag_data_struct.tag_id);
						LCD_vidGoTo(0,14);
						LCD_SEND_number(Machine_points);
						LCD_vidGoTo(1,0);
						LCD_vidsendword("Points : ");
						LCD_SEND_number(tag_data_struct.tag_points_number);

						tag_data_struct.tag_points_number-=Machine_points;

						operation_status=NFC_write_Tag_Points(tag_data_struct.tag_points_number);

						if(operation_status==TAG_operation_done)
						{
#if Debug_APP
							uart_TX_string(" Done write Tag Points \r\n");   //For Debug only
#endif

							_delay_ms(1000);
							for(U8 i=0;i<5;i++)
							{
								LCD_vidGoTo(1,9);
								LCD_vidsendword("       ");
								_delay_ms(500);
								LCD_vidGoTo(1,9);
								LCD_SEND_number(tag_data_struct.tag_points_number);
								_delay_ms(500);
							}


						}
						else
						{
							LCD_vidsendword("Error writing Points");
#if Debug_APP
							uart_TX_string(" error write Tag Points \r\n");   //For Debug only

#endif
						}


					}

				}
				else if(operation_status==TAG_operation_Not_done)
				{
#if Debug_APP
					uart_TX_string(" error reading Tag \r\n");   //For Debug only

#endif
					LCD_vidClear();
					LCD_vidsendword("Error reading ");
					_delay_ms(2000);
				}

				else if(operation_status==Tag_exist_Not_valid)
				{
#if Debug_APP
					uart_TX_string(" error Tag Not Valid \r\n");   //For Debug only

#endif
					LCD_vidClear();
					LCD_vidsendword("Error Tag Not");
					LCD_vidGoTo(1,0);
					LCD_vidsendword("Valid");
					_delay_ms(2000);
				}




			}

		}
	}





	return 0;
}




/*
 *
 *
				//				operation_status=NFC_write_company_id(company_id);
#if Debug_APP
				if(operation_status==TAG_operation_done)
					uart_TX_string(" Done write Company ID \r\n");   //For Debug only
				else
					uart_TX_string(" error write Company ID \r\n");   //For Debug only

#endif

				//				operation_status=NFC_write_tag_ID(12);
#if Debug_APP
				if(operation_status==TAG_operation_done)
					uart_TX_string(" Done write Tag ID \r\n");   //For Debug only
				else
					uart_TX_string(" error write Tag ID \r\n");   //For Debug only

#endif
				//				operation_status=NFC_write_Tag_Points(350);

#if Debug_APP
				if(operation_status==TAG_operation_done)
					uart_TX_string(" Done write Tag Points \r\n");   //For Debug only
				else
					uart_TX_string(" error write Tag Points \r\n");   //For Debug only

#endif

 * */
