/*
  mitsubishi2mqtt - Mitsubishi Heat Pump to MQTT control for Home Assistant.
  Copyright (c) 2019 gysmo38, dzungpv, shampeon, endeavour, jascdk, chrdavis, alekslyse.  All right reserved.
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
const char txt_control[] PROGMEM = "コントロール";
const char txt_setup[] PROGMEM = "設定";
const char txt_status[] PROGMEM = "ステータス";
const char txt_firmware_upgrade[] PROGMEM = "ファームウェア更新";
const char txt_reboot[] PROGMEM = "再起動";

//Setup Menu
const char txt_MQTT[] PROGMEM = "MQTT";
const char txt_WIFI[] PROGMEM = "WIFI";
const char txt_unit[] PROGMEM = "本体";
const char txt_others[] PROGMEM = "その他";
const char txt_reset[] PROGMEM = "初期化";

//Buttons
const char txt_back[] PROGMEM = "戻る";
const char txt_save[] PROGMEM = "保存して再起動";
const char txt_logout[] PROGMEM = "ログアウト";
const char txt_upgrade[] PROGMEM = "更新開始";
//Pages