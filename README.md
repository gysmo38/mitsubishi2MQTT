# mitsubishi2MQTT
Use MQTT and  ESP8266 module to control Mitsubishi HVAC unit.
It use SwiCago librairies: https://github.com/SwiCago/HeatPump

***
Features:
Initial config with WIFI AP mode and portal
Control unit with webinterface
Configuration MQTT
Control with MQTT
Homeassistant autodiscovery with MQTT

***
Screenshots:

Main Page
![](https://github.com/gysmo38/mitsubishi2MQTT/blob/master/images/main_page.png)

Control page
![](https://github.com/gysmo38/mitsubishi2MQTT/blob/master/images/control_page.png)

Config page
![](https://github.com/gysmo38/mitsubishi2MQTT/blob/master/images/config_page.png)

***
How to use:
Flash the sketch with flash size include SPIFFS option.
After flash, connect to device AP with name HVAC_XXXX (XXXX last 4 character MAC address), enter 192.168.1.1 and set Wifi information, save & reboot
Set MQTT information for use with Home Assistant (Optinal), find the device IP with last 4 character MAC address in your router
