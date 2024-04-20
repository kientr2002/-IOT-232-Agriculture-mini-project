#include "main.h"

void publish_data_sensor_to_mqtt(String mymqtt_feed[], int feed_size, int data_feed[]){
  if(timer1_flag == 1){
    for(int i = 0; i < feed_size; i++){
      mymqtt.publish(mymqtt_feed[i], String(data_feed[i]));
    }
    set_timer_to_publish_sensor_data(TIME_TO_PUBLISH_SENSOR_DATA);
  }
}

void publish_data_button_to_mqtt(bool button_state, bool& button_previous_state){
  if(button_previous_state != button_state){
      mymqtt.publish(mymqtt_feed[3], String(button_state));
  }
  button_previous_state = button_state;
}



void subscribe_data_button_to_mqtt(bool& button_state, bool& button_previous_state, String data){
  if(data.substring(0, 30) == "kientranvictory/feeds/button1:"){
    if(data.substring(30) == "1"){
      button_state = 1;
      button_previous_state = 1;
    } else {
      button_state = 0;
      button_previous_state = 0;      
    }
  }
}

void subscribe_data_time_to_mqtt(int& hour, int& minute, String data){
  if(data.substring(0, 27) == "kientranvictory/feeds/time:"){
    String temp_data = data.substring(27);
    int colon_index = temp_data.indexOf(':');
    hour = (temp_data.substring(0, colon_index)).toInt();
    minute = (temp_data.substring(colon_index + 1)).toInt();
  }
}

void turn_led_by_time(int current_hour, int current_minute, int hour, int minute, bool& button_state, bool& time_trigger_flag){

  if(current_hour == hour && current_minute == minute){
    button_state = BUTTON_ON;
    if(time_trigger_flag == false){
      time_trigger_flag = true;
    }
  } else {
    if(time_trigger_flag == true){
      time_trigger_flag = false;
      button_state = BUTTON_OFF;
    }
  }

}

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

  set_timer_to_publish_sensor_data(TIME_TO_PUBLISH_SENSOR_DATA); //timer to publish data (temp, humi, light) to adafruit
  set_timer_to_get_time(TIME_TO_CHECK_TIME); // timer to compare with real time and user fixed time

}

  
void loop() {
  /* initial input value */
  int data_sensor[3];
  data_sensor[0] = DHT11_temperature();  
  data_sensor[1] = DHT11_humidity();
  data_sensor[2] = lightMeter.readLightLevel();
  int current_hour = timeClient.getHours();
  int curent_minute = timeClient.getMinutes();
  String data = mymqtt.getDataSubscribe();

  turn_led_by_time(current_hour, curent_minute, hour, minute, button_state, time_trigger_flag);
  
  button_state = change_state_button(button_state, button_turning(BUTTONPIN, button_counter));
  
  led_state = change_led_state(button_state, data_sensor[2], led_trigger_flag);

  /* Publish to MQTT */
  publish_data_sensor_to_mqtt(mymqtt_feed, sizeof(data_sensor)/sizeof(int), data_sensor);
  publish_data_button_to_mqtt(button_state, button_previous_state);

  /* Subscribe to MQTT */
  subscribe_data_button_to_mqtt(button_state, button_previous_state, data);
  subscribe_data_time_to_mqtt(hour, minute, data);
  /* Output function */
  led_turning(led_state, REDPIN, BLUEPIN, GREENPIN);

  
  mymqtt.checkConnect();
  timeClient.update();
  timerRun();
}