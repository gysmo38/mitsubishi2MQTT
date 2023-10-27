/*
  mitsubishi2mqtt - Mitsubishi Heat Pump to MQTT control for Home Assistant.
  Copyright (c) 2023 by Pham Viet Dzung @dzungpv.  All right reserved.
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
// code originally written by Paul Derbyshire - https://github.com/emsesp/EMS-ESP

#include "languages/en-GB.h" // default language English
#include "languages/vi-VN.h" // Vietnamese
#include "languages/da-DA.h" // Danish
#include "languages/de-DE.h" // German
#include "languages/es-ES.h" // Spanish
#include "languages/fr-FR.h" // French
#include "languages/it-IT.h" // Italian
#include "languages/ja-JP.h" // Papanese
#include "languages/zh-CN.h" // Chinese

#pragma once

// Define language codes here and add to languages[] in config.h
#define MITSU2MQTT_LOCALE_EN "en"
#define MITSU2MQTT_LOCALE_VI "vi"
#define MITSU2MQTT_LOCALE_DA "da"
#define MITSU2MQTT_LOCALE_DE "de"
#define MITSU2MQTT_LOCALE_ES "es"
#define MITSU2MQTT_LOCALE_FR "fr"
#define MITSU2MQTT_LOCALE_IT "it"
#define MITSU2MQTT_LOCALE_JA "ja"
#define MITSU2MQTT_LOCALE_ZH "zh"

// IMPORTANT! translations are in the order: en, vi, de, es, fr, it, ja, zh
//
// if there is no translation, it will default to en
//

// Breadcum
MAKE_WORD_TRANSLATION(txt_setup_page, en::txt_setup_page, vi::txt_setup_page, da::txt_setup_page, de::txt_setup_page, es::txt_setup_page, fr::txt_setup_page, it::txt_setup_page, ja::txt_setup_page, zh::txt_setup_page)                                         // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_fw_page, en::txt_upload_fw_page, vi::txt_upload_fw_page, da::txt_upload_fw_page, de::txt_upload_fw_page, es::txt_upload_fw_page, fr::txt_upload_fw_page, it::txt_upload_fw_page, ja::txt_upload_fw_page, zh::txt_upload_fw_page) // TODO translate
MAKE_WORD_TRANSLATION(txt_fw_update_page, en::txt_fw_update_page, vi::txt_fw_update_page, da::txt_fw_update_page, de::txt_fw_update_page, es::txt_fw_update_page, fr::txt_fw_update_page, it::txt_fw_update_page, ja::txt_fw_update_page, zh::txt_fw_update_page) // TODO translate
MAKE_WORD_TRANSLATION(txt_check_fw_page, en::txt_check_fw_page, vi::txt_check_fw_page, da::txt_check_fw_page, de::txt_check_fw_page, es::txt_check_fw_page, fr::txt_check_fw_page, it::txt_check_fw_page, ja::txt_check_fw_page, zh::txt_check_fw_page)           // TODO translate
MAKE_WORD_TRANSLATION(txt_home_page, en::txt_home_page, vi::txt_home_page, da::txt_home_page, de::txt_home_page, es::txt_home_page, fr::txt_home_page, it::txt_home_page, ja::txt_home_page, zh::txt_home_page)                                                   // TODO translate

// Main Menu
MAKE_WORD_TRANSLATION(txt_control, en::txt_control, vi::txt_control, da::txt_control, de::txt_control, es::txt_control, fr::txt_control, it::txt_control, ja::txt_control, zh::txt_control)                                                                 // TODO translate
MAKE_WORD_TRANSLATION(txt_setup, en::txt_setup, vi::txt_setup, da::txt_setup, de::txt_setup, es::txt_setup, fr::txt_setup, it::txt_setup, ja::txt_setup, zh::txt_setup)                                                                                     // TODO translate
MAKE_WORD_TRANSLATION(txt_status, en::txt_status, vi::txt_status, da::txt_status, de::txt_status, es::txt_status, fr::txt_status, it::txt_status, ja::txt_status, zh::txt_status)                                                                           // TODO translate
MAKE_WORD_TRANSLATION(txt_firmware_upgrade, en::txt_firmware_upgrade, vi::txt_firmware_upgrade, da::txt_firmware_upgrade, de::txt_firmware_upgrade, es::txt_firmware_upgrade, fr::txt_firmware_upgrade, it::txt_firmware_upgrade, ja::txt_firmware_upgrade, zh::txt_firmware_upgrade) // TODO translate
MAKE_WORD_TRANSLATION(txt_reboot, en::txt_reboot, vi::txt_reboot, da::txt_reboot, de::txt_reboot, es::txt_reboot, fr::txt_reboot, it::txt_reboot, ja::txt_reboot, zh::txt_reboot)                                                                           // TODO translate

// Setup Menu
MAKE_WORD_TRANSLATION(txt_mqtt, en::txt_mqtt, vi::txt_mqtt, da::txt_mqtt, de::txt_mqtt, es::txt_mqtt, fr::txt_mqtt, it::txt_mqtt, ja::txt_mqtt, zh::txt_mqtt)                                                                                           // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi, en::txt_wifi, vi::txt_wifi, da::txt_wifi, de::txt_wifi, es::txt_wifi, fr::txt_wifi, it::txt_wifi, ja::txt_wifi, zh::txt_wifi)                                                                                           // TODO translate
MAKE_WORD_TRANSLATION(txt_unit, en::txt_unit, vi::txt_unit, da::txt_unit, de::txt_unit, es::txt_unit, fr::txt_unit, it::txt_unit, ja::txt_unit, zh::txt_unit)                                                                                           // TODO translate
MAKE_WORD_TRANSLATION(txt_others, en::txt_others, vi::txt_others, da::txt_others, de::txt_others, es::txt_others, fr::txt_others, it::txt_others, ja::txt_others, zh::txt_others)                                                                                       // TODO translate
MAKE_WORD_TRANSLATION(txt_reset, en::txt_reset, vi::txt_reset, da::txt_reset, de::txt_reset, es::txt_reset, fr::txt_reset, it::txt_reset, ja::txt_reset, zh::txt_reset)                                                                                                // TODO translate
MAKE_WORD_TRANSLATION(txt_reset_confirm, en::txt_reset_confirm, vi::txt_reset_confirm, da::txt_reset_confirm, de::txt_reset_confirm, es::txt_reset_confirm, fr::txt_reset_confirm, it::txt_reset_confirm, ja::txt_reset_confirm, zh::txt_reset_confirm) // TODO translate

// Buttons
MAKE_WORD_TRANSLATION(txt_back, en::txt_back, vi::txt_back, da::txt_back, de::txt_back, es::txt_back, fr::txt_back, it::txt_back, ja::txt_back, zh::txt_back)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_save, en::txt_save, vi::txt_save, da::txt_save, de::txt_save, es::txt_save, fr::txt_save, it::txt_save, ja::txt_save, zh::txt_save)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_logout, en::txt_logout, vi::txt_logout, da::txt_logout, de::txt_logout, es::txt_logout, fr::txt_logout, it::txt_logout, ja::txt_logout, zh::txt_logout)           // TODO translate
MAKE_WORD_TRANSLATION(txt_upgrade, en::txt_upgrade, vi::txt_upgrade, da::txt_upgrade, de::txt_upgrade, es::txt_upgrade, fr::txt_upgrade, it::txt_upgrade, ja::txt_upgrade, zh::txt_upgrade) // TODO translate
MAKE_WORD_TRANSLATION(txt_login, en::txt_login, vi::txt_login, da::txt_login, de::txt_login, es::txt_login, fr::txt_login, it::txt_login, ja::txt_login, zh::txt_login)                     // TODO translate

// Form choices
MAKE_WORD_TRANSLATION(txt_f_on, en::txt_f_on, vi::txt_f_on, da::txt_f_on, de::txt_f_on, es::txt_f_on, fr::txt_f_on, it::txt_f_on, ja::txt_f_on, zh::txt_f_on)                                                   // TODO translate
MAKE_WORD_TRANSLATION(txt_f_off, en::txt_f_off, vi::txt_f_off, da::txt_f_off, de::txt_f_off, es::txt_f_off, fr::txt_f_off, it::txt_f_off, ja::txt_f_off, zh::txt_f_off)                                         // TODO translate
MAKE_WORD_TRANSLATION(txt_f_auto, en::txt_f_auto, vi::txt_f_auto, da::txt_f_auto, de::txt_f_auto, es::txt_f_auto, fr::txt_f_auto, it::txt_f_auto, ja::txt_f_auto, zh::txt_f_auto)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_f_heat, en::txt_f_heat, vi::txt_f_heat, da::txt_f_heat, de::txt_f_heat, es::txt_f_heat, fr::txt_f_heat, it::txt_f_heat, ja::txt_f_heat, zh::txt_f_heat)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_f_dry, en::txt_f_dry, vi::txt_f_dry, da::txt_f_dry, de::txt_f_dry, es::txt_f_dry, fr::txt_f_dry, it::txt_f_dry, ja::txt_f_dry, zh::txt_f_dry)                                         // TODO translate
MAKE_WORD_TRANSLATION(txt_f_cool, en::txt_f_cool, vi::txt_f_cool, da::txt_f_cool, de::txt_f_cool, es::txt_f_cool, fr::txt_f_cool, it::txt_f_cool, ja::txt_f_cool, zh::txt_f_cool)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_f_fan, en::txt_f_fan, vi::txt_f_fan, da::txt_f_fan, de::txt_f_fan, es::txt_f_fan, fr::txt_f_fan, it::txt_f_fan, ja::txt_f_fan, zh::txt_f_fan)                                         // TODO translate
MAKE_WORD_TRANSLATION(txt_f_quiet, en::txt_f_quiet, vi::txt_f_quiet, da::txt_f_quiet, de::txt_f_quiet, es::txt_f_quiet, fr::txt_f_quiet, it::txt_f_quiet, ja::txt_f_quiet, zh::txt_f_quiet)                     // TODO translate
MAKE_WORD_TRANSLATION(txt_f_speed, en::txt_f_speed, vi::txt_f_speed, da::txt_f_speed, de::txt_f_speed, es::txt_f_speed, fr::txt_f_speed, it::txt_f_speed, ja::txt_f_speed, zh::txt_f_speed)                     // TODO translate
MAKE_WORD_TRANSLATION(txt_f_swing, en::txt_f_swing, vi::txt_f_swing, da::txt_f_swing, de::txt_f_swing, es::txt_f_swing, fr::txt_f_swing, it::txt_f_swing, ja::txt_f_swing, zh::txt_f_swing)                                      // TODO translate
MAKE_WORD_TRANSLATION(txt_f_pos, en::txt_f_pos, vi::txt_f_pos, da::txt_f_pos, de::txt_f_pos, es::txt_f_pos, fr::txt_f_pos, it::txt_f_pos, ja::txt_f_pos, zh::txt_f_pos)                                         // TODO translate
MAKE_WORD_TRANSLATION(txt_f_celsius, en::txt_f_celsius, vi::txt_f_celsius, da::txt_f_celsius, de::txt_f_celsius, es::txt_f_celsius, fr::txt_f_celsius, it::txt_f_celsius, ja::txt_f_celsius, zh::txt_f_celsius) // TODO translate
MAKE_WORD_TRANSLATION(txt_f_fh, en::txt_f_fh, vi::txt_f_fh, da::txt_f_fh, de::txt_f_fh, es::txt_f_fh, fr::txt_f_fh, it::txt_f_fh, ja::txt_f_fh, zh::txt_f_fh)                                                   // TODO translate
MAKE_WORD_TRANSLATION(txt_f_allmodes, en::txt_f_allmodes, vi::txt_f_allmodes, da::txt_f_allmodes, de::txt_f_allmodes, es::txt_f_allmodes, fr::txt_f_allmodes, it::txt_f_allmodes, ja::txt_f_allmodes, zh::txt_f_allmodes)           // TODO translate
MAKE_WORD_TRANSLATION(txt_f_noheat, en::txt_f_noheat, vi::txt_f_noheat, da::txt_f_noheat, de::txt_f_noheat, es::txt_f_noheat, fr::txt_f_noheat, it::txt_f_noheat, ja::txt_f_noheat, zh::txt_f_noheat)           // TODO translate
MAKE_WORD_TRANSLATION(txt_f_noquiet, en::txt_f_noquiet, vi::txt_f_noquiet, da::txt_f_noquiet, de::txt_f_noquiet, es::txt_f_noquiet, fr::txt_f_noquiet, it::txt_f_noquiet, ja::txt_f_noquiet, zh::txt_f_noquiet) // TODO translate

// Page Reboot, save & Resseting
MAKE_WORD_TRANSLATION(txt_m_reboot, en::txt_m_reboot, vi::txt_m_reboot, da::txt_m_reboot, de::txt_m_reboot, es::txt_m_reboot, fr::txt_m_reboot, it::txt_m_reboot, ja::txt_m_reboot, zh::txt_m_reboot)           // TODO translate
MAKE_WORD_TRANSLATION(txt_m_reset, en::txt_m_reset, vi::txt_m_reset, da::txt_m_reset, de::txt_m_reset, es::txt_m_reset, fr::txt_m_reset, it::txt_m_reset, ja::txt_m_reset, zh::txt_m_reset)                     // TODO translate
MAKE_WORD_TRANSLATION(txt_m_reset_1, en::txt_m_reset_1, vi::txt_m_reset_1, da::txt_m_reset_1, de::txt_m_reset_1, es::txt_m_reset_1, fr::txt_m_reset_1, it::txt_m_reset_1, ja::txt_m_reset_1, zh::txt_m_reset_1) // TODO translate
MAKE_WORD_TRANSLATION(txt_m_save, en::txt_m_save, vi::txt_m_save, da::txt_m_save, de::txt_m_save, es::txt_m_save, fr::txt_m_save, it::txt_m_save, ja::txt_m_save, zh::txt_m_save)                               // TODO translate

// Page MQTT
MAKE_WORD_TRANSLATION(txt_mqtt_title, en::txt_mqtt_title, vi::txt_mqtt_title, da::txt_mqtt_title, de::txt_mqtt_title, es::txt_mqtt_title, fr::txt_mqtt_title, it::txt_mqtt_title, ja::txt_mqtt_title, zh::txt_mqtt_title)                                         // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_fn, en::txt_mqtt_fn, vi::txt_mqtt_fn, da::txt_mqtt_fn, de::txt_mqtt_fn, es::txt_mqtt_fn, fr::txt_mqtt_fn, it::txt_mqtt_fn, ja::txt_mqtt_fn, zh::txt_mqtt_fn)                                                                       // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_fn_desc, en::txt_mqtt_fn_desc, vi::txt_mqtt_fn_desc, da::txt_mqtt_fn_desc, de::txt_mqtt_fn_desc, es::txt_mqtt_fn_desc, fr::txt_mqtt_fn_desc, it::txt_mqtt_fn_desc, ja::txt_mqtt_fn_desc, zh::txt_mqtt_fn_desc)                     // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_host, en::txt_mqtt_host, vi::txt_mqtt_host, da::txt_mqtt_host, de::txt_mqtt_host, es::txt_mqtt_host, fr::txt_mqtt_host, it::txt_mqtt_host, ja::txt_mqtt_host, zh::txt_mqtt_host)                                                   // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_port, en::txt_mqtt_port, vi::txt_mqtt_port, da::txt_mqtt_port, de::txt_mqtt_port, es::txt_mqtt_port, fr::txt_mqtt_port, it::txt_mqtt_port, ja::txt_mqtt_port, zh::txt_mqtt_port)                                                   // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_port_desc, en::txt_mqtt_port_desc, vi::txt_mqtt_port_desc, da::txt_mqtt_port_desc, de::txt_mqtt_port_desc, es::txt_mqtt_port_desc, fr::txt_mqtt_port_desc, it::txt_mqtt_port_desc, ja::txt_mqtt_port_desc, zh::txt_mqtt_port_desc) // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_user, en::txt_mqtt_user, vi::txt_mqtt_user, da::txt_mqtt_user, de::txt_mqtt_user, es::txt_mqtt_user, fr::txt_mqtt_user, it::txt_mqtt_user, ja::txt_mqtt_user, zh::txt_mqtt_user)                                                   // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_password, en::txt_mqtt_password, vi::txt_mqtt_password, da::txt_mqtt_password, de::txt_mqtt_password, es::txt_mqtt_password, fr::txt_mqtt_password, it::txt_mqtt_password, ja::txt_mqtt_password, zh::txt_mqtt_password)           // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_topic, en::txt_mqtt_topic, vi::txt_mqtt_topic, da::txt_mqtt_topic, de::txt_mqtt_topic, es::txt_mqtt_topic, fr::txt_mqtt_topic, it::txt_mqtt_topic, ja::txt_mqtt_topic, fr::txt_mqtt_topic)                                         // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_ph_user, en::txt_mqtt_ph_user, vi::txt_mqtt_ph_user, da::txt_mqtt_ph_user, de::txt_mqtt_ph_user, es::txt_mqtt_ph_user, fr::txt_mqtt_ph_user, it::txt_mqtt_ph_user, ja::txt_mqtt_ph_user, zh::txt_mqtt_ph_user)                     // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_ph_pwd, en::txt_mqtt_ph_pwd, vi::txt_mqtt_ph_pwd, da::txt_mqtt_ph_pwd, de::txt_mqtt_ph_pwd, es::txt_mqtt_ph_pwd, fr::txt_mqtt_ph_pwd, it::txt_mqtt_ph_pwd, ja::txt_mqtt_ph_pwd, zh::txt_mqtt_ph_pwd)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_ph_topic, en::txt_mqtt_ph_topic, vi::txt_mqtt_ph_topic, da::txt_mqtt_ph_topic, de::txt_mqtt_ph_topic, es::txt_mqtt_ph_topic, fr::txt_mqtt_ph_topic, it::txt_mqtt_ph_topic, ja::txt_mqtt_ph_topic, zh::txt_mqtt_ph_topic)           // TODO translate

// Page Others
MAKE_WORD_TRANSLATION(txt_others_title, en::txt_others_title, vi::txt_others_title, da::txt_others_title, de::txt_others_title, es::txt_others_title, fr::txt_others_title, it::txt_others_title, ja::txt_others_title, zh::txt_others_title)                                                                                 // TODO translate
MAKE_WORD_TRANSLATION(txt_others_haauto, en::txt_others_haauto, vi::txt_others_haauto, da::txt_others_haauto, de::txt_others_haauto, es::txt_others_haauto, fr::txt_others_haauto, it::txt_others_haauto, ja::txt_others_haauto, zh::txt_others_haauto)                                                                       // TODO translate
MAKE_WORD_TRANSLATION(txt_others_hatopic, en::txt_others_hatopic, vi::txt_others_hatopic, da::txt_others_hatopic, de::txt_others_hatopic, es::txt_others_hatopic, fr::txt_others_hatopic, it::txt_others_hatopic, ja::txt_others_hatopic, zh::txt_others_hatopic)                                                             // TODO translate
MAKE_WORD_TRANSLATION(txt_others_debug_packets, en::txt_others_debug_packets, vi::txt_others_debug_packets, da::txt_others_debug_packets, de::txt_others_debug_packets, es::txt_others_debug_packets, fr::txt_others_debug_packets, it::txt_others_debug_packets, ja::txt_others_debug_packets, zh::txt_others_debug_packets) // TODO translate
MAKE_WORD_TRANSLATION(txt_others_debug_log, en::txt_others_debug_log, vi::txt_others_debug_log, da::txt_others_debug_log, de::txt_others_debug_log, es::txt_others_debug_log, fr::txt_others_debug_log, it::txt_others_debug_log, ja::txt_others_debug_log, zh::txt_others_debug_log)                                         // TODO translate

// Page Status
MAKE_WORD_TRANSLATION(txt_status_title, en::txt_status_title, vi::txt_status_title, da::txt_status_title, de::txt_status_title, es::txt_status_title, fr::txt_status_title, it::txt_status_title, ja::txt_status_title, zh::txt_status_title)                                                             // TODO translate
MAKE_WORD_TRANSLATION(txt_status_hvac, en::txt_status_hvac, vi::txt_status_hvac, da::txt_status_hvac, de::txt_status_hvac, es::txt_status_hvac, fr::txt_status_hvac, it::txt_status_hvac, ja::txt_status_hvac, zh::txt_status_hvac)                                                                       // TODO translate
MAKE_WORD_TRANSLATION(txt_retries_hvac, en::txt_retries_hvac, vi::txt_retries_hvac, da::txt_retries_hvac, de::txt_retries_hvac, es::txt_retries_hvac, fr::txt_retries_hvac, it::txt_retries_hvac, ja::txt_retries_hvac, zh::txt_retries_hvac)                                                             // TODO translate
MAKE_WORD_TRANSLATION(txt_status_mqtt, en::txt_status_mqtt, vi::txt_status_mqtt, da::txt_status_mqtt, de::txt_status_mqtt, es::txt_status_mqtt, fr::txt_status_mqtt, it::txt_status_mqtt, ja::txt_status_mqtt, zh::txt_status_mqtt)                                                                       // TODO translate
MAKE_WORD_TRANSLATION(txt_status_wifi_ip, en::txt_status_wifi_ip, vi::txt_status_wifi_ip, da::txt_status_wifi_ip, de::txt_status_wifi_ip, es::txt_status_wifi_ip, fr::txt_status_wifi_ip, it::txt_status_wifi_ip, ja::txt_status_wifi_ip, zh::txt_status_wifi_ip)                                         // TODO translate
MAKE_WORD_TRANSLATION(txt_failed_get_wifi_ip, en::txt_failed_get_wifi_ip, vi::txt_failed_get_wifi_ip, da::txt_failed_get_wifi_ip, de::txt_failed_get_wifi_ip, es::txt_failed_get_wifi_ip, fr::txt_failed_get_wifi_ip, it::txt_failed_get_wifi_ip, ja::txt_failed_get_wifi_ip, zh::txt_failed_get_wifi_ip) // TODO translate
MAKE_WORD_TRANSLATION(txt_status_wifi, en::txt_status_wifi, vi::txt_status_wifi, en::txt_status_wifi, vi::txt_status_wifi, en::txt_status_wifi, vi::txt_status_wifi, en::txt_status_wifi, vi::txt_status_wifi)                                                                                            // TODO translate
MAKE_WORD_TRANSLATION(txt_build_version, en::txt_build_version, vi::txt_build_version, da::txt_build_version, de::txt_build_version, es::txt_build_version, fr::txt_build_version, it::txt_build_version, ja::txt_build_version, zh::txt_build_version)                                                   // TODO translate
MAKE_WORD_TRANSLATION(txt_build_date, en::txt_build_date, vi::txt_build_date, da::txt_build_date, de::txt_build_date, es::txt_build_date, fr::txt_build_date, it::txt_build_date, ja::txt_build_date, zh::txt_build_date)                                                                                 // TODO translate
MAKE_WORD_TRANSLATION(txt_status_freeheap, en::txt_status_freeheap, vi::txt_status_freeheap, da::txt_status_freeheap, de::txt_status_freeheap, es::txt_status_freeheap, fr::txt_status_freeheap, it::txt_status_freeheap, ja::txt_status_freeheap, zh::txt_status_freeheap)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_current_time, en::txt_current_time, vi::txt_current_time, da::txt_current_time, de::txt_current_time, es::txt_current_time, fr::txt_current_time, it::txt_current_time, ja::txt_current_time, zh::txt_current_time)                                                             // TODO translate
MAKE_WORD_TRANSLATION(txt_boot_time, en::txt_boot_time, vi::txt_boot_time, da::txt_boot_time, de::txt_boot_time, es::txt_boot_time, fr::txt_boot_time, it::txt_boot_time, ja::txt_boot_time, zh::txt_boot_time)                                                                                           // TODO translate
MAKE_WORD_TRANSLATION(txt_status_connect, en::txt_status_connect, vi::txt_status_connect, da::txt_status_connect, de::txt_status_connect, es::txt_status_connect, fr::txt_status_connect, it::txt_status_connect, ja::txt_status_connect, zh::txt_status_connect)                                         // TODO translate
MAKE_WORD_TRANSLATION(txt_status_disconnect, en::txt_status_disconnect, vi::txt_status_disconnect, da::txt_status_disconnect, de::txt_status_disconnect, es::txt_status_disconnect, fr::txt_status_disconnect, it::txt_status_disconnect, ja::txt_status_disconnect, zh::txt_status_disconnect)           // TODO translate

// Page WIFI
MAKE_WORD_TRANSLATION(txt_wifi_title, en::txt_wifi_title, vi::txt_wifi_title, da::txt_wifi_title, de::txt_wifi_title, es::txt_wifi_title, fr::txt_wifi_title, it::txt_wifi_title, ja::txt_wifi_title, zh::txt_wifi_title)                                                                                 // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi_hostname, en::txt_wifi_hostname, vi::txt_wifi_hostname, da::txt_wifi_hostname, de::txt_wifi_hostname, es::txt_wifi_hostname, fr::txt_wifi_hostname, it::txt_wifi_hostname, ja::txt_wifi_hostname, zh::txt_wifi_hostname)                                                   // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi_hostname_desc, en::txt_wifi_hostname_desc, vi::txt_wifi_hostname_desc, da::txt_wifi_hostname_desc, de::txt_wifi_hostname_desc, es::txt_wifi_hostname_desc, fr::txt_wifi_hostname_desc, it::txt_wifi_hostname_desc, ja::txt_wifi_hostname_desc, zh::txt_wifi_hostname_desc) // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi_ssid, en::txt_wifi_ssid, vi::txt_wifi_ssid, da::txt_wifi_ssid, de::txt_wifi_ssid, es::txt_wifi_ssid, fr::txt_wifi_ssid, it::txt_wifi_ssid, ja::txt_wifi_ssid, zh::txt_wifi_ssid)                                                                                           // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi_ssid_enter, en::txt_wifi_ssid_enter, vi::txt_wifi_ssid_enter, da::txt_wifi_ssid_enter, de::txt_wifi_ssid_enter, es::txt_wifi_ssid_enter, fr::txt_wifi_ssid_enter, it::txt_wifi_ssid_enter, ja::txt_wifi_ssid_enter, zh::txt_wifi_ssid_enter)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi_ssid_select, en::txt_wifi_ssid_select, vi::txt_wifi_ssid_select, da::txt_wifi_ssid_select, de::txt_wifi_ssid_select, es::txt_wifi_ssid_select, fr::txt_wifi_ssid_select, it::txt_wifi_ssid_select, ja::txt_wifi_ssid_select, zh::txt_wifi_ssid_select)                     // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi_psk, en::txt_wifi_psk, vi::txt_wifi_psk, da::txt_wifi_psk, de::txt_wifi_psk, es::txt_wifi_psk, fr::txt_wifi_psk, it::txt_wifi_psk, ja::txt_wifi_psk, zh::txt_wifi_psk)                                                                                                     // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi_otap, en::txt_wifi_otap, vi::txt_wifi_otap, da::txt_wifi_otap, de::txt_wifi_otap, es::txt_wifi_otap, fr::txt_wifi_otap, it::txt_wifi_otap, ja::txt_wifi_otap, zh::txt_wifi_otap)                                                                                           // TODO translate

// Page Control
MAKE_WORD_TRANSLATION(txt_ctrl_title, en::txt_ctrl_title, vi::txt_ctrl_title, da::txt_ctrl_title, de::txt_ctrl_title, es::txt_ctrl_title, fr::txt_ctrl_title, it::txt_ctrl_title, ja::txt_ctrl_title, zh::txt_ctrl_title) // TODO translate
MAKE_WORD_TRANSLATION(txt_ctrl_temp, en::txt_ctrl_temp, vi::txt_ctrl_temp, da::txt_ctrl_temp, de::txt_ctrl_temp, es::txt_ctrl_temp, fr::txt_ctrl_temp, it::txt_ctrl_temp, ja::txt_ctrl_temp, zh::txt_ctrl_temp)           // TODO translate
MAKE_WORD_TRANSLATION(txt_ctrl_power, en::txt_ctrl_power, vi::txt_ctrl_power, da::txt_ctrl_power, de::txt_ctrl_power, es::txt_ctrl_power, fr::txt_ctrl_power, it::txt_ctrl_power, ja::txt_ctrl_power, zh::txt_ctrl_power) // TODO translate
MAKE_WORD_TRANSLATION(txt_ctrl_mode, en::txt_ctrl_mode, vi::txt_ctrl_mode, da::txt_ctrl_mode, de::txt_ctrl_mode, es::txt_ctrl_mode, fr::txt_ctrl_mode, it::txt_ctrl_mode, ja::txt_ctrl_mode, zh::txt_ctrl_mode)           // TODO translate
MAKE_WORD_TRANSLATION(txt_ctrl_fan, en::txt_ctrl_fan, vi::txt_ctrl_fan, da::txt_ctrl_fan, de::txt_ctrl_fan, es::txt_ctrl_fan, fr::txt_ctrl_fan, it::txt_ctrl_fan, ja::txt_ctrl_fan, zh::txt_ctrl_fan)                     // TODO translate
MAKE_WORD_TRANSLATION(txt_ctrl_vane, en::txt_ctrl_vane, vi::txt_ctrl_vane, da::txt_ctrl_vane, de::txt_ctrl_vane, es::txt_ctrl_vane, fr::txt_ctrl_vane, it::txt_ctrl_vane, ja::txt_ctrl_vane, zh::txt_ctrl_vane)           // TODO translate
MAKE_WORD_TRANSLATION(txt_ctrl_wvane, en::txt_ctrl_wvane, vi::txt_ctrl_wvane, da::txt_ctrl_wvane, de::txt_ctrl_wvane, es::txt_ctrl_wvane, fr::txt_ctrl_wvane, it::txt_ctrl_wvane, ja::txt_ctrl_wvane, zh::txt_ctrl_wvane) // TODO translate
MAKE_WORD_TRANSLATION(txt_ctrl_ctemp, en::txt_ctrl_ctemp, vi::txt_ctrl_ctemp, da::txt_ctrl_ctemp, de::txt_ctrl_ctemp, es::txt_ctrl_ctemp, fr::txt_ctrl_ctemp, it::txt_ctrl_ctemp, ja::txt_ctrl_ctemp, zh::txt_ctrl_ctemp) // TODO translate

// Page Unit
MAKE_WORD_TRANSLATION(txt_unit_title, en::txt_unit_title, vi::txt_unit_title, da::txt_unit_title, de::txt_unit_title, es::txt_unit_title, fr::txt_unit_title, it::txt_unit_title, ja::txt_unit_title, zh::txt_unit_title)                                                                                                                                   // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_language, en::txt_unit_language, vi::txt_unit_language, da::txt_unit_language, de::txt_unit_language, es::txt_unit_language, fr::txt_unit_language, it::txt_unit_language, ja::txt_unit_language, zh::txt_unit_language)                                                                                                     // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_temp, en::txt_unit_temp, vi::txt_unit_temp, da::txt_unit_temp, de::txt_unit_temp, es::txt_unit_temp, fr::txt_unit_temp, it::txt_unit_temp, ja::txt_unit_temp, zh::txt_unit_temp)                                                                                                                                             // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_steptemp, en::txt_unit_steptemp, vi::txt_unit_steptemp, da::txt_unit_steptemp, de::txt_unit_steptemp, es::txt_unit_steptemp, fr::txt_unit_steptemp, it::txt_unit_steptemp, ja::txt_unit_steptemp, zh::txt_unit_steptemp)                                                                                                     // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_modes, en::txt_unit_modes, vi::txt_unit_modes, da::txt_unit_modes, de::txt_unit_modes, es::txt_unit_modes, fr::txt_unit_modes, it::txt_unit_modes, ja::txt_unit_modes, zh::txt_unit_modes)                                                                                                                                   // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_fan_modes, en::txt_unit_fan_modes, vi::txt_unit_fan_modes, da::txt_unit_fan_modes, de::txt_unit_fan_modes, es::txt_unit_fan_modes, fr::txt_unit_fan_modes, it::txt_unit_fan_modes, ja::txt_unit_fan_modes, zh::txt_unit_fan_modes)                                                                                           // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_password, en::txt_unit_password, vi::txt_unit_password, da::txt_unit_password, de::txt_unit_password, es::txt_unit_password, fr::txt_unit_password, it::txt_unit_password, ja::txt_unit_password, zh::txt_unit_password)                                                                                                     // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_password_confirm, en::txt_unit_password_confirm, vi::txt_unit_password_confirm, da::txt_unit_password_confirm, de::txt_unit_password_confirm, es::txt_unit_password_confirm, fr::txt_unit_password_confirm, it::txt_unit_password_confirm, ja::txt_unit_password_confirm, zh::txt_unit_password_confirm)                     // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_password_not_match, en::txt_unit_password_not_match, vi::txt_unit_password_not_match, da::txt_unit_password_not_match, de::txt_unit_password_not_match, es::txt_unit_password_not_match, fr::txt_unit_password_not_match, it::txt_unit_password_not_match, ja::txt_unit_password_not_match, zh::txt_unit_password_not_match) // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_login_username, en::txt_unit_login_username, vi::txt_unit_login_username, da::txt_unit_login_username, de::txt_unit_login_username, es::txt_unit_login_username, fr::txt_unit_login_username, it::txt_unit_login_username, ja::txt_unit_login_username, zh::txt_unit_login_username)                                         // TODO translate

// Page Login
MAKE_WORD_TRANSLATION(txt_login_title, en::txt_login_title, vi::txt_login_title, da::txt_login_title, de::txt_login_title, es::txt_login_title, fr::txt_login_title, it::txt_login_title, ja::txt_login_title, zh::txt_login_title)                                                             // TODO translate
MAKE_WORD_TRANSLATION(txt_login_username, en::txt_login_username, vi::txt_login_username, da::txt_login_username, de::txt_login_username, es::txt_login_username, fr::txt_login_username, it::txt_login_username, ja::txt_login_username, zh::txt_login_username)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_login_password, en::txt_login_password, vi::txt_login_password, en::txt_login_password, vi::txt_login_password, en::txt_login_password, vi::txt_login_password, en::txt_login_password, vi::txt_login_password)                                                       // TODO translate
MAKE_WORD_TRANSLATION(txt_login_sucess, en::txt_login_sucess, vi::txt_login_sucess, da::txt_login_sucess, de::txt_login_sucess, es::txt_login_sucess, fr::txt_login_sucess, it::txt_login_sucess, ja::txt_login_sucess, zh::txt_login_sucess)                                                   // TODO translate
MAKE_WORD_TRANSLATION(txt_login_fail, en::txt_login_fail, vi::txt_login_fail, da::txt_login_fail, de::txt_login_fail, es::txt_login_fail, fr::txt_login_fail, it::txt_login_fail, ja::txt_login_fail, zh::txt_login_fail)                                                                       // TODO translate
MAKE_WORD_TRANSLATION(txt_login_open_status, en::txt_login_open_status, vi::txt_login_open_status, da::txt_login_open_status, de::txt_login_open_status, es::txt_login_open_status, fr::txt_login_open_status, it::txt_login_open_status, ja::txt_login_open_status, zh::txt_login_open_status) // TODO translate
MAKE_WORD_TRANSLATION(txt_login_ph_user, en::txt_login_ph_user, vi::txt_login_ph_user, da::txt_login_ph_user, de::txt_login_ph_user, es::txt_login_ph_user, fr::txt_login_ph_user, it::txt_login_ph_user, ja::txt_login_ph_user, zh::txt_login_ph_user)                                         // TODO translate
MAKE_WORD_TRANSLATION(txt_login_ph_pwd, en::txt_login_ph_pwd, vi::txt_login_ph_pwd, da::txt_login_ph_pwd, de::txt_login_ph_pwd, es::txt_login_ph_pwd, fr::txt_login_ph_pwd, it::txt_login_ph_pwd, ja::txt_login_ph_pwd, zh::txt_login_ph_pwd)                                                   // TODO translate

// Page Upgrade
MAKE_WORD_TRANSLATION(txt_upgrade_title, en::txt_upgrade_title, vi::txt_upgrade_title, da::txt_upgrade_title, de::txt_upgrade_title, es::txt_upgrade_title, fr::txt_upgrade_title, it::txt_upgrade_title, ja::txt_upgrade_title, zh::txt_upgrade_title) // TODO translate
MAKE_WORD_TRANSLATION(txt_upgrade_info, en::txt_upgrade_info, vi::txt_upgrade_info, da::txt_upgrade_info, de::txt_upgrade_info, es::txt_upgrade_info, fr::txt_upgrade_info, it::txt_upgrade_info, ja::txt_upgrade_info, zh::txt_upgrade_info)           // TODO translate
MAKE_WORD_TRANSLATION(txt_upgrade_start, en::txt_upgrade_start, vi::txt_upgrade_start, da::txt_upgrade_start, de::txt_upgrade_start, es::txt_upgrade_start, fr::txt_upgrade_start, it::txt_upgrade_start, ja::txt_upgrade_start, zh::txt_upgrade_start) // TODO translate

// Page Upload
MAKE_WORD_TRANSLATION(txt_upload, en::txt_upload, vi::txt_upload, da::txt_upload, de::txt_upload, es::txt_upload, fr::txt_upload, it::txt_upload, ja::txt_upload, zh::txt_upload)                                                                                                                                   // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_nofile, en::txt_upload_nofile, vi::txt_upload_nofile, da::txt_upload_nofile, de::txt_upload_nofile, es::txt_upload_nofile, fr::txt_upload_nofile, it::txt_upload_nofile, ja::txt_upload_nofile, zh::txt_upload_nofile)                                                             // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_filetoolarge, en::txt_upload_filetoolarge, vi::txt_upload_filetoolarge, da::txt_upload_filetoolarge, de::txt_upload_filetoolarge, es::txt_upload_filetoolarge, fr::txt_upload_filetoolarge, it::txt_upload_filetoolarge, ja::txt_upload_filetoolarge, zh::txt_upload_filetoolarge) // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_fileheader, en::txt_upload_fileheader, vi::txt_upload_fileheader, da::txt_upload_fileheader, de::txt_upload_fileheader, es::txt_upload_fileheader, fr::txt_upload_fileheader, it::txt_upload_fileheader, ja::txt_upload_fileheader, zh::txt_upload_fileheader)                     // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_flashsize, en::txt_upload_flashsize, vi::txt_upload_flashsize, da::txt_upload_flashsize, de::txt_upload_flashsize, es::txt_upload_flashsize, fr::txt_upload_flashsize, it::txt_upload_flashsize, ja::txt_upload_flashsize, zh::txt_upload_flashsize)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_buffer, en::txt_upload_buffer, vi::txt_upload_buffer, da::txt_upload_buffer, de::txt_upload_buffer, es::txt_upload_buffer, fr::txt_upload_buffer, it::txt_upload_buffer, ja::txt_upload_buffer, zh::txt_upload_buffer)                                                             // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_failed, en::txt_upload_failed, vi::txt_upload_failed, da::txt_upload_failed, de::txt_upload_failed, es::txt_upload_failed, fr::txt_upload_failed, it::txt_upload_failed, ja::txt_upload_failed, zh::txt_upload_failed)                                                             // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_aborted, en::txt_upload_aborted, vi::txt_upload_aborted, da::txt_upload_aborted, de::txt_upload_aborted, es::txt_upload_aborted, fr::txt_upload_aborted, it::txt_upload_aborted, ja::txt_upload_aborted, zh::txt_upload_aborted)                                                   // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_code, en::txt_upload_code, vi::txt_upload_code, da::txt_upload_code, de::txt_upload_code, es::txt_upload_code, fr::txt_upload_code, it::txt_upload_code, ja::txt_upload_code, zh::txt_upload_code)                                                                                 // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_error, en::txt_upload_error, vi::txt_upload_error, da::txt_upload_error, de::txt_upload_error, es::txt_upload_error, fr::txt_upload_error, it::txt_upload_error, ja::txt_upload_error, zh::txt_upload_error)                                                                       // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_success, en::txt_upload_success, vi::txt_upload_success, da::txt_upload_success, de::txt_upload_success, es::txt_upload_success, fr::txt_upload_success, it::txt_upload_success, ja::txt_upload_success, zh::txt_upload_success)                                                   // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_refresh, en::txt_upload_refresh, vi::txt_upload_refresh, da::txt_upload_refresh, de::txt_upload_refresh, es::txt_upload_refresh, fr::txt_upload_refresh, it::txt_upload_refresh, ja::txt_upload_refresh, zh::txt_upload_refresh)                                                   // TODO translate

// Page Init
MAKE_WORD_TRANSLATION(txt_init_title, en::txt_init_title, vi::txt_init_title, da::txt_init_title, de::txt_init_title, es::txt_init_title, fr::txt_init_title, it::txt_init_title, ja::txt_init_title, zh::txt_init_title)                                                                       // TODO translate
MAKE_WORD_TRANSLATION(txt_init_reboot_mes, en::txt_init_reboot_mes, vi::txt_init_reboot_mes, da::txt_init_reboot_mes, de::txt_init_reboot_mes, es::txt_init_reboot_mes, fr::txt_init_reboot_mes, it::txt_init_reboot_mes, ja::txt_init_reboot_mes, zh::txt_init_reboot_mes)                     // TODO translate
MAKE_WORD_TRANSLATION(txt_init_reboot_mes_1, en::txt_init_reboot_mes_1, vi::txt_init_reboot_mes_1, da::txt_init_reboot_mes_1, de::txt_init_reboot_mes_1, es::txt_init_reboot_mes_1, fr::txt_init_reboot_mes_1, it::txt_init_reboot_mes_1, ja::txt_init_reboot_mes_1, zh::txt_init_reboot_mes_1) // TODO translate
MAKE_WORD_TRANSLATION(txt_init_reboot, en::txt_init_reboot, vi::txt_init_reboot, da::txt_init_reboot, de::txt_init_reboot, es::txt_init_reboot, fr::txt_init_reboot, it::txt_init_reboot, ja::txt_init_reboot, zh::txt_init_reboot)                                                             // TODO translate