/*
 * mitsubishi2mqtt
 *
 */
#define OTA

String m2mqtt_version = "0.4b";

//Define global variables for files
String wifi_conf = "wifi.json";
String mqtt_conf = "mqtt.json";
String console_file = "console.log";

// Define global variables for network
String hostname = "HVAC_";
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

// Define global variables for HA topics
String ha_power_set_topic;
String ha_mode_set_topic;
String ha_temp_set_topic;
String ha_fan_set_topic;
String ha_vane_set_topic;
String ha_wideVane_set_topic;
String ha_state_topic;
String ha_debug_topic;
String ha_debug_set_topic;
String ha_config_topic;
String ha_discovery_topic;
String hvac_name;

// debug mode, when true, will send all packets received from the heatpump to topic heatpump_debug_topic
// this can also be set by sending "on" to heatpump_debug_set_topic
bool _debugMode = false;

// Customization
const char* min_temp                    = "16"; // Minimum temperature, check value from heatpump remote control
const char* max_temp                    = "31"; // Maximum temperature, check value from heatpump remote control
const char* temp_step                   = "1"; // Temperature setting step, check value from heatpump remote control

// pinouts
const int redLedPin  = 0; // Onboard LED = digital pin 0 (red LED on adafruit ESP8266 huzzah)
const int blueLedPin = 2; // Onboard LED = digital pin 0 (blue LED on adafruit ESP8266 huzzah)

// sketch settings
const unsigned int SEND_ROOM_TEMP_INTERVAL_MS = 30000;
