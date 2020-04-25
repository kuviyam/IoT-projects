# Arduino piano MQTT SUB
import os
import paho.mqtt.client as mqtt
import pysynth as ps

MQTT_BROKER = "mqtt.eclipse.org"
MQTT_PORT = 1883
MQTT_SUB_TOPIC = "kuviyam/chandrasekar/piano"

def play_sound(duration, note):
    freq = float(ps.getfreq()[0][note])
    print(note)
    os.system('play -nq -t alsa synth {} sine {} &'.format(duration, freq))
    # sudo apt install sox

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe(MQTT_SUB_TOPIC)


def on_message(client, userdata, msg):
    play_sound(0.1, msg.payload.decode('utf-8'))

if __name__ == "__main__":
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(MQTT_BROKER, MQTT_PORT, 60)
    client.loop_forever()
