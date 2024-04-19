#ifndef _INCLUDE_MAIN_H_
#define _INCLUDE_MAIN_H_

#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "led/led.h"
#include "DHT11/dht11.h"
#include "button/button.h"
#include "wifi/wifi.h"
#include "mqtt/mqtt.h"
#include "software_timer/software_timer.h"




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

#define TIME_TO_PUBLISH_SENSOR_DATA 30
#define TIME_TO_CHECK_TIME 60





extern int button_counter = 0;

extern bool button_state = BUTTON_OFF;

extern bool button_previous_state = button_state;

extern bool led_state = LED_OFF;

extern bool led_previous_state = led_state;

extern bool subscribe_flag = false;

extern int hour = 0;

extern int minute = 0;

extern bool time_trigger_flag = false;

struct SubscribedData {
    String topic;
    String payload;
};


DHT* dht;
BH1750 lightMeter;

//MQTT configuration
const char* mymqtt_server = "io.adafruit.com";
const int mymqtt_port = 1883;
const char* mymqtt_username = "kientranvictory";
const char* mymqtt_password = "";
String mymqtt_feed[] = {"kientranvictory/feeds/sensor1", "kientranvictory/feeds/sensor2", "kientranvictory/feeds/sensor3", "kientranvictory/feeds/button1", "kientranvictory/feeds/time"};
SubscribedData mymqtt_feed_subscribe[] = {
    {"kientranvictory/feeds/sensor1", ""},
    {"kientranvictory/feeds/sensor2", ""},
    {"kientranvictory/feeds/sensor3", ""},
    {"kientranvictory/feeds/button1", ""},
    {"kientranvictory/feeds/time", ""},
    
};
int num_of_mqtt = sizeof(mymqtt_feed)/sizeof(String);

MyMQTT mymqtt(mymqtt_server, mymqtt_username, mymqtt_password);




//WIFI configuration
const char* mywifi_username = "Siuuuuuuu";
const char* mywifi_password = "";


//Time getting
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200, 60000);

#endif // !_INCLUDE_MAIN_H_