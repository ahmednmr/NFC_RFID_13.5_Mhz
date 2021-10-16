/*
 * Nmr NFC_Normal Boards 17/9/2021
 */

#include "main.h"


#define ENTRY_STATE entry



/*=========================================================================
 * 									Main
 *=======================================================================*/
int main(void)
{

	ret_codes_t rc=  ret_init_state ;

	while(1)
	{
		switch (rc) {
		case ret_init_state:
			rc=init_state();
			break;

		case ret_idle_state:
			rc=idle_state();
			break;


		case ret_user_state:
			rc=user_card_state();
			break;


		case ret_setting_state:
			rc=setting_card_state();
			break;


		case ret_load_state:
			rc=load_card_state();
			break;

		}




	}
	return 0 ;
}
