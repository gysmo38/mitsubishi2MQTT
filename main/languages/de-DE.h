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
namespace de
{
  // Breadcum
  const char txt_setup_page[] PROGMEM = "Setup-Seite";
  const char txt_upload_fw_page[] PROGMEM = "Firmware hochladen";
  const char txt_fw_update_page[] PROGMEM = "Firmware aktualisieren";
  const char txt_check_fw_page[] PROGMEM = "Neue Firmware prüfen";
  const char txt_home_page[] PROGMEM = "Homepage";
  // Main Menu
  const char txt_control[] PROGMEM = "Klimaanlage bedienen";
  const char txt_setup[] PROGMEM = "Einstellungen";
  const char txt_status[] PROGMEM = "Status";
  const char txt_firmware_upgrade[] PROGMEM = "Firmware Upgrade";
  const char txt_reboot[] PROGMEM = "Neustart";

  // Setup Menu
  const char txt_mqtt[] PROGMEM = "MQTT";
  const char txt_wifi[] PROGMEM = "WLAN";
  const char txt_unit[] PROGMEM = "Einheiten";
  const char txt_others[] PROGMEM = "weiteres";
  const char txt_reset[] PROGMEM = "Einstellungen zurücksetzen";
  const char txt_reset_confirm[] PROGMEM = "Willst du wirklich alle Einstellungen zurücksetzen?";
  const char txt_mqtt_fn_desc[] PROGMEM = "(no space or special char)";
  const char txt_mqtt_port_desc[] PROGMEM = "(default 1883, not support 8883)";
  const char txt_mqtt_ph_topic[] PROGMEM = "Enter Mqtt topic";
  const char txt_mqtt_ph_user[] PROGMEM = "Enter Mqtt user";
  const char txt_mqtt_ph_pwd[] PROGMEM = "Enter Mqtt password";

  // Buttons
  const char txt_back[] PROGMEM = "zurück";
  const char txt_save[] PROGMEM = "speichern & neustart";
  const char txt_logout[] PROGMEM = "ABMELDEN";
  const char txt_upgrade[] PROGMEM = "Upgrade starten";
  const char txt_login[] PROGMEM = "ANMELDEN";

  // Form choices
  const char txt_f_on[] PROGMEM = "EIN";
  const char txt_f_off[] PROGMEM = "AUS";
  const char txt_f_auto[] PROGMEM = "AUTO";
  const char txt_f_heat[] PROGMEM = "HEIZEN";
  const char txt_f_dry[] PROGMEM = "TROCKNEN";
  const char txt_f_cool[] PROGMEM = "KÜHLEN";
  const char txt_f_fan[] PROGMEM = "Lüfter";
  const char txt_f_quiet[] PROGMEM = "LEISE";
  const char txt_f_speed[] PROGMEM = "Geschwindigkeit";
  const char txt_f_swing[] PROGMEM = "SCHWINGEN";
  const char txt_f_pos[] PROGMEM = "POSITION";
  const char txt_f_celsius[] PROGMEM = "Celsius";
  const char txt_f_fh[] PROGMEM = "Fahrenheit";
  const char txt_f_allmodes[] PROGMEM = "jeder Modus";
  const char txt_f_noheat[] PROGMEM = "jeder Modus, außer heizen";
  const char txt_f_noquiet[] PROGMEM = "Not support quiet mode";

  // Page Reboot, save & Resseting
  const char txt_m_reboot[] PROGMEM = "Neustart... Aktualisierung in";
  const char txt_m_reset[] PROGMEM = "Zurücksetzen... Verbinde mit SSID";
  const char txt_m_reset_1[] PROGMEM = "Sie können sich wieder mit der SSID verbinden";
  const char txt_m_save[] PROGMEM = "Einstellungen speichern und neustart... Aktualisierung in";

  // Page MQTT
  const char txt_mqtt_title[] PROGMEM = "MQTT Parameter";
  const char txt_mqtt_fn[] PROGMEM = "Anzeigename";
  const char txt_mqtt_host[] PROGMEM = "Host";
  const char txt_mqtt_port[] PROGMEM = "Port (default 1883)";
  const char txt_mqtt_user[] PROGMEM = "Benutzername";
  const char txt_mqtt_password[] PROGMEM = "Passwort";
  const char txt_mqtt_topic[] PROGMEM = "Topic";

  // Page Others
  const char txt_others_title[] PROGMEM = "Weitere Parameter";
  const char txt_others_haauto[] PROGMEM = "HA Autodiscovery";
  const char txt_others_hatopic[] PROGMEM = "HA Autodiscovery topic";
  const char txt_others_debug_packets[] PROGMEM = "MQTT topic debug packets";
  const char txt_others_debug_log[] PROGMEM = "MQTT topic debug logs";

  // Page Status
  const char txt_status_title[] PROGMEM = "Status";
  const char txt_status_hvac[] PROGMEM = "HVAC Status";
  const char txt_retries_hvac[] PROGMEM = "HVAC Connection Retries";
  const char txt_status_mqtt[] PROGMEM = "MQTT Status";
  const char txt_status_wifi[] PROGMEM = "WLAN RSSI";
  const char txt_status_connect[] PROGMEM = "CONNECTED";
  const char txt_status_disconnect[] PROGMEM = "DISCONNECTED";
  const char txt_status_wifi_ip[] PROGMEM = "WIFI IP";
  const char txt_failed_get_wifi_ip[] PROGMEM = "Failed to get IP address";
  const char txt_build_version[] PROGMEM = "Build Version";
  const char txt_build_date[] PROGMEM = "Build Date";
  const char txt_status_freeheap[] PROGMEM = "Free Heap";
  const char txt_current_time[] PROGMEM = "Current Time";
  const char txt_boot_time[] PROGMEM = "Boot Time";

  // Page WIFI
  const char txt_wifi_title[] PROGMEM = "WLAN Parameter";
  const char txt_wifi_hostname[] PROGMEM = "Hostname";
  const char txt_wifi_ssid[] PROGMEM = "SSID";
  const char txt_wifi_psk[] PROGMEM = "PSK";
  const char txt_wifi_otap[] PROGMEM = "OTA Passwort";
  const char txt_wifi_hostname_desc[] PROGMEM = "(no space or special char)";
  const char txt_wifi_ssid_enter[] PROGMEM = "(Enter a name)";
  const char txt_wifi_ssid_select[] PROGMEM = "or choose a network:";

  // Page Control
  const char txt_ctrl_title[] PROGMEM = "Kontrolleinheit";
  const char txt_ctrl_temp[] PROGMEM = "Temperatur";
  const char txt_ctrl_power[] PROGMEM = "Power";
  const char txt_ctrl_mode[] PROGMEM = "Modus";
  const char txt_ctrl_fan[] PROGMEM = "Lüfter";
  const char txt_ctrl_vane[] PROGMEM = "Leitschaufel";
  const char txt_ctrl_wvane[] PROGMEM = "breite Leitschaufel";
  const char txt_ctrl_ctemp[] PROGMEM = "Raumtemperatur";

  // Page Unit
  const char txt_unit_title[] PROGMEM = "Unit configuration";
  const char txt_unit_temp[] PROGMEM = "Temperatureinheit";
  const char txt_unit_maxtemp[] PROGMEM = "max. Temperatur";
  const char txt_unit_mintemp[] PROGMEM = "min. Temperatur";
  const char txt_unit_steptemp[] PROGMEM = "Temperaturschritte";
  const char txt_unit_modes[] PROGMEM = "unterstützter Modus";
  const char txt_unit_password[] PROGMEM = "Web Passwort";
  const char txt_unit_language[] PROGMEM = "Language";
  const char txt_unit_fan_modes[] PROGMEM = "Fan mode support";
  const char txt_unit_password_confirm[] PROGMEM = "Confirm Login password";
  const char txt_unit_password_not_match[] PROGMEM = "Confirm Password did not match";
  const char txt_unit_login_username[] PROGMEM = "Note: Default login user is";

  // Page Login
  const char txt_login_title[] PROGMEM = "Authentifizierung";
  const char txt_login_password[] PROGMEM = "Passwort";
  const char txt_login_sucess[] PROGMEM = "Anmeldung erfolgreich, du wirst gleich weitergeleitet.";
  const char txt_login_fail[] PROGMEM = "Falscher/s Benutzername/Passwort! Erneut versuchen.";
  const char txt_login_username[] PROGMEM = "Username";
  const char txt_login_open_status[] PROGMEM = "Open status page";
  const char txt_login_ph_user[] PROGMEM = "Enter username";
  const char txt_login_ph_pwd[] PROGMEM = "Enter password";

  // Page Upgrade
  const char txt_upgrade_title[] PROGMEM = "Upgrade";
  const char txt_upgrade_info[] PROGMEM = "Firmware OTA upgrade, über .bin Datei upload";
  const char txt_upgrade_start[] PROGMEM = "Upload gestartet";

  // Page Upload
  const char txt_upload_nofile[] PROGMEM = "keine Datei ausgewählt";
  const char txt_upload_filetoolarge[] PROGMEM = "Datei ist größer als der verfügbare Speicher";
  const char txt_upload_fileheader[] PROGMEM = "File magic header fängt nicht mit 0xE9 an";
  const char txt_upload_flashsize[] PROGMEM = "Datei-Flash-Größe ist größer als Geräte-Flash-Größe";
  const char txt_upload_buffer[] PROGMEM = "Datei-Upload-Puffer stimmt nicht überein";
  const char txt_upload_failed[] PROGMEM = "Upload fehlgeschlagen. Aktivieren Sie die Protokollierungsoption 3, um weitere Informationen zu erhalten";
  const char txt_upload_aborted[] PROGMEM = "Upload abgebrochen";
  const char txt_upload_code[] PROGMEM = "Upload Fehlercode ";
  const char txt_upload_error[] PROGMEM = "Update Fehlercode (see Updater.cpp) ";
  const char txt_upload_success[] PROGMEM = "erfolgreich";
  const char txt_upload_refresh[] PROGMEM = "Aktualisierung in";
  const char txt_upload[] PROGMEM = "Upload";

  // Page Init
  const char txt_init_title[] PROGMEM = "Ersteinrichtung";
  const char txt_init_reboot_mes[] PROGMEM = "Verbinden mit Ihrem WLAN - Netzwerk mit lokaler Adresse";
  const char txt_init_reboot_mes_1[] PROGMEM = "Verwenden Sie diese Adresse, um nach dem Neustart auf Ihr Gerät zuzugreifen.Neustart in";
  const char txt_init_reboot[] PROGMEM = "Neustart...";
}