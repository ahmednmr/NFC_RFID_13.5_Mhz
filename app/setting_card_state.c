#include "../main.h"


ret_codes_t setting_card_state(void)
{
	ret_codes_t   return_state=ret_idle_state;
	U16 new_machin_points=0,new_company_id=0;


#if Debug_APP
	uart_TX_string("\r\n master_card_state \r\n");
#endif

	new_machin_points=tag_data_struct.tag_points_number;
	Machine_points=(U32)new_machin_points;
	eeprom_write_dword((uint32_t *)MACHINE_POINTS_E2PROM_ADD,Machine_points);
	_delay_ms(10);


	new_company_id=tag_data_struct.tag_company_id;
	Company_ID=(U32)new_company_id;
	eeprom_write_dword((uint32_t *)COMPANY_ID_NUMBER_E2PROM_ADD,Company_ID);
	_delay_ms(10);


	LCD_vidsend_sentance("machine points");
	LCD_vidGoTo(1,0);
	LCD_SEND_number(Machine_points);
	SHOW_SCREEN_DELAY;
	LCD_vidClear();

	LCD_vidsend_sentance("Company ID");
	LCD_vidGoTo(1,0);
	LCD_SEND_number(Company_ID);
	SHOW_SCREEN_DELAY;
	LCD_vidClear();
	return_state=ret_idle_state;

	return return_state;
}
