#ifndef _INCLUDE_DHT11_H_
#define _INCLUDE_DHT11_H_
#include <DHT.h>

extern DHT* dht;
void init_DHT11(int pin, uint8_t type);
float DHT11_temperature();
float DHT11_humidity();

#endif // !_INCLUDE_DHT11_H_