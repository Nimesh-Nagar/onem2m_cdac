from paho.mqtt import client as mqtt
import time

MQTT_BROKER = "127.0.0.1"
MQTT_PORT = 1883
QOS = 1
# MQTT_TOPIC = "/oneM2M/resp/CSE_S_ID/+/#"
MQTT_TOPIC = "/oneM2M/req/Sensor_ID/CSE_S_ID/json"

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker")
    else:
        print("Connection Failed with code "+str(rc))

def on_message(client, userdata, message):
    print("RESPONCE FROM OneM2M : ")
    print(message.payload.decode("utf-8"))   

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
# client.username_pw_set(USERNAME, PASSWORD)
client.connect(MQTT_BROKER,MQTT_PORT)
client.loop_start()

client.subscribe(MQTT_TOPIC)
time.sleep(20)