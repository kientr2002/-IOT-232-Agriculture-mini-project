#ifndef _INCLUDE_BUTTON_H_
#define _INCLUDE_BUTTON_H_

#include <esp32-hal-gpio.h>

#define DEBOUNCE_TIME 200



bool button_turning(int buttonPin, int& button_counter);
bool change_state_button(bool button_state, bool button_turning);


#endif // !_INCLUDE_BUTTON_H_