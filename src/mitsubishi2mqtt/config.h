/*
  mitsubishi2mqtt - Mitsubishi Heat Pump to MQTT control for Home Assistant.
  Copyright (c) 2019 gysmo38, dzungpv, shampeon, endeavour, jascdk, chrdavis, alekslyse.  All right reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

//#define MY_LANGUAGE fr-FR // define your language

const PROGMEM char* m2mqtt_version = "0.7.3";

//Define global variables for files
#ifdef ESP32
const PROGMEM char* wifi_conf = "/wifi.json";
const PROGMEM char* mqtt_conf = "/mqtt.json";
const PROGMEM char* advance_conf = "/advance.json";
const PROGMEM char* console_file = "/console.log";
const PROGMEM char* others_conf = "/others.json";
// pinouts
const PROGMEM  uint8_t blueLedPin = 2;            // The ESP32 has an internal blue LED at D2 (GPIO 02)
#else
const PROGMEM char* wifi_conf = "wifi.json";
const PROGMEM char* mqtt_conf = "mqtt.json";
const PROGMEM char* unit_conf = "unit.json";
const PROGMEM char* console_file = "console.log";
const PROGMEM char* others_conf = "others.json";
// pinouts
const PROGMEM  uint8_t blueLedPin = LED_BUILTIN; // Onboard LED = digital pin 2 "D4" (blue LED on WEMOS D1-Mini)
#endif
const PROGMEM  uint8_t redLedPin = 0;

// Define global variables for network
const PROGMEM char* hostnamePrefix = "HVAC_";
const PROGMEM uint32_t WIFI_RETRY_INTERVAL_MS = 300000;
int wifi_timeout;
bool wifi_config_exists;
String hostname = "";
String ap_ssid;
String ap_pwd;
String ota_pwd;

// Define global variables for MQTT
String mqtt_fn;
String mqtt_server;
String mqtt_port;
String mqtt_username;
String mqtt_password;
String mqtt_topic = "mitsubishi2mqtt";
String mqtt_client_id;

//Define global variables for Others settings
bool others_haa;
String others_haa_topic;

// Define global variables for HA topics
String ha_power_set_topic;
String ha_mode_set_topic;
String ha_temp_set_topic;
String ha_remote_temp_set_topic;
String ha_fan_set_topic;
String ha_vane_set_topic;
String ha_wideVane_set_topic;
String ha_settings_topic;
String ha_state_topic;
String ha_debug_topic;
String ha_debug_set_topic;
String ha_config_topic;
String ha_discovery_topic;
String ha_custom_packet;
String hvac_name;

//login
String login_username = "admin";
String login_password;

// debug mode, when true, will send all packets received from the heatpump to topic heatpump_debug_topic
// this can also be set by sending "on" to heatpump_debug_set_topic
bool _debugMode = false;

// Customization
uint8_t min_temp                    = 16; // Minimum temperature, check value from heatpump remote control
uint8_t max_temp                    = 31; // Maximum temperature, check value from heatpump remote control
String temp_step                   = "1"; // Temperature setting step, check value from heatpump remote control

// sketch settings
const PROGMEM uint32_t SEND_ROOM_TEMP_INTERVAL_MS = 45000; // 45 seconds (anything less may cause bouncing)
const PROGMEM uint32_t MQTT_RETRY_INTERVAL_MS = 1000; // 1 seconds
const PROGMEM uint32_t HP_RETRY_INTERVAL_MS = 1000; // 1 seconds
const PROGMEM uint32_t HP_MAX_RETRIES = 5;

// temp settings
bool useFahrenheit = false;
// support heat mode settings, some model do not support heat mode
bool supportHeatMode = true;
