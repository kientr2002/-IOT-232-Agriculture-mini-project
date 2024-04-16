/*
  Example of BH1750 library usage. This example initialises the BH1750 object using the default high resolution continuous mode and then makes a light level reading every second.
*/

#include <Wire.h>
#include <BH1750.h>

// BH1750 lightMeter;
// int redpin = 27; // select the pin for the red LED
// int bluepin =26; // select the pin for the  blue LED
// int greenpin =25; // select the pin for the green LED

// void setup(){
//   Serial.begin(115200);
//   pinMode(redpin, OUTPUT);
//   pinMode(bluepin, OUTPUT);
//   pinMode(greenpin, OUTPUT);
//   // Initialize the I2C bus (BH1750 library doesn't do this automatically)
//   Wire.begin();
//   // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
//   // For Wemos / Lolin D1 Mini Pro and the Ambient Light shield use Wire.begin(D2, D1);

//   lightMeter.begin();


//   Serial.println(F("BH1750 Test begin"));
// }

// int lightSensorToLED(float lux_value){
//   if(lux_value < 1){
//     return 1;
//   } else {
//     return 0;
//   }
// }

// void LedValue(int val){
//   switch (val)
//   {
//   case 1:
//     /* code */
//     analogWrite(27, 0);
//     analogWrite(25, 0);  
//     break;
//   case 0:
//     analogWrite(27, 0);
//     analogWrite(25, 0);  
//     break;
//   default:
//     break;
//   }

// }

// void loop() {
//   float lux_value = lightMeter.readLightLevel(); 
//   int LED_State = lightSensorToLED(lux_value);

//   Serial.println(lux_value);
//   LedValue(LED_State);

//   delay(1000);
// }


int DHpin = 17; // input/output pin

byte dat[5];

byte read_data()

{

byte i = 0;

byte result = 0;

for (i = 0; i < 8; i++) {

while (digitalRead(DHpin) == LOW); // wait 50us

delayMicroseconds(30); //The duration of the high level is judged to determine whether the data is '0' or '1'

if (digitalRead(DHpin) == HIGH)

result |= (1 << (8 - i)); //High in the former, low in the post

while (digitalRead(DHpin) == HIGH); //Data '1', waiting for the next bit of reception

}

return result;

}

void start_test()

{

digitalWrite(DHpin, LOW); //Pull down the bus to send the start signal

delay(30); //The delay is greater than 18 ms so that DHT 11 can detect the start signal

digitalWrite(DHpin, HIGH);

delayMicroseconds(40); //Wait for DHT11 to respond

pinMode(DHpin, INPUT);

while(digitalRead(DHpin) == HIGH);

delayMicroseconds(80); //The DHT11 responds by pulling the bus low for 80us;

if(digitalRead(DHpin) == LOW)

delayMicroseconds(80); //DHT11 pulled up after the bus 80us to start sending data;

for(int i = 0; i < 5; i++) //Receiving temperature and humidity data, check bits are not considered;

dat[i] = read_data();

pinMode(DHpin, OUTPUT);

digitalWrite(DHpin, HIGH); //After the completion of a release of data bus, waiting for the host to start the next signal

}

void setup()

{

Serial.begin(115200);

pinMode(DHpin, OUTPUT);

}

void loop()

{

start_test();

Serial.print("Humdity = ");

Serial.print(dat[0], DEC); //Displays the integer bits of humidity;

Serial.print('.');

Serial.print(dat[1], DEC); //Displays the decimal places of the humidity;

Serial.println('%');

Serial.print("Temperature = ");

Serial.print(dat[2], DEC); //Displays the integer bits of temperature;

Serial.print('.');

Serial.print(dat[3], DEC); //Displays the decimal places of the temperature;

Serial.println('C');

byte checksum = dat[0] + dat[1] + dat[2] + dat[3];

if (dat[4] != checksum)

Serial.println("– Checksum Error!");

else

Serial.println("– OK");

delay(1000);

}