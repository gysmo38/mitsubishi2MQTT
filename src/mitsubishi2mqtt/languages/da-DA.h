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

//Main Menu
const char txt_control[] PROGMEM = "Kontrol";
const char txt_setup[] PROGMEM = "Indstillinger";
const char txt_status[] PROGMEM = "Status";
const char txt_firmware_upgrade[] PROGMEM = "Firmware Opgradering";
const char txt_reboot[] PROGMEM = "Genstart";

//Setup Menu
const char txt_MQTT[] PROGMEM = "MQTT";
const char txt_WIFI[] PROGMEM = "WIFI";
const char txt_unit[] PROGMEM = "Enhed";
const char txt_others[] PROGMEM = "Diverse";
const char txt_reset[] PROGMEM = "Reset konfiguration";
const char txt_reset_confirm[] PROGMEM = "Do you really want to reset this unit?";


//Buttons
const char txt_back[] PROGMEM = "Tilbage";
const char txt_save[] PROGMEM = "Gem & Genstart";
const char txt_logout[] PROGMEM = "Log ud";
const char txt_upgrade[] PROGMEM = "Start opgradering";
const char txt_login[] PROGMEM = "LOGIN";

//Form choices
const char txt_f_on[] PROGMEM = "ON";
const char txt_f_off[] PROGMEM = "OFF";
const char txt_f_auto[] PROGMEM = "AUTO";
const char txt_f_heat[] PROGMEM = "HEAT";
const char txt_f_dry[] PROGMEM = "DRY";
const char txt_f_cool[] PROGMEM = "COOL";
const char txt_f_fan[] PROGMEM = "FAN";
const char txt_f_quiet[] PROGMEM = "QUIET";
const char txt_f_speed[] PROGMEM = "SPEED";
const char txt_f_swing[] PROGMEM = "SWING";
const char txt_f_pos[] PROGMEM = "POSITION";
const char txt_f_celsius[] PROGMEM = "Celsius";
const char txt_f_fh[] PROGMEM = "Fahrenheit";
const char txt_f_allmodes[] PROGMEM = "All modes";
const char txt_f_noheat[] PROGMEM = "All modes execept heat";


//Page Reboot, save & Resseting
const char txt_m_reboot[] PROGMEM = "Rebooting... Refresh in";
const char txt_m_reset[] PROGMEM = "Resetting... Connect to SSID";
const char txt_m_save[] PROGMEM = "Saving configuration and rebooting... Refresh in";

//Page MQTT
const char txt_mqtt_title[] PROGMEM = "MQTT Parameters";
const char txt_mqtt_fn[] PROGMEM = "Friendly name";
const char txt_mqtt_host[] PROGMEM = "Host";
const char txt_mqtt_port[] PROGMEM = "Port (default 1883)";
const char txt_mqtt_user[] PROGMEM = "User";
const char txt_mqtt_password[] PROGMEM = "Password";
const char txt_mqtt_topic[] PROGMEM = "Topic";

//Page Others
const char txt_others_title[] PROGMEM = "Others Parameters";
const char txt_others_haauto[] PROGMEM = "HA Autodiscovery";
const char txt_others_hatopic[] PROGMEM = "HA Autodiscovery topic";
const char txt_others_debug_packets[] PROGMEM = "MQTT topic debug packets";
const char txt_others_debug_log[] PROGMEM = "MQTT topic debug logs";

//Page Status
const char txt_status_title[] PROGMEM = "Status";
const char txt_status_hvac[] PROGMEM = "HVAC Status";
const char txt_retries_hvac[] PROGMEM = "HVAC Connection Retries";
const char txt_status_mqtt[] PROGMEM = "MQTT Status";
const char txt_status_wifi[] PROGMEM = "WIFI RSSI";
const char txt_status_connect[] PROGMEM = "CONNECTED";
const char txt_status_disconnect[] PROGMEM = "DICONNECTED";

//Page WIFI
const char txt_wifi_title[] PROGMEM = "WIFI Parameters";
const char txt_wifi_hostname[] PROGMEM = "Hostname";
const char txt_wifi_SSID[] PROGMEM = "SSID";
const char txt_wifi_psk[] PROGMEM = "PSK";
const char txt_wifi_otap[] PROGMEM = "OTA Password";

//Page Control
const char txt_ctrl_title[] PROGMEM = "Control Unit";
const char txt_ctrl_temp[] PROGMEM = "Temperature";
const char txt_ctrl_power[] PROGMEM = "Power";
const char txt_ctrl_mode[] PROGMEM = "Mode";
const char txt_ctrl_fan[] PROGMEM = "Fan";
const char txt_ctrl_vane[] PROGMEM = "Vane";
const char txt_ctrl_wvane[] PROGMEM = "Wide Vane";
const char txt_ctrl_ctemp[] PROGMEM = "Current temperature";

//Page Unit
const char txt_unit_title[] PROGMEM = "Unit configuration";
const char txt_unit_temp[] PROGMEM = "Temperature unit";
const char txt_unit_maxtemp[] PROGMEM = "Maximun temperature";
const char txt_unit_mintemp[] PROGMEM = "Minimun temperature";
const char txt_unit_steptemp[] PROGMEM = "Temerature step";
const char txt_unit_modes[] PROGMEM = "Mode support";
const char txt_unit_password[] PROGMEM = "Web password";

//Page Login
const char txt_login_title[] PROGMEM = "Authentication";
const char txt_login_password[] PROGMEM = "Password";
const char txt_login_sucess[] PROGMEM = "Login successful, you will be redirect in few seconds.";
const char txt_login_fail[] PROGMEM = "Wrong username/password! try again.";

//Page Upgrade
const char txt_upgrade_title[] PROGMEM = "Upgrade";
const char txt_upgrade_info[] PROGMEM = "Firmware OTA upgrade by bin file upload";
const char txt_upgrade_start[] PROGMEM = "Upload started";

//Page Upload
const char txt_upload_nofile[] PROGMEM = "No file selected";
const char txt_upload_filetoolarge[] PROGMEM = "File size is larger than available free space";
const char txt_upload_fileheader[] PROGMEM = "File magic header does not start with 0xE9";
const char txt_upload_flashsize[] PROGMEM = "File flash size is larger than device flash size";
const char txt_upload_buffer[] PROGMEM = "File upload buffer miscompare";
const char txt_upload_failed[] PROGMEM = "Upload failed. Enable logging option 3 for more information";
const char txt_upload_aborted[] PROGMEM = "Upload aborted";
const char txt_upload_code[] PROGMEM = "Upload error code ";
const char txt_upload_error[] PROGMEM = "Update error code (see Updater.cpp) ";
const char txt_upload_sucess[] PROGMEM = "successful";
const char txt_upload_refresh[] PROGMEM = "Refresh in";

//Page Init
const char txt_init_title[] PROGMEM = "Initial setup";
const char txt_init_reboot_mes[] PROGMEM = "Rebooting and connecting to your WiFi network! You should see it listed in on your access point.";
const char txt_init_reboot[] PROGMEM = "Rebooting...";
