#include <ESP8266WiFi.h>      // WIFI for ESP8266
#include <ESP8266mDNS.h>      // mDNS for ESP8266
#include <ESP8266WebServer.h> // webServer for ESP8266
#include <ArduinoJson.h>      // json to process MQTT: ArduinoJson 6.11.4
#include <PubSubClient.h>     // MQTT: PubSubClient 2.7.0
#include <DNSServer.h>        // DNS for captive portal
#include "FS.h"               // SPIFFS for store config 
#include <math.h>             // for rounding to Fahrenheit values

#include <ArduinoOTA.h>   // for OTA
#include <HeatPump.h>     // Swiacago library: https://github.com/SwiCago/HeatPump
//#include <Ticker.h>     // for LED status (Using a Wemos D1-Mini)
#include "config.h"       // config file
#include "html_common.h"  // common code HTML (like header, footer)
#include "html_init.h"    // code html for initial config
#include "html_menu.h"    // code html for menu
#include "html_pages.h"   // code html for pages

//Ticker ticker;

// wifi, mqtt and heatpump client instances
WiFiClient espClient;
PubSubClient mqtt_client(espClient);

//Captive portal variables, only used for config page
const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
IPAddress netMsk(255, 255, 255, 0);
DNSServer dnsServer;
ESP8266WebServer server(80);
boolean captive = false;
boolean mqtt_config = false;
boolean wifi_config = false;

//HVAC
HeatPump hp;
unsigned long lastTempSend;
unsigned long lastMqttRetry;

void setup() {
  // Start serial for debug before HVAC connect to serial
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting Mitsubishi2MQTT");
  // Mount SPIFFS filesystem
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
  }

  //set led pin as output
  pinMode(blueLedPin, OUTPUT);
  /*
    ticker.attach(0.6, tick);
  */

  //Define hostname
  hostname += String(ESP.getChipId(), HEX);
  mqtt_client_id = hostname;
  WiFi.hostname(hostname);
  setDefaults();
  load_wifi();
  if (init_wifi()) {
    SPIFFS.remove(console_file);
    //write_log("Starting Mitsubishi2MQTT");
    //Web interface
    server.on("/", handle_root);
    server.on("/control", handle_control);
    server.on("/setup", handle_setup);
    server.on("/mqtt", handle_mqtt);
    server.on("/wifi", handle_wifi);
    server.on("/unit", handle_unit);
    server.on("/status", handle_status);
    server.on("/others", handle_others);
    server.onNotFound(handleNotFound);
    server.begin();
    lastMqttRetry = 0;
    if (load_mqtt()) {
      //write_log("Starting MQTT");
      // setup HA topics
      ha_power_set_topic    = mqtt_topic + "/" + mqtt_fn + "/power/set";
      ha_mode_set_topic     = mqtt_topic + "/" + mqtt_fn + "/mode/set";
      ha_temp_set_topic     = mqtt_topic + "/" + mqtt_fn + "/temp/set";
      ha_remote_temp_set_topic = mqtt_topic + "/" + mqtt_fn + "/remote_temp/set";
      ha_fan_set_topic      = mqtt_topic + "/" + mqtt_fn + "/fan/set";
      ha_vane_set_topic     = mqtt_topic + "/" + mqtt_fn + "/vane/set";
      ha_wideVane_set_topic = mqtt_topic + "/" + mqtt_fn + "/wideVane/set";
      ha_settings_topic     = mqtt_topic  + "/" + mqtt_fn + "/settings";
      ha_state_topic        = mqtt_topic  + "/" + mqtt_fn + "/state";
      ha_debug_topic        = mqtt_topic + "/" + mqtt_fn + "/debug";
      ha_debug_set_topic    = mqtt_topic + "/" + mqtt_fn + "/debug/set";
      ha_config_topic       = "homeassistant/climate/" + mqtt_fn + "/config";
      // startup mqtt connection
      init_MQTT();
    }
    else {
      //write_log("Not found MQTT config go to configuration page");
    }
    load_unit();
    Serial.println("Connection to HVAC. Stop serial log.");
    //write_log("Connection to HVAC");
    hp.setSettingsChangedCallback(hpSettingsChanged);
    hp.setStatusChangedCallback(hpStatusChanged);
    hp.setPacketCallback(hpPacketDebug);
    hp.connect(&Serial);
    lastTempSend = millis();
  }
  else {
    dnsServer.start(DNS_PORT, "*", apIP);
    init_captivePortal();
  }
  init_OTA();
}

/*
  void tick()
  {
  //toggle state
  int state = digitalRead(blueLedPin);  // get the current state of GPIO2 pin
  digitalWrite(blueLedPin, !state);     // set pin to the opposite state
  }*/

bool load_wifi() {
  ap_ssid = "";
  ap_pwd  = "";
  File configFile = SPIFFS.open(wifi_conf, "r");
  if (!configFile) {
    Serial.println("Failed to open wifi config file");
    return false;
  }
  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Wifi config file size is too large");
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
  ota_pwd  = doc["ota_pwd"].as<String>();
  return true;
}


void save_mqtt(String mqttFn, String mqttHost, String mqttPort, String mqttUser,
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
    Serial.println("failed to open config file for writing");
  }
  serializeJson(doc, Serial);
  serializeJson(doc, configFile);
  configFile.close();
}

void save_unit(String tempUnit) {
  const size_t capacity = JSON_OBJECT_SIZE(2) + 400;
  DynamicJsonDocument doc(capacity);
  // if mqtt port is empty, we use default port
  doc["unit_tempUnit"]   = tempUnit;
  File configFile = SPIFFS.open(unit_conf, "w");
  if (!configFile) {
    Serial.println("failed to open config file for writing");
  }
  serializeJson(doc, Serial);
  serializeJson(doc, configFile);
  configFile.close();
}


void save_wifi(String apSsid, String apPwd, String hostName, String otaPwd) {
  const size_t capacity = JSON_OBJECT_SIZE(4) + 130;
  DynamicJsonDocument doc(capacity);
  doc["ap_ssid"] = apSsid;
  doc["ap_pwd"] = apPwd;
  doc["hostname"] = hostName;
  doc["ota_pwd"] = otaPwd;
  File configFile = SPIFFS.open(wifi_conf, "w");
  if (!configFile) {
    Serial.println("failed to open wifi file for writing");
  }
  serializeJson(doc, Serial);
  serializeJson(doc, configFile);
  delay(10);
  configFile.close();
}

void save_others(String haa, String haat, String debug) {
  const size_t capacity = JSON_OBJECT_SIZE(3) + 130;
  DynamicJsonDocument doc(capacity);
  doc["haa"] = haa;
  doc["haat"] = haat;
  doc["debug"] = debug;
  File configFile = SPIFFS.open(others_conf, "w");
  if (!configFile) {
    Serial.println("failed to open wifi file for writing");
  }
  serializeJson(doc, configFile);
  delay(10);
  configFile.close();
}

// Initialize captive portal page
void init_captivePortal() {
  Serial.println("Starting captive portal");
  server.on("/", handle_init_setup);
  server.on("/save", handle_save_wifi);
  server.on("/reboot", handle_reboot);
  server.onNotFound(handleNotFound);
  server.begin();
  captive = true;
}

void init_MQTT() {
  mqtt_client.setServer(mqtt_server.c_str(), atoi(mqtt_port.c_str()));
  mqtt_client.setCallback(mqttCallback);
  mqttConnect();
}

// Enable OTA only when connected as a client.
void init_OTA() {
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
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}

bool load_mqtt() {
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

bool load_unit() {
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
  const size_t capacity = JSON_OBJECT_SIZE(2) + 400;
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, buf.get());
  String unit_tempUnit            = doc["unit_tempUnit"].as<String>();
  if (unit_tempUnit == "fah") useFahrenheit = true;
  return true;
}

void setDefaults() {
  ap_ssid = "";
  ap_pwd  = "";
  others_haa = "ON";
  others_haa_topic = "homeassistant";
  others_debug = "OFF";

}

boolean init_wifi() {
  if (ap_ssid[0] == '\0') {
    Serial.println("\n\r \n\rStarting in AP mode");
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, netMsk);
    WiFi.softAP(hostname.c_str());
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
    //ticker.attach(0.2, tick); // Start LED to flash rapidly to indicate we are ready for setting up the wifi-connection (entered captive portal).
    wifi_config = false;
    return false;
  }
  else {
    wifi_config = connectWifi();
    return wifi_config;
  }
}

// Handler webserver response

void handleNotFound() {
  if (captive) {
    server.send(200, "text/html", html_init_setup);
  }
  else {
    String toSend = html_common_header + html_menu_root + html_common_footer;
    server.send(200, "text/html", toSend);
  }
}

void handle_save_wifi() {
  Serial.println("Saving wifi config");
  if (server.hasArg("submit")) {
    save_wifi(server.arg("ssid"), server.arg("psk"), server.arg("hn"), server.arg("otapwd"));
  }
  String toSend = html_common_header + html_init_save + html_common_footer;
  toSend.replace("_UNIT_NAME_", hostname);
  toSend.replace("_VERSION_", m2mqtt_version);
  server.send(200, "text/html", toSend);
  delay(100);
  ESP.restart();
}

void handle_reboot() {
  Serial.println("Rebooting");
  String toSend = html_common_header + html_init_reboot + html_common_footer;
  toSend.replace("_UNIT_NAME_", hostname);
  toSend.replace("_VERSION_", m2mqtt_version);
  server.send(200, "text/html", toSend);
  delay(100);
  ESP.restart();
}

void handle_root() {
  if (server.hasArg("REBOOT")) {
    String toSend = html_common_header + html_page_reboot + html_common_footer;
    toSend.replace("_UNIT_NAME_", hostname);
    toSend.replace("_VERSION_", m2mqtt_version);
    server.send(200, "text/html", toSend);
    delay(10);
    ESP.reset();
  }
  else {
    String toSend = html_common_header + html_menu_root + html_common_footer;
    toSend.replace("_UNIT_NAME_", hostname);
    toSend.replace("_VERSION_", m2mqtt_version);
    server.send(200, "text/html", toSend);
  }
}

void handle_init_setup() {
  String toSend = html_common_header + html_init_setup + html_common_footer;
  toSend.replace("_UNIT_NAME_", hostname);
  toSend.replace("_VERSION_", m2mqtt_version);
  server.send(200, "text/html", toSend);
}

void handle_setup() {
  if (server.hasArg("RESET")) {
    String toSend = html_common_header + html_page_reset + html_common_footer;
    toSend.replace("_UNIT_NAME_", hostname);
    toSend.replace("_VERSION_", m2mqtt_version);
    server.send(200, "text/html", toSend);
    SPIFFS.format();
    delay(10);
    ESP.reset();
  }
  else {
    String toSend = html_common_header + html_menu_setup + html_common_footer;
    toSend.replace("_UNIT_NAME_", hostname);
    toSend.replace("_VERSION_", m2mqtt_version);
    server.send(200, "text/html", toSend);
  }

}

void handle_others() {
  if (server.hasArg("save")) {

  }
  else {
    String toSend = html_common_header + html_page_others + html_common_footer;
    toSend.replace("_UNIT_NAME_", mqtt_fn);
    toSend.replace("_VERSION_", m2mqtt_version);
    toSend.replace("_HAA_TOPIC_", others_haa_topic);
    if (strcmp(others_haa.c_str(), "ON") == 0) {
      toSend.replace("_HAA_ON_", "selected");
    }
    else {
      toSend.replace("_HAA_OFF_", "selected");
    }
    if (strcmp(others_debug.c_str(), "ON") == 0) {
      toSend.replace("_DEBUG_ON_", "selected");
    }
    else {
      toSend.replace("_DEBUG_OFF_", "selected");
    }
    server.send(200, "text/html", toSend);
  }

}

void handle_mqtt() {
  if (server.hasArg("save")) {
    save_mqtt(server.arg("fn"), server.arg("mh"), server.arg("ml"), server.arg("mu"), server.arg("mp"), server.arg("mt"));
    String toSend = html_common_header + html_page_save_reboot + html_common_footer;
    toSend.replace("_UNIT_NAME_", hostname);
    toSend.replace("_VERSION_", m2mqtt_version);
    server.send(200, "text/html", toSend);
    delay(10);
    ESP.reset();
  }
  else {
    String toSend = html_common_header + html_page_mqtt + html_common_footer;
    toSend.replace("_UNIT_NAME_", mqtt_fn);
    toSend.replace("_MQTT_HOST_", mqtt_server);
    toSend.replace("_MQTT_PORT_", String(mqtt_port));
    toSend.replace("_MQTT_USER_", mqtt_username);
    toSend.replace("_MQTT_PASSWORD_", mqtt_password);
    toSend.replace("_MQTT_TOPIC_", mqtt_topic);
    toSend.replace("_VERSION_", m2mqtt_version);
    server.send(200, "text/html", toSend);
  }
}

void handle_unit() {
  if (server.hasArg("save")) {
    save_unit(server.arg("tu"));
    String toSend = html_common_header + html_page_save_reboot + html_common_footer;
    toSend.replace("_UNIT_NAME_", hostname);
    toSend.replace("_VERSION_", m2mqtt_version);
    server.send(200, "text/html", toSend);
    delay(10);
    ESP.reset();
  }
  else {
    String toSend = html_common_header + html_page_unit + html_common_footer;
    toSend.replace("_UNIT_NAME_", mqtt_fn);
    toSend.replace("_VERSION_", m2mqtt_version);
    if (useFahrenheit) toSend.replace("_TU_FAH_", "selected");
    else toSend.replace("_TU_CEL_", "selected");
    server.send(200, "text/html", toSend);
  }
}

void handle_wifi() {
  if (server.hasArg("save")) {
    save_wifi(server.arg("ssid"), server.arg("psk"), server.arg("hn"), server.arg("otapwd"));
    String toSend = html_common_header + html_page_save_reboot + html_common_footer;
    toSend.replace("_UNIT_NAME_", hostname);
    toSend.replace("_VERSION_", m2mqtt_version);
    server.send(200, "text/html", toSend);
    delay(10);
    ESP.reset();
  }
  else {
    String toSend = html_common_header + html_page_wifi + html_common_footer;
    toSend.replace("_UNIT_NAME_", hostname);
    toSend.replace("_SSID_", ap_ssid);
    toSend.replace("_PSK_", ap_pwd);
    toSend.replace("_OTA_PWD_", ota_pwd);
    toSend.replace("_VERSION_", m2mqtt_version);
    server.send(200, "text/html", toSend);
  }

}

void handle_status() {
  String toSend = html_common_header + html_page_status + html_common_footer;
  if (server.hasArg("mrconn")) mqttConnect();
  toSend.replace("_UNIT_NAME_", hostname);
  toSend.replace("_VERSION_", m2mqtt_version);
  String connected = "<font color='green'><b>CONNECTED</b></font>";
  String disconnected = "<font color='red'><b>DISCONNECTED</b></font>";
  if ((Serial) and hp.isConnected()) toSend.replace("_HVAC_STATUS_", connected);
  else  toSend.replace("_HVAC_STATUS_", disconnected);
  if (mqtt_client.connected()) toSend.replace("_MQTT_STATUS_", connected);
  else toSend.replace("_MQTT_STATUS_", disconnected);
  toSend.replace("_MQTT_REASON_", String(mqtt_client.state()));
  toSend.replace("_WIFI_STATUS_", String(WiFi.RSSI()));
  server.send(200, "text/html", toSend);
}



void handle_control() {

  heatpumpSettings settings = hp.getSettings();
  settings = change_states(settings);
  String toSend = html_common_header + html_page_control + html_common_footer;
  //write_log("Enter HVAC control");
  toSend.replace("_UNIT_NAME_", hostname);
  toSend.replace("_VERSION_", m2mqtt_version);
  toSend.replace("_RATE_", "60");
  toSend.replace("_ROOMTEMP_", String(getTemperature(hp.getRoomTemperature(), useFahrenheit)));	  toSend.replace("_ROOMTEMP_", String(hp.getRoomTemperature()));
  toSend.replace("_USE_FAHRENHEIT_", (String)useFahrenheit);
  toSend.replace("_TEMP_SCALE_", getTemperatureScale());

  if (strcmp(settings.power, "ON") == 0) {
    toSend.replace("_POWER_ON_", "selected");
  }
  else if (strcmp(settings.power, "OFF") == 0) {
    toSend.replace("_POWER_OFF_", "selected");
  }

  if (strcmp(settings.mode, "HEAT") == 0) {
    toSend.replace("_MODE_H_", "selected");
  }
  else if (strcmp(settings.mode, "DRY") == 0) {
    toSend.replace("_MODE_D_", "selected");
  }
  else if (strcmp(settings.mode, "COOL") == 0) {
    toSend.replace("_MODE_C_", "selected");
  }
  else if (strcmp(settings.mode, "FAN") == 0) {
    toSend.replace("_MODE_F_", "selected");
  }
  else if (strcmp(settings.mode, "AUTO") == 0) {
    toSend.replace("_MODE_A_", "selected");
  }
  if (strcmp(settings.fan, "AUTO") == 0) {
    toSend.replace("_FAN_A_", "selected");
  }
  else if (strcmp(settings.fan, "QUIET") == 0) {
    toSend.replace("_FAN_Q_", "selected");
  }
  else if (strcmp(settings.fan, "1") == 0) {
    toSend.replace("_FAN_1_", "selected");
  }
  else if (strcmp(settings.fan, "2") == 0) {
    toSend.replace("_FAN_2_", "selected");
  }
  else if (strcmp(settings.fan, "3") == 0) {
    toSend.replace("_FAN_3_", "selected");
  }
  else if (strcmp(settings.fan, "4") == 0) {
    toSend.replace("_FAN_4_", "selected");
  }

  toSend.replace("_VANE_V_", settings.vane);
  if (strcmp(settings.vane, "AUTO") == 0) {
    toSend.replace("_VANE_A_", "selected");
  }
  else if (strcmp(settings.vane, "1") == 0) {
    toSend.replace("_VANE_1_", "selected");
  }
  else if (strcmp(settings.vane, "2") == 0) {
    toSend.replace("_VANE_2_", "selected");
  }
  else if (strcmp(settings.vane, "3") == 0) {
    toSend.replace("_VANE_3_", "selected");
  }
  else if (strcmp(settings.vane, "4") == 0) {
    toSend.replace("_VANE_4_", "selected");
  }
  else if (strcmp(settings.vane, "5") == 0) {
    toSend.replace("_VANE_5_", "selected");
  }
  else if (strcmp(settings.vane, "SWING") == 0) {
    toSend.replace("_VANE_S_", "selected");
  }
  toSend.replace("_WIDEVANE_V_", settings.wideVane);
  if (strcmp(settings.wideVane, "<<") == 0) {
    toSend.replace("_WVANE_1_", "selected");
  }
  else if (strcmp(settings.wideVane, "<") == 0) {
    toSend.replace("_WVANE_2_", "selected");
  }
  else if (strcmp(settings.wideVane, "|") == 0) {
    toSend.replace("_WVANE_3_", "selected");
  }
  else if (strcmp(settings.wideVane, ">") == 0) {
    toSend.replace("_WVANE_4_", "selected");
  }
  else if (strcmp(settings.wideVane, ">>") == 0) {
    toSend.replace("_WVANE_5_", "selected");
  }
  else if (strcmp(settings.wideVane, "SWING") == 0) {
    toSend.replace("_WVANE_S_", "selected");
  }
  toSend.replace("_TEMP_", String(getTemperature(hp.getTemperature(), useFahrenheit)));
  server.send(200, "text/html", toSend);
  delay(100);
}

void write_log(String log) {
  File logFile = SPIFFS.open(console_file.c_str(), "a");
  logFile.println(log);
  logFile.close();
}

heatpumpSettings change_states(heatpumpSettings settings) {
  if (server.hasArg("CONNECT")) {
    hp.connect(&Serial);
  }
  else {
    bool update = false;
    if (server.hasArg("POWER")) {
      settings.power = server.arg("POWER").c_str();
      update = true;
    }
    if (server.hasArg("MODE")) {
      settings.mode = server.arg("MODE").c_str();
      update = true;
    }
    if (server.hasArg("TEMP")) {
      settings.temperature = setTemperature(server.arg("TEMP").toInt(), useFahrenheit);
      update = true;
    }
    if (server.hasArg("FAN")) {
      settings.fan = server.arg("FAN").c_str();
      update = true;
    }
    if (server.hasArg("VANE")) {
      settings.vane = server.arg("VANE").c_str();
      update = true;
    }
    if (server.hasArg("WIDEVANE")) {
      settings.wideVane = server.arg("WIDEVANE").c_str();
      update = true;
    }
    if (update) {
      hp.setSettings(settings);
      hp.update();
    }
  }
  return settings;
}

void hpSettingsChanged() {
  // send room temp, operating info and all information
  heatpumpSettings currentSettings = hp.getSettings();

  const size_t bufferSizeInfo = JSON_OBJECT_SIZE(6);
  StaticJsonDocument<bufferSizeInfo> rootInfo;

  rootInfo["temperature"]     = getTemperature(currentSettings.temperature, useFahrenheit);
  rootInfo["fan"]             = currentSettings.fan;
  rootInfo["vane"]            = currentSettings.vane;

  String hppower = String(currentSettings.power);
  String hpmode = String(currentSettings.mode);

  hppower.toLowerCase();
  hpmode.toLowerCase();

  if (hpmode == "fan") {
    rootInfo["mode"] = "fan_only";
  }
  else if (hpmode == "auto") {
    rootInfo["mode"] = "heat_cool";
  }
  else {
    rootInfo["mode"] = hpmode.c_str();
  }

  if (hppower == "off") {
    rootInfo["mode"] = "off";
  }

  String mqttOutput;
  serializeJson(rootInfo, mqttOutput);

  if (!mqtt_client.publish(ha_settings_topic.c_str(), mqttOutput.c_str(), true)) {
    if (_debugMode) mqtt_client.publish(ha_debug_topic.c_str(), "failed to publish hp settings");
  }

  hpStatusChanged(hp.getStatus());
}

String hpGetMode() {
  heatpumpSettings currentSettings = hp.getSettings();
  String hppower = String(currentSettings.power);
  String hpmode = String(currentSettings.mode);
  hppower.toLowerCase();
  hpmode.toLowerCase();
  String result;
  if (hppower == "off") result = "off";
  else {
    if (hpmode == "fan") result = "fan_only";
    else if (hpmode == "auto") result = "heat_cool";
    else result = hpmode.c_str();
  }
  return result;
}

String hpGetAction() {
  heatpumpSettings currentSettings = hp.getSettings();
  String hppower = String(currentSettings.power);
  String hpmode = String(currentSettings.mode);
  hppower.toLowerCase();
  hpmode.toLowerCase();
  String result = "idle";
  if (hppower == "off") result = "off";
  else {
    if (hpmode == "auto") result = "auto";
    //        if (currentStatus.roomTemperature > currentSettings.temperature) result = "cooling"
    //        else result = "heating";
    else if (hpmode == "cool") result = "cooling";
    else if (hpmode == "heat") result = "heating";
    else if (hpmode == "dry")  result = "drying";
    else if (hpmode == "fan")  result = "idle";
  }
  return result;
}

void hpStatusChanged(heatpumpStatus currentStatus) {

  // send room temp, operating info and all information
  heatpumpSettings currentSettings = hp.getSettings();

  const size_t bufferSizeInfo = JSON_OBJECT_SIZE(7);
  StaticJsonDocument<bufferSizeInfo> rootInfo;

  rootInfo["roomTemperature"] = getTemperature(currentStatus.roomTemperature, useFahrenheit);
  rootInfo["temperature"]     = getTemperature(currentSettings.temperature, useFahrenheit);
  //rootInfo["operating"]       = currentStatus.operating;
  rootInfo["fan"]             = currentSettings.fan;
  rootInfo["vane"]            = currentSettings.vane;
  rootInfo["action"]          = hpGetAction();
  rootInfo["mode"]            = hpGetMode();
  String mqttOutput;
  serializeJson(rootInfo, mqttOutput);

  if (!mqtt_client.publish_P(ha_state_topic.c_str(), mqttOutput.c_str(), false)) {
    if (_debugMode) mqtt_client.publish(ha_debug_topic.c_str(), "failed to publish hp status change");
  }

}

void hpPacketDebug(byte* packet, unsigned int length, char* packetDirection) {
  if (_debugMode) {
    String message;
    for (int idx = 0; idx < length; idx++) {
      if (packet[idx] < 16) {
        message += "0"; // pad single hex digits with a 0
      }
      message += String(packet[idx], HEX) + " ";
    }

    const size_t bufferSize = JSON_OBJECT_SIZE(1);
    StaticJsonDocument<bufferSize> root;

    root[packetDirection] = message;
    String mqttOutput;
    serializeJson(root, mqttOutput);
    if (!mqtt_client.publish(ha_debug_topic.c_str(), mqttOutput.c_str())) {
      mqtt_client.publish(ha_debug_topic.c_str(), "failed to publish to heatpump/debug topic");
    }
  }
}

// Used to send a dummy packet in state topic to validate action in HA interface
void hpSendDummy(char* name, char* value, char* name2, char* value2) {

  //For sending dummy state packet
  const size_t bufferSizeInfo = JSON_OBJECT_SIZE(12);
  StaticJsonDocument<bufferSizeInfo> rootInfo;
  heatpumpStatus currentStatus = hp.getStatus();
  heatpumpSettings currentSettings = hp.getSettings();
  rootInfo["roomTemperature"] = getTemperature(currentStatus.roomTemperature, useFahrenheit);
  rootInfo["temperature"]     = getTemperature(currentSettings.temperature, useFahrenheit);
  rootInfo["fan"]             = currentSettings.fan;
  rootInfo["vane"]            = currentSettings.vane;
  rootInfo["action"]          = hpGetAction();
  rootInfo["mode"]            = hpGetMode();
  rootInfo[name] = value;
  if (name2 != "") rootInfo[name2] = value2;
  //Send dummy MQTT state packet before unit update
  String mqttOutput;
  serializeJson(rootInfo, mqttOutput);
  if (!mqtt_client.publish_P(ha_state_topic.c_str(), mqttOutput.c_str(), false)) {
    if (_debugMode) mqtt_client.publish(ha_debug_topic.c_str(), "failed to publish dummy hp status change");
  }
  // Restart counter for waiting enought time for the unit to update before sending a state packet
  lastTempSend = millis();
}


void mqttCallback(char* topic, byte* payload, unsigned int length) {

  // Copy payload into message buffer
  char message[length + 1];
  for (int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
  }
  message[length] = '\0';

  // HA topics
  // Receive power topic
  if (strcmp(topic, ha_power_set_topic.c_str()) == 0) {
    String modeUpper = message;
    modeUpper.toUpperCase();
    if (modeUpper == "OFF") {
      hp.setPowerSetting(modeUpper.c_str());
      hp.update();
    }
  }
  else if (strcmp(topic, ha_mode_set_topic.c_str()) == 0) {
    const size_t bufferSize = JSON_OBJECT_SIZE(2);
    StaticJsonDocument<bufferSize> root;
    root["mode"] = message;
    String modeUpper = message;
    modeUpper.toUpperCase();
    if (modeUpper == "HEAT_COOL") {
      modeUpper = "AUTO";
      hpSendDummy("mode", "heat_cool", "action", "idle");
    }
    if (modeUpper == "HEAT") {
      hpSendDummy("mode", "heat", "action", "heating");
    }
    if (modeUpper == "COOL") {
      hpSendDummy("mode", "cool", "action", "cooling");
    }
    if (modeUpper == "DRY") {
      hpSendDummy("mode", "dry", "action", "drying");

    }
    if (modeUpper == "FAN_ONLY") {
      modeUpper = "FAN";
      hpSendDummy("action", "fan_only", "mode", "fan_only");
    }
    if (modeUpper == "OFF") {
      hp.setPowerSetting("OFF");
      hpSendDummy("action", "off", "mode", "off");
    } else {
      //hpSendDummy("action","on");
      hp.setPowerSetting("ON");
      hp.setModeSetting(modeUpper.c_str());
    }
    hp.update();
  }
  else if (strcmp(topic, ha_temp_set_topic.c_str()) == 0) {
    float temperature = strtof(message, NULL);
    const size_t bufferSize = JSON_OBJECT_SIZE(2);
    StaticJsonDocument<bufferSize> root;
    root["temperature"] = message;
    hpSendDummy("temperature", message, "", "");
    hp.setTemperature(setTemperature(temperature, useFahrenheit));
    hp.update();
  }
  else if (strcmp(topic, ha_fan_set_topic.c_str()) == 0) {
    const size_t bufferSize = JSON_OBJECT_SIZE(2);
    StaticJsonDocument<bufferSize> root;
    root["fan"] = message;
    hpSendDummy("fan", message, "", "");
    hp.setFanSpeed(message);
    hp.update();
  }
  else if (strcmp(topic, ha_vane_set_topic.c_str()) == 0) {
    const size_t bufferSize = JSON_OBJECT_SIZE(2);
    StaticJsonDocument<bufferSize> root;
    root["vane"] = message;
    hpSendDummy("vane", message, "", "");
    hp.setVaneSetting(message);
    hp.update();
  }
  else if (strcmp(topic, ha_remote_temp_set_topic.c_str()) == 0) {
    float temperature = strtof(message, NULL);
    hp.setRemoteTemperature(temperature);
    hp.update();
  }
  else if (strcmp(topic, ha_debug_set_topic.c_str()) == 0) { //if the incoming message is on the heatpump_debug_set_topic topic...
    if (strcmp(message, "on") == 0) {
      _debugMode = true;
      mqtt_client.publish(ha_debug_topic.c_str(), "debug mode enabled");
    } else if (strcmp(message, "off") == 0) {
      _debugMode = false;
      mqtt_client.publish(ha_debug_topic.c_str(), "debug mode disabled");
    }
  } else {
    mqtt_client.publish(ha_debug_topic.c_str(), strcat("heatpump: wrong mqtt topic: ", topic));
  }
}

void haConfig() {

  // send HA config packet
  // setup HA payload device
  const size_t capacity = JSON_ARRAY_SIZE(5) + 2 * JSON_ARRAY_SIZE(6) + JSON_ARRAY_SIZE(7) + JSON_OBJECT_SIZE(24) + 2048;
  DynamicJsonDocument haConfig(capacity);

  haConfig["name"]                          = mqtt_fn;
  haConfig["unique_id"]                     = String(ESP.getChipId(), HEX);

  JsonArray haConfigModes = haConfig.createNestedArray("modes");
  haConfigModes.add("heat_cool"); //native AUTO mode
  haConfigModes.add("cool");
  haConfigModes.add("dry");
  haConfigModes.add("heat");
  haConfigModes.add("fan_only");  //native FAN mode
  haConfigModes.add("off");


  haConfig["mode_cmd_t"]                    = ha_mode_set_topic;
  haConfig["mode_stat_t"]                   = ha_state_topic;
  haConfig["mode_stat_tpl"]                 = "{{ value_json.mode if (value_json is defined and value_json.mode is defined and value_json.mode|length) else 'off' }}"; //Set default value for fix "Could not parse data for HA"
  haConfig["temp_cmd_t"]                    = ha_temp_set_topic;
  haConfig["temp_stat_t"]                   = ha_state_topic;
  haConfig["temp_stat_tpl"]                 = "{{ value_json.temperature if (value_json is defined and value_json.temperature is defined and value_json.temperature|int > " + (String)getTemperature(16, useFahrenheit) + ") else '" + (String)getTemperature(26, useFahrenheit) + "' }}"; //Set default value for fix "Could not parse data for HA"
  haConfig["curr_temp_t"]                   = ha_state_topic;
  haConfig["curr_temp_tpl"]                 = "{{ value_json.roomTemperature if (value_json is defined and value_json.roomTemperature is defined and value_json.roomTemperature|int > " + (String)getTemperature(8, useFahrenheit) + ") else '" + (String)getTemperature(26, useFahrenheit) + "' }}"; //Set default value for fix "Could not parse data for HA"
  haConfig["min_temp"]                      = min_temp;
  haConfig["max_temp"]                      = max_temp;
  haConfig["temp_step"]                     = temp_step;
  haConfig["pow_cmd_t"]                     = ha_power_set_topic;

  JsonArray haConfigFan_modes = haConfig.createNestedArray("fan_modes");
  haConfigFan_modes.add("AUTO");
  haConfigFan_modes.add("QUIET");
  haConfigFan_modes.add("1");
  haConfigFan_modes.add("2");
  haConfigFan_modes.add("3");
  haConfigFan_modes.add("4");

  haConfig["fan_mode_cmd_t"]                = ha_fan_set_topic;
  haConfig["fan_mode_stat_t"]               = ha_state_topic;
  haConfig["fan_mode_stat_tpl"]             = "{{ value_json.fan if (value_json is defined and value_json.fan is defined and value_json.fan|length) else 'AUTO' }}"; //Set default value for fix "Could not parse data for HA"

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
  haConfig["swing_mode_stat_tpl"]           = "{{ value_json.vane if (value_json is defined and value_json.vane is defined and value_json.vane|length) else 'AUTO' }}"; //Set default value for fix "Could not parse data for HA"
  haConfig["action_topic"]                  = ha_state_topic;
  haConfig["action_template"]               = "{{ value_json.action if (value_json is defined and value_json.action is defined and value_json.action|length) else 'idle' }}"; //Set default value for fix "Could not parse data for HA"

  JsonObject haConfigDevice = haConfig.createNestedObject("device");

  haConfigDevice["ids"]   = mqtt_fn;
  haConfigDevice["name"]  = mqtt_fn;
  haConfigDevice["sw"]    = "Mitsubishi2MQTT " + m2mqtt_version;
  haConfigDevice["mdl"]   = "HVAC MITSUBISHI";
  haConfigDevice["mf"]    = "MITSUBISHI ELECTRIC";

  String mqttOutput;
  serializeJson(haConfig, mqttOutput);
  mqtt_client.beginPublish(ha_config_topic.c_str(), mqttOutput.length(), true);
  mqtt_client.print(mqttOutput);
  mqtt_client.endPublish();
}

void mqttConnect() {
  // Loop until we're reconnected
  int attempts = 0;
  while (!mqtt_client.connected()) {
    // Attempt to connect
    mqtt_client.connect(mqtt_client_id.c_str(), mqtt_username.c_str(), mqtt_password.c_str());
    // If state < 0 (MQTT_CONNECTED) => network problem we retry 5 times and then waiting for MQTT_RETRY_INTERVAL_MS and retry reapeatly
    if (mqtt_client.state() < MQTT_CONNECTED) {
      if (attempts == 5) {
        lastMqttRetry = millis();
        return;
      }
      else {
        delay(10);
        attempts++;
      }
    }
    // If state > 0 (MQTT_CONNECTED) => config or server problem we stop retry
    else if (mqtt_client.state() > MQTT_CONNECTED) {
      return;
    }
    // We are connected
    else    {
      mqtt_client.subscribe(ha_debug_set_topic.c_str());
      mqtt_client.subscribe(ha_power_set_topic.c_str());
      mqtt_client.subscribe(ha_mode_set_topic.c_str());
      mqtt_client.subscribe(ha_fan_set_topic.c_str());
      mqtt_client.subscribe(ha_temp_set_topic.c_str());
      mqtt_client.subscribe(ha_vane_set_topic.c_str());
      haConfig();
    }
  }
}

bool connectWifi() {
  WiFi.hostname(hostname);
  if (WiFi.getMode() != WIFI_STA) {
    WiFi.mode(WIFI_STA);
    delay(10);
  }
  WiFi.begin(ap_ssid, ap_pwd);
  Serial.println("Connecting to " + ap_ssid);
  unsigned long wifiStartTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - wifiStartTime < 10000) {
    Serial.write('.');
    //Serial.print(WiFi.status());
    // wait 500ms, flashing the blue LED to indicate WiFi connecting...
    digitalWrite(blueLedPin, LOW);
    delay(250);
    digitalWrite(blueLedPin, HIGH);
    delay(250);
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("");
    Serial.print("Failed to connect to wifi");
    return false;
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ap_ssid);
  Serial.println("Ready");
  Serial.print("IP address: ");
  unsigned long dhcpStartTime = millis();
  while ((WiFi.localIP().toString() == "0.0.0.0" || WiFi.localIP().toString() == "") && millis() - dhcpStartTime < 5000) {
    Serial.write('.');
    delay(500);
  }
  if (WiFi.localIP().toString() == "0.0.0.0" || WiFi.localIP().toString() == "") {
    Serial.println("");
    Serial.print("Failed to get IP address");
    return false;
  }
  Serial.println(WiFi.localIP());
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

float getTemperature(float temperature, bool isFahrenheit) {
  if (isFahrenheit) {
    return toFahrenheit(temperature);
  } else {
    return temperature;
  }
}

float setTemperature(float temperature, bool isFahrenheit) {
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

void loop() {
  server.handleClient();
  ArduinoOTA.handle();
  if (!captive and mqtt_config) {
    // Sync HVAC UNIT
    hp.sync();
    //MQTT failed retry to connect
    if (mqtt_client.state() < MQTT_CONNECTED)
    {
      if ((millis() > (lastMqttRetry + MQTT_RETRY_INTERVAL_MS)) or lastMqttRetry == 0) {
        mqttConnect();
      }
    }
    //MQTT config problem on MQTT do nothing
    else if (mqtt_client.state() > MQTT_CONNECTED ) return;
    //MQTT connected send status
    else {
      if (millis() > (lastTempSend + SEND_ROOM_TEMP_INTERVAL_MS)) { // only send the temperature every SEND_ROOM_TEMP_INTERVAL_MS
        hpStatusChanged(hp.getStatus());
        lastTempSend = millis();
      }
      mqtt_client.loop();
    }
  }
  else {
    dnsServer.processNextRequest();
  }
}
