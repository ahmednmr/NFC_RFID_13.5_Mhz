#include "../main.h"


ret_codes_t user_card_state(void)
{

	ret_codes_t   return_state=ret_idle_state;
	en_tag_status operation_status=TAG_operation_Not_done;

#if Debug_APP
	uart_TX_string("\r\n user_card_state \r\n");
#endif


	if((U16)tag_data_struct.tag_points_number<(U16)Machine_points)
	{


#if Debug_APP
		uart_TX_string("\r\n Machine_points =  ");
		uart_TX_number(Machine_points);

		uart_TX_string("\r\n tag Points =  ");
		uart_TX_number(tag_data_struct.tag_points_number);

		uart_TX_string("\r\n Not enough tag points \r\n");

#endif

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
		Buzzer_ON();
		_delay_ms(2000);
		Buzzer_OFF();

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

		tag_data_struct.tag_points_number=(U16)tag_data_struct.tag_points_number-(U16)Machine_points;

		operation_status=NFC_write_Tag_Points(tag_data_struct.tag_points_number);



		if(operation_status==TAG_operation_done)
		{
#if Debug_APP
			uart_TX_string(" Done write Tag Points \r\n");   //For Debug only
#endif

			total_load_points+=Machine_points;
			eeprom_write_dword((uint32_t *)TOTAL_LOAD_POINTS_E2PROM_ADD,total_load_points);     // save total_load_points in E2prom
			_delay_ms(10);
//			_delay_ms(1000);
			// output to the game
			for(U8 i=0;i<4;i++)
			{
				Buzzer_Toggel();//buzzer alert
				LCD_vidGoTo(1,9);
				LCD_vidsendword("       ");
				_delay_ms(400);
				LCD_vidGoTo(1,9);
				LCD_SEND_number(tag_data_struct.tag_points_number);
				_delay_ms(400);

			}
			Buzzer_OFF();
		}
		else
		{
			LCD_vidsend_sentance("Error writing Points");
			SHOW_SCREEN_DELAY;
#if Debug_APP
			uart_TX_string(" error write Tag Points \r\n");   //For Debug only

#endif
		}

	}

	return return_state;
}
