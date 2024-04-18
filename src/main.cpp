#include "main.h"



void setup() {
  /*initialize the pushbutton pin as an input*/
  pinMode(BUTTONPIN, INPUT);
  pinMode(REDPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);

  /* init source */
  Serial.begin(115200);  
  Wire.begin();
  lightMeter.begin();
  init_DHT11(DHTPIN, DHTTYPE);

}

  
void loop() {
  /* initial input value */
  float temperature_value = DHT11_temperature();  
  float humidity_value = DHT11_humidity();
  float light_value = lightMeter.readLightLevel();
  if(button_turning(BUTTONPIN, button_counter) == true){
    led_turning(LED_ON, REDPIN, BLUEPIN, GREENPIN);
    Serial.println(String(temperature_value) + ":" + String(humidity_value) + ":" + String(light_value) + ":" + "LED ON");
    delay(2000);
  } else {
    led_turning(LED_OFF, REDPIN, BLUEPIN, GREENPIN);
  }

}