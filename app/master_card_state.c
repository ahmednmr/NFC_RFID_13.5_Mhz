#include "../main.h"


ret_codes_t master_card_state(void)
{
	ret_codes_t   return_state=ret_idle_state;

#if Debug_APP
			uart_TX_string(" master_card_state \r\n");
#endif


		LCD_vidsend_sentance("1-Play The Game 2-Settings");
		while(1);

		return return_state;
}
