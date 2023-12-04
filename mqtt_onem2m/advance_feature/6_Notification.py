from paho.mqtt import client as mqtt
import time 
import json

MQTT_BROKER = "127.0.0.1"
MQTT_PORT = 1883
QOS = 1
MQTT_TOPIC = "/oneM2M/req/Sensor_ID/CSE_S_ID/json"

# data = {
#     "fr" : "Sensor_ID",
#     "to" : "/CSE_S_ID/server/sensor_ae01/container_02",
#     "rqi" : "123",
#     "rvi" : "3",
#     "op" : 1,
#     "pc" : {
#         "m2m:cin" : {
#             "cnf": "text/plains:1", 
#             "con": "ON"
#             }
#         },   
#     "ty" : 4
# }

data = {
    "fr" : "Sensor_ID",
    "op" : 5,
    "pc" : {
        "m2m:sgn":
        {
            "nev":{
                "rep":
                {
                    "cin":
                    {
                        "cnf" : "text/plain:1" ,
                        "con" : "ON"
                    }
                },
                "net" : [3]
                },
            "sur" : "/CSE_S_ID/Sub_ctrl_02"
        }
    },
    "rqi" : "123",
    "rvi" : "3",
    "to" : "/CSE_S_ID/server/sensor_ae01/container_02"
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
    while True:
        result = client.publish(MQTT_TOPIC,sensor_data)
        status = result[0]
        if status == 0:
            print("Message Published ")
        else:
            print(" Error to publish message ")
        time.sleep(15)

if __name__ == "__main__":
    run(sensor_data)

    