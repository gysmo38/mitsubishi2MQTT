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
const char txt_control[] PROGMEM = "Comandi";
const char txt_setup[] PROGMEM = "Impostazioni";
const char txt_status[] PROGMEM = "Stato";
const char txt_firmware_upgrade[] PROGMEM = "Aggiornamento Firmware";
const char txt_reboot[] PROGMEM = "Riavvio";

//Setup Menu
const char txt_MQTT[] PROGMEM = "MQTT";
const char txt_WIFI[] PROGMEM = "Wi-Fi";
const char txt_unit[] PROGMEM = "Unità";
const char txt_others[] PROGMEM = "Altri parametri";
const char txt_reset[] PROGMEM = "Reset configurazione";
const char txt_reset_confirm[] PROGMEM = "Sei sicuro di voler resettare l'unità?";

//Buttons
const char txt_back[] PROGMEM = "Indietro";
const char txt_save[] PROGMEM = "Salva & Riavvia";
const char txt_logout[] PROGMEM = "Logout";
const char txt_upgrade[] PROGMEM = "Avvia aggiornamento";
const char txt_login[] PROGMEM = "Login";

//Form choices
const char txt_f_on[] PROGMEM = "Acceso";
const char txt_f_off[] PROGMEM = "Spento";
const char txt_f_auto[] PROGMEM = "Automatico";
const char txt_f_heat[] PROGMEM = "Riscaldamento";
const char txt_f_dry[] PROGMEM = "Deumidificatore";
const char txt_f_cool[] PROGMEM = "Condizionamento";
const char txt_f_fan[] PROGMEM = "Ventilazione";
const char txt_f_quiet[] PROGMEM = "Silenzioso";
const char txt_f_speed[] PROGMEM = "Velocità";
const char txt_f_swing[] PROGMEM = "Oscillazione";
const char txt_f_pos[] PROGMEM = "Posizione";
const char txt_f_celsius[] PROGMEM = "Celsius";
const char txt_f_fh[] PROGMEM = "Fahrenheit";
const char txt_f_allmodes[] PROGMEM = "Tutte le modalità";
const char txt_f_noheat[] PROGMEM = "Tutte le modalità escluso riscaldamento";


//Page Reboot, save & Resseting
const char txt_m_reboot[] PROGMEM = "Riavvio... Refresh in";
const char txt_m_reset[] PROGMEM = "Reset in corso... Connettersi all'SSID";
const char txt_m_save[] PROGMEM = "Salvataggio configurazione e riavvio... Refresh in";

//Page MQTT
const char txt_mqtt_title[] PROGMEM = "Parametri MQTT";
const char txt_mqtt_fn[] PROGMEM = "Nome familiare";
const char txt_mqtt_host[] PROGMEM = "Host";
const char txt_mqtt_port[] PROGMEM = "Porta (default 1883)";
const char txt_mqtt_user[] PROGMEM = "User";
const char txt_mqtt_password[] PROGMEM = "Password";
const char txt_mqtt_topic[] PROGMEM = "Topic";

//Page Others
const char txt_others_title[] PROGMEM = "Altri parametetri";
const char txt_others_haauto[] PROGMEM = "HA Autodiscovery";
const char txt_others_hatopic[] PROGMEM = "HA Autodiscovery topic";
const char txt_others_debug_packets[] PROGMEM = "MQTT topic debug packets";
const char txt_others_debug_log[] PROGMEM = "MQTT topic debug logs";

//Page Status
const char txt_status_title[] PROGMEM = "Stato";
const char txt_status_hvac[] PROGMEM = "Stato HVAC";
const char txt_retries_hvac[] PROGMEM = "HVAC Connection Retries";
const char txt_status_mqtt[] PROGMEM = "Stato MQTT";
const char txt_status_wifi[] PROGMEM = "WIFI RSSI";
const char txt_status_connect[] PROGMEM = "CONNESSO";
const char txt_status_disconnect[] PROGMEM = "DISCONNESSO";

//Page WIFI
const char txt_wifi_title[] PROGMEM = "Parametri WIFI";
const char txt_wifi_hostname[] PROGMEM = "Hostname";
const char txt_wifi_SSID[] PROGMEM = "SSID";
const char txt_wifi_psk[] PROGMEM = "PSK";
const char txt_wifi_otap[] PROGMEM = "Password OTA";

//Page Control
const char txt_ctrl_title[] PROGMEM = "Controllo Unità";
const char txt_ctrl_temp[] PROGMEM = "Temperatura";
const char txt_ctrl_power[] PROGMEM = "Alimentazione";
const char txt_ctrl_mode[] PROGMEM = "Modalità";
const char txt_ctrl_fan[] PROGMEM = "Ventilazione";
const char txt_ctrl_vane[] PROGMEM = "Oscillazione verticale";
const char txt_ctrl_wvane[] PROGMEM = "Oscillazione orizzontale";
const char txt_ctrl_ctemp[] PROGMEM = "Temperatura attuale";

//Page Unit
const char txt_unit_title[] PROGMEM = "Configurazione unità";
const char txt_unit_temp[] PROGMEM = "Unità temperatura";
const char txt_unit_maxtemp[] PROGMEM = "Temperatura massima";
const char txt_unit_mintemp[] PROGMEM = "Temperatura minima";
const char txt_unit_steptemp[] PROGMEM = "Step temperatura";
const char txt_unit_modes[] PROGMEM = "Modalità supportate";
const char txt_unit_password[] PROGMEM = "Password Web";

//Page Login
const char txt_login_title[] PROGMEM = "Autenticazione";
const char txt_login_password[] PROGMEM = "Password";
const char txt_login_sucess[] PROGMEM = "Login avvenuto, verrai reinderizzato tra pochi secondi.";
const char txt_login_fail[] PROGMEM = "Username/password errati! Riprova.";

//Page Upgrade
const char txt_upgrade_title[] PROGMEM = "Upgrade";
const char txt_upgrade_info[] PROGMEM = "Aggiornamento firmware OTA tramite upload del file bin.";
const char txt_upgrade_start[] PROGMEM = "Caricamento avviato";

//Page Upload
const char txt_upload_nofile[] PROGMEM = "Nessun file selezionato";
const char txt_upload_filetoolarge[] PROGMEM = "La dimensione del file è maggiore dello spazio disponibile";
const char txt_upload_fileheader[] PROGMEM = "L'header del file non inizia con 0xE9";
const char txt_upload_flashsize[] PROGMEM = "La dimensione del file è maggiore della dimensione del dispositivo";
const char txt_upload_buffer[] PROGMEM = "Buffer del caricamento file errato";
const char txt_upload_failed[] PROGMEM = "Caricamento fallito. Abilita l'opzione di log 3 per ulteriori informazioni";
const char txt_upload_aborted[] PROGMEM = "Caricamento annullato";
const char txt_upload_code[] PROGMEM = "Errore di caricamento codice ";
const char txt_upload_error[] PROGMEM = "Errore di caricamento codice (vedi Updater.cpp) ";
const char txt_upload_sucess[] PROGMEM = "Successo";
const char txt_upload_refresh[] PROGMEM = "Refresh in";

//Page Init
const char txt_init_title[] PROGMEM = "Setup iniziale";
const char txt_init_reboot_mes[] PROGMEM = "Riavvio e connessione alla tua rete WiFi! Dovresti vederlo nella lista del tuo Access Point.";
const char txt_init_reboot[] PROGMEM = "Riavvio...";
