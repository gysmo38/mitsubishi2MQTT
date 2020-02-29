/*
 * mitsubishi2mqtt
 *
 */

const PROGMEM char* m2mqtt_version = "0.4.9";

//Define global variables for files
const PROGMEM char* wifi_conf = "wifi.json";
const PROGMEM char* mqtt_conf = "mqtt.json";
const PROGMEM char* advance_conf = "advance.json";
const PROGMEM char* console_file = "console.log";
const PROGMEM char* others_conf = "others.json";

// Define global variables for network
const PROGMEM char* hostnamePrefix = "HVAC_";
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
String others_debug;
String others_haa;
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
String hvac_name;
//login
String login_username = "admin";
String login_password;

// debug mode, when true, will send all packets received from the heatpump to topic heatpump_debug_topic
// this can also be set by sending "on" to heatpump_debug_set_topic
bool _debugMode = false;

// Customization
const PROGMEM uint8_t min_temp                    = 16; // Minimum temperature, check value from heatpump remote control
const PROGMEM uint8_t max_temp                    = 31; // Maximum temperature, check value from heatpump remote control
const PROGMEM char* temp_step                   = "1"; // Temperature setting step, check value from heatpump remote control

// pinouts
const PROGMEM  uint8_t blueLedPin = LED_BUILTIN; // Onboard LED = digital pin 2 "D4" (blue LED on WEMOS D1-Mini)
const PROGMEM  uint8_t redLedPin = 0;
// sketch settings
const PROGMEM uint32_t SEND_ROOM_TEMP_INTERVAL_MS = 30000;
const PROGMEM uint32_t MQTT_RETRY_INTERVAL_MS = 1000; //1 seconds

// temp settings
bool useFahrenheit = false;
// support heat mode settings, some model do not support heat mode 
bool supportHeatMode = true;
