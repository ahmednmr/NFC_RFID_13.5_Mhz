#include "../main.h"

ret_codes_t load_card_state(void)
{

	ret_codes_t   return_state=ret_idle_state;
	en_tag_status operation_status=TAG_operation_Not_done;

#if Debug_APP
	uart_TX_string("\r\n Load Card State \r\n");
#endif


	tag_data_struct.tag_points_number+=total_load_points;

	operation_status=NFC_write_Tag_Points(tag_data_struct.tag_points_number);


	if(operation_status==TAG_operation_done)
	{
#if Debug_APP
		uart_TX_string(" Done loading Points \r\n");
		uart_TX_number(total_load_points);
		uart_TX_string("  ");
		uart_TX_number(tag_data_struct.tag_points_number);
#endif

		LCD_vidsend_sentance("Done loading Points = ");
		LCD_SEND_number(total_load_points);
		LCD_vidsendword("  ");
		LCD_SEND_number(tag_data_struct.tag_points_number);
		SHOW_SCREEN_DELAY;
		SHOW_SCREEN_DELAY;
	}
	else
	{
		LCD_vidsend_sentance("Error loading Points");
		SHOW_SCREEN_DELAY;
#if Debug_APP
		uart_TX_string("Error loading Points \r\n");   //For Debug only

#endif
	}


	total_load_points=0;
	eeprom_write_dword((uint32_t *)TOTAL_LOAD_POINTS_E2PROM_ADD,total_load_points);     // clear total_load_points in E2prom;
	_delay_ms(10);




	return return_state;
}
