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

  /* Connect Wifi */
  setup_wifi(mywifi_username, mywifi_password);

  /* Connect to Time Server*/

  timeClient.begin();

  /* Connect MQTT */

  mymqtt.connectToMQTT();
  mymqtt.checkConnect();
   
  for(int i = 0; i < num_of_mqtt; i++){
    mymqtt.subscribe(mymqtt_feed[i]);
  }

  

}

  
void loop() {
  /* initial input value */
  float temperature_value = DHT11_temperature();  
  float humidity_value = DHT11_humidity();
  float light_value = lightMeter.readLightLevel();
  button_state = change_state_button(button_state, button_turning(BUTTONPIN, button_counter));
  led_state = change_led_state(button_state, light_value);
  /* Output function */
  led_turning(led_state, REDPIN, BLUEPIN, GREENPIN);
  mymqtt.checkConnect();
}