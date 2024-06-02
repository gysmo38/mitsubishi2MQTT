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

const PROGMEM char* m2mqtt_version = "Mitsubishi2MQTT - magi's edition (2024.5.1)";

//Define global variables for files
#ifdef ESP32
const PROGMEM char* wifi_conf = "/wifi.json";
const PROGMEM char* mqtt_conf = "/mqtt.json";
const PROGMEM char* unit_conf = "/unit.json";
const PROGMEM char* console_file = "/console.log";
const PROGMEM char* others_conf = "/others.json";
const PROGMEM char* energy_file = "/energy.json";
#else
const PROGMEM char* wifi_conf = "wifi.json";
const PROGMEM char* mqtt_conf = "mqtt.json";
const PROGMEM char* unit_conf = "unit.json";
const PROGMEM char* console_file = "console.log";
const PROGMEM char* others_conf = "others.json";
const PROGMEM char* energy_file = "energy.json";
#endif

// Define global variables for network
const PROGMEM char* hostnamePrefix = "HVAC_";
const PROGMEM uint32_t WIFI_RETRY_INTERVAL_MS = 300000;
unsigned long wifi_timeout;
bool wifi_config_exists;
String hostname = "";
String ap_ssid;
String ap_pwd;
String ota_pwd;

//CN105Kit Product version
#ifdef __ESP32S3__
const PROGMEM char* hardware_version = "WiFiKit Serial 1.2";
#elif defined(__ESP07__) 
const PROGMEM char* hardware_version = "CN105Kit V2 (ESP07)";
#elif defined(__ESP12E__) 
const PROGMEM char* hardware_version = "CN105Kit V1/V2.1 (ESP12E)";

#endif

// Define global variables for MQTT
String mqtt_fn;
String mqtt_server;
String mqtt_port;
String mqtt_username;
String mqtt_password;
String mqtt_topic = "mitsubishi2mqtt";
String mqtt_client_id;
const PROGMEM char* mqtt_payload_available = "online";
const PROGMEM char* mqtt_payload_unavailable = "offline";

//icons
const PROGMEM char* HA_AC_icon = "mdi:air-conditioner";
const PROGMEM char* HA_thermometer_icon = "mdi:thermometer";
const PROGMEM char* HA_lightning_bolt = "mdi:lightning-bolt-circle";
const PROGMEM char* HA_counter = "mdi:counter";
const PROGMEM char* HA_restart = "mdi:restart";
const PROGMEM char* HA_vane_vertical_icon = "mdi:arrow-up-down";
const PROGMEM char* HA_vane_horizontal_icon = "mdi:arrow-left-right";

//Define global variables for Others settings
bool others_haa;
bool others_avail_report;
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
String ha_climate_config_topic;
String ha_sensor_room_temp_config_topic;
String ha_sensor_power_config_topic;
String ha_sensor_energy_config_topic;
String ha_select_vane_vertical_config_topic;
String ha_select_vane_horizontal_config_topic;
String ha_button_reset_energy_config_topic;
String ha_button_energy_set_topic;
String ha_discovery_topic;
String ha_custom_packet;
String ha_availability_topic;
String hvac_name;

//login
String login_username = "admin";
String login_password;

// debug mode, when true, will send all packets received from the heatpump to topic heatpump_debug_topic
// this can also be set by sending "on" to heatpump_debug_set_topic
bool _debugMode = false;

// sketch settings
const PROGMEM uint32_t SEND_ROOM_TEMP_INTERVAL_MS = 15000; // 15 seconds (anything less than 45 seconds may cause problems, but it's faster.)
const PROGMEM uint32_t POLL_DELAY_AFTER_SET_MS = 35000; // After send command, wait at least 35 seconds for A/C to update status.
const PROGMEM uint32_t MQTT_RETRY_INTERVAL_MS = 1000; // 1 seconds
const PROGMEM uint32_t HP_RETRY_INTERVAL_MS = 1000; // 1 seconds
const PROGMEM uint32_t HP_MAX_RETRIES = 10; // Double the interval between retries up to this many times, then keep retrying forever at that maximum interval.
// Default values give a final retry interval of 1000ms * 2^10, which is 1024 seconds, about 17 minutes. 


// Customization
uint8_t min_temp                    = 16; // Minimum temperature, check value from heatpump remote control
uint8_t max_temp                    = 31; // Maximum temperature, check value from heatpump remote control
String temp_step                    = "1"; // Temperature setting step, check value from heatpump remote control
uint32_t update_int                 = SEND_ROOM_TEMP_INTERVAL_MS;

//Energy
#define ENERGY_SAVE_THRESHOLD 0.1 //Save energy only if the value differentiate from previous value X kWh.
#define ENERGY_SAVE_INTERVAL 10 //Save energy every 10 minutes


// temp settings
bool useFahrenheit = false;
// support heat mode settings, some model do not support heat mode
bool supportHeatMode = true;

// Languages
#include "languages/en-GB.h" // default language English

//IOs
#ifdef ESP32
  #define LED_PWR 5
  #define LED_ACT 6
  #define BTN_1 0
  #define BUZZER 14
  #define BUZZER_FREQ 4000
  #define LED_ON      HIGH
  #define LED_OFF     LOW
#endif

#ifdef ESP8266
  #define LED_ACT 2
  #define LED_ON      LOW
  #define LED_OFF     HIGH
#endif

//Buzzer settings
enum Buzzer_preset{
  ON,
  SET,
  OFF
};
bool beep = true;