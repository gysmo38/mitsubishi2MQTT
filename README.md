# mitsubishi2MQTT
Use MQTT and ESP8266/ESP32 module to control Mitsubishi HVAC unit.
It use SwiCago libraries: https://github.com/SwiCago/HeatPump

***
Features:
 - Initial config:  WIFI AP mode and web portal
 - Web interface for configuration, status and control, firmware upgrade
 - Homeassistant autodiscovery and control with MQTT
 - Control with MQTT
 - Multilanguages

Screenshots:

![Main page](https://github.com/gysmo38/mitsubishi2MQTT/blob/master/images/main_page.png)

![](https://github.com/gysmo38/mitsubishi2MQTT/blob/master/images/control_page.png)

![](https://github.com/gysmo38/mitsubishi2MQTT/blob/master/images/config_page.png)

***
How to use:
 - Step 1: flash the sketch with flash size include SPIFFS option.
 - Step 2: connect to device AP with name HVAC_XXXX (XXXX last 4 character MAC address)
 - Step 3: You should be automatically redirected to the web portal or go to 192.168.1.1
 - Step 4: set Wifi information, save & reboot. Fall back to AP mode if WiFi connection fails (AP password sets to default SSID name from step 2).
 - Step 5: find the device IP with last 4 character MAC address in your router
 - Step 6: (optional): Set MQTT information for use with Home Assistant
 - Step 7: (optional): Set Login password to prevent unwanted access in SETUP->ADVANCE->Login Password

Nightly builds are available for select platforms via GitHub Actions. Go to [the platformio workflow](https://github.com/gysmo38/mitsubishi2MQTT/actions/workflows/platformio.yml), select the latest build, then check the **Artifacts** section. 

***
For nodered fans MQTT topic use cases
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
# Grafana dashboard
To use Grafana you need to have Prometheus and Grafana (v10 or newer) installed.
Config for Prometheus:
```  - job_name: Mitsubishi2mqtt
    static_configs:
        - targets:
            - IP-TO-Mitsubishi2mqtt
```
Then add Prometheus as a datasource in Grafana
Grafana -> Connections -> Add new connection -> Prometheus -> ```Prometheus server URL: PROMETHEUS-IP:PORT```

Then you can import the dashboard in Grafana -> Dashboards -> New -> Import and upload the file https://github.com/gysmo38/mitsubishi2MQTT/blob/master/Mitsubishi2mqtt.json

![](https://github.com/gysmo38/mitsubishi2MQTT/blob/master/images/Grafana-screenshot.png)

If you like my work and use it ;)<br>

<a href='https://ko-fi.com/L3L0GSF7X' target='_blank'><img height='36' style='border:0px;height:36px;' src='https://storage.ko-fi.com/cdn/kofi2.png?v=3' border='0' alt='Buy Me a Coffee at ko-fi.com' /></a>
