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
const char txt_control[] PROGMEM = "Control";
const char txt_setup[] PROGMEM = "Configuració";
const char txt_status[] PROGMEM = "Estat";
const char txt_firmware_upgrade[] PROGMEM = "Actualització de microprogramari";
const char txt_reboot[] PROGMEM = "Reinicia";

//Setup Menu
const char txt_MQTT[] PROGMEM = "MQTT";
const char txt_WIFI[] PROGMEM = "WIFI";
const char txt_unit[] PROGMEM = "Unitat";
const char txt_others[] PROGMEM = "Altres";
const char txt_reset[] PROGMEM = "Restableix la configuració";
const char txt_reset_confirm[] PROGMEM = "Voleu restablir el controlador?";

//Buttons
const char txt_back[] PROGMEM = "Enrere";
const char txt_save[] PROGMEM = "Desa i reinicia";
const char txt_logout[] PROGMEM = "Surt";
const char txt_upgrade[] PROGMEM = "Inicia l'actualització";
const char txt_login[] PROGMEM = "LOGIN";

//Form choices
const char txt_f_on[] PROGMEM = "ON";
const char txt_f_off[] PROGMEM = "OFF";
const char txt_f_auto[] PROGMEM = "AUTO";
const char txt_f_heat[] PROGMEM = "CALOR";
const char txt_f_dry[] PROGMEM = "ASSECAR";
const char txt_f_cool[] PROGMEM = "FRED";
const char txt_f_fan[] PROGMEM = "VENTILADOR";
const char txt_f_quiet[] PROGMEM = "SILENCIÓS";
const char txt_f_speed[] PROGMEM = "VELOCITAT";
const char txt_f_swing[] PROGMEM = "DIFUSOR";
const char txt_f_pos[] PROGMEM = "POSICIÓ";
const char txt_f_celsius[] PROGMEM = "Celsius";
const char txt_f_fh[] PROGMEM = "Fahrenheit";
const char txt_f_allmodes[] PROGMEM = "Tots els modes";
const char txt_f_noheat[] PROGMEM = "Tots els modes excepte calor";


//Page Reboot, save & Resseting
const char txt_m_reboot[] PROGMEM = "S'està reiniciant... Refresca en";
const char txt_m_reset[] PROGMEM = "S'està restablint... Connectant al SSID";
const char txt_m_save[] PROGMEM = "S'està desant la configuració i s'està reiniciant... Refresca en";

//Page MQTT
const char txt_mqtt_title[] PROGMEM = "Configuració MQTT";
const char txt_mqtt_fn[] PROGMEM = "Nom descriptiu";
const char txt_mqtt_host[] PROGMEM = "Amfitrió";
const char txt_mqtt_port[] PROGMEM = "Port (1883 per defecte)";
const char txt_mqtt_user[] PROGMEM = "Usuari";
const char txt_mqtt_password[] PROGMEM = "Contrasenya";
const char txt_mqtt_topic[] PROGMEM = "Tema";

//Page Others
const char txt_others_title[] PROGMEM = "Altra configuració";
const char txt_others_haauto[] PROGMEM = "HA autodescobriment";
const char txt_others_hatopic[] PROGMEM = "HA tema d'autodescobriment";
const char txt_others_debug_packets[] PROGMEM = "MQTT topic debug packets";
const char txt_others_debug_log[] PROGMEM = "MQTT topic debug logs";

//Page Status
const char txt_status_title[] PROGMEM = "Estat";
const char txt_status_hvac[] PROGMEM = "Estat HVAC";
const char txt_retries_hvac[] PROGMEM = "Nombre de intents de connexió HVAC";
const char txt_status_mqtt[] PROGMEM = "Estat MQTT";
const char txt_status_wifi[] PROGMEM = "WIFI RSSI";
const char txt_status_connect[] PROGMEM = "CONNECTAT";
const char txt_status_disconnect[] PROGMEM = "DESCONNECTAT";

//Page WIFI
const char txt_wifi_title[] PROGMEM = "Configuració WIFI";
const char txt_wifi_hostname[] PROGMEM = "Nom d'amfitrió";
const char txt_wifi_SSID[] PROGMEM = "SSID";
const char txt_wifi_psk[] PROGMEM = "PSK";
const char txt_wifi_otap[] PROGMEM = "Contrasenya OTA";

//Page Control
const char txt_ctrl_title[] PROGMEM = "Control climatització";
const char txt_ctrl_temp[] PROGMEM = "Temperatura objectiu";
const char txt_ctrl_power[] PROGMEM = "Engega";
const char txt_ctrl_mode[] PROGMEM = "Mode";
const char txt_ctrl_fan[] PROGMEM = "Ventilador";
const char txt_ctrl_vane[] PROGMEM = "Difusor vertical";
const char txt_ctrl_wvane[] PROGMEM = "Difusor horitzontal";
const char txt_ctrl_ctemp[] PROGMEM = "Temperatura actual";

//Page Unit
const char txt_unit_title[] PROGMEM = "Configuració climatització";
const char txt_unit_temp[] PROGMEM = "Unitat de temperatura";
const char txt_unit_maxtemp[] PROGMEM = "Temperatura màxima";
const char txt_unit_mintemp[] PROGMEM = "Temperatura mínima";
const char txt_unit_steptemp[] PROGMEM = "Temperature step";
const char txt_unit_modes[] PROGMEM = "Mode disponible";
const char txt_unit_password[] PROGMEM = "Contrasenya web";

//Page Login
const char txt_login_title[] PROGMEM = "Autenticació";
const char txt_login_password[] PROGMEM = "Contrasenya";
const char txt_login_sucess[] PROGMEM = "Inici de sessió correcte, se us redirigirà d'aquí a uns segons";
const char txt_login_fail[] PROGMEM = "Nom d'usuari/contrasenya incorrectes! Torna-ho a provar.";

//Page Upgrade
const char txt_upgrade_title[] PROGMEM = "Actualització";
const char txt_upgrade_info[] PROGMEM = "Actualització de microprogramari per càrrega de fitxers";
const char txt_upgrade_start[] PROGMEM = "S'ha iniciat la pujada";

//Page Upload
const char txt_upload_nofile[] PROGMEM = "No s'ha seleccionat cap fitxer";
const char txt_upload_filetoolarge[] PROGMEM = "La mida del fitxer és més gran que l'espai lliure disponible";
const char txt_upload_fileheader[] PROGMEM = "La capçalera màgica del fitxer no comença amb 0xE9";
const char txt_upload_flashsize[] PROGMEM = "La mida del flaix del fitxer és més gran que la mida del flaix del dispositiu";
const char txt_upload_buffer[] PROGMEM = "La memòria intermèdia de càrrega de fitxers no coincideix";
const char txt_upload_failed[] PROGMEM = "Ha fallat la pujada. Activa l'opció de registre 3 per a més informació";
const char txt_upload_aborted[] PROGMEM = "S'ha interromput la pujada";
const char txt_upload_code[] PROGMEM = "Codi d'error de pujada ";
const char txt_upload_error[] PROGMEM = "Codi d'error de pujada (vegeu Updater.cpp) ";
const char txt_upload_sucess[] PROGMEM = "Correcte";
const char txt_upload_refresh[] PROGMEM = "Refresca en";

//Page Init
const char txt_init_title[] PROGMEM = "Configuració inicial";
const char txt_init_reboot_mes[] PROGMEM = "S'està reiniciant i connectant a la xarxa WiFi! Hauries de veure'l llistat al teu punt d'accés.";
const char txt_init_reboot[] PROGMEM = "Reiniciant...";
