package com.example.ui_miniproject;


import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.TextView;

import com.github.angads25.toggle.interfaces.OnToggledListener;
import com.github.angads25.toggle.model.ToggleableView;
import com.github.angads25.toggle.widget.LabeledSwitch;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallbackExtended;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.nio.charset.Charset;

public class MainActivity extends AppCompatActivity {
    MQTTHelper mqttHelper;
    TextView txtTemp, txtHumi, txtLight, txtTime, txtTimeSubscribe;
    LabeledSwitch btnLED;
    Button btnSubmit;
    @Override

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        txtTemp = findViewById(R.id.txtTemprature);
        txtHumi = findViewById(R.id.txtHumidity);
        txtLight = findViewById(R.id.txtLight);
        txtTime = findViewById(R.id.txtTime);
        txtTimeSubscribe = findViewById(R.id.txtTimeSubscribe);

        btnLED = findViewById(R.id.btnLED);
        btnSubmit = findViewById(R.id.btnSubmit);
        btnLED.setOnToggledListener(new OnToggledListener() {
            @Override
            public void onSwitched(ToggleableView toggleableView, boolean isOn) {
                if(isOn == true){
                    sendDataMQTT("kientranvictory/feeds/button1", "1");
                } else {
                    sendDataMQTT("kientranvictory/feeds/button1", "0");
                }
            }
        });


        startMQTT();

    }
    public void sendDataMQTT(String topic, String value){
        MqttMessage msg = new MqttMessage();
        msg.setId(1234);
        msg.setQos(0);
        msg.setRetained(false);

        byte[] b = value.getBytes(Charset.forName("UTF-8"));
        msg.setPayload(b);

        try {
            mqttHelper.mqttAndroidClient.publish(topic, msg);
        }catch (MqttException e){
        }
    }
    public void startMQTT(){
        mqttHelper = new MQTTHelper(this);
        mqttHelper.setCallback(new MqttCallbackExtended() {
            @Override
            public void connectComplete(boolean reconnect, String serverURI) {

            }

            @Override
            public void connectionLost(Throwable cause) {

            }

            @Override
            public void messageArrived(String topic, MqttMessage message) throws Exception {
                Log.d("Test", topic + "===" + message.toString());
                if(topic.contains("sensor1")){ //
                    txtTemp.setText(message.toString() + "°C");
                } else if(topic.contains("sensor2")){
                    txtHumi.setText(message.toString()+"%");
                } else if(topic.contains("sensor3")){
                    txtLight.setText(message.toString()+"lx");
                } else if(topic.contains("time")){
                    txtTime.setText(message.toString());
                } else if(topic.contains(("button1"))){
                    if(message.toString().equals("1")){
                        btnLED.setOn(true);
                    } else if (message.toString().equals("0")){
                        btnLED.setOn(false);
                    }
                }
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken token) {

            }
        });
    }
}