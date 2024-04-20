#include "led.h"

void led_turning(bool state, int redpin, int bluepin, int greenpin){
  if(state == true){
    analogWrite(redpin, 255);
    analogWrite(bluepin, 255);
    analogWrite(greenpin, 255); 
  } else {
    analogWrite(redpin, 0);
    analogWrite(bluepin, 0);
    analogWrite(greenpin, 0); 
  }
}

bool change_led_state(bool& button_state, int light_value, bool& led_trigger_flag){
 if(button_state == true && led_trigger_flag == false){
    return true;
  } else {
    if(light_value < 10){
      button_state = true;
      led_trigger_flag = true;
      return true; //sua lai thanh true
    } else {
       button_state = false;
      led_trigger_flag = false;
    }
  }
  return false;
  
}