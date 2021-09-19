#include "../main.h"


ret_codes_t user_card_state(void)
{

	ret_codes_t   return_state=ret_idle_state;
	en_tag_status operation_status=TAG_operation_Not_done;

#if Debug_APP
			uart_TX_string(" user_card_state \r\n");
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

			total_load_points+=Machine_points;
			// save total_load_points in E2prom
			_delay_ms(1000);
			// output to the game
			for(U8 i=0;i<5;i++)
			{
				LCD_vidGoTo(1,9);
				LCD_vidsendword("       ");
				_delay_ms(500);
				LCD_vidGoTo(1,9);
				LCD_SEND_number(tag_data_struct.tag_points_number);
				_delay_ms(500);
				//buzzer alert
			}

		}
		else
		{
			LCD_vidsendword("Error writing Points");
			SHOW_SCREEN_DELAY;
#if Debug_APP
			uart_TX_string(" error write Tag Points \r\n");   //For Debug only

#endif
		}

	}

	return return_state;
}
