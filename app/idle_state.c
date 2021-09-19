#include "../main.h"

ret_codes_t idle_state(void)
{
	ret_codes_t   return_state=ret_idle_state;
	en_tag_status read_tag_status=Tag_not_exist,operation_status=TAG_operation_Not_done;

#if Debug_APP
	uart_TX_string(" idel_state \r\n");
#endif


	LCD_vidsend_sentance("Please Scan Tag");

	while(read_tag_status!=Tag_exist)
	{
		read_tag_status=NFC_read_tag();
		if(read_tag_status==Tag_not_exist)
		{
#if Debug_APP
			//			uart_TX_string(" Tag Not exist \r\n");
#endif
		}
		_delay_ms(400);
	}
	if(read_tag_status==Tag_exist)
	{
#if Debug_APP
		uart_TX_string(" Tag  exist \r\n");
#endif

		operation_status=NFC_read_tag_data(&tag_data_struct);

		if((tag_data_struct.tag_company_id)!=Company_ID)
		{
			operation_status=Tag_exist_Not_valid;
		}


		switch (operation_status) {
		case TAG_operation_done:

#if Debug_APP

			uart_TX_string("\r\n Company ID  ");    //For Debug only
			uart_TX_long_number(tag_data_struct.tag_company_id);

			uart_TX_string("\r\n Tag ID  ");    //For Debug only
			uart_TX_long_number(tag_data_struct.tag_id);

			uart_TX_string("\r\n Points Number ");    //For Debug only
			uart_TX_long_number(tag_data_struct.tag_points_number);

#endif
			if(tag_data_struct.tag_id==MASTER_CARD_ID)
			{
				return_state=ret_master_state;
			}
			else if(tag_data_struct.tag_id==LOAD_CARD_ID)
			{
				return_state=ret_load_state;
			}
			else
			{
				return_state=ret_user_state;
			}



			break;

		case TAG_operation_Not_done:
#if Debug_APP
			uart_TX_string(" error reading Tag \r\n");   //For Debug only

#endif
			LCD_vidsend_sentance("Error reading ");
			SHOW_SCREEN_DELAY;
			break;


		case Tag_exist_Not_valid:
#if Debug_APP
			uart_TX_string(" error Tag Not Valid \r\n");   //For Debug only

#endif
			LCD_vidsend_sentance("Error Tag Not Valid");
			SHOW_SCREEN_DELAY;
			break;

		}



	}

	return (return_state);
}
