**mitsubishi2MQTT**
Use MQTT and ESP8266/ESP32 module to control Mitsubishi HVAC unit.
It use SwiCago libraries: https://github.com/SwiCago/HeatPump

***
## Features:
 - Initial config:  WIFI AP mode and web portal
 - Web interface for configuration, status and control, firmware upgrade
 - Homeassistant autodiscovery and control with MQTT
 - Control with MQTT
 - Multilanguages, user can change in SETUP->UNIT or choose in initial setup

## Screenshots:
| ![Main](https://github.com/dzungpv/mitsubishi2MQTT/blob/master/images/main_page.jpeg) | ![Control](https://github.com/dzungpv/mitsubishi2MQTT/blob/master/images/control_page.jpeg) | ![Config](https://github.com/dzungpv/mitsubishi2MQTT/blob/master/images/config_page.jpeg) |
| --------------------------------------- | --------------------------------------- | --------------------------------------- |                                
| ![Init](https://github.com/dzungpv/mitsubishi2MQTT/blob/master/images/initial_setup.jpeg) | ![Unit](https://github.com/dzungpv/mitsubishi2MQTT/blob/master/images/unit_page.jpeg) | ![Status](https://github.com/dzungpv/mitsubishi2MQTT/blob/master/images/status_page.jpeg) |


***
## How to use:
 - Step 1: Flash the sketch with flash size include SPIFFS option.
 - Step 2: Connect to device AP with name HVAC-XXXXXXXXXXXX (XXXX... 12 character MAC address)
 - Step 3: You should be automatically redirected to the web portal or go to 192.168.4.1
 - Step 4: Set Wifi information, mqtt(optional), language and save & reboot. Fall back to AP mode if WiFi connection fails (AP password sets to default SSID name from step 2).
 - Step 5: Connect to the device I with local domain: HVAC-XXXXXXXXXXXX.local
 - Step 6: (optional): Set MQTT information for use with Home Assistant
 - Step 7: (optional): Set Login password to prevent unwanted access in SETUP->ADVANCE->Login Password
 - Step 8: (optional): Turn off heat mode or quiet mode in SETUP->UNIT

Nightly builds are available for select platforms via GitHub Actions. Go to [the workflow](https://github.com/dzungpv/mitsubishi2MQTT/actions/workflows/build.yml), select the latest build, then check the **Artifacts** section. 
***
## How to build:
  - Arduino: Intall require libraries, rename file main.cpp in main folder to main.ino, open it and build
  - Platformio: Install, open it and choose a variant to build
  - ESP IDF: clone the project with --recursive tag, install [ESP IDF 4.4.6 ](https://docs.espressif.com/projects/esp-idf/en/v4.4/esp32/get-started/index.html) set the target and run command: idf.py build

***
## MQTT topic use cases
- topic/power/set OFF
- topic/mode/set AUTO HEAT COOL DRY FAN_ONLY OFF ON
- topic/temp/set 16-31
- topic/remote_temp/set also called "room_temp", the implementation defined in "HeatPump" seems not work in some models
- topic/fan/set 1-4 AUTO QUIET
- topic/vane/set 1-5 SWING AUTO
- topic/wideVane/set << < | > >>
- topic/settings
- topic/state
- topic/debug/packets
- topic/debug/packets/set on off
- topic/debug/logs
- topic/debug/logs/set on off
- topic/custom/send as example "fc 42 01 30 10 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 7b " see https://github.com/SwiCago/HeatPump/blob/master/src/HeatPump.h
- topic/system/set reboot 
***
If you like my work and use it, give a star.
