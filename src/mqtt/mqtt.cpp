#include "mqtt.h"


void MyMQTT::connectToMQTT() {
    client.setServer(mqtt_server.c_str(), 1883);
    reConnect();
    client.setCallback([this](char* topic, byte* payload, unsigned int length) {
        this->callback(topic, payload, length);
    });
}

void MyMQTT::subscribe(String feedName) {
#ifdef ADAFRUIT
    String topic = user + "/feeds/" + feedName;
#endif
    Serial.println(feedName);
    String topic = feedName;
    client.subscribe(topic.c_str());
}

bool MyMQTT::publish(String feedName, String message) {
#ifdef ADAFRUIT
    String topic = user + "/feeds/" + feedName;
#endif
    String topic = feedName;
    Serial.print("Publishing to topic: ");
    Serial.println(feedName);
    Serial.print("Status: ");
    if(client.publish(topic.c_str(), message.c_str(),1)){
      Serial.println("Success!");
    //   delay(5000);
      return 1;
    }
    Serial.println("Failed!");
    // delay(5000);
    return 0;
}

void MyMQTT::checkConnect(){
    if (!client.connected()) {
        Serial.println("MQTT Connection lost!");
        reConnect();
    }
    client.loop();
}

void MyMQTT::callback(char* topic, byte* payload, unsigned int length) {
    // Your callback implementation here
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    dataSubscribe = topic;
    dataSubscribe += ":";
    for (int i = 0; i < length; i++) {
        dataSubscribe += (char)payload[i];
    }
    Serial.println(dataSubscribe);

}

void MyMQTT::reConnect() {
    while (!client.connected()) {
        int randomNumber = random(0, 101);
        char clientId[4]; // Allocate space for 3 digits plus null terminator
        snprintf(clientId, sizeof(clientId), "%d", randomNumber);
        Serial.print("Attempting MQTT connection...");
        if (client.connect(clientId, user.c_str(), password.c_str())) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

String MyMQTT::getDataSubscribe(){
  String tempDataSubscribe = dataSubscribe;
  dataSubscribe = "";
  return tempDataSubscribe;
}