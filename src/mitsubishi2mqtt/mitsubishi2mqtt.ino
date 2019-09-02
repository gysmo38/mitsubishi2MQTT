#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <HeatPump.h>
#include <DNSServer.h>
#include "FS.h"

#include "config.h"
#include "web_interface.h"

#ifdef OTA
#include <ArduinoOTA.h>
#endif

// wifi, mqtt and heatpump client instances
WiFiClient espClient;
PubSubClient mqtt_client(espClient);;

//Captive portal variables, only used for config page
const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
IPAddress netMsk(255, 255, 255, 0);
DNSServer dnsServer;
ESP8266WebServer server(80);
boolean captive = false;
boolean mqtt_config = false;

//HVAC
HeatPump hp;
unsigned long lastTempSend;

void setup() {
  //Define hostname
  hostname += String(ESP.getChipId(),HEX);
  mqtt_client_id = hostname;
  WiFi.hostname(hostname);
  setDefaults();
  load_wifi();
  if (init_wifi()) {
    SPIFFS.remove(console_file);  
    write_log("Starting Mitsubishi2MQTT...");
    init_OTA();
    //Web interface
    server.on("/", handle_root);
    server.on("/control", handle_control);
    server.on("/setup", handle_setup);
    server.on("/mqtt", handle_mqtt);
    server.on("/wifi", handle_wifi);
    server.on("/console", handle_console);
    server.on("/generate_204", handle_root);
    server.onNotFound(handleNotFound);
    server.begin();
    if(load_mqtt()) {
      write_log("Starting MQTT");
      // startup mqtt connection
      init_MQTT();
  
      // setup HA topics
      ha_power_set_topic    = mqtt_topic + "/" + mqtt_fn + "/power/set";
      ha_mode_set_topic     = mqtt_topic + "/" + mqtt_fn + "/mode/set";
      ha_temp_set_topic     = mqtt_topic + "/" + mqtt_fn + "/temp/set";
      ha_fan_set_topic      = mqtt_topic + "/" + mqtt_fn + "/fan/set";
      ha_vane_set_topic     = mqtt_topic + "/" + mqtt_fn + "/vane/set";
      ha_wideVane_set_topic = mqtt_topic + "/" + mqtt_fn + "/wideVane/set";
      ha_state_topic        = mqtt_topic  + "/" + mqtt_fn + "/state";
      ha_debug_topic        = mqtt_topic + "/" + mqtt_fn + "/debug";
      ha_debug_set_topic    = mqtt_topic + "/" + mqtt_fn + "/debug/set";
      ha_config_topic       = "homeassistant/climate/" + mqtt_fn + "/config";

      write_log("Connection to HVAC");

      hp.setSettingsChangedCallback(hpSettingsChanged);
      hp.setStatusChangedCallback(hpStatusChanged);
      hp.setPacketCallback(hpPacketDebug);
      hp.connect(&Serial);
      lastTempSend = millis();
    }
    else {
      write_log("Not found MQTT config go to configuration page");
    }
  }
  else {
    dnsServer.start(DNS_PORT, "*", apIP);
    init_captivePortal();
  }
}

bool load_wifi() {
  Serial.println("Loading wifi configuration");
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return false;
  }
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
  Serial.println("Hotname: "+hostname);
  Serial.println("SSID: "+ap_ssid);
  Serial.println("PSK: "+ap_pwd);
  Serial.println("OTA pwd: "+ota_pwd);

  return true;
}


void save_mqtt(String mqttFn, String mqttHost, String mqttPort, String mqttUser,
                 String mqttPwd, String mqttTopic) {

  const size_t capacity = JSON_OBJECT_SIZE(50);
  DynamicJsonDocument doc(capacity);
  doc["mqtt_fn"]   = mqttFn;
  doc["mqtt_host"] = mqttHost;
  doc["mqtt_port"] = mqttPort;
  doc["mqtt_user"] = mqttUser;
  doc["mqtt_pwd"] = mqttPwd;
  doc["mqtt_topic"] = mqttTopic;
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  File configFile = SPIFFS.open(mqtt_conf, "w");
  if (!configFile) {
    Serial.println("failed to open config file for writing");
  }
  serializeJson(doc, Serial);
  serializeJson(doc, configFile);
  configFile.close();
}

void save_wifi(String apSsid, String apPwd, String hostName, String otaPwd) {

  const size_t capacity = JSON_OBJECT_SIZE(4) + 110;
  DynamicJsonDocument doc(capacity);
  doc["ap_ssid"] = apSsid;
  doc["ap_pwd"] = apPwd;
  doc["hostname"] = hostName;
  doc["ota_pwd"] = otaPwd;
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  SPIFFS.format();
  File configFile = SPIFFS.open(wifi_conf, "w");
  if (!configFile) {
    Serial.println("failed to open wifi file for writing");
  }
  serializeJson(doc, Serial);
  serializeJson(doc, configFile);
  delay(10);
  configFile.close();
}

// Initialize captive portal page
void init_captivePortal() {
  Serial.println("Starting captive portal");
  server.on("/", handle_init_setup);
  server.on("/save", handle_save_wifi);
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
  write_log("Start OTA Listener");
  ArduinoOTA.setHostname(hostname.c_str());
  if(ota_pwd.length()>0){
     ArduinoOTA.setPassword(ota_pwd.c_str());
  }
  ArduinoOTA.onStart([]() {
    write_log("Start");
  });
  ArduinoOTA.onEnd([]() {
    write_log("\nEnd");
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
  write_log("Loading MQTT configuration");

  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return false;
  }
  File configFile = SPIFFS.open(mqtt_conf, "r");
  if (!configFile) {
    write_log("Failed to open MQTT config file");
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    write_log("Config file size is too large");
    return false;
  }
  std::unique_ptr<char[]> buf(new char[size]);

  configFile.readBytes(buf.get(), size);
  const size_t capacity = JSON_OBJECT_SIZE(20) + 130;
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, buf.get());
  mqtt_fn             = doc["mqtt_fn"].as<String>();
  mqtt_server         = doc["mqtt_host"].as<String>();
  mqtt_port           = doc["mqtt_port"].as<String>();
  mqtt_username       = doc["mqtt_user"].as<String>();
  mqtt_password       = doc["mqtt_pwd"].as<String>();
  mqtt_topic          = doc["mqtt_topic"].as<String>();

  write_log("=== START DEBUG MQTT ===");
  write_log("Friendly Name" + mqtt_fn);
  write_log("IP Server " + mqtt_server);
  write_log("IP Port " + mqtt_port);
  write_log("Username " + mqtt_username);
  write_log("Password " + mqtt_password);
  write_log("Topic " + mqtt_topic);
  write_log("=== END DEBUG MQTT ===");
  
  mqtt_config = true;
  return true;
}

void setDefaults() {
  ap_ssid = "";
  ap_pwd  = "";
}

boolean init_wifi() {
  if (ap_ssid[0] == '\0') {
    Serial.println("\n\r \n\rStarting in AP mode");
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, netMsk);
    WiFi.softAP(hostname.c_str());
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
    return false;
  }
  else {
    WiFi.hostname(hostname);
    if (WiFi.getMode() != WIFI_STA) {
      WiFi.mode(WIFI_STA);
      delay(10);
    }
    WiFi.begin(ap_ssid, ap_pwd);
    Serial.println("\n\r \n\rConnecting to "+ ap_ssid);
    unsigned long startTime = millis();
      while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) {
      Serial.write('.');
      //Serial.print(WiFi.status());
      delay(500);
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ap_ssid);
    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    return true;
  }
}

// Handler webserver response

void handleNotFound() {
  server.send(200, "text/html", html_init_setup);
}

void handle_save_wifi() {
  Serial.println("Saving wifi config");
  if (server.hasArg("submit")) {
    save_wifi(server.arg("ssid"), server.arg("psk"), server.arg("hn"),server.arg("otapwd"));
  }
  String toSend = html_header + html_init_save + html_footer;
  toSend.replace("_UNIT_NAME_", hostname);
  toSend.replace("_VERSION_", m2mqtt_version);
  server.send(200, "text/html", toSend);
  delay(100);
  ESP.restart();
}

void handle_root() {
  if (server.hasArg("REBOOT")) {
    String toSend = html_header + html_reboot + html_footer;
    toSend.replace("_UNIT_NAME_", hostname);
    toSend.replace("_VERSION_", m2mqtt_version);
    server.send(200,"text/html",toSend);
    delay(10);
    ESP.reset();
  }
  else {
    String toSend = html_header + html_root + html_footer;  
    toSend.replace("_UNIT_NAME_", hostname);
    toSend.replace("_VERSION_", m2mqtt_version);
    server.send(200, "text/html", toSend);
  }
}

void handle_init_setup() {
  String toSend = html_header + html_init_setup + html_footer;
  toSend.replace("_UNIT_NAME_", hostname);
  toSend.replace("_VERSION_", m2mqtt_version);
  server.send(200, "text/html", toSend);
}

void handle_setup() {
    if (server.hasArg("RESET")) {
      String toSend = html_header + html_reset + html_footer;
      toSend.replace("_UNIT_NAME_", hostname);
      toSend.replace("_VERSION_", m2mqtt_version);
      server.send(200,"text/html",toSend);
      SPIFFS.format();
      delay(10);
      ESP.reset();
  }
  else {
    String toSend = html_header + html_setup + html_footer;
    toSend.replace("_UNIT_NAME_", hostname);
    toSend.replace("_VERSION_", m2mqtt_version);
    server.send(200, "text/html", toSend);
  }

}

void handle_mqtt() {
  if (server.hasArg("save")) {
    save_mqtt(server.arg("fn"),server.arg("mh"),server.arg("ml"),server.arg("mu"),server.arg("mp"),server.arg("mt"));
    String toSend = html_header + html_save_reboot + html_footer;
    toSend.replace("_UNIT_NAME_", hostname);
    toSend.replace("_VERSION_", m2mqtt_version);
    server.send(200, "text/html", toSend);
    delay(10);
    ESP.reset();
  }
  else {
    String toSend = html_header + html_mqtt + html_footer;
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

void handle_wifi() {
  if (server.hasArg("save")) {
    save_wifi(server.arg("ssid"),server.arg("psk"),server.arg("hn"),server.arg("otapwd"));
    String toSend = html_header + html_save_reboot + html_footer;
    toSend.replace("_UNIT_NAME_", hostname);
    toSend.replace("_VERSION_", m2mqtt_version);
    server.send(200, "text/html", toSend);
    delay(10);
    ESP.reset();
  }
  else {
    String toSend = html_header + html_wifi + html_footer;
    toSend.replace("_UNIT_NAME_", hostname);
    toSend.replace("_SSID_", ap_ssid);
    toSend.replace("_PSK_", ap_pwd);
    toSend.replace("_OTA_PWD_", ota_pwd);
    toSend.replace("_VERSION_", m2mqtt_version);
    server.send(200, "text/html", toSend);
  }

}

void handle_console() {
  String toSend = html_header + html_console + html_footer;
  toSend.replace("_UNIT_NAME_", hostname);
  toSend.replace("_VERSION_", m2mqtt_version);
  File logFile = SPIFFS.open(console_file.c_str(),"r");
  String logBuffer;
  if(!logFile) {
    toSend.replace("_CONSOLE_", "Open log file failed");
  }
  else {
    while(logFile.available()) {
      logBuffer += logFile.readString();
    }
    toSend.replace("_CONSOLE_",logBuffer.c_str());
  }
  logFile.close();
  server.send(200, "text/html", toSend);
}



void handle_control() {
  write_log("Enter HVAC control");
  heatpumpSettings settings = hp.getSettings();
  settings = change_states(settings);
  String toSend = html_control;
  toSend.replace("_UNIT_NAME_", hostname);
  toSend.replace("_VERSION_", m2mqtt_version);
  toSend.replace("_RATE_", "60");
  toSend.replace("_ROOMTEMP_", String(hp.getRoomTemperature()));
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
  toSend.replace("_TEMP_", String(hp.getTemperature()));
  server.send(200, "text/html", toSend);
}

void write_log(String log) {
  File logFile = SPIFFS.open(console_file.c_str(),"a");
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
      settings.temperature = server.arg("TEMP").toInt();
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

  rootInfo["roomTemperature"] = hp.getRoomTemperature();
  rootInfo["temperature"]     = currentSettings.temperature;
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

  if (!mqtt_client.publish(ha_state_topic.c_str(), mqttOutput.c_str(), true)) {
    mqtt_client.publish(ha_debug_topic.c_str(), "failed to publish hp status");
  }
}

void hpStatusChanged(heatpumpStatus currentStatus) {
 
  // send room temp, operating info and all information
  heatpumpSettings currentSettings = hp.getSettings();

  const size_t bufferSizeInfo = JSON_OBJECT_SIZE(7);
  StaticJsonDocument<bufferSizeInfo> rootInfo;

  rootInfo["roomTemperature"] = hp.getRoomTemperature();
  rootInfo["temperature"]     = currentSettings.temperature;
 // rootInfo["hvac_action"]     = currentStatus.operating;;
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

  if (!mqtt_client.publish(ha_state_topic.c_str(), mqttOutput.c_str())) {
    mqtt_client.publish(ha_debug_topic.c_str(), "failed to publish hp status change");
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

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  // Copy payload into message buffer
  char message[length + 1];
  for (int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
  }
  message[length] = '\0';

  // HA topics
  if (strcmp(topic, ha_power_set_topic.c_str()) == 0) {
    String offUpper = message;
    offUpper.toUpperCase();
    if(offUpper == "OFF"){
      hp.setPowerSetting(offUpper.c_str());
      hp.update(); 
    }
  }
  else if (strcmp(topic, ha_mode_set_topic.c_str()) == 0) {
    const size_t bufferSize = JSON_OBJECT_SIZE(2);
    StaticJsonDocument<bufferSize> root;
    root["mode"] = message;
    String mqttOutput;
    serializeJson(root, mqttOutput);
    mqtt_client.publish(ha_state_topic.c_str(), mqttOutput.c_str());
    String modeUpper = message;
    modeUpper.toUpperCase();
    if(modeUpper=="HEAT_COOL"){
      modeUpper = "AUTO";
    }
    if(modeUpper=="FAN_ONLY"){
      modeUpper = "FAN";
    }
    if(modeUpper=="OFF"){
      hp.setPowerSetting("OFF");
    }else{
      hp.setPowerSetting("ON"); 
    }
    hp.setModeSetting(modeUpper.c_str());
    hp.update();
  }
  else if (strcmp(topic, ha_temp_set_topic.c_str()) == 0) {
    float temperature = strtof(message, NULL);
    const size_t bufferSize = JSON_OBJECT_SIZE(2);
    StaticJsonDocument<bufferSize> root;
    root["temperature"] = message;
    String mqttOutput;
    serializeJson(root, mqttOutput);
    mqtt_client.publish(ha_state_topic.c_str(), mqttOutput.c_str());
    hp.setTemperature(temperature);
    hp.update();
  }
  else if (strcmp(topic, ha_fan_set_topic.c_str()) == 0) {
    const size_t bufferSize = JSON_OBJECT_SIZE(2);
    StaticJsonDocument<bufferSize> root;
    root["fan"] = message;
    String mqttOutput;
    serializeJson(root, mqttOutput);
    mqtt_client.publish(ha_state_topic.c_str(), mqttOutput.c_str());
    hp.setFanSpeed(message);
    hp.update();
  }
  else if (strcmp(topic, ha_vane_set_topic.c_str()) == 0) {
    const size_t bufferSize = JSON_OBJECT_SIZE(2);
    StaticJsonDocument<bufferSize> root;
    root["vane"] = message;
    String mqttOutput;
    serializeJson(root, mqttOutput);
    mqtt_client.publish(ha_state_topic.c_str(), mqttOutput.c_str());
    hp.setVaneSetting(message);
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
  const size_t capacity = 3 * JSON_ARRAY_SIZE(5) + JSON_ARRAY_SIZE(7) + JSON_OBJECT_SIZE(23) + JSON_OBJECT_SIZE(100);
  DynamicJsonDocument haConfig(capacity);

  haConfig["name"]                          = mqtt_fn;
  haConfig["unique_id"]                     = String(ESP.getChipId(),HEX);
  
  JsonArray haConfigModes = haConfig.createNestedArray("modes");
  haConfigModes.add("heat_cool"); //native AUTO mode
  haConfigModes.add("cool");
  haConfigModes.add("dry");
  haConfigModes.add("heat");
  haConfigModes.add("fan_only");  //native FAN mode
  haConfigModes.add("off");

  
  haConfig["mode_cmd_t"]                    = mqtt_topic + "/" + mqtt_fn + "/mode/set";
  haConfig["mode_stat_t"]                   = mqtt_topic  + "/" + mqtt_fn + "/state";
  haConfig["mode_stat_tpl"]                 = "{{ value_json.mode }}";
  haConfig["temp_cmd_t"]                    = mqtt_topic + "/" + mqtt_fn + "/temp/set";
  haConfig["temp_stat_t"]                   = mqtt_topic + "/" + mqtt_fn + "/state";
  haConfig["temp_stat_tpl"]                 = "{{ value_json.temperature }}";
  haConfig["curr_temp_t"]                   = mqtt_topic  + "/" + mqtt_fn + "/state";
  haConfig["curr_temp_tpl"]                 = "{{ value_json.roomTemperature }}";
  haConfig["min_temp"]                      = min_temp;
  haConfig["max_temp"]                      = max_temp;
  haConfig["temp_step"]                     = temp_step;
  haConfig["pow_cmd_t"]                     = mqtt_topic + "/" + mqtt_fn + "/power/set";
  
  JsonArray haConfigFan_modes = haConfig.createNestedArray("fan_modes");
  haConfigFan_modes.add("AUTO");
  haConfigFan_modes.add("QUIET");
  haConfigFan_modes.add("1");
  haConfigFan_modes.add("2");
  haConfigFan_modes.add("3");
  haConfigFan_modes.add("4");
  
  haConfig["fan_mode_cmd_t"]                = mqtt_topic + "/" + mqtt_fn + "/fan/set";
  haConfig["fan_mode_stat_t"]               = mqtt_topic + "/" + mqtt_fn + "/state";
  haConfig["fan_mode_stat_tpl"]             = "{{ value_json.fan }}";
  
  JsonArray haConfigSwing_modes = haConfig.createNestedArray("swing_modes");
  haConfigSwing_modes.add("AUTO");
  haConfigSwing_modes.add("1");
  haConfigSwing_modes.add("2");
  haConfigSwing_modes.add("3");
  haConfigSwing_modes.add("4");
  haConfigSwing_modes.add("5");
  haConfigSwing_modes.add("SWING");
  
  haConfig["swing_mode_cmd_t"]              = mqtt_topic + "/" + mqtt_fn + "/vane/set";
  haConfig["swing_mode_stat_t"]             = mqtt_topic + "/" + mqtt_fn + "/state";
  haConfig["swing_mode_stat_tpl"]           = "{{ value_json.vane }}";
 
  JsonObject haConfigDevice = haConfig.createNestedObject("device");

  haConfigDevice["ids"]   = mqtt_fn;
  haConfigDevice["name"]  = mqtt_fn;
  haConfigDevice["sw"]    = "Mitsubishi2MQTT "+m2mqtt_version;
  haConfigDevice["mdl"]   = "HVAC MITUBISHI";
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
    if (mqtt_client.connect(mqtt_client_id.c_str(), mqtt_username.c_str(), mqtt_password.c_str())) {
      write_log("MQTT connected");
      mqtt_client.subscribe(ha_debug_set_topic.c_str());
      mqtt_client.subscribe(ha_power_set_topic.c_str());
      mqtt_client.subscribe(ha_mode_set_topic.c_str());
      mqtt_client.subscribe(ha_fan_set_topic.c_str());
      mqtt_client.subscribe(ha_temp_set_topic.c_str());
      mqtt_client.subscribe(ha_vane_set_topic.c_str());
      haConfig();
    }
    else if(attempts == 5) {
      write_log("MQTT disconnected. Failed to connect, stop after 5 try");
      mqtt_config = false;
      return;
    }
    else {
      // Wait 5 seconds before retrying
      delay(5000);
      attempts++;
    }
  }
}

void loop() {
  server.handleClient();
  if(captive) {
    dnsServer.processNextRequest();
  }
  #ifdef OTA
    ArduinoOTA.handle();
  #endif
  if(!captive and mqtt_config) {
    if (!mqtt_client.connected()) {
      mqttConnect();
    }
    hp.sync();
    if (millis() > (lastTempSend + SEND_ROOM_TEMP_INTERVAL_MS)) { // only send the temperature every SEND_ROOM_TEMP_INTERVAL_MS
      hpStatusChanged(hp.getStatus());
      lastTempSend = millis();
    }
    mqtt_client.loop();
  }
}
