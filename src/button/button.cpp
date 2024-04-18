#include "button.h"
#include <HWCDC.h>
#include <USBCDC.h>
#include <stdbool.h>
#include <HardwareSerial.h>



bool button_turning(int buttonPin, int& button_counter){
  int  buttonState = digitalRead(buttonPin);
  if (buttonState == 1) {
    // turn LED on
    button_counter++;

  }  else {
    // turn LED off
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