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
const char txt_control[] PROGMEM = "エアコン操作";
const char txt_setup[] PROGMEM = "設定";
const char txt_status[] PROGMEM = "ステータス";
const char txt_firmware_upgrade[] PROGMEM = "ファームウェア更新";
const char txt_reboot[] PROGMEM = "再起動";

//Setup Menu
const char txt_MQTT[] PROGMEM = "MQTT";
const char txt_WIFI[] PROGMEM = "WIFI";
const char txt_unit[] PROGMEM = "エアコン本体";
const char txt_others[] PROGMEM = "その他";
const char txt_reset[] PROGMEM = "初期化";
const char txt_reset_confirm[] PROGMEM = "Do you really want to reset this unit?";

//Buttons
const char txt_back[] PROGMEM = "戻る";
const char txt_save[] PROGMEM = "保存して再起動";
const char txt_logout[] PROGMEM = "ログアウト";
const char txt_upgrade[] PROGMEM = "アップデート開始";
const char txt_login[] PROGMEM = "LOGIN";

//Form choices
const char txt_f_on[] PROGMEM = "オン";
const char txt_f_off[] PROGMEM = "オフ";
const char txt_f_auto[] PROGMEM = "自動";
const char txt_f_heat[] PROGMEM = "暖房";
const char txt_f_dry[] PROGMEM = "除湿";
const char txt_f_cool[] PROGMEM = "冷房";
const char txt_f_fan[] PROGMEM = "送風";
const char txt_f_quiet[] PROGMEM = "静";
const char txt_f_speed[] PROGMEM = "風速";
const char txt_f_swing[] PROGMEM = "スイング";
const char txt_f_pos[] PROGMEM = "風向";
const char txt_f_celsius[] PROGMEM = "摂氏";
const char txt_f_fh[] PROGMEM = "華氏";
const char txt_f_allmodes[] PROGMEM = "全ての機能";
const char txt_f_noheat[] PROGMEM = "暖房以外の全ての機能";


//Page Reboot, save & Resseting
const char txt_m_reboot[] PROGMEM = "再起動中";
const char txt_m_reset[] PROGMEM = "初期化中... SSIDに接続してください";
const char txt_m_save[] PROGMEM = "設定を保存し、再起動中";

//Page MQTT
const char txt_mqtt_title[] PROGMEM = "MQTT設定";
const char txt_mqtt_fn[] PROGMEM = "フレンドリー名";
const char txt_mqtt_host[] PROGMEM = "ホスト";
const char txt_mqtt_port[] PROGMEM = "ポート（初期値 1883）";
const char txt_mqtt_user[] PROGMEM = "ユーザー名";
const char txt_mqtt_password[] PROGMEM = "パスワード";
const char txt_mqtt_topic[] PROGMEM = "トピック";

//Page Others
const char txt_others_title[] PROGMEM = "その他設定";
const char txt_others_haauto[] PROGMEM = "HA自動検出";
const char txt_others_hatopic[] PROGMEM = "HA自動検出トピック";
const char txt_others_debug_packets[] PROGMEM = "MQTT topic debug packets";
const char txt_others_debug_log[] PROGMEM = "MQTT topic debug logs";

//Page Status
const char txt_status_title[] PROGMEM = "ステータス";
const char txt_status_hvac[] PROGMEM = "エアコン本体";
const char txt_retries_hvac[] PROGMEM = "HVAC Connection Retries";
const char txt_status_mqtt[] PROGMEM = "MQTT";
const char txt_status_wifi[] PROGMEM = "WIFI RSSI";
const char txt_status_connect[] PROGMEM = "接続中";
const char txt_status_disconnect[] PROGMEM = "切断中";

//Page WIFI
const char txt_wifi_title[] PROGMEM = "WIFI設定";
const char txt_wifi_hostname[] PROGMEM = "ホスト名";
const char txt_wifi_SSID[] PROGMEM = "SSID";
const char txt_wifi_psk[] PROGMEM = "PSK";
const char txt_wifi_otap[] PROGMEM = "OTAパスワード";

//Page Control
const char txt_ctrl_title[] PROGMEM = "エアコン操作";
const char txt_ctrl_temp[] PROGMEM = "設定温度";
const char txt_ctrl_power[] PROGMEM = "電源";
const char txt_ctrl_mode[] PROGMEM = "運転モード";
const char txt_ctrl_fan[] PROGMEM = "風量";
const char txt_ctrl_vane[] PROGMEM = "上下風向";
const char txt_ctrl_wvane[] PROGMEM = "左右風向";
const char txt_ctrl_ctemp[] PROGMEM = "現在の室温";

//Page Unit
const char txt_unit_title[] PROGMEM = "エアコン本体設定";
const char txt_unit_temp[] PROGMEM = "温度単位";
const char txt_unit_maxtemp[] PROGMEM = "最高設定温度";
const char txt_unit_mintemp[] PROGMEM = "最低設定温度";
const char txt_unit_steptemp[] PROGMEM = "設定温度単位";
const char txt_unit_modes[] PROGMEM = "対応機能";
const char txt_unit_password[] PROGMEM = "Webパスワード";

//Page Login
const char txt_login_title[] PROGMEM = "ログイン";
const char txt_login_password[] PROGMEM = "パスワード";
const char txt_login_sucess[] PROGMEM = "ログイン成功、数秒後にリダイレクトされます";
const char txt_login_fail[] PROGMEM = "ユーザー名・パスワードが間違っています、もう一度試してください";

//Page Upgrade
const char txt_upgrade_title[] PROGMEM = "ファームウェア更新";
const char txt_upgrade_info[] PROGMEM = "binファイルをアップロードし、ファームウェアのOTAアップデートを行う";
const char txt_upgrade_start[] PROGMEM = "アップロード中";

//Page Upload
const char txt_upload_nofile[] PROGMEM = "ファイルが選択されていません";
const char txt_upload_filetoolarge[] PROGMEM = "ファイルのサイズが空き容量を超えています";
const char txt_upload_fileheader[] PROGMEM = "ファイルのマジックナンバーが0xE9から始まっていません";
const char txt_upload_flashsize[] PROGMEM = "ファイルのフラッシュサイズがデバイスのフラッシュ容量を超えています";
const char txt_upload_buffer[] PROGMEM = "ファイルアップロードのバッファサイズが一致しません";
const char txt_upload_failed[] PROGMEM = "アップロード失敗. loggingのオプション3を有効にし、詳細を確認してください";
const char txt_upload_aborted[] PROGMEM = "アップロード中止";
const char txt_upload_code[] PROGMEM = "アップロードエラーコード ";
const char txt_upload_error[] PROGMEM = "アップデートエラーコード (Updater.cppを参照してください) ";
const char txt_upload_sucess[] PROGMEM = "成功";
const char txt_upload_refresh[] PROGMEM = "再読込中";

//Page Init
const char txt_init_title[] PROGMEM = "初期設定";
const char txt_init_reboot_mes[] PROGMEM = "Rebooting and connecting to your WiFi network! You should see it listed in on your access point.";
const char txt_init_reboot[] PROGMEM = "Rebooting...";
