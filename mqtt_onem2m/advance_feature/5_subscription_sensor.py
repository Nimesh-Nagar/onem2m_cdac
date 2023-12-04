from paho.mqtt import client as mqtt
import time 
import json

MQTT_BROKER = "127.0.0.1"
MQTT_PORT = 1883
QOS = 1
MQTT_TOPIC = "/oneM2M/req/Sensor_ID/CSE_S_ID/json"

data = {
    "fr" : "Sensor_ID",
    "to" : "/CSE_S_ID/server/sensor_ae01/container_02",
    "rqi" : "123",
    "rvi" : "3",
    "op" : 1,
    "pc" : {
        "m2m:sub" : {
            "rn":"Sub_ctrl_02",
            "enc": {
                "net": [3]
            },
            "nu":["Sensor_ID"],
            "nct":1
            # "exc":1
        }
    },   
    "ty" : 23
}

sensor_data = json.dumps(data)

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connect to MQTT Broker ")
    else:
        print("Failed to connect code : {rc}") 

def run(sensor_data):
    client = mqtt.Client()
    client.on_connect = on_connect
    client.connect(MQTT_BROKER,MQTT_PORT,QOS)
    client.loop_start()
    
    result = client.publish(MQTT_TOPIC,sensor_data)
    status = result[0]
    if status == 0:
        print("Message Published ")
    else:
        print(" Error to publish message ")
    time.sleep(10)

if __name__ == "__main__":
    run(sensor_data)

    