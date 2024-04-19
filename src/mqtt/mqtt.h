#ifndef _INCLUDE_MQTT_H_
#define _INCLUDE_MQTT_H_

#include <PubSubClient.h>
#include <WiFi.h>



class MyMQTT {
private:
    String mqtt_server;
    String user;
    String password;
    WiFiClient espClient;
    PubSubClient client;
    String dataSubscribe;

public:
    MyMQTT(String server, String user, String password) 
    : mqtt_server(server), user(user), password(password), client(espClient) {
      client.setBufferSize(2048);
    }
    
    void connectToMQTT();
    void subscribe(String);
    bool publish(String, String);
    bool checkSubscribe();
    void checkConnect();
    
    String getDataSubscribe();
private:
    void callback(char*, byte*, unsigned int);
    void reConnect();
};

#endif // !_INCLUDE_MQTT_H_