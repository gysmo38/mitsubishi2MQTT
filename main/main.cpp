/*
  mitsubishi2mqtt - Mitsubishi Heat Pump to MQTT control for Home Assistant.
  Copyright (c) 2022 gysmo38, dzungpv, shampeon, endeavour, jascdk, chrdavis, alekslyse.  All right reserved.
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

#include "FS.h"               // SPIFFS for store config
#ifdef ESP32
#include <WiFi.h>             // WIFI for ESP32
#include <WiFiUdp.h>
#include <ESPmDNS.h>          // mDNS for ESP32
#include <AsyncTCP.h>         // ESPAsyncWebServer for ESP32
#include "SPIFFS.h"           // ESP32 SPIFFS for store config
extern "C" {
	#include "freertos/FreeRTOS.h" //AsyncMqttClient
	#include "freertos/timers.h"
}
#else
#include <ESP8266WiFi.h>      // WIFI for ESP8266
#include <WiFiClient.h>
#include <ESP8266mDNS.h>      // mDNS for ESP8266
#include <ESPAsyncTCP.h>      // ESPAsyncWebServer for ESP8266
#define U_PART U_FS
#endif
#include <AsyncMqttClient.h>
#include <ESPAsyncWebServer.h>  //ESPAsyncWebServer
AsyncWebServer server(80);    // Async Web server
#define WEBSOCKET_ENABLE 1 // Uncomment to enable websocket
#ifdef WEBSOCKET_ENABLE
AsyncWebSocket ws("/ws"); // Async Web socket
#endif
AsyncEventSource events("/events"); // Create an Event Source on /events

#include <ArduinoJson.h>      // json to process MQTT: ArduinoJson 6.11.4
#include <DNSServer.h>        // DNS for captive portal
#include <math.h>             // for rounding to Fahrenheit values

#include <ArduinoOTA.h>   // for OTA
#include <HeatPump.h>     // SwiCago library: https://github.com/SwiCago/HeatPump
#include <Ticker.h>     // for LED status (Using a Wemos D1-Mini)
#include "config.h"       // config file
#include "html_common.h"  // common code HTML (like header, footer)
#include "javascript_common.h"  // common code javascript (like refresh page)
#include "html_init.h"    // code html for initial config
#include "html_menu.h"    // code html for menu
#include "html_pages.h"   // code html for pages
#include "html_metrics.h" // prometheus metrics
// Languages
#ifndef MY_LANGUAGE
  #include "languages/en-GB.h" // default language English
#else
  #define QUOTEME(x) QUOTEME_1(x)
  #define QUOTEME_1(x) #x
  #define INCLUDE_FILE(x) QUOTEME(languages/x.h)
  #include INCLUDE_FILE(MY_LANGUAGE)
#endif

// wifi, mqtt and heatpump client instances
AsyncMqttClient mqttClient;        // AsyncMqtt
#ifdef ESP32
TimerHandle_t mqttReconnectTimer;  //timer for esp32 AsyncMqttClient
TimerHandle_t wifiReconnectTimer;  //timer for esp32 AsyncMqttClient
#elif defined(ESP8266)
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker mqttReconnectTimer;         //timer for esp8266 AsyncMqttClient
Ticker wifiReconnectTimer;         //timer for esp8266 AsyncMqttClient
#endif

int mqtt_attempts = 0;
bool mqtt_connected = false;
uint8_t mqtt_disconnected_reason;


//Captive portal variables, only used for config page
const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
IPAddress netMsk(255, 255, 255, 0);
DNSServer dnsServer;

boolean captive = false;
boolean mqtt_config = false;
boolean wifi_config = false;
boolean remoteTempActive = false;

//HVAC
HeatPump hp;
unsigned long lastTempSend;
unsigned long lastMqttRetry;
unsigned long lastHpSync;
unsigned int hpConnectionRetries;
unsigned int hpConnectionTotalRetries;
unsigned long lastRemoteTemp;

//Local state
StaticJsonDocument<JSON_OBJECT_SIZE(12)> rootInfo;

//Web OTA
int uploaderror = 0;
size_t ota_content_len;

// Start header for build with IDF and Platformio
bool loadWifi();
bool loadMqtt();
bool loadUnit();
bool loadOthers();
void saveMqtt(String mqttFn, String mqttHost, String mqttPort, String mqttUser, String mqttPwd, String mqttTopic);
void saveUnit(String tempUnit, String supportMode, String loginPassword, String minTemp, String maxTemp, String tempStep);
void saveWifi(String apSsid, String apPwd, String hostName, String otaPwd);
void saveOthers(String haa, String haat, String debugPckts, String debugLogs);
void initCaptivePortal();
void initMqtt();
void initOTA();
void setDefaults();
boolean initWifi();
void sendWrappedHTML(AsyncWebServerRequest *request, const String &content);
void handleNotFound(AsyncWebServerRequest *request);
void handleSaveWifi(AsyncWebServerRequest *request);
void handleReboot(AsyncWebServerRequest *request);
void handleRoot(AsyncWebServerRequest *request);
void handleInitSetup(AsyncWebServerRequest *request);
void handleSetup(AsyncWebServerRequest *request);
void rebootAndSendPage(AsyncWebServerRequest *request);
void handleOthers(AsyncWebServerRequest *request);
void handleMqtt(AsyncWebServerRequest *request);
void handleUnit(AsyncWebServerRequest *request);
void handleWifi(AsyncWebServerRequest *request);
void handleStatus(AsyncWebServerRequest *request);
void handleControl(AsyncWebServerRequest *request);
void handleMetrics(AsyncWebServerRequest *request);
void handleLogin(AsyncWebServerRequest *request);
void handleUpgrade(AsyncWebServerRequest *request);
void handleUploadDone(AsyncWebServerRequest *request);
void handleUploadLoop(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);
void write_log(String log);
heatpumpSettings change_states(AsyncWebServerRequest *request, heatpumpSettings settings);
void readHeatPumpSettings();
void hpSettingsChanged();
String hpGetMode(heatpumpSettings hpSettings);
String hpGetAction(heatpumpStatus hpStatus, heatpumpSettings hpSettings);
void hpStatusChanged(heatpumpStatus currentStatus);
void hpCheckRemoteTemp();
void hpPacketDebug(byte *packet, unsigned int length, const char *packetDirection);
void hpSendLocalState();
void mqttCallback(char *topic, char *payload, unsigned int length);
void haConfig();
void mqttConnect();
bool connectWifi();
float toFahrenheit(float fromCelcius);
float toCelsius(float fromFahrenheit);
float convertCelsiusToLocalUnit(float temperature, bool isFahrenheit);
float convertLocalUnitToCelsius(float temperature, bool isFahrenheit);
String getTemperatureScale();
String getId();
bool is_authenticated(AsyncWebServerRequest *request);
bool checkLogin(AsyncWebServerRequest *request);
// AsyncMQTT
#ifdef ESP32
void WiFiEvent(WiFiEvent_t event);
#elif defined(ESP8266)
void onWifiConnect(const WiFiEventStationModeGotIP &event);
void onWifiDisconnect(const WiFiEventStationModeDisconnected &event);
#endif
void onMqttConnect(bool sessionPresent);
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
void onMqttSubscribe(uint16_t packetId, uint8_t qos);
void onMqttUnsubscribe(uint16_t packetId);
void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
void onMqttPublish(uint16_t packetId);
// End  header for build with IDF and Platformio

#ifdef ESP8266
#define ESP_LOGE(tag, format, ...)
#define ESP_LOGW(tag, format, ...)
#define ESP_LOGI(tag, format, ...)
#define ESP_LOGD(tag, format, ...)
#define ESP_LOGV(tag, format, ...)
#endif

void setup() {
  // Start serial for debug before HVAC connect to serial
  Serial.begin(115200);
  // Serial.println(F("Starting Mitsubishi2MQTT"));
  // Mount SPIFFS filesystem
  if (SPIFFS.begin())
  {
    // Serial.println(F("Mounted file system"));
  }
  else
  {
    // Serial.println(F("Failed to mount FS -> formating"));
    SPIFFS.format();
    // if (SPIFFS.begin())
      // Serial.println(F("Mounted file system after formating"));
  }
  //set led pin as output
  pinMode(blueLedPin, OUTPUT);
  /*
    ticker.attach(0.6, tick);
  */

  //Define hostname
  hostname += hostnamePrefix;
  hostname += getId();
  setDefaults();
  wifi_config_exists = loadWifi();
  loadOthers();
  mqtt_client_id = hostname;
  if (loadMqtt()) {
      //write_log("Starting MQTT");
      // setup HA topics
      ha_mode_set_topic        = mqtt_topic + "/" + mqtt_fn + "/mode/set";
      ha_temp_set_topic        = mqtt_topic + "/" + mqtt_fn + "/temp/set";
      ha_remote_temp_set_topic = mqtt_topic + "/" + mqtt_fn + "/remote_temp/set";
      ha_fan_set_topic         = mqtt_topic + "/" + mqtt_fn + "/fan/set";
      ha_vane_set_topic        = mqtt_topic + "/" + mqtt_fn + "/vane/set";
      ha_wideVane_set_topic    = mqtt_topic + "/" + mqtt_fn + "/wideVane/set";
      ha_settings_topic        = mqtt_topic + "/" + mqtt_fn + "/settings";
      ha_state_topic           = mqtt_topic + "/" + mqtt_fn + "/state";
      ha_debug_pckts_topic     = mqtt_topic + "/" + mqtt_fn + "/debug/packets";
      ha_debug_pckts_set_topic = mqtt_topic + "/" + mqtt_fn + "/debug/packets/set";
      ha_debug_logs_topic      = mqtt_topic + "/" + mqtt_fn + "/debug/logs";
      ha_debug_logs_set_topic  = mqtt_topic + "/" + mqtt_fn + "/debug/logs/set";
      ha_custom_packet         = mqtt_topic + "/" + mqtt_fn + "/custom/send";
      ha_availability_topic    = mqtt_topic + "/" + mqtt_fn + "/availability";
      ha_system_set_topic      = mqtt_topic + "/" + mqtt_fn + "/system/set";

      if (others_haa) {
        ha_config_topic       = others_haa_topic + "/climate/" + mqtt_fn + "/config";
      }
      // startup mqtt connection
      initMqtt();
    }
    else {
      //write_log("Not found MQTT config go to configuration page");
    }
  loadUnit();
#ifdef ESP32
  WiFi.setHostname(hostname.c_str());
#else
  WiFi.hostname(hostname.c_str());
#endif
  if (initWifi()) {
    if (SPIFFS.exists(console_file)) {
      SPIFFS.remove(console_file);
    }
    //write_log("Starting Mitsubishi2MQTT");
    //Web interface
    server.on("/", handleRoot);
    server.on("/control", handleControl);
    server.on("/setup", handleSetup);
    server.on("/mqtt", handleMqtt);
    server.on("/wifi", handleWifi);
    server.on("/unit", handleUnit);
    server.on("/status", handleStatus);
    server.on("/others", handleOthers);
    server.on("/metrics", handleMetrics);
    server.onNotFound(handleNotFound);
    if (login_password.length() > 0) {
      server.on("/login", handleLogin);
      //here the list of headers to be recorded, use for authentication
      const char * headerkeys[] = {"User-Agent", "Cookie"} ;
      size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
      //ask server to track these headers
    }
    server.on("/upgrade", handleUpgrade);
    server.on("/upload", HTTP_ASYNC_ANY, handleUploadDone, handleUploadLoop);

    server.begin();
    lastMqttRetry = 0;
    lastHpSync = 0;
    hpConnectionRetries = 0;
    hpConnectionTotalRetries = 0;
    // Serial.println(F("Connection to HVAC. Stop serial log."));
    //write_log("Connection to HVAC");
    hp.setSettingsChangedCallback(hpSettingsChanged);
    hp.setStatusChangedCallback(hpStatusChanged);
    hp.setPacketCallback(hpPacketDebug);
    // Allow Remote/Panel
    hp.enableExternalUpdate();
    hp.enableAutoUpdate();
    hp.connect(&Serial);
    heatpumpStatus currentStatus = hp.getStatus();
    heatpumpSettings currentSettings = hp.getSettings();
    rootInfo["roomTemperature"]     = convertCelsiusToLocalUnit(currentStatus.roomTemperature, useFahrenheit);
    rootInfo["temperature"]         = convertCelsiusToLocalUnit(currentSettings.temperature, useFahrenheit);
    rootInfo["fan"]                 = currentSettings.fan;
    rootInfo["vane"]                = currentSettings.vane;
    rootInfo["wideVane"]            = currentSettings.wideVane;
    rootInfo["mode"]                = hpGetMode(currentSettings);
    rootInfo["action"]              = hpGetAction(currentStatus, currentSettings);
    rootInfo["compressorFrequency"] = currentStatus.compressorFrequency;
    lastTempSend = millis();
  }
  else {
    dnsServer.start(DNS_PORT, "*", apIP);
    initCaptivePortal();
  }
  initOTA();
}

bool loadWifi() {
  ap_ssid = "";
  ap_pwd  = "";
  if (!SPIFFS.exists(wifi_conf)) {
    // Serial.println(F("Wifi config file not exist!"));
    return false;
  }
  File configFile = SPIFFS.open(wifi_conf, "r");
  if (!configFile) {
    // Serial.println(F("Failed to open wifi config file"));
    return false;
  }
  size_t size = configFile.size();
  if (size > 1024) {
    // Serial.println(F("Wifi config file size is too large"));
    return false;
  }

  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  const size_t capacity = JSON_OBJECT_SIZE(4) + 130;
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, buf.get());
  hostname = doc["hostname"].as<String>();
  ap_ssid  = doc["ap_ssid"].as<String>();
  ap_pwd   = doc["ap_pwd"].as<String>();
  //prevent ota password is "null" if not exist key
  if (doc.containsKey("ota_pwd")) {
    ota_pwd  = doc["ota_pwd"].as<String>();
  } else {
    ota_pwd = "";
  }
  return true;
}
bool loadMqtt() {
  if (!SPIFFS.exists(mqtt_conf)) {
    Serial.println(F("MQTT config file not exist!"));
    return false;
  }
  //write_log("Loading MQTT configuration");
  File configFile = SPIFFS.open(mqtt_conf, "r");
  if (!configFile) {
    //write_log("Failed to open MQTT config file");
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    //write_log("Config file size is too large");
    return false;
  }
  std::unique_ptr<char[]> buf(new char[size]);

  configFile.readBytes(buf.get(), size);
  const size_t capacity = JSON_OBJECT_SIZE(6) + 400;
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, buf.get());
  mqtt_fn             = doc["mqtt_fn"].as<String>();
  mqtt_server         = doc["mqtt_host"].as<String>();
  mqtt_port           = doc["mqtt_port"].as<String>();
  mqtt_username       = doc["mqtt_user"].as<String>();
  mqtt_password       = doc["mqtt_pwd"].as<String>();
  mqtt_topic          = doc["mqtt_topic"].as<String>();

  //write_log("=== START DEBUG MQTT ===");
  //write_log("Friendly Name" + mqtt_fn);
  //write_log("IP Server " + mqtt_server);
  //write_log("IP Port " + mqtt_port);
  //write_log("Username " + mqtt_username);
  //write_log("Password " + mqtt_password);
  //write_log("Topic " + mqtt_topic);
  //write_log("=== END DEBUG MQTT ===");

  mqtt_config = true;
  return true;
}

bool loadUnit() {
  if (!SPIFFS.exists(unit_conf)) {
    // Serial.println(F("Unit config file not exist!"));
    return false;
  }
  File configFile = SPIFFS.open(unit_conf, "r");
  if (!configFile) {
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    return false;
  }
  std::unique_ptr<char[]> buf(new char[size]);

  configFile.readBytes(buf.get(), size);
  const size_t capacity = JSON_OBJECT_SIZE(3) + 200;
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, buf.get());
  //unit
  String unit_tempUnit            = doc["unit_tempUnit"].as<String>();
  if (unit_tempUnit == "fah") useFahrenheit = true;
  min_temp              = doc["min_temp"].as<uint8_t>();
  max_temp              = doc["max_temp"].as<uint8_t>();
  temp_step             = doc["temp_step"].as<String>();
  //mode
  String supportMode = doc["support_mode"].as<String>();
  if (supportMode == "nht") supportHeatMode = false;
  //prevent login password is "null" if not exist key
  if (doc.containsKey("login_password")) {
    login_password = doc["login_password"].as<String>();
  } else {
    login_password = "";
  }
  return true;
}

bool loadOthers() {
  if (!SPIFFS.exists(others_conf)) {
    // Serial.println(F("Others config file not exist!"));
    return false;
  }
  File configFile = SPIFFS.open(others_conf, "r");
  if (!configFile) {
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    return false;
  }
  std::unique_ptr<char[]> buf(new char[size]);

  configFile.readBytes(buf.get(), size);
  const size_t capacity = JSON_OBJECT_SIZE(4) + 200;
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, buf.get());
  //unit
  String unit_tempUnit    = doc["unit_tempUnit"].as<String>();
  if (unit_tempUnit == "fah") useFahrenheit = true;
  others_haa_topic        = doc["haat"].as<String>();
  String haa              = doc["haa"].as<String>();
  String debugPckts       = doc["debugPckts"].as<String>();
  String debugLogs        = doc["debugLogs"].as<String>();
  if (strcmp(haa.c_str(), "OFF") == 0) {
    others_haa = false;
  }
  if (strcmp(debugPckts.c_str(), "ON") == 0) {
    _debugModePckts = true;
  }
  if (strcmp(debugLogs.c_str(), "ON") == 0) {
    _debugModeLogs = true;
  }
  return true;
}
void saveMqtt(String mqttFn, String mqttHost, String mqttPort, String mqttUser,
              String mqttPwd, String mqttTopic) {

  const size_t capacity = JSON_OBJECT_SIZE(6) + 400;
  DynamicJsonDocument doc(capacity);
  // if mqtt port is empty, we use default port
  if (mqttPort[0] == '\0') mqttPort = "1883";
  doc["mqtt_fn"]   = mqttFn;
  doc["mqtt_host"] = mqttHost;
  doc["mqtt_port"] = mqttPort;
  doc["mqtt_user"] = mqttUser;
  doc["mqtt_pwd"] = mqttPwd;
  doc["mqtt_topic"] = mqttTopic;
  File configFile = SPIFFS.open(mqtt_conf, "w");
  if (!configFile) {
    // Serial.println(F("Failed to open config file for writing"));
  }
  serializeJson(doc, configFile);
  configFile.close();
}

void saveUnit(String tempUnit, String supportMode, String loginPassword, String minTemp, String maxTemp, String tempStep) {
  const size_t capacity = JSON_OBJECT_SIZE(6) + 200;
  DynamicJsonDocument doc(capacity);
  // if temp unit is empty, we use default celcius
  if (tempUnit.isEmpty()) tempUnit = "cel";
  doc["unit_tempUnit"]   = tempUnit;
  // if minTemp is empty, we use default 16
  if (minTemp.isEmpty()) minTemp = 16;
  doc["min_temp"]   = minTemp;
  // if maxTemp is empty, we use default 31
  if (maxTemp.isEmpty()) maxTemp = 31;
  doc["max_temp"]   = maxTemp;
  // if tempStep is empty, we use default 1
  if (tempStep.isEmpty()) tempStep = 1;
  doc["temp_step"] = tempStep;
  // if support mode is empty, we use default all mode
  if (supportMode.isEmpty()) supportMode = "all";
  doc["support_mode"]   = supportMode;
  // if login password is empty, we use empty
  if (loginPassword.isEmpty()) loginPassword = "";

  doc["login_password"]   = loginPassword;
  File configFile = SPIFFS.open(unit_conf, "w");
  if (!configFile) {
    // Serial.println(F("Failed to open config file for writing"));
  }
  serializeJson(doc, configFile);
  configFile.close();
}

void saveWifi(String apSsid, String apPwd, String hostName, String otaPwd) {
  const size_t capacity = JSON_OBJECT_SIZE(4) + 130;
  DynamicJsonDocument doc(capacity);
  doc["ap_ssid"] = apSsid;
  doc["ap_pwd"] = apPwd;
  doc["hostname"] = hostName;
  doc["ota_pwd"] = otaPwd;
  File configFile = SPIFFS.open(wifi_conf, "w");
  if (!configFile) {
    // Serial.println(F("Failed to open wifi file for writing"));
  }
  serializeJson(doc, configFile);
  delay(10);
  configFile.close();
}

void saveOthers(String haa, String haat, String debugPckts, String debugLogs) {
  const size_t capacity = JSON_OBJECT_SIZE(4) + 130;
  DynamicJsonDocument doc(capacity);
  doc["haa"] = haa;
  doc["haat"] = haat;
  doc["debugPckts"] = debugPckts;
  doc["debugLogs"] = debugLogs;
  File configFile = SPIFFS.open(others_conf, "w");
  if (!configFile) {
    // Serial.println(F("Failed to open wifi file for writing"));
  }
  serializeJson(doc, configFile);
  delay(10);
  configFile.close();
}

// Initialize captive portal page
void initCaptivePortal() {
  // Serial.println(F("Starting captive portal"));
  server.on("/", handleInitSetup);
  server.on("/save", handleSaveWifi);
  server.on("/reboot", handleReboot);
  server.onNotFound(handleNotFound);
  server.begin();
  captive = true;
}

void initMqtt() {
  ESP_LOGD(TAG, "Setup Async Mqtt...");
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  //mqttClient.onSubscribe(onMqttSubscribe);
  //mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);

  const char *apipch = mqtt_server.c_str();
  IPAddress apip;
  if (apip.fromString(apipch))
  {                       // try to parse into the IPAddress
    //Serial.println(apip); // print the parsed IPAddress
    ESP_LOGD(TAG, "Connecting to MQTT server IP: %s, port: %s", apipch, mqtt_port);
  }
  else
  {
    ESP_LOGD(TAG, "UnParsable IP");
  }
  mqttClient.setServer(mqtt_server.c_str(), atoi(mqtt_port.c_str()));
  mqttClient.setCredentials(mqtt_username.c_str(), mqtt_password.c_str());
  mqttClient.setClientId(mqtt_client_id.c_str());
  mqttClient.setWill(ha_availability_topic.c_str(), 1, true, mqtt_payload_unavailable);
}

// Enable OTA only when connected as a client.
void initOTA() {
  //write_log("Start OTA Listener");
  ArduinoOTA.setHostname(hostname.c_str());
  if (ota_pwd.length() > 0) {
    ArduinoOTA.setPassword(ota_pwd.c_str());
  }
  ArduinoOTA.onStart([]() {
    //write_log("Start");
  });
  ArduinoOTA.onEnd([]() {
    //write_log("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    //    write_log("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    //    write_log("Error[%u]: ", error);
    // if (error == OTA_AUTH_ERROR) Serial.println(F("Auth Failed"));
    // else if (error == OTA_BEGIN_ERROR) Serial.println(F("Begin Failed"));
    // else if (error == OTA_CONNECT_ERROR) Serial.println(F("Connect Failed"));
    // else if (error == OTA_RECEIVE_ERROR) Serial.println(F("Receive Failed"));
    // else if (error == OTA_END_ERROR) Serial.println(F("End Failed"));
  });
  ArduinoOTA.begin();
}
void setDefaults() {
  ap_ssid = "";
  ap_pwd  = "";
  others_haa = true;
  others_haa_topic = "homeassistant";

}

boolean initWifi() {
  bool connectWifiSuccess = true;
  if (ap_ssid[0] != '\0') {
    // wifi connection handle
#ifdef ESP32
    mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(mqttConnect));
    wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(connectWifi));
    WiFi.onEvent(WiFiEvent);
#elif defined(ESP8266)
    wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
    wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect); // timer for esp8266 AsyncMqttClient
#endif
    connectWifiSuccess = wifi_config = connectWifi();
    if (connectWifiSuccess) {
      return true;
    }
    else
    {
      // reset hostname back to default before starting AP mode for privacy
      hostname = hostnamePrefix;
      hostname += getId();
    }
  }

  // Serial.println(F("\n\r \n\rStarting in AP mode"));
  WiFi.mode(WIFI_AP);
  wifi_timeout = millis() + WIFI_RETRY_INTERVAL_MS;
  WiFi.persistent(false); //fix crash esp32 https://github.com/espressif/arduino-esp32/issues/2025
  WiFi.softAPConfig(apIP, apIP, netMsk);
  if (!connectWifiSuccess and login_password != "") {
    // Set AP password when falling back to AP on fail
    WiFi.softAP(hostname.c_str(), login_password.c_str());
  }
  else {
    // First time setup does not require password
    WiFi.softAP(hostname.c_str());
  }
  delay(2000); // VERY IMPORTANT

  // Serial.print(F("IP address: "));
  // Serial.println(WiFi.softAPIP());
  //ticker.attach(0.2, tick); // Start LED to flash rapidly to indicate we are ready for setting up the wifi-connection (entered captive portal).
  wifi_config = false;
  return false;
}

// Handler webserver response

void sendWrappedHTML(AsyncWebServerRequest *request, const String &content)
{
  String headerContent = FPSTR(html_common_header);
  String footerContent = FPSTR(html_common_footer);
  String toSend(headerContent);
  toSend += content;
  toSend += footerContent;
  toSend.replace(F("_UNIT_NAME_"), hostname);
  toSend.replace(F("_VERSION_"), m2mqtt_version);
  request->send_P(200, "text/html", toSend.c_str());
  headerContent = "";
  footerContent = "";
}

void handleNotFound(AsyncWebServerRequest *request) {
  if (captive) {
    String initSetupContent = FPSTR(html_init_setup);
    initSetupContent.replace("_TXT_INIT_TITLE_",FPSTR(txt_init_title));
    initSetupContent.replace("_TXT_INIT_HOST_",FPSTR(txt_wifi_hostname));
    initSetupContent.replace("_UNIT_NAME_", hostname);
    initSetupContent.replace("_TXT_INIT_SSID_",FPSTR(txt_wifi_SSID));
    initSetupContent.replace("_TXT_INIT_PSK_",FPSTR(txt_wifi_psk));
    initSetupContent.replace("_TXT_INIT_OTA_",FPSTR(txt_wifi_otap));
    initSetupContent.replace("_TXT_SAVE_",FPSTR(txt_save));
    initSetupContent.replace("_TXT_REBOOT_",FPSTR(txt_reboot));

    sendWrappedHTML(request, initSetupContent);
  }
  else {
    String menuRootPage = FPSTR(html_menu_root);
    menuRootPage.replace(F("_SHOW_LOGOUT_"), (String)(login_password.length() > 0));
    // not show control button if hp not connected
    menuRootPage.replace(F("_SHOW_CONTROL_"), (String)(hp.isConnected()));
    sendWrappedHTML(request, menuRootPage);
  }
}

void handleSaveWifi(AsyncWebServerRequest *request) {
  if (!checkLogin(request)) return;

  // Serial.println(F("Saving wifi config"));
  if (request->hasArg("submit")) {
    saveWifi(request->arg("ssid"), request->arg("psk"), request->arg("hn"), request->arg("otapwd"));
  }
  String initSavePage =  FPSTR(html_init_save);
  initSavePage.replace("_TXT_INIT_REBOOT_MESS_",FPSTR(txt_init_reboot_mes));
  sendWrappedHTML(request, initSavePage);
  delay(500);
  ESP.restart();
}

void handleReboot(AsyncWebServerRequest *request) {
  if (!checkLogin(request)) return;

  String initRebootPage = FPSTR(html_init_reboot);
  initRebootPage.replace("_TXT_INIT_REBOOT_",FPSTR(txt_init_reboot));
  sendWrappedHTML(request, initRebootPage);
  delay(500);
  ESP.restart();
}

void handleRoot(AsyncWebServerRequest *request) {
  if (!checkLogin(request)) return;

  if (request->hasArg("REBOOT")) {
    String rebootPage =  FPSTR(html_page_reboot);
    String countDown = FPSTR(count_down_script);
    rebootPage.replace("_TXT_M_REBOOT_",FPSTR(txt_m_reboot));
    sendWrappedHTML(request, rebootPage + countDown);
    delay(500);
#ifdef ESP32
    ESP.restart();
#else
    ESP.reset();
#endif
  }
  else {
    String menuRootPage =  FPSTR(html_menu_root);
    menuRootPage.replace("_SHOW_LOGOUT_", (String)(login_password.length() > 0));
    //not show control button if hp not connected
    menuRootPage.replace("_SHOW_CONTROL_", (String)(hp.isConnected()));
    menuRootPage.replace("_TXT_CONTROL_",FPSTR(txt_control));
    menuRootPage.replace("_TXT_SETUP_",FPSTR(txt_setup));
    menuRootPage.replace("_TXT_STATUS_",FPSTR(txt_status));
    menuRootPage.replace("_TXT_FW_UPGRADE_",FPSTR(txt_firmware_upgrade));
    menuRootPage.replace("_TXT_REBOOT_",FPSTR(txt_reboot));
    menuRootPage.replace("_TXT_LOGOUT_",FPSTR(txt_logout));
    sendWrappedHTML(request, menuRootPage);
  }
}

void handleInitSetup(AsyncWebServerRequest *request) {
  String initSetupPage = FPSTR(html_init_setup);
  initSetupPage.replace("_TXT_INIT_TITLE_",FPSTR(txt_init_title));
  initSetupPage.replace("_TXT_INIT_HOST_",FPSTR(txt_wifi_hostname));
  initSetupPage.replace("_TXT_INIT_SSID_",FPSTR(txt_wifi_SSID));
  initSetupPage.replace("_TXT_INIT_PSK_",FPSTR(txt_wifi_psk));
  initSetupPage.replace("_TXT_INIT_OTA_",FPSTR(txt_wifi_otap));
  initSetupPage.replace("_TXT_SAVE_",FPSTR(txt_save));
  initSetupPage.replace("_TXT_REBOOT_",FPSTR(txt_reboot));

  sendWrappedHTML(request, initSetupPage);
}

void handleSetup(AsyncWebServerRequest *request) {
  if (!checkLogin(request)) return;

  if (request->hasArg("RESET")) {
    String pageReset = FPSTR(html_page_reset);
    String ssid = hostnamePrefix;
    ssid += getId();
    pageReset.replace("_TXT_M_RESET_",FPSTR(txt_m_reset));
    pageReset.replace("_SSID_",ssid);
    sendWrappedHTML(request, pageReset);
    SPIFFS.format();
    delay(500);
#ifdef ESP32
    ESP.restart();
#else
    ESP.reset();
#endif
  }
  else {
    String menuSetupPage = FPSTR(html_menu_setup);
    menuSetupPage.replace("_TXT_MQTT_",FPSTR(txt_MQTT));
    menuSetupPage.replace("_TXT_WIFI_",FPSTR(txt_WIFI));
    menuSetupPage.replace("_TXT_UNIT_",FPSTR(txt_unit));
    menuSetupPage.replace("_TXT_OTHERS_",FPSTR(txt_others));
    menuSetupPage.replace("_TXT_RESET_",FPSTR(txt_reset));
    menuSetupPage.replace("_TXT_BACK_",FPSTR(txt_back));
    menuSetupPage.replace("_TXT_RESETCONFIRM_",FPSTR(txt_reset_confirm));
    sendWrappedHTML(request, menuSetupPage);
  }

}

void rebootAndSendPage(AsyncWebServerRequest *request) {
    String saveRebootPage =  FPSTR(html_page_save_reboot);
    String countDown = FPSTR(count_down_script);
    saveRebootPage.replace("_TXT_M_SAVE_",FPSTR(txt_m_save));
    sendWrappedHTML(request, saveRebootPage + countDown);
    delay(500);
    ESP.restart();
}

void handleOthers(AsyncWebServerRequest *request) {
  if (!checkLogin(request)) return;

  if (request->hasArg("save"))
  {
    saveOthers(request->arg("HAA"), request->arg("haat"), request->arg("DebugPckts"),request->arg("DebugLogs"));
    rebootAndSendPage(request);
  }
  else {
    String othersPage =  FPSTR(html_page_others);
    othersPage.replace("_TXT_SAVE_", FPSTR(txt_save));
    othersPage.replace("_TXT_BACK_", FPSTR(txt_back));
    othersPage.replace("_TXT_F_ON_", FPSTR(txt_f_on));
    othersPage.replace("_TXT_F_OFF_", FPSTR(txt_f_off));
    othersPage.replace("_TXT_OTHERS_TITLE_", FPSTR(txt_others_title));
    othersPage.replace("_TXT_OTHERS_HAAUTO_", FPSTR(txt_others_haauto));
    othersPage.replace("_TXT_OTHERS_HATOPIC_", FPSTR(txt_others_hatopic));
    othersPage.replace("_TXT_OTHERS_DEBUG_PCKTS_",FPSTR(txt_others_debug_packets));
    othersPage.replace("_TXT_OTHERS_DEBUG_LOGS_",FPSTR(txt_others_debug_log));

    othersPage.replace("_HAA_TOPIC_", others_haa_topic);
    if (others_haa) {
      othersPage.replace("_HAA_ON_", "selected");
    }
    else {
      othersPage.replace("_HAA_OFF_", "selected");
    }
    if (_debugModePckts) {
      othersPage.replace("_DEBUG_PCKTS_ON_", "selected");
    }
    else {
      othersPage.replace("_DEBUG_PCKTS_OFF_", "selected");
    }
    if (_debugModeLogs) {
      othersPage.replace("_DEBUG_LOGS_ON_", "selected");
    }
    else {
      othersPage.replace("_DEBUG_LOGS_OFF_", "selected");
    }
    sendWrappedHTML(request, othersPage);
  }
}

void handleMqtt(AsyncWebServerRequest *request) {
  if (!checkLogin(request)) return;

  if (request->hasArg("save"))
  {
    saveMqtt(request->arg("fn"), request->arg("mh"), request->arg("ml"), request->arg("mu"), request->arg("mp"), request->arg("mt"));
    rebootAndSendPage(request);
  }
  else {
    String mqttPage =  FPSTR(html_page_mqtt);
    mqttPage.replace("_TXT_SAVE_", FPSTR(txt_save));
    mqttPage.replace("_TXT_BACK_", FPSTR(txt_back));
    mqttPage.replace("_TXT_MQTT_TITLE_", FPSTR(txt_mqtt_title));
    mqttPage.replace("_TXT_MQTT_FN_", FPSTR(txt_mqtt_fn));
    mqttPage.replace("_TXT_MQTT_HOST_", FPSTR(txt_mqtt_host));
    mqttPage.replace("_TXT_MQTT_PORT_", FPSTR(txt_mqtt_port));
    mqttPage.replace("_TXT_MQTT_USER_", FPSTR(txt_mqtt_user));
    mqttPage.replace("_TXT_MQTT_PASSWORD_", FPSTR(txt_mqtt_password));
    mqttPage.replace("_TXT_MQTT_TOPIC_", FPSTR(txt_mqtt_topic));
    mqttPage.replace(F("_MQTT_FN_"), mqtt_fn);
    mqttPage.replace(F("_MQTT_HOST_"), mqtt_server);
    mqttPage.replace(F("_MQTT_PORT_"), String(mqtt_port));
    mqttPage.replace(F("_MQTT_USER_"), mqtt_username);
    mqttPage.replace(F("_MQTT_PASSWORD_"), mqtt_password);
    mqttPage.replace(F("_MQTT_TOPIC_"), mqtt_topic);
    sendWrappedHTML(request, mqttPage);
  }
}

void handleUnit(AsyncWebServerRequest *request) {
  if (!checkLogin(request)) return;

  if (request->hasArg("save"))
  {
    saveUnit(request->arg("tu"), request->arg("md"), request->arg("lpw"), (String)convertLocalUnitToCelsius(request->arg("min_temp").toInt(), useFahrenheit), (String)convertLocalUnitToCelsius(request->arg("max_temp").toInt(), useFahrenheit), request->arg("temp_step"));
    rebootAndSendPage(request);
  }
  else {
    String unitPage =  FPSTR(html_page_unit);
    unitPage.replace("_TXT_SAVE_", FPSTR(txt_save));
    unitPage.replace("_TXT_BACK_", FPSTR(txt_back));
    unitPage.replace("_TXT_UNIT_TITLE_", FPSTR(txt_unit_title));
    unitPage.replace("_TXT_UNIT_TEMP_", FPSTR(txt_unit_temp));
    unitPage.replace("_TXT_UNIT_MINTEMP_", FPSTR(txt_unit_mintemp));
    unitPage.replace("_TXT_UNIT_MAXTEMP_", FPSTR(txt_unit_maxtemp));
    unitPage.replace("_TXT_UNIT_STEPTEMP_", FPSTR(txt_unit_steptemp));
    unitPage.replace("_TXT_UNIT_MODES_", FPSTR(txt_unit_modes));
    unitPage.replace("_TXT_UNIT_PASSWORD_", FPSTR(txt_unit_password));
    unitPage.replace("_TXT_F_CELSIUS_", FPSTR(txt_f_celsius));
    unitPage.replace("_TXT_F_FH_", FPSTR(txt_f_fh));
    unitPage.replace("_TXT_F_ALLMODES_", FPSTR(txt_f_allmodes));
    unitPage.replace("_TXT_F_NOHEAT_", FPSTR(txt_f_noheat));
    unitPage.replace(F("_MIN_TEMP_"), String(convertCelsiusToLocalUnit(min_temp, useFahrenheit)));
    unitPage.replace(F("_MAX_TEMP_"), String(convertCelsiusToLocalUnit(max_temp, useFahrenheit)));
    unitPage.replace(F("_TEMP_STEP_"), String(temp_step));
    //temp
    if (useFahrenheit) unitPage.replace(F("_TU_FAH_"), F("selected"));
    else unitPage.replace(F("_TU_CEL_"), F("selected"));
    //mode
    if (supportHeatMode) unitPage.replace(F("_MD_ALL_"), F("selected"));
    else unitPage.replace(F("_MD_NONHEAT_"), F("selected"));
    unitPage.replace(F("_LOGIN_PASSWORD_"), login_password);
    sendWrappedHTML(request, unitPage);
  }
}

void handleWifi(AsyncWebServerRequest *request) {
  if (!checkLogin(request)) return;

  if (request->hasArg("save"))
  {
    saveWifi(request->arg("ssid"), request->arg("psk"), request->arg("hn"), request->arg("otapwd"));
    rebootAndSendPage(request);
#ifdef ESP32
    ESP.restart();
#else
    ESP.reset();
#endif
  }
  else {
    String wifiPage =  FPSTR(html_page_wifi);
    String str_ap_ssid = ap_ssid;
    String str_ap_pwd  = ap_pwd;
    String str_ota_pwd = ota_pwd;
    str_ap_ssid.replace("'", F("&apos;"));
    str_ap_pwd.replace("'", F("&apos;"));
    str_ota_pwd.replace("'", F("&apos;"));
    wifiPage.replace("_TXT_SAVE_", FPSTR(txt_save));
    wifiPage.replace("_TXT_BACK_", FPSTR(txt_back));
    wifiPage.replace("_TXT_WIFI_TITLE_", FPSTR(txt_wifi_title));
    wifiPage.replace("_TXT_WIFI_HOST_", FPSTR(txt_wifi_hostname));
    wifiPage.replace("_TXT_WIFI_SSID_", FPSTR(txt_wifi_SSID));
    wifiPage.replace("_TXT_WIFI_PSK_", FPSTR(txt_wifi_psk));
    wifiPage.replace("_TXT_WIFI_OTAP_", FPSTR(txt_wifi_otap));
    wifiPage.replace(F("_SSID_"), str_ap_ssid);
    wifiPage.replace(F("_PSK_"), str_ap_pwd);
    wifiPage.replace(F("_OTA_PWD_"), str_ota_pwd);
    sendWrappedHTML(request, wifiPage);
  }

}

void handleStatus(AsyncWebServerRequest *request) {
  if (!checkLogin(request)) return;

  String statusPage =  FPSTR(html_page_status);
  statusPage.replace("_TXT_BACK_", FPSTR(txt_back));
  statusPage.replace("_TXT_STATUS_TITLE_", FPSTR(txt_status_title));
  statusPage.replace("_TXT_STATUS_HVAC_", FPSTR(txt_status_hvac));
  statusPage.replace("_TXT_STATUS_MQTT_", FPSTR(txt_status_mqtt));
  statusPage.replace("_TXT_STATUS_WIFI_", FPSTR(txt_status_wifi));
  statusPage.replace("_TXT_RETRIES_HVAC_", FPSTR(txt_retries_hvac));

  if (request->hasArg("mrconn")) mqttConnect();

  String connected = F("<span style='color:#47c266'><b>");
  connected += FPSTR(txt_status_connect);
  connected += F("</b><span>");

  String disconnected = F("<span style='color:#d43535'><b>");
  disconnected += FPSTR(txt_status_disconnect);
  disconnected += F("</b></span>");

  if ((Serial) and hp.isConnected()) statusPage.replace(F("_HVAC_STATUS_"), connected);
  else  statusPage.replace(F("_HVAC_STATUS_"), disconnected);
  if (mqttClient.connected()) statusPage.replace(F("_MQTT_STATUS_"), connected);
  else statusPage.replace(F("_MQTT_STATUS_"), disconnected);
  statusPage.replace(F("_HVAC_RETRIES_"), String(hpConnectionTotalRetries));
  statusPage.replace(F("_MQTT_REASON_"), String(mqtt_disconnected_reason));
  statusPage.replace(F("_WIFI_STATUS_"), String(WiFi.RSSI()));
  sendWrappedHTML(request, statusPage);
}



void handleControl(AsyncWebServerRequest *request) {
  if (!checkLogin(request)) return;

  //not connected to hp, redirect to status page
  if (!hp.isConnected())
  {
    AsyncWebServerResponse *response = request->beginResponse(301);
    response->addHeader("Location", "/status");
    response->addHeader("Cache-Control", "no-cache");
    request->send(response);
    return;
  }
  heatpumpSettings settings = hp.getSettings();
  settings = change_states(request, settings);
  String controlPage =  FPSTR(html_page_control);
  String headerContent = FPSTR(html_common_header);
  String footerContent = FPSTR(html_common_footer);
  //write_log("Enter HVAC control");
  headerContent.replace("_UNIT_NAME_", hostname);
  footerContent.replace("_VERSION_", m2mqtt_version);
  controlPage.replace("_TXT_BACK_", FPSTR(txt_back));
  controlPage.replace("_UNIT_NAME_", hostname);
  controlPage.replace("_RATE_", "60");
  controlPage.replace("_ROOMTEMP_", String(convertCelsiusToLocalUnit(hp.getRoomTemperature(), useFahrenheit)));
  controlPage.replace("_USE_FAHRENHEIT_", (String)useFahrenheit);
  controlPage.replace("_TEMP_SCALE_", getTemperatureScale());
  controlPage.replace("_HEAT_MODE_SUPPORT_", (String)supportHeatMode);
  controlPage.replace(F("_MIN_TEMP_"), String(convertCelsiusToLocalUnit(min_temp, useFahrenheit)));
  controlPage.replace(F("_MAX_TEMP_"), String(convertCelsiusToLocalUnit(max_temp, useFahrenheit)));
  controlPage.replace(F("_TEMP_STEP_"), String(temp_step));
  controlPage.replace("_TXT_CTRL_CTEMP_", FPSTR(txt_ctrl_ctemp));
  controlPage.replace("_TXT_CTRL_TEMP_", FPSTR(txt_ctrl_temp));
  controlPage.replace("_TXT_CTRL_TITLE_", FPSTR(txt_ctrl_title));
  controlPage.replace("_TXT_CTRL_POWER_", FPSTR(txt_ctrl_power));
  controlPage.replace("_TXT_CTRL_MODE_", FPSTR(txt_ctrl_mode));
  controlPage.replace("_TXT_CTRL_FAN_", FPSTR(txt_ctrl_fan));
  controlPage.replace("_TXT_CTRL_VANE_", FPSTR(txt_ctrl_vane));
  controlPage.replace("_TXT_CTRL_WVANE_", FPSTR(txt_ctrl_wvane));
  controlPage.replace("_TXT_F_ON_", FPSTR(txt_f_on));
  controlPage.replace("_TXT_F_OFF_", FPSTR(txt_f_off));
  controlPage.replace("_TXT_F_AUTO_", FPSTR(txt_f_auto));
  controlPage.replace("_TXT_F_HEAT_", FPSTR(txt_f_heat));
  controlPage.replace("_TXT_F_DRY_", FPSTR(txt_f_dry));
  controlPage.replace("_TXT_F_COOL_", FPSTR(txt_f_cool));
  controlPage.replace("_TXT_F_FAN_", FPSTR(txt_f_fan));
  controlPage.replace("_TXT_F_QUIET_", FPSTR(txt_f_quiet));
  controlPage.replace("_TXT_F_SPEED_", FPSTR(txt_f_speed));
  controlPage.replace("_TXT_F_SWING_", FPSTR(txt_f_swing));
  controlPage.replace("_TXT_F_POS_", FPSTR(txt_f_pos));

  if (strcmp(settings.power, "ON") == 0) {
    controlPage.replace("_POWER_ON_", "selected");
  }
  else if (strcmp(settings.power, "OFF") == 0) {
    controlPage.replace("_POWER_OFF_", "selected");
  }

  if (strcmp(settings.mode, "HEAT") == 0) {
    controlPage.replace("_MODE_H_", "selected");
  }
  else if (strcmp(settings.mode, "DRY") == 0) {
    controlPage.replace("_MODE_D_", "selected");
  }
  else if (strcmp(settings.mode, "COOL") == 0) {
    controlPage.replace("_MODE_C_", "selected");
  }
  else if (strcmp(settings.mode, "FAN") == 0) {
    controlPage.replace("_MODE_F_", "selected");
  }
  else if (strcmp(settings.mode, "AUTO") == 0) {
    controlPage.replace("_MODE_A_", "selected");
  }

  if (strcmp(settings.fan, "AUTO") == 0) {
    controlPage.replace("_FAN_A_", "selected");
  }
  else if (strcmp(settings.fan, "QUIET") == 0) {
    controlPage.replace("_FAN_Q_", "selected");
  }
  else if (strcmp(settings.fan, "1") == 0) {
    controlPage.replace("_FAN_1_", "selected");
  }
  else if (strcmp(settings.fan, "2") == 0) {
    controlPage.replace("_FAN_2_", "selected");
  }
  else if (strcmp(settings.fan, "3") == 0) {
    controlPage.replace("_FAN_3_", "selected");
  }
  else if (strcmp(settings.fan, "4") == 0) {
    controlPage.replace("_FAN_4_", "selected");
  }

  controlPage.replace("_VANE_V_", settings.vane);
  if (strcmp(settings.vane, "AUTO") == 0) {
    controlPage.replace("_VANE_A_", "selected");
  }
  else if (strcmp(settings.vane, "1") == 0) {
    controlPage.replace("_VANE_1_", "selected");
  }
  else if (strcmp(settings.vane, "2") == 0) {
    controlPage.replace("_VANE_2_", "selected");
  }
  else if (strcmp(settings.vane, "3") == 0) {
    controlPage.replace("_VANE_3_", "selected");
  }
  else if (strcmp(settings.vane, "4") == 0) {
    controlPage.replace("_VANE_4_", "selected");
  }
  else if (strcmp(settings.vane, "5") == 0) {
    controlPage.replace("_VANE_5_", "selected");
  }
  else if (strcmp(settings.vane, "SWING") == 0) {
    controlPage.replace("_VANE_S_", "selected");
  }

  controlPage.replace("_WIDEVANE_V_", settings.wideVane);
  if (strcmp(settings.wideVane, "<<") == 0) {
    controlPage.replace("_WVANE_1_", "selected");
  }
  else if (strcmp(settings.wideVane, "<") == 0) {
    controlPage.replace("_WVANE_2_", "selected");
  }
  else if (strcmp(settings.wideVane, "|") == 0) {
    controlPage.replace("_WVANE_3_", "selected");
  }
  else if (strcmp(settings.wideVane, ">") == 0) {
    controlPage.replace("_WVANE_4_", "selected");
  }
  else if (strcmp(settings.wideVane, ">>") == 0) {
    controlPage.replace("_WVANE_5_", "selected");
  }
  else if (strcmp(settings.wideVane, "<>") == 0) {
    controlPage.replace("_WVANE_6_", "selected");
  }
  else if (strcmp(settings.wideVane, "SWING") == 0) {
    controlPage.replace("_WVANE_S_", "selected");
  }
  controlPage.replace("_TEMP_", String(convertCelsiusToLocalUnit(hp.getTemperature(), useFahrenheit)));

  sendWrappedHTML(request, controlPage);
  controlPage = "";
  // We need to send the page content in chunks to overcome
  // a limitation on the maximum size we can send at one
  // time (approx 6k).
}

void handleMetrics(AsyncWebServerRequest *request){
  String metrics =    FPSTR(html_metrics);

  heatpumpSettings currentSettings = hp.getSettings();
  heatpumpStatus currentStatus = hp.getStatus();

  String hppower = currentSettings.power == "ON" ? "1" : "0";

  String hpfan = currentSettings.fan;
  if(hpfan == "AUTO") hpfan = "-1";
  if(hpfan == "QUIET") hpfan = "0";

  String hpvane = currentSettings.vane;
  if(hpvane == "AUTO") hpvane = "-1";
  if(hpvane == "SWING") hpvane = "0";

  String hpwidevane = "-2";
  if(currentSettings.wideVane == "SWING") hpwidevane = "0";
  if(currentSettings.wideVane == "<<") hpwidevane = "1";
  if(currentSettings.wideVane == "<") hpwidevane = "2";
  if(currentSettings.wideVane == "|") hpwidevane = "3";
  if(currentSettings.wideVane == ">") hpwidevane = "4";
  if(currentSettings.wideVane == ">>") hpwidevane = "5";
  if(currentSettings.wideVane == "<>") hpwidevane = "6";

  String hpmode = "-2";
  if(currentSettings.mode == "AUTO") hpmode = "-1";
  if(currentSettings.mode == "COOL") hpmode = "1";
  if(currentSettings.mode == "DRY") hpmode = "2";
  if(currentSettings.mode == "HEAT") hpmode = "3";
  if(currentSettings.mode == "FAN") hpmode = "4";
  if(hppower == "0") hpmode = "0";

  metrics.replace("_UNIT_NAME_", hostname);
  metrics.replace("_VERSION_", m2mqtt_version);
  metrics.replace("_POWER_", hppower);
  metrics.replace("_ROOMTEMP_", (String)currentStatus.roomTemperature);
  metrics.replace("_TEMP_", (String)currentSettings.temperature);
  metrics.replace("_FAN_", hpfan);
  metrics.replace("_VANE_", hpvane);
  metrics.replace("_WIDEVANE_", hpwidevane);
  metrics.replace("_MODE_", hpmode);
  metrics.replace("_OPER_", (String)currentStatus.operating);
  metrics.replace("_COMPFREQ_", (String)currentStatus.compressorFrequency);
  sendWrappedHTML(request, metrics);

}

// login page, also called for logout
void handleLogin(AsyncWebServerRequest *request)
{
  bool loginSuccess = false;
  String msg;
  String loginPage = FPSTR(html_page_login);
  // localize
  loginPage.replace("_TXT_LOGIN_TITLE_", FPSTR(txt_login_title));
  loginPage.replace("_TXT_LOGIN_PASSWORD_", FPSTR(txt_login_password));
  loginPage.replace("_TXT_LOGIN_", FPSTR(txt_login));
  if (request->hasHeader("Cookie"))
  {
    // Found cookie;
    String cookie = request->header("Cookie");
  }
  if (request->hasArg("USERNAME") || request->hasArg("PASSWORD") || request->hasArg("LOGOUT"))
  {
    if (request->hasArg("LOGOUT"))
    {
      // logout
      loginSuccess = false;
    }
    if (request->hasArg("USERNAME") && request->hasArg("PASSWORD"))
    {
      if (request->arg("USERNAME") == login_username && request->arg("PASSWORD") == login_password)
      {
        loginSuccess = true;
        msg = F("<b><font color='red'>");
        msg += FPSTR(txt_login_sucess);
        msg += F("</font></b>");
        loginPage += F("<script>");
        loginPage += F("setTimeout(function () {");
        loginPage += F("window.location.href= '/';");
        loginPage += F("}, 3000);");
        loginPage += F("</script>");
        // Log in Successful;
      }
      else
      {
        msg = F("<b><font color='red'>");
        msg += FPSTR(txt_login_fail);
        msg += F("</font></b>");
        // Log in Failed;
      }
    }
  }
  else
  {
    if (is_authenticated(request) or login_password.length() == 0)
    {
      // use javascript in the case browser disable redirect
      String redirectPage = F("<html lang=\"en\" class=\"\"><head><meta charset='utf-8'>");
      redirectPage += F("<script>");
      redirectPage += F("setTimeout(function () {");
      redirectPage += F("window.location.href= '/';");
      redirectPage += F("}, 1000);");
      redirectPage += F("</script>");
      redirectPage += F("</body></html>");
      AsyncWebServerResponse *response = request->beginResponse(301, "text/html", redirectPage);
      response->addHeader("Location", "/");
      response->addHeader("Cache-Control", "no-cache");
      request->send(response);
      return;
    }
  }
  loginPage.replace(F("_LOGIN_SUCCESS_"), (String)loginSuccess);
  loginPage.replace(F("_LOGIN_MSG_"), msg);

  String headerContent = FPSTR(html_common_header);
  String footerContent = FPSTR(html_common_footer);
  String toSend(headerContent);
  toSend += loginPage;
  toSend += footerContent;
  toSend.replace(F("_UNIT_NAME_"), hostname);
  AsyncWebServerResponse *response = request->beginResponse(200, "text/html", toSend);
  if (loginSuccess)
  {
    response->addHeader("Set-Cookie", "M2MSESSIONID=1");
    response->addHeader("Cache-Control", "no-cache");
  }
  else
  {
    response->addHeader("Set-Cookie", "M2MSESSIONID=0");
    response->addHeader("Cache-Control", "no-cache");
  }
  request->send(response);
}

void handleUpgrade(AsyncWebServerRequest *request) {
  if (!checkLogin(request)) return;

  uploaderror = 0;
  String upgradePage = FPSTR(html_page_upgrade);
  upgradePage.replace("_TXT_B_UPGRADE_",FPSTR(txt_upgrade));
  upgradePage.replace("_TXT_BACK_",FPSTR(txt_back));
  upgradePage.replace("_TXT_UPGRADE_TITLE_",FPSTR(txt_upgrade_title));
  upgradePage.replace("_TXT_UPGRADE_INFO_",FPSTR(txt_upgrade_info));
  upgradePage.replace("_TXT_UPGRADE_START_",FPSTR(txt_upgrade_start));

  sendWrappedHTML(request, upgradePage);
}

void handleUploadDone(AsyncWebServerRequest *request) {
  //Serial.printl(PSTR("HTTP: Firmware upload done"));
  bool restartflag = false;
  String uploadDonePage = FPSTR(html_page_upload);
  String content = F("<div style='text-align:center;'><b>Upload ");
  if (uploaderror) {
    content += F("<span style='color:#d43535'>failed</span></b><br/><br/>");
    if (uploaderror == 1) {
      content += FPSTR(txt_upload_nofile);
    } else if (uploaderror == 2) {
      content += FPSTR(txt_upload_filetoolarge);
    } else if (uploaderror == 3) {
      content += FPSTR(txt_upload_fileheader);
    } else if (uploaderror == 4) {
      content += FPSTR(txt_upload_flashsize);
    } else if (uploaderror == 5) {
      content += FPSTR(txt_upload_buffer);
    } else if (uploaderror == 6) {
      content += FPSTR(txt_upload_failed);
    } else if (uploaderror == 7) {
      content += FPSTR(txt_upload_aborted);
    } else {
      content += FPSTR(txt_upload_error);
      content += String(uploaderror);
    }
    if (Update.hasError()) {
      content += FPSTR(txt_upload_code);
      content += String(Update.getError());
    }
  } else {
    content += F("<span style='color:#47c266; font-weight: bold;'>");
    content += FPSTR(txt_upload_sucess);
    content += F("</span><br/><br/>");
    content += FPSTR(txt_upload_refresh);
    content += F("<span id='count'>10s</span>...");
    content += FPSTR(count_down_script);
    restartflag = true;
  }
  content += F("</div><br/>");
  uploadDonePage.replace("_UPLOAD_MSG_", content);
  uploadDonePage.replace("_TXT_BACK_", FPSTR(txt_back));
  sendWrappedHTML(request, uploadDonePage);
  if (restartflag) {
    delay(500);
#ifdef ESP32
    ESP.restart();
#else
    ESP.reset();
#endif
  }
}


void handleUploadLoop(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
{
  // Based on https://github.com/lbernstone/asyncUpdate/blob/master/AsyncUpdate.ino
  if (uploaderror)
  {
    Update.end();
    return;
  }
  if (filename.c_str()[0] == 0)
  {
    uploaderror = 1;
    return;
  }
  if (!index)
  {
    ota_content_len = request->contentLength();
    // if filename includes spiffs, update the spiffs partition
    int cmd = (filename.indexOf("spiffs") > -1) ? U_PART : U_FLASH;
    // uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000; // 0x1000 start boot loader
#ifdef ESP8266
    Update.runAsync(true);
    if (!Update.begin(ota_content_len, cmd))
    {
#else
    if (!Update.begin(UPDATE_SIZE_UNKNOWN, cmd))
    {
#endif
      uploaderror = 2;
      return;
    }
  }
  if (!Update.hasError())
  {
    if (Update.write(data, len) != len)
    {
      uploaderror = 5;
#ifdef ESP8266
    }
    else
    {
#endif
    }
  }
  else
  {
    uploaderror = Update.getError();
    Update.end();
  }
  if (uploaderror)
  {
    Update.end();
    return;
  }

  if (final)
  {
    if (!Update.end(true))
    {
      uploaderror = 6;
    }
    else
    {

    }
  }
}

void write_log(String log) {
  File logFile = SPIFFS.open(console_file, "a");
  logFile.println(log);
  logFile.close();
}

heatpumpSettings change_states(AsyncWebServerRequest *request, heatpumpSettings settings) {
  if (request->hasArg("CONNECT")) {
    hp.connect(&Serial);
  }
  else {
    bool update = false;
    if (request->hasArg("POWER")) {
      settings.power = request->arg("POWER").c_str();
      update = true;
    }
    if (request->hasArg("MODE")) {
      settings.mode = request->arg("MODE").c_str();
      update = true;
    }
    if (request->hasArg("TEMP")) {
      settings.temperature = convertLocalUnitToCelsius(request->arg("TEMP").toInt(), useFahrenheit);
      update = true;
    }
    if (request->hasArg("FAN")) {
      settings.fan = request->arg("FAN").c_str();
      update = true;
    }
    if (request->hasArg("VANE")) {
      settings.vane = request->arg("VANE").c_str();
      update = true;
    }
    if (request->hasArg("WIDEVANE")) {
      settings.wideVane = request->arg("WIDEVANE").c_str();
      update = true;
    }
    if (update) {
      hp.setSettings(settings);
    }
  }
  return settings;
}

void readHeatPumpSettings() {
  heatpumpSettings currentSettings = hp.getSettings();

  rootInfo.clear();
  rootInfo["temperature"]     = convertCelsiusToLocalUnit(currentSettings.temperature, useFahrenheit);
  rootInfo["fan"]             = currentSettings.fan;
  rootInfo["vane"]            = currentSettings.vane;
  rootInfo["wideVane"]        = currentSettings.wideVane;
  rootInfo["mode"]            = hpGetMode(currentSettings);
}

void hpSettingsChanged() {
  // send room temp, operating info and all information
  readHeatPumpSettings();

  String mqttOutput;
  serializeJson(rootInfo, mqttOutput);

  if (!mqttClient.publish(ha_settings_topic.c_str(), 1, true, mqttOutput.c_str())) {
    if (_debugModeLogs) mqttClient.publish(ha_debug_logs_topic.c_str(), 1, false, (char*)("Failed to publish hp settings"));
  }

  hpStatusChanged(hp.getStatus());
}

String hpGetMode(heatpumpSettings hpSettings) {
  // Map the heat pump state to one of HA's HVAC_MODE_* values.
  // https://github.com/home-assistant/core/blob/master/homeassistant/components/climate/const.py#L3-L23

  String hppower = String(hpSettings.power);
  if (hppower.equalsIgnoreCase("off")){
    return "off";
  }

  String hpmode = String(hpSettings.mode);
  hpmode.toLowerCase();

  if (hpmode == "fan")       return "fan_only";
  else if (hpmode == "auto") return "heat_cool";
  else                       return hpmode; // cool, heat, dry
}

String hpGetAction(heatpumpStatus hpStatus, heatpumpSettings hpSettings) {
  // Map heat pump state to one of HA's CURRENT_HVAC_* values.
  // https://github.com/home-assistant/core/blob/master/homeassistant/components/climate/const.py#L80-L86

  String hppower = String(hpSettings.power);
  if (hppower.equalsIgnoreCase("off")) {
    return "off";
  }

  String hpmode = String(hpSettings.mode);
  hpmode.toLowerCase();

  if (hpmode == "fan")          return "fan";
  else if (!hpStatus.operating) return "idle";
  else if (hpmode == "auto")    return "idle";
  else if (hpmode == "cool")    return "cooling";
  else if (hpmode == "heat")    return "heating";
  else if (hpmode == "dry")     return "drying";
  else                          return hpmode; // unknown
}

void hpStatusChanged(heatpumpStatus currentStatus) {
  if (millis() - lastTempSend > SEND_ROOM_TEMP_INTERVAL_MS) { // only send the temperature every SEND_ROOM_TEMP_INTERVAL_MS (millis rollover tolerant)
    hpCheckRemoteTemp(); // if the remote temperature feed from mqtt is stale, disable it and revert to the internal thermometer.

    // send room temp, operating info and all information
    heatpumpSettings currentSettings = hp.getSettings();

    if (currentStatus.roomTemperature == 0) return;

    rootInfo.clear();
    rootInfo["roomTemperature"]     = convertCelsiusToLocalUnit(currentStatus.roomTemperature, useFahrenheit);
    rootInfo["temperature"]         = convertCelsiusToLocalUnit(currentSettings.temperature, useFahrenheit);
    rootInfo["fan"]                 = currentSettings.fan;
    rootInfo["vane"]                = currentSettings.vane;
    rootInfo["wideVane"]            = currentSettings.wideVane;
    rootInfo["mode"]                = hpGetMode(currentSettings);
    rootInfo["action"]              = hpGetAction(currentStatus, currentSettings);
    rootInfo["compressorFrequency"] = currentStatus.compressorFrequency;
    String mqttOutput;
    serializeJson(rootInfo, mqttOutput);

    if (!mqttClient.publish(ha_state_topic.c_str(), 1, false, mqttOutput.c_str())) {
      if (_debugModeLogs) mqttClient.publish(ha_debug_logs_topic.c_str(), 1, false, (char*)("Failed to publish hp status change"));
    }

    lastTempSend = millis();
  }
}

void hpCheckRemoteTemp(){
    if (remoteTempActive && (millis() - lastRemoteTemp > CHECK_REMOTE_TEMP_INTERVAL_MS)) { //if it's been 5 minutes since last remote_temp message, revert back to HP internal temp sensor
     remoteTempActive = false;
     float temperature = 0;
     hp.setRemoteTemperature(temperature);
     hp.update();
    }
}


void hpPacketDebug(byte* packet, unsigned int length, const char* packetDirection) {
  if (_debugModePckts) {
    String message;
    for (unsigned int idx = 0; idx < length; idx++) {
      if (packet[idx] < 16) {
        message += "0"; // pad single hex digits with a 0
      }
      message += String(packet[idx], HEX) + " ";
    }

    const size_t bufferSize = JSON_OBJECT_SIZE(10);
    StaticJsonDocument<bufferSize> root;

    root[packetDirection] = message;
    String mqttOutput;
    serializeJson(root, mqttOutput);
    if (!mqttClient.publish(ha_debug_pckts_topic.c_str(), 1, false, mqttOutput.c_str())) {
      mqttClient.publish(ha_debug_logs_topic.c_str(), 1, false, (char*)("Failed to publish to heatpump/debug topic"));
    }
  }
}

// Used to send a dummy packet in state topic to validate action in HA interface
// HA change GUI appareance before having a valid state from the unit
void hpSendLocalState() {

  String mqttOutput;
  serializeJson(rootInfo, mqttOutput);
  mqttClient.publish(ha_debug_pckts_topic.c_str(), 1, false,  mqttOutput.c_str());
  if (!mqttClient.publish(ha_state_topic.c_str(), 1, false, mqttOutput.c_str())) {
    if (_debugModeLogs) mqttClient.publish(ha_debug_logs_topic.c_str(), 1, false, (char*)("Failed to publish dummy hp status change"));
  }

  // Restart counter for waiting enought time for the unit to update before sending a state packet
  lastTempSend = millis();
}

void mqttCallback(char* topic, char* payload, unsigned int length) {

  // Copy payload into message buffer
  char message[length + 1];
  for (unsigned int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
  }
  message[length] = '\0';

  // HA topics
  // Receive power topic
  if (strcmp(topic, ha_mode_set_topic.c_str()) == 0) {
    String modeUpper = message;
    modeUpper.toUpperCase();
    if (modeUpper == "OFF") {
      rootInfo["mode"] = "off";
      rootInfo["action"] = "off";
      hpSendLocalState();
      hp.setPowerSetting("OFF");
    } else {
      if (modeUpper == "HEAT_COOL") {
        rootInfo["mode"] = "heat_cool";
        rootInfo["action"] = "idle";
        modeUpper = "AUTO";
      } else if (modeUpper == "HEAT") {
        rootInfo["mode"] = "heat";
        rootInfo["action"] = "heating";
      } else if (modeUpper == "COOL") {
        rootInfo["mode"] = "cool";
        rootInfo["action"] = "cooling";
      } else if (modeUpper == "DRY") {
        rootInfo["mode"] = "dry";
        rootInfo["action"] = "drying";
      } else if (modeUpper == "FAN_ONLY") {
        rootInfo["mode"] = "fan_only";
        rootInfo["action"] = "fan";
        modeUpper = "FAN";
      } else {
        return;
      }
      hpSendLocalState();
      hp.setPowerSetting("ON");
      hp.setModeSetting(modeUpper.c_str());
    }
  }
  else if (strcmp(topic, ha_temp_set_topic.c_str()) == 0) {
    float temperature = strtof(message, NULL);
    float temperature_c = convertLocalUnitToCelsius(temperature, useFahrenheit);
    if (temperature_c < min_temp || temperature_c > max_temp) {
      temperature_c = 23;
      rootInfo["temperature"] = convertCelsiusToLocalUnit(temperature_c, useFahrenheit);
    } else {
      rootInfo["temperature"] = temperature;
    }
    hpSendLocalState();
    hp.setTemperature(temperature_c);
  }
  else if (strcmp(topic, ha_fan_set_topic.c_str()) == 0) {
    rootInfo["fan"] = (String) message;
    hpSendLocalState();
    hp.setFanSpeed(message);
  }
  else if (strcmp(topic, ha_vane_set_topic.c_str()) == 0) {
    rootInfo["vane"] = (String) message;
    hpSendLocalState();
    hp.setVaneSetting(message);
  }
  else if (strcmp(topic, ha_wideVane_set_topic.c_str()) == 0) {
    rootInfo["wideVane"] = (String) message;
    hpSendLocalState();
    hp.setWideVaneSetting(message);
  }
  else if (strcmp(topic, ha_remote_temp_set_topic.c_str()) == 0) {
    float temperature = strtof(message, NULL);
    if (temperature == 0){ //Remote temp disabled by mqtt topic set
      remoteTempActive = false; //clear the remote temp flag
      hp.setRemoteTemperature(0.0);
    }
    else {
      remoteTempActive = true; //Remote temp has been pushed.
      lastRemoteTemp = millis(); //Note time
      hp.setRemoteTemperature(convertLocalUnitToCelsius(temperature, useFahrenheit));
    }
  }
  else if (strcmp(topic, ha_system_set_topic.c_str()) == 0) { // We receive command for board
    if (strcmp(message, "reboot") == 0) { // We receive reboot command
      ESP.restart();
    }
  }
  else if (strcmp(topic, ha_debug_pckts_set_topic.c_str()) == 0) { //if the incoming message is on the heatpump_debug_set_topic topic...
    if (strcmp(message, "on") == 0) {
      _debugModePckts = true;
      mqttClient.publish(ha_debug_pckts_topic.c_str(), 1, false, (char*)("Debug packets mode enabled"));
    } else if (strcmp(message, "off") == 0) {
      _debugModePckts = false;
      mqttClient.publish(ha_debug_pckts_topic.c_str(), 1, false, (char *)("Debug packets mode disabled"));
    }
  }
  else if (strcmp(topic, ha_debug_logs_set_topic.c_str()) == 0) { //if the incoming message is on the heatpump_debug_set_topic topic...
    if (strcmp(message, "on") == 0) {
      _debugModeLogs = true;
      mqttClient.publish(ha_debug_logs_topic.c_str(), 1, false, (char*)("Debug logs mode enabled"));
    } else if (strcmp(message, "off") == 0) {
      _debugModeLogs = false;
      mqttClient.publish(ha_debug_logs_topic.c_str(), 1, false, (char *)("Debug logs mode disabled"));
    }
  }
  else if(strcmp(topic, ha_custom_packet.c_str()) == 0) { //send custom packet for advance user
      String custom = message;

      // copy custom packet to char array
      char buffer[(custom.length() + 1)]; // +1 for the NULL at the end
      custom.toCharArray(buffer, (custom.length() + 1));

      byte bytes[20]; // max custom packet bytes is 20
      int byteCount = 0;
      char *nextByte;

      // loop over the byte string, breaking it up by spaces (or at the end of the line - \n)
      nextByte = strtok(buffer, " ");
      while (nextByte != NULL && byteCount < 20) {
        bytes[byteCount] = strtol(nextByte, NULL, 16); // convert from hex string
        nextByte = strtok(NULL, "   ");
        byteCount++;
      }

      // dump the packet so we can see what it is. handy because you can run the code without connecting the ESP to the heatpump, and test sending custom packets
      hpPacketDebug(bytes, byteCount, "customPacket");

      hp.sendCustomPacket(bytes, byteCount);
  }
  else {
    mqttClient.publish(ha_debug_logs_topic.c_str(), 1, false, strcat((char *)"heatpump: wrong mqtt topic: ", topic));
  }
}

void haConfig() {

  // send HA config packet
  // setup HA payload device
  const size_t capacity = JSON_ARRAY_SIZE(5) + 2 * JSON_ARRAY_SIZE(6) + JSON_ARRAY_SIZE(7) + JSON_OBJECT_SIZE(24) + 2048;
  DynamicJsonDocument haConfig(capacity);

  haConfig["name"]                          = nullptr;
  haConfig["unique_id"]                     = getId();

  JsonArray haConfigModes = haConfig.createNestedArray("modes");
  haConfigModes.add("heat_cool"); //native AUTO mode
  haConfigModes.add("cool");
  haConfigModes.add("dry");
  if (supportHeatMode) {
    haConfigModes.add("heat");
  }
  haConfigModes.add("fan_only");  //native FAN mode
  haConfigModes.add("off");


  haConfig["mode_cmd_t"]                    = ha_mode_set_topic;
  haConfig["mode_stat_t"]                   = ha_state_topic;
  haConfig["mode_stat_tpl"]                 = F("{{ value_json.mode if (value_json is defined and value_json.mode is defined and value_json.mode|length) else 'off' }}"); //Set default value for fix "Could not parse data for HA"
  haConfig["temp_cmd_t"]                    = ha_temp_set_topic;
  haConfig["temp_stat_t"]                   = ha_state_topic;
  haConfig["avty_t"]                        = ha_availability_topic; // MQTT last will (status) messages topic
  haConfig["pl_not_avail"]                  = mqtt_payload_unavailable; // MQTT offline message payload
  haConfig["pl_avail"]                      = mqtt_payload_available; // MQTT online message payload
  //Set default value for fix "Could not parse data for HA"
  String temp_stat_tpl_str                  = F("{% if (value_json is defined and value_json.temperature is defined) %}{% if (value_json.temperature|int >= ");
  temp_stat_tpl_str                        +=(String)convertCelsiusToLocalUnit(min_temp, useFahrenheit) + " and value_json.temperature|int <= ";
  temp_stat_tpl_str                        +=(String)convertCelsiusToLocalUnit(max_temp, useFahrenheit) + ") %}{{ value_json.temperature }}";
  temp_stat_tpl_str                        +="{% elif (value_json.temperature|int < " + (String)convertCelsiusToLocalUnit(min_temp, useFahrenheit) + ") %}" + (String)convertCelsiusToLocalUnit(min_temp, useFahrenheit) + "{% elif (value_json.temperature|int > " + (String)convertCelsiusToLocalUnit(max_temp, useFahrenheit) + ") %}" + (String)convertCelsiusToLocalUnit(max_temp, useFahrenheit) +  "{% endif %}{% else %}" + (String)convertCelsiusToLocalUnit(22, useFahrenheit) + "{% endif %}";
  haConfig["temp_stat_tpl"]                 = temp_stat_tpl_str;
  haConfig["curr_temp_t"]                   = ha_state_topic;
  String curr_temp_tpl_str                  = F("{{ value_json.roomTemperature if (value_json is defined and value_json.roomTemperature is defined and value_json.roomTemperature|int > ");
  curr_temp_tpl_str                        += (String)convertCelsiusToLocalUnit(1, useFahrenheit) + ") }}"; //Set default value for fix "Could not parse data for HA"
  haConfig["curr_temp_tpl"]                 = curr_temp_tpl_str;
  haConfig["min_temp"]                      = convertCelsiusToLocalUnit(min_temp, useFahrenheit);
  haConfig["max_temp"]                      = convertCelsiusToLocalUnit(max_temp, useFahrenheit);
  haConfig["temp_step"]                     = temp_step;
  haConfig["temperature_unit"]              = useFahrenheit ? "F" : "C";

  JsonArray haConfigFan_modes = haConfig.createNestedArray("fan_modes");
  haConfigFan_modes.add("AUTO");
  haConfigFan_modes.add("QUIET");
  haConfigFan_modes.add("1");
  haConfigFan_modes.add("2");
  haConfigFan_modes.add("3");
  haConfigFan_modes.add("4");

  haConfig["fan_mode_cmd_t"]                = ha_fan_set_topic;
  haConfig["fan_mode_stat_t"]               = ha_state_topic;
  haConfig["fan_mode_stat_tpl"]             = F("{{ value_json.fan if (value_json is defined and value_json.fan is defined and value_json.fan|length) else 'AUTO' }}"); //Set default value for fix "Could not parse data for HA"

  JsonArray haConfigSwing_modes = haConfig.createNestedArray("swing_modes");
  haConfigSwing_modes.add("AUTO");
  haConfigSwing_modes.add("1");
  haConfigSwing_modes.add("2");
  haConfigSwing_modes.add("3");
  haConfigSwing_modes.add("4");
  haConfigSwing_modes.add("5");
  haConfigSwing_modes.add("SWING");

  haConfig["swing_mode_cmd_t"]              = ha_vane_set_topic;
  haConfig["swing_mode_stat_t"]             = ha_state_topic;
  haConfig["swing_mode_stat_tpl"]           = F("{{ value_json.vane if (value_json is defined and value_json.vane is defined and value_json.vane|length) else 'AUTO' }}"); //Set default value for fix "Could not parse data for HA"
  haConfig["action_topic"]                  = ha_state_topic;
  haConfig["action_template"]               = F("{{ value_json.action if (value_json is defined and value_json.action is defined and value_json.action|length) else 'idle' }}"); //Set default value for fix "Could not parse data for HA"

  JsonObject haConfigDevice = haConfig.createNestedObject("device");

  haConfigDevice["ids"]   = mqtt_fn;
  haConfigDevice["name"]  = mqtt_fn;
  haConfigDevice["sw"]    = "Mitsubishi2MQTT " + String(m2mqtt_version);
  haConfigDevice["mdl"]   = "HVAC MITSUBISHI";
  haConfigDevice["mf"]    = "MITSUBISHI ELECTRIC";
  haConfigDevice["configuration_url"]    = "http://"+WiFi.localIP().toString();
  
  String mqttOutput;
  serializeJson(haConfig, mqttOutput);
  mqttClient.publish(ha_config_topic.c_str(), 1, true, mqttOutput.c_str());
}


void mqttConnect()
{
  ESP_LOGD(TAG, "Connecting to MQTT...");
  
  if (mqtt_server[0] != '\0' && mqtt_port[0] != '\0')
  {
    mqttClient.connect();
  }

  if (!mqtt_connected)
  {
    if (mqtt_attempts == 5)
    {
      mqtt_attempts = 0;
      lastMqttRetry = millis();
    }
    else
    {
      mqtt_attempts++;
    }
  }
}

bool connectWifi() {
#ifdef ESP32
  WiFi.setHostname(hostname.c_str());
#else
  WiFi.hostname(hostname.c_str());
#endif
  if (WiFi.getMode() != WIFI_STA) {
    WiFi.mode(WIFI_STA);
    delay(10);
  }
#ifdef ESP32
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
#endif
  WiFi.begin(ap_ssid.c_str(), ap_pwd.c_str());
  // Serial.println("Connecting to " + ap_ssid);
  wifi_timeout = millis() + 30000;
  while (WiFi.status() != WL_CONNECTED && millis() < wifi_timeout) {
    Serial.write('.');
    //Serial.print(WiFi.status());
    // wait 500ms, flashing the blue LED to indicate WiFi connecting...
    digitalWrite(blueLedPin, LOW);
    delay(250);
    digitalWrite(blueLedPin, HIGH);
    delay(250);
  }
  if (WiFi.status() != WL_CONNECTED) {
    // Serial.println(F("Failed to connect to wifi"));
    return false;
  }
  // Serial.println(F("Connected to "));
  // Serial.println(ap_ssid);
  // Serial.println(F("Ready"));
  // Serial.print("IP address: ");
    while (WiFi.localIP().toString() == "0.0.0.0" || WiFi.localIP().toString() == "") {
    // Serial.write('.');
    delay(500);
  }
  if (WiFi.localIP().toString() == "0.0.0.0" || WiFi.localIP().toString() == "") {
    // Serial.println(F("Failed to get IP address"));
    return false;
  }
  // Serial.println(WiFi.localIP());
  //ticker.detach(); // Stop blinking the LED because now we are connected:)
  //keep LED off (For Wemos D1-Mini)
  digitalWrite(blueLedPin, HIGH);
  return true;
}

// temperature helper functions
float toFahrenheit(float fromCelcius) {
  return round(1.8 * fromCelcius + 32.0);
}

float toCelsius(float fromFahrenheit) {
  return (fromFahrenheit - 32.0) / 1.8;
}

float convertCelsiusToLocalUnit(float temperature, bool isFahrenheit) {
  if (isFahrenheit) {
    return toFahrenheit(temperature);
  } else {
    return temperature;
  }
}

float convertLocalUnitToCelsius(float temperature, bool isFahrenheit) {
  if (isFahrenheit) {
    return toCelsius(temperature);
  } else {
    return temperature;
  }
}

String getTemperatureScale() {
  if (useFahrenheit) {
    return "F";
  } else {
    return "C";
  }
}

String getId() {
#ifdef ESP32
  uint64_t macAddress = ESP.getEfuseMac();
  uint32_t chipID = macAddress >> 24;
#else
  uint32_t chipID = ESP.getChipId();
#endif
  return String(chipID, HEX);
}

// Check if header is present and correct
bool is_authenticated(AsyncWebServerRequest *request)
{
  if (request->hasHeader("Cookie"))
  {
    // Found cookie;
    String cookie = String(request->getHeader("Cookie")->value().c_str());
    if (cookie.indexOf("M2MSESSIONID=1") != -1)
    {
      // Authentication Successful
      return true;
    }
  }
  // Authentication Failed
  return false;
}

bool checkLogin(AsyncWebServerRequest *request)
{
  if (!is_authenticated(request) and login_password.length() > 0)
  {
    // use javascript in the case browser disable redirect
    String redirectPage = F("<html lang=\"en\" class=\"\"><head><meta charset='utf-8'>");
    redirectPage += F("<script>");
    redirectPage += F("setTimeout(function () {");
    redirectPage += F("window.location.href= '/login';");
    redirectPage += F("}, 1000);");
    redirectPage += F("</script>");
    redirectPage += F("</body></html>");
    AsyncWebServerResponse *response = request->beginResponse(301, "text/html", redirectPage);
    response->addHeader("Location", "/login");
    response->addHeader("Cache-Control", "no-cache");
    request->send(response);
    return true;
  }
  return false;
}

void loop() {
  ArduinoOTA.handle();

  //reset board to attempt to connect to wifi again if in ap mode or wifi dropped out and time limit passed
  bool wifiConnected = WiFi.getMode() == WIFI_STA and WiFi.status() == WL_CONNECTED;
  if (wifiConnected) {
	  wifi_timeout = millis() + WIFI_RETRY_INTERVAL_MS;
  } else if (wifi_config_exists and millis() > wifi_timeout) {
	  ESP.restart();
  }

  if (!captive) {
    // Sync HVAC UNIT
    if (!hp.isConnected()) {
      // Use exponential backoff for retries, where each retry is double the length of the previous one.
      unsigned long durationNextSync = (1 << hpConnectionRetries) * HP_RETRY_INTERVAL_MS;
      if (((millis() - lastHpSync > durationNextSync) or lastHpSync == 0)) {
        lastHpSync = millis();
        // If we've retried more than the max number of tries, keep retrying at that fixed interval, which is several minutes.
        hpConnectionRetries = min(hpConnectionRetries + 1u, HP_MAX_RETRIES);
        hpConnectionTotalRetries++;
        hp.sync();
      }
    } else {
        hpConnectionRetries = 0;
        hp.sync();
    }

	if (mqtt_config) {
		//MQTT failed retry to connect
    if (wifiConnected && !mqtt_connected && ((millis() - lastMqttRetry > MQTT_RETRY_INTERVAL_MS)))
    {
      ESP_LOGD(TAG, "MQTT lost connection, retry from loop");
      mqttConnect();
    }
		//MQTT connected send status
		if(wifiConnected && mqtt_connected)
    {
		  hpStatusChanged(hp.getStatus());
		}
	}
  }
  else {
    dnsServer.processNextRequest();
  }
}

#ifdef ESP32
void WiFiEvent(WiFiEvent_t event) {
    ESP_LOGD(TAG, "[WiFi-event] event: %d\n", event);
    switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
        ESP_LOGD(TAG, "WiFi connected, IP address: %s", WiFi.localIP().toString().c_str());
        mqttConnect();
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        ESP_LOGD(TAG, "WiFi lost connection");
#ifdef ESP32
        xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
        xTimerStart(wifiReconnectTimer, 0);
#else
        mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
        wifiReconnectTimer.once(2, connectWifi);
#endif
        break;
    }
}
#elif defined(ESP8266)

void onWifiConnect(const WiFiEventStationModeGotIP& event) {
  ESP_LOGD(TAG, "Connected to Wi-Fi.");
  mqttConnect();
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  ESP_LOGD(TAG, "Disconnected from Wi-Fi.");
  mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
  wifiReconnectTimer.once(2, connectWifi);
}

#endif

void onMqttConnect(bool sessionPresent) {
  ESP_LOGD(TAG, "Connected to MQTT.");
  ESP_LOGD(TAG, "Session present: %d", sessionPresent);
  mqtt_connected = true;

  mqttClient.subscribe(ha_system_set_topic.c_str(), 1);
  mqttClient.subscribe(ha_debug_pckts_set_topic.c_str(), 1);
  mqttClient.subscribe(ha_debug_logs_set_topic.c_str(), 1);
  mqttClient.subscribe(ha_mode_set_topic.c_str(), 1);
  mqttClient.subscribe(ha_fan_set_topic.c_str(), 1);
  mqttClient.subscribe(ha_temp_set_topic.c_str(), 1);
  mqttClient.subscribe(ha_vane_set_topic.c_str(), 1);
  mqttClient.subscribe(ha_wideVane_set_topic.c_str(), 1);
  mqttClient.subscribe(ha_remote_temp_set_topic.c_str(), 1);
  mqttClient.subscribe(ha_custom_packet.c_str(), 1);
  // send online message
  mqttClient.publish(ha_availability_topic.c_str(), 1, true, mqtt_payload_available);
  haConfig();
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  mqtt_connected = false;
  mqtt_disconnected_reason = (uint8_t)reason;
  ESP_LOGE(TAG, "Disconnected from MQTT. reason: %d", reason);
  if (WiFi.isConnected())
  {
#ifdef ESP32
        xTimerStart(mqttReconnectTimer, 0);
#else
        mqttReconnectTimer.once(2, mqttConnect);
#endif
  }
}

// void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
//   ESP_LOGD(TAG, "Subscribe acknowledged. packetId: %d, qos: %d", packetId, qos);
// }

// void onMqttUnsubscribe(uint16_t packetId) {
//   ESP_LOGD(TAG, "Unsubscribe acknowledged. packetId:  %d", packetId);
// }

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  ESP_LOGD(TAG, "Publish received. topic: %s, qos: %d dup: %d, retain: %d", topic, properties.qos, properties.dup, properties.retain);
  ESP_LOGD(TAG, "Publish received. len: %d, index: %d, total: %d", len, index, total);
  mqttCallback(topic, payload, len);
}

void onMqttPublish(uint16_t packetId)
{
  ESP_LOGD(TAG, "Publish acknowledged. packetId:  %d", packetId);
}
