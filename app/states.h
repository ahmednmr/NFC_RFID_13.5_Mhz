/*
 * states.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Nmr
 */

#ifndef APP_STATES_H_
#define APP_STATES_H_


/* return codes */
typedef enum ret_codes{
	ret_init_state = 0,
	ret_idle_state ,
	ret_user_state,
	ret_setting_state,
	ret_load_state,


}ret_codes_t;



ret_codes_t init_state(void);
ret_codes_t idle_state(void);
ret_codes_t user_card_state(void);
ret_codes_t setting_card_state(void);
ret_codes_t load_card_state(void);



#endif /* APP_STATES_H_ */
