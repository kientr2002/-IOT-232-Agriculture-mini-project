#include "button.h"
#include <HWCDC.h>
#include <USBCDC.h>
#include <stdbool.h>
#include <HardwareSerial.h>



bool button_turning(int buttonPin, int& button_counter){
  int  buttonState = digitalRead(buttonPin);
  if (buttonState == 1) {
    button_counter++;

  }  else {
    if(button_counter > 0){
      if(button_counter > DEBOUNCE_TIME){
        button_counter = 0;
        return true;
      }
      button_counter = 0;
    }
  }
  return false;
}


bool change_state_button(bool button_state, bool button_turning){
  if(button_turning == true){
      if(button_state == true){
        return false;
      } else {
        return true;
      }
  }
  return button_state;
}