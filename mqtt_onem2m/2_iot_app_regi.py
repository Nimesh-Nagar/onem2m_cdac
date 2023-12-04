from paho.mqtt import client as mqtt
import time 
import json

MQTT_BROKER = "127.0.0.1"
MQTT_PORT = 1883
QOS = 1
MQTT_TOPIC = "/oneM2M/reg_req/Sensor_App_ID/CSE_S_ID/json"

data = {
    "fr" : "Sensor_App_ID",
    "to" : "/CSE_S_ID/server",
    "rqi" : "123",
    "rvi" : "3",
    "op" : 1,
    "pc" : {
        "m2m:ae" : {
            "api": "N01.com.farm.sensor02",
            "rr" : True,
            "poa": ["mqtt://127.0.0.1:1883"],
            "srv": ["2a","3","4"],
            "rn" : "App_ae01"
            }
        },   
    "ty" : 2
}

crt_ae = json.dumps(data)

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connect to MQTT Broker ")
    else:
        print("Failed to connect code : {rc}")        

client = mqtt.Client("pub")
client.on_connect = on_connect
client.connect(MQTT_BROKER,MQTT_PORT,QOS)
client.loop_start()

client.publish(MQTT_TOPIC, crt_ae)
time.sleep(20)

