-- (https://github.com/kuviyam/IoT-projects/nodeMCU-MQTT-Example)
-- This project uses BME280 sensor + Buzzer + nodeMCU + mqtt + mqtt dashboard android app

-- Message formats
-- UP   -> {"pressure":"1003.3","temperature":"25.4", "humidity":"65.1"}
-- DOWN -> {"buzzer":"1"}
-- Change MQTT Settings

BUZZER = 3
gpio.mode(BUZZER, gpio.OUTPUT)  -- set buzzer pin and configure as output

-- mqtt configuration
mqtt_host = "broker.hivemq.com"
mqtt_port = 1883
publish_topic = "kuviyam/chandrasekar/up"
subscribe_topic = "kuviyam/chandrasekar/down"
client_id = "s4jr8"  -- must be unique

m = mqtt.Client(client_id, 120)
m:lwt("/lwt", "offline", 0, 0)
m:on("connect", function(client) print ("connected") end)
m:on("offline", function(client) print ("offline") end)

-- on message receive event
m:on("message", function(client, topic, data)
    print(topic .. ":" )
    if data ~= nil then
        print(data)
        local payload = string.match(data, "{.*}")
        print(payload)
        local t = sjson.decode(payload)
        if t.buzzer == '1' then                     -- switch on buzzer
            print("ON")
            gpio.write(BUZZER, gpio.HIGH)
        else if t.buzzer == '0' then                -- switch off buzzer
            print("OFF")
            gpio.write(BUZZER, gpio.LOW)
        end
    end
  end
end)

-- on connect event
m:connect(mqtt_host, mqtt_port, 0, function(client)
    print("connected")
    client:subscribe(subscribe_topic, 0, function(client) print("subscribed") end)
    end,
    function(client, reason)
        print("failed reason: " .. reason)
    end)
        tmr.alarm(2, 3000, tmr.ALARM_AUTO, function()
        sda, scl = 2, 1
        i2c.setup(0, sda, scl, i2c.SLOW)
        bme280.setup()
        temp_raw, press_raw, humi_raw = bme280.read(alt)  --read bme sensor data
        temp = temp_raw*0.01
        press = press_raw*0.001
        humi = humi_raw*0.001
        updata = '{"pressure":"'..press..'","temperature":"'..temp..'", "humidity":"'..humi..'"}'

        -- publish BME sensor data every 3 seconds
        m:publish(publish_topic, updata, 0, 0, function(client) print("sent") end)
        print("sent" .. updata)
        button = 0
end)

m:close();
