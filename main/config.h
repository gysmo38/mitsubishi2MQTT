/*
  mitsubishi2mqtt - Mitsubishi Heat Pump to MQTT control for Home Assistant.
  Copyright (c) 2023 gysmo38, dzungpv, shampeon, endeavour, jascdk, chrdavis, alekslyse.  All right reserved.
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

const PROGMEM char* m2mqtt_version = "2023.8.0";

//Define global variables for files
#ifdef ESP32
const PROGMEM char* wifi_conf = "/wifi.json";
const PROGMEM char* mqtt_conf = "/mqtt.json";
const PROGMEM char* unit_conf = "/unit.json";
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
unsigned long wifi_timeout;
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
const PROGMEM char* mqtt_payload_available = "online";
const PROGMEM char* mqtt_payload_unavailable = "offline";

//Define global variables for Others settings
bool others_haa;
String others_haa_topic;

// Define global variables for HA topics
String ha_system_set_topic;
String ha_mode_set_topic;
String ha_temp_set_topic;
String ha_remote_temp_set_topic;
String ha_fan_set_topic;
String ha_vane_set_topic;
String ha_wideVane_set_topic;
String ha_settings_topic;
String ha_state_topic;
String ha_debug_pckts_topic;
String ha_debug_pckts_set_topic;
String ha_debug_logs_topic;  
String ha_debug_logs_set_topic;
String ha_config_topic;
String ha_discovery_topic;
String ha_custom_packet;
String ha_availability_topic;
String hvac_name;

//login
String login_username = "admin";
String login_password;

// debug mode logs, when true, will send all debug messages to topic heatpump_debug_logs_topic
// this can also be set by sending "on" to heatpump_debug_set_topic
bool _debugModeLogs = false;
// debug mode packets, when true, will send all packets received from the heatpump to topic heatpump_debug_packets_topic
// this can also be set by sending "on" to heatpump_debug_set_topic
bool _debugModePckts = false;

// Customization
uint8_t min_temp                    = 16; // Minimum temperature, in your selected unit, check value from heatpump remote control
uint8_t max_temp                    = 31; // Maximum temperature, in your selected unit, check value from heatpump remote control
String temp_step                   = "1"; // Temperature setting step, check value from heatpump remote control

// sketch settings
const PROGMEM uint32_t SEND_ROOM_TEMP_INTERVAL_MS = 30000; // 45 seconds (anything less may cause bouncing)
const PROGMEM uint32_t CHECK_REMOTE_TEMP_INTERVAL_MS = 300000; //5 minutes
const PROGMEM uint32_t MQTT_RETRY_INTERVAL_MS = 1000; // 1 second
const PROGMEM uint32_t HP_RETRY_INTERVAL_MS = 1000; // 1 second
const PROGMEM uint32_t HP_MAX_RETRIES = 10; // Double the interval between retries up to this many times, then keep retrying forever at that maximum interval.
// Default values give a final retry interval of 1000ms * 2^10, which is 1024 seconds, about 17 minutes. 

// temp settings
bool useFahrenheit = false;
// support heat mode settings, some model do not support heat mode
bool supportHeatMode = true;

// Multi language support, all store in the flash, just change in the Unit settings
byte system_language_index = 0; // default language index 0:en
// #define MITSU2MQTT_EN_ONLY 1   // un comment to enable English only for debug 
#include "language_util.h" // Multi languages support

// Languages supported. Note: the order is important and must match locale_translations.h
#if defined(MITSU2MQTT_TEST) || defined(MITSU2MQTT_EN_ONLY)
// in Debug mode use one language (en) to save flash memory needed for the tests
const char *const languages[] = {MITSU2MQTT_LOCALE_EN};
const char *const language_names[] = {"English"};
#elif defined(MITSU2MQTT_VI_ONLY)
const char *const languages[] = {MITSU2MQTT_LOCALE_VI};
const char *const language_names[] = {"Tiếng Việt"};
#else
const char *const languages[] = {
    MITSU2MQTT_LOCALE_EN,
    MITSU2MQTT_LOCALE_VI,
    // MITSU2MQTT_LOCALE_DE,
    // MITSU2MQTT_LOCALE_ES,
    // MITSU2MQTT_LOCALE_FR,
    // MITSU2MQTT_LOCALE_IT,
    // MITSU2MQTT_LOCALE_JA,
    // MITSU2MQTT_LOCALE_ZH
};
const char *const language_names[] = {
    "English",
    "Tiếng Việt",
    // "Deutsch",
    // "Español",
    // "Français",
    // "Italiano",
    // "日本語",
    // "中文"
};
#endif

static constexpr uint8_t NUM_LANGUAGES = sizeof(languages) / sizeof(const char *);
