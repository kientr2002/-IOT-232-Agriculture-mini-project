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