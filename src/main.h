#ifndef _INCLUDE_MAIN_H_
#define _INCLUDE_MAIN_H_

#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>


#include "led/led.h"
#include "DHT11/dht11.h"
#include "button/button.h"


#define REDPIN  27 // select the pin for the red LED
#define BLUEPIN 26 // select the pin for the  blue LED
#define GREENPIN 25 // select the pin for the green LED
#define DHTPIN 32     // what digital pin the DHT sensor is connected to
#define DHTTYPE DHT11   // there are multiple kinds of DHT sensors
#define BUTTONPIN 17  // the number of the pushbutton pin

#define LED_ON true
#define LED_OFF false

#define BUTTON_ON true
#define BUTTON_OFF false

#define BUTTON_TRIGGER true

#define DEBOUNCE_TIME 2000




extern int button_counter = 0;
extern bool button_state = BUTTON_ON;

extern bool led_state = LED_OFF;
extern bool led_trigger_button_flag = false;

DHT* dht;
BH1750 lightMeter;


#endif // !_INCLUDE_MAIN_H_