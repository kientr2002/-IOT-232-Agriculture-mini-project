#include "dht11.h"


void init_DHT11(int pin, uint8_t type){
  
  dht = new DHT(pin,type);
  dht->begin();
}

float DHT11_temperature(){
  float t = isnan((*dht).readTemperature()) ? 0 : (*dht).readTemperature();
  return t;
}

float DHT11_humidity(){
  float h = isnan((*dht).readHumidity()) ? 0 : (*dht).readHumidity();
  return h;
}
