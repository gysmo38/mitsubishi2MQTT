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

#pragma once

// Define language codes here and add to languages[] in config.h
#define MITSU2MQTT_LOCALE_EN "en"
#define MITSU2MQTT_LOCALE_VI "vi"
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
MAKE_WORD_TRANSLATION(txt_setup_page, en::txt_setup_page, vi::txt_setup_page)             // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_fw_page, en::txt_upload_fw_page, vi::txt_upload_fw_page) // TODO translate
MAKE_WORD_TRANSLATION(txt_fw_update_page, en::txt_fw_update_page, vi::txt_fw_update_page) // TODO translate
MAKE_WORD_TRANSLATION(txt_check_fw_page, en::txt_check_fw_page, vi::txt_check_fw_page)    // TODO translate
MAKE_WORD_TRANSLATION(txt_home_page, en::txt_home_page, vi::txt_home_page)                // TODO translate

// Main Menu
MAKE_WORD_TRANSLATION(txt_control, en::txt_control, vi::txt_control)                            // TODO translate
MAKE_WORD_TRANSLATION(txt_setup, en::txt_setup, vi::txt_setup)                                  // TODO translate
MAKE_WORD_TRANSLATION(txt_status, en::txt_status, vi::txt_status)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_firmware_upgrade, en::txt_firmware_upgrade, vi::txt_firmware_upgrade) // TODO translate
MAKE_WORD_TRANSLATION(txt_reboot, en::txt_reboot, vi::txt_reboot)                               // TODO translate

// Setup Menu
MAKE_WORD_TRANSLATION(txt_mqtt, en::txt_mqtt, vi::txt_mqtt)                            // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi, en::txt_wifi, vi::txt_wifi)                            // TODO translate
MAKE_WORD_TRANSLATION(txt_unit, en::txt_unit, vi::txt_unit)                            // TODO translate
MAKE_WORD_TRANSLATION(txt_others, en::txt_others, vi::txt_others)                      // TODO translate
MAKE_WORD_TRANSLATION(txt_reset, en::txt_reset, vi::txt_reset)                         // TODO translate
MAKE_WORD_TRANSLATION(txt_reset_confirm, en::txt_reset_confirm, vi::txt_reset_confirm) // TODO translate

// Buttons
MAKE_WORD_TRANSLATION(txt_back, en::txt_back, vi::txt_back)          // TODO translate
MAKE_WORD_TRANSLATION(txt_save, en::txt_save, vi::txt_save)          // TODO translate
MAKE_WORD_TRANSLATION(txt_logout, en::txt_logout, vi::txt_logout)    // TODO translate
MAKE_WORD_TRANSLATION(txt_upgrade, en::txt_upgrade, vi::txt_upgrade) // TODO translate
MAKE_WORD_TRANSLATION(txt_login, en::txt_login, vi::txt_login)       // TODO translate

// Form choices
MAKE_WORD_TRANSLATION(txt_f_on, en::txt_f_on, vi::txt_f_on)                   // TODO translate
MAKE_WORD_TRANSLATION(txt_f_off, en::txt_f_off, vi::txt_f_off)                // TODO translate
MAKE_WORD_TRANSLATION(txt_f_auto, en::txt_f_auto, vi::txt_f_auto)             // TODO translate
MAKE_WORD_TRANSLATION(txt_f_heat, en::txt_f_heat, vi::txt_f_heat)             // TODO translate
MAKE_WORD_TRANSLATION(txt_f_dry, en::txt_f_dry, vi::txt_f_dry)                // TODO translate
MAKE_WORD_TRANSLATION(txt_f_cool, en::txt_f_cool, vi::txt_f_cool)             // TODO translate
MAKE_WORD_TRANSLATION(txt_f_fan, en::txt_f_fan, vi::txt_f_fan)                // TODO translate
MAKE_WORD_TRANSLATION(txt_f_quiet, en::txt_f_quiet, vi::txt_f_quiet)          // TODO translate
MAKE_WORD_TRANSLATION(txt_f_speed, en::txt_f_speed, vi::txt_f_speed)          // TODO translate
MAKE_WORD_TRANSLATION(txt_f_swing, en::txt_f_swing, vi::txt_f_swing)          // TODO translate
MAKE_WORD_TRANSLATION(txt_f_pos, en::txt_f_pos, vi::txt_f_pos)                // TODO translate
MAKE_WORD_TRANSLATION(txt_f_celsius, en::txt_f_celsius, vi::txt_f_celsius)    // TODO translate
MAKE_WORD_TRANSLATION(txt_f_fh, en::txt_f_fh, vi::txt_f_fh)                   // TODO translate
MAKE_WORD_TRANSLATION(txt_f_allmodes, en::txt_f_allmodes, vi::txt_f_allmodes) // TODO translate
MAKE_WORD_TRANSLATION(txt_f_noheat, en::txt_f_noheat, vi::txt_f_noheat)       // TODO translate
MAKE_WORD_TRANSLATION(txt_f_noquiet, en::txt_f_noquiet, vi::txt_f_noquiet)    // TODO translate

// Page Reboot, save & Resseting
MAKE_WORD_TRANSLATION(txt_m_reboot, en::txt_m_reboot, vi::txt_m_reboot)    // TODO translate
MAKE_WORD_TRANSLATION(txt_m_reset, en::txt_m_reset, vi::txt_m_reset)       // TODO translate
MAKE_WORD_TRANSLATION(txt_m_reset_1, en::txt_m_reset_1, vi::txt_m_reset_1) // TODO translate
MAKE_WORD_TRANSLATION(txt_m_save, en::txt_m_save, vi::txt_m_save)          // TODO translate

// Page MQTT
MAKE_WORD_TRANSLATION(txt_mqtt_title, en::txt_mqtt_title, vi::txt_mqtt_title)             // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_fn, en::txt_mqtt_fn, vi::txt_mqtt_fn)                      // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_fn_desc, en::txt_mqtt_fn_desc, vi::txt_mqtt_fn_desc)       // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_host, en::txt_mqtt_host, vi::txt_mqtt_host)                // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_port, en::txt_mqtt_port, vi::txt_mqtt_port)                // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_port_desc, en::txt_mqtt_port_desc, vi::txt_mqtt_port_desc) // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_user, en::txt_mqtt_user, vi::txt_mqtt_user)                // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_password, en::txt_mqtt_password, vi::txt_mqtt_password)    // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_topic, en::txt_mqtt_topic, vi::txt_mqtt_topic)             // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_ph_user, en::txt_mqtt_ph_user, vi::txt_mqtt_ph_user)       // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_ph_pwd, en::txt_mqtt_ph_pwd, vi::txt_mqtt_ph_pwd)          // TODO translate
MAKE_WORD_TRANSLATION(txt_mqtt_ph_topic, en::txt_mqtt_ph_topic, vi::txt_mqtt_ph_topic)    // TODO translate

// Page Others
MAKE_WORD_TRANSLATION(txt_others_title, en::txt_others_title, vi::txt_others_title)                         // TODO translate
MAKE_WORD_TRANSLATION(txt_others_haauto, en::txt_others_haauto, vi::txt_others_haauto)                      // TODO translate
MAKE_WORD_TRANSLATION(txt_others_hatopic, en::txt_others_hatopic, vi::txt_others_hatopic)                   // TODO translate
MAKE_WORD_TRANSLATION(txt_others_debug_packets, en::txt_others_debug_packets, vi::txt_others_debug_packets) // TODO translate
MAKE_WORD_TRANSLATION(txt_others_debug_log, en::txt_others_debug_log, vi::txt_others_debug_log)             // TODO translate


// Page Status
MAKE_WORD_TRANSLATION(txt_status_title, en::txt_status_title, vi::txt_status_title)                   // TODO translate
MAKE_WORD_TRANSLATION(txt_status_hvac, en::txt_status_hvac, vi::txt_status_hvac)                      // TODO translate
MAKE_WORD_TRANSLATION(txt_retries_hvac, en::txt_retries_hvac, vi::txt_retries_hvac)                   // TODO translate
MAKE_WORD_TRANSLATION(txt_status_mqtt, en::txt_status_mqtt, vi::txt_status_mqtt)                      // TODO translate
MAKE_WORD_TRANSLATION(txt_status_wifi_ip, en::txt_status_wifi_ip, vi::txt_status_wifi_ip)             // TODO translate
MAKE_WORD_TRANSLATION(txt_failed_get_wifi_ip, en::txt_failed_get_wifi_ip, vi::txt_failed_get_wifi_ip) // TODO translate
MAKE_WORD_TRANSLATION(txt_status_wifi, en::txt_status_wifi, vi::txt_status_wifi)                      // TODO translate
MAKE_WORD_TRANSLATION(txt_build_version, en::txt_build_version, vi::txt_build_version)                // TODO translate
MAKE_WORD_TRANSLATION(txt_build_date, en::txt_build_date, vi::txt_build_date)                         // TODO translate
MAKE_WORD_TRANSLATION(txt_status_freeheap, en::txt_status_freeheap, vi::txt_status_freeheap)          // TODO translate
MAKE_WORD_TRANSLATION(txt_current_time, en::txt_current_time, vi::txt_current_time)                   // TODO translate
MAKE_WORD_TRANSLATION(txt_boot_time, en::txt_boot_time, vi::txt_boot_time)                            // TODO translate
MAKE_WORD_TRANSLATION(txt_status_connect, en::txt_status_connect, vi::txt_status_connect)             // TODO translate
MAKE_WORD_TRANSLATION(txt_status_disconnect, en::txt_status_disconnect, vi::txt_status_disconnect)    // TODO translate

// Page WIFI
MAKE_WORD_TRANSLATION(txt_wifi_title, en::txt_wifi_title, vi::txt_wifi_title)                         // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi_hostname, en::txt_wifi_hostname, vi::txt_wifi_hostname)                // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi_hostname_desc, en::txt_wifi_hostname_desc, vi::txt_wifi_hostname_desc) // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi_ssid, en::txt_wifi_ssid, vi::txt_wifi_ssid)                            // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi_ssid_enter, en::txt_wifi_ssid_enter, vi::txt_wifi_ssid_enter)          // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi_ssid_select, en::txt_wifi_ssid_select, vi::txt_wifi_ssid_select)       // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi_psk, en::txt_wifi_psk, vi::txt_wifi_psk)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_wifi_otap, en::txt_wifi_otap, vi::txt_wifi_otap)                            // TODO translate

// Page Control
MAKE_WORD_TRANSLATION(txt_ctrl_title, en::txt_ctrl_title, vi::txt_ctrl_title) // TODO translate
MAKE_WORD_TRANSLATION(txt_ctrl_temp, en::txt_ctrl_temp, vi::txt_ctrl_temp)    // TODO translate
MAKE_WORD_TRANSLATION(txt_ctrl_power, en::txt_ctrl_power, vi::txt_ctrl_power) // TODO translate
MAKE_WORD_TRANSLATION(txt_ctrl_mode, en::txt_ctrl_mode, vi::txt_ctrl_mode)    // TODO translate
MAKE_WORD_TRANSLATION(txt_ctrl_fan, en::txt_ctrl_fan, vi::txt_ctrl_fan)       // TODO translate
MAKE_WORD_TRANSLATION(txt_ctrl_vane, en::txt_ctrl_vane, vi::txt_ctrl_vane)    // TODO translate
MAKE_WORD_TRANSLATION(txt_ctrl_wvane, en::txt_ctrl_wvane, vi::txt_ctrl_wvane) // TODO translate
MAKE_WORD_TRANSLATION(txt_ctrl_ctemp, en::txt_ctrl_ctemp, vi::txt_ctrl_ctemp) // TODO translate

// Page Unit
MAKE_WORD_TRANSLATION(txt_unit_title, en::txt_unit_title, vi::txt_unit_title)                                        // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_language, en::txt_unit_language, vi::txt_unit_language)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_temp, en::txt_unit_temp, vi::txt_unit_temp)                                           // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_maxtemp, en::txt_unit_maxtemp, vi::txt_unit_maxtemp)                                  // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_mintemp, en::txt_unit_mintemp, vi::txt_unit_mintemp)                                  // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_steptemp, en::txt_unit_steptemp, vi::txt_unit_steptemp)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_modes, en::txt_unit_modes, vi::txt_unit_modes)                                        // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_fan_modes, en::txt_unit_fan_modes, vi::txt_unit_fan_modes)                            // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_password, en::txt_unit_password, vi::txt_unit_password)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_password_confirm, en::txt_unit_password_confirm, vi::txt_unit_password_confirm)       // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_password_not_match, en::txt_unit_password_not_match, vi::txt_unit_password_not_match) // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_login_username, en::txt_unit_login_username, vi::txt_unit_login_username)             // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_1_0_steptemp, en::txt_unit_1_0_steptemp, vi::txt_unit_1_0_steptemp)                   // TODO translate
MAKE_WORD_TRANSLATION(txt_unit_0_5_steptemp, en::txt_unit_0_5_steptemp, vi::txt_unit_0_5_steptemp)                   // TODO translate

// Page Login
MAKE_WORD_TRANSLATION(txt_login_title, en::txt_login_title, vi::txt_login_title)                   // TODO translate
MAKE_WORD_TRANSLATION(txt_login_username, en::txt_login_username, vi::txt_login_username)          // TODO translate
MAKE_WORD_TRANSLATION(txt_login_password, en::txt_login_password, vi::txt_login_password)          // TODO translate
MAKE_WORD_TRANSLATION(txt_login_sucess, en::txt_login_sucess, vi::txt_login_sucess)                // TODO translate
MAKE_WORD_TRANSLATION(txt_login_fail, en::txt_login_fail, vi::txt_login_fail)                      // TODO translate
MAKE_WORD_TRANSLATION(txt_login_open_status, en::txt_login_open_status, vi::txt_login_open_status) // TODO translate
MAKE_WORD_TRANSLATION(txt_login_ph_user, en::txt_login_ph_user, vi::txt_login_ph_user)             // TODO translate
MAKE_WORD_TRANSLATION(txt_login_ph_pwd, en::txt_login_ph_pwd, vi::txt_login_ph_pwd)                // TODO translate

// Page Upgrade
MAKE_WORD_TRANSLATION(txt_upgrade_title, en::txt_upgrade_title, vi::txt_upgrade_title) // TODO translate
MAKE_WORD_TRANSLATION(txt_upgrade_info, en::txt_upgrade_info, vi::txt_upgrade_info)    // TODO translate
MAKE_WORD_TRANSLATION(txt_upgrade_start, en::txt_upgrade_start, vi::txt_upgrade_start) // TODO translate

// Page Upload
MAKE_WORD_TRANSLATION(txt_upload, en::txt_upload, vi::txt_upload)                                        // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_nofile, en::txt_upload_nofile, vi::txt_upload_nofile)                   // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_filetoolarge, en::txt_upload_filetoolarge, vi::txt_upload_filetoolarge) // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_fileheader, en::txt_upload_fileheader, vi::txt_upload_fileheader)       // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_flashsize, en::txt_upload_flashsize, vi::txt_upload_flashsize)          // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_buffer, en::txt_upload_buffer, vi::txt_upload_buffer)                   // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_failed, en::txt_upload_failed, vi::txt_upload_failed)                   // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_aborted, en::txt_upload_aborted, vi::txt_upload_aborted)                // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_code, en::txt_upload_code, vi::txt_upload_code)                         // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_error, en::txt_upload_error, vi::txt_upload_error)                      // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_success, en::txt_upload_success, vi::txt_upload_success)                // TODO translate
MAKE_WORD_TRANSLATION(txt_upload_refresh, en::txt_upload_refresh, vi::txt_upload_refresh)                // TODO translate

// Page Init
MAKE_WORD_TRANSLATION(txt_init_title, en::txt_init_title, vi::txt_init_title)                      // TODO translate
MAKE_WORD_TRANSLATION(txt_init_reboot_mes, en::txt_init_reboot_mes, vi::txt_init_reboot_mes)       // TODO translate
MAKE_WORD_TRANSLATION(txt_init_reboot_mes_1, en::txt_init_reboot_mes_1, vi::txt_init_reboot_mes_1) // TODO translate
MAKE_WORD_TRANSLATION(txt_init_reboot, en::txt_init_reboot, vi::txt_init_reboot)                   // TODO translate

// Page Init Firmware Check
MAKE_WORD_TRANSLATION(txt_init_fw_check_mes, en::txt_init_fw_check_mes, vi::txt_init_fw_check_mes)       // TODO translate
MAKE_WORD_TRANSLATION(txt_init_fw_check_mes_1, en::txt_init_fw_check_mes_1, vi::txt_init_fw_check_mes_1) // TODO translate
MAKE_WORD_TRANSLATION(txt_b_check_new_fw, en::txt_b_check_new_fw, vi::txt_b_check_new_fw)                // TODO translate
MAKE_WORD_TRANSLATION(txt_fw_check_mes, en::txt_fw_check_mes, vi::txt_fw_check_mes)                      // TODO translate

// Page Init Firmware Check
MAKE_WORD_TRANSLATION(txt_ota_latest, en::txt_ota_latest, vi::txt_ota_latest)                                  // TODO translate
MAKE_WORD_TRANSLATION(txt_ota_invalid, en::txt_ota_invalid, vi::txt_ota_invalid)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_ota_available, en::txt_ota_available, vi::txt_ota_available)                         // TODO translate
MAKE_WORD_TRANSLATION(txt_ota_close_n_wait, en::txt_ota_close_n_wait, vi::txt_ota_close_n_wait)                // TODO translate
MAKE_WORD_TRANSLATION(txt_ota_checking, en::txt_ota_checking, vi::txt_ota_checking)                            // TODO translate
MAKE_WORD_TRANSLATION(txt_ota_check_failed, en::txt_ota_check_failed, vi::txt_ota_check_failed)                // TODO translate
MAKE_WORD_TRANSLATION(txt_ota_check_failed_code, en::txt_ota_check_failed_code, vi::txt_ota_check_failed_code) // TODO translate
MAKE_WORD_TRANSLATION(txt_ota_no_data, en::txt_ota_no_data, vi::txt_ota_no_data)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_ota_success, en::txt_ota_success, vi::txt_ota_success)                               // TODO translate
MAKE_WORD_TRANSLATION(txt_ota_file_corrupt, en::txt_ota_file_corrupt, vi::txt_ota_file_corrupt)                // TODO translate