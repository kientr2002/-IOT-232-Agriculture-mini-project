#ifndef _LED_H_
#define _LED_H_
#include <BH1750.h>

void led_turning(bool state, int redpin, int bluepin, int greenpin);
bool change_led_state(bool button_state, int light_value);

#endif // !_LED_H_