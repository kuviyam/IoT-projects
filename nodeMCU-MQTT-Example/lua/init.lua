-- (https://github.com/kuviyam/IoT-projects/nodeMCU-MQTT-Example)
-- This file will execute first in nodeMCU
-- it will try to connect to wifi and execute main.lua if connection succeed
-- ## set correct ssid and password of your wifi router AP

if true then
    print("set up wifi mode")
    wifi.setmode(wifi.STATION)
    wifi.sta.config {ssid="hackday", pwd="hackday975"}     --config ssid and password.
    wifi.sta.connect()
    cnt = 0
    tmr.alarm(1, 3000, 1, function()
        if (wifi.sta.getip() == nil) and (cnt < 20) then
            print("IP unavaiable, Waiting...")
            cnt = cnt + 1
        else
            tmr.stop(1)
            if (cnt < 20) then print("Config done, IP is "..wifi.sta.getip())
            dofile("main.lua")
            else print("Wifi setup time more than 20s")
            end
        end
     end)
else
    print("\n")
    print("Failed connecting to hotspot")
end
