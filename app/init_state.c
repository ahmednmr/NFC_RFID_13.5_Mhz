#include "../main.h"


ret_codes_t init_state(void){

	ret_codes_t   return_state=ret_init_state;
	en_tag_status init_status;

	KeyPad_Init();
	Buzzer_Init();
	LCD_VidInit();
	LCD_vidsendword("welcome");

	init_status=NFC_init();

#if Debug_APP
	uart_TX_string(" init_state \r\n");
#endif


	if(init_status==NFC_NOT_Connected)
	{
#if Debug_APP
		uart_TX_string(" NFC Not Connected \r\n");   //For Debug only
#endif

		LCD_vidsend_sentance("Please connect NFC ");
		SHOW_SCREEN_DELAY;
	}
	else if (init_status==NFC_Connected)
	{
#if Debug_APP
		uart_TX_string(" NFC Connected \r\n");   //For Debug only
#endif


//		eeprom_write_dword((uint32_t *)MACHINE_POINTS_E2PROM_ADD,20);
//		_delay_ms(10);
//		eeprom_write_dword((uint32_t *)TOTAL_LOAD_POINTS_E2PROM_ADD,0);
//		_delay_ms(10);
//
//		eeprom_write_dword((uint32_t *)COMPANY_ID_NUMBER_E2PROM_ADD,31190);
//		_delay_ms(10);
//

		Machine_points=eeprom_read_dword((uint32_t *)MACHINE_POINTS_E2PROM_ADD);
		_delay_ms(10);

		total_load_points=eeprom_read_dword((uint32_t *)TOTAL_LOAD_POINTS_E2PROM_ADD);
		_delay_ms(10);

		Company_ID=eeprom_read_dword((uint32_t *)COMPANY_ID_NUMBER_E2PROM_ADD);
		_delay_ms(10);



#if Debug_APP
		uart_TX_string("\r\n Machine_points =  ");
		uart_TX_number(Machine_points);

		uart_TX_string("\r\n total_load_points =  ");
		uart_TX_number(total_load_points);

		uart_TX_string("\r\n Company_ID =  ");
		uart_TX_number(Company_ID);
		uart_TX_string("\r\n");
#endif

		LCD_vidsend_sentance("NFC connected");
		SHOW_SCREEN_DELAY;
		return_state=ret_idle_state;

	}


	return return_state;

}

