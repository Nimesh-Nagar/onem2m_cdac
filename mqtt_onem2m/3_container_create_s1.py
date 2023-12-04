from paho.mqtt import client as mqtt
import time 
import json

MQTT_BROKER = "127.0.0.1"
MQTT_PORT = 1883
QOS = 1
MQTT_TOPIC = "/oneM2M/req/Sensor_ID/CSE_S_ID/json"

data= {
    "fr" : "Sensor_ID",
    "to" : "/CSE_S_ID/server/sensor_ae01",
    "op" : 1,
    "rqi" : "123",
    "rvi" : "3",
    "pc" : {
        "m2m:cnt" : {
        "rn": "container_02"
        }
    },

    "ty" : 3
}

crt_container = json.dumps(data)

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connect to MQTT Broker ")
    else:
        print("Failed to connect code : {rc}")        


client = mqtt.Client("cnt")
client.on_connect = on_connect
client.connect(MQTT_BROKER,MQTT_PORT,QOS)
client.loop_start()

client.publish(MQTT_TOPIC, crt_container)
time.sleep(20)