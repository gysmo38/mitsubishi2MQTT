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
const char txt_control[] PROGMEM = "控制";
const char txt_setup[] PROGMEM = "设置";
const char txt_status[] PROGMEM = "状态";
const char txt_firmware_upgrade[] PROGMEM = "固件升级";
const char txt_reboot[] PROGMEM = "重启";

//Setup Menu
const char txt_MQTT[] PROGMEM = "MQTT";
const char txt_WIFI[] PROGMEM = "WIFI";
const char txt_unit[] PROGMEM = "单元";
const char txt_others[] PROGMEM = "其他";
const char txt_reset[] PROGMEM = "重置设置";
const char txt_reset_confirm[] PROGMEM = "是否确认重置此单元?";

//Buttons
const char txt_back[] PROGMEM = "后退";
const char txt_save[] PROGMEM = "保存并重启";
const char txt_logout[] PROGMEM = "退出";
const char txt_upgrade[] PROGMEM = "开始升级";
const char txt_login[] PROGMEM = "登录";

//Form choices
const char txt_f_on[] PROGMEM = "开启";
const char txt_f_off[] PROGMEM = "关闭";
const char txt_f_auto[] PROGMEM = "自动";
const char txt_f_heat[] PROGMEM = "制暖";
const char txt_f_dry[] PROGMEM = "干燥";
const char txt_f_cool[] PROGMEM = "制冷";
const char txt_f_fan[] PROGMEM = "送风";
const char txt_f_quiet[] PROGMEM = "安静";
const char txt_f_speed[] PROGMEM = "风速";
const char txt_f_swing[] PROGMEM = "摆动";
const char txt_f_pos[] PROGMEM = "风向";
const char txt_f_celsius[] PROGMEM = "摄氏";
const char txt_f_fh[] PROGMEM = "华氏";
const char txt_f_allmodes[] PROGMEM = "全部模式";
const char txt_f_noheat[] PROGMEM = "除制暖外全部模式";
const char txt_f_5s[] PROGMEM = "5秒";
const char txt_f_15s[] PROGMEM = "15秒";
const char txt_f_30s[] PROGMEM = "30秒";
const char txt_f_45s[] PROGMEM = "45秒";
const char txt_f_60s[] PROGMEM = "60秒";


//Page Reboot, save & Resseting
const char txt_m_reboot[] PROGMEM = "重启中... 刷新";
const char txt_m_reset[] PROGMEM = "重新配置中... 连接至SSID";
const char txt_m_save[] PROGMEM = "保持配置并重启中... 刷新";

//Page MQTT
const char txt_mqtt_title[] PROGMEM = "MQTT 参数";
const char txt_mqtt_fn[] PROGMEM = "友好名称";
const char txt_mqtt_host[] PROGMEM = "主机";
const char txt_mqtt_port[] PROGMEM = "端口(默认1883)";
const char txt_mqtt_user[] PROGMEM = "账户";
const char txt_mqtt_password[] PROGMEM = "密码";
const char txt_mqtt_topic[] PROGMEM = "主题";

//Page Others
const char txt_others_title[] PROGMEM = "其他参数";
const char txt_others_haauto[] PROGMEM = "HA 自动发现";
const char txt_others_hatopic[] PROGMEM = "HA 自动发现主题";
const char txt_others_availability_report[] PROGMEM = "HA 可用性报告";
const char txt_others_debug[] PROGMEM = "调试";

//Page Status
const char txt_status_title[] PROGMEM = "状态";
const char txt_status_hvac[] PROGMEM = "空调状态";
const char txt_retries_hvac[] PROGMEM = "HVAC Connection Retries";
const char txt_status_mqtt[] PROGMEM = "MQTT状态";
const char txt_status_wifi[] PROGMEM = "WIFI信号";
const char txt_status_connect[] PROGMEM = "已连接";
const char txt_status_disconnect[] PROGMEM = "未连接";

//Page WIFI
const char txt_wifi_title[] PROGMEM = "WIFI参数";
const char txt_wifi_hostname[] PROGMEM = "主机名";
const char txt_wifi_SSID[] PROGMEM = "SSID";
const char txt_wifi_psk[] PROGMEM = "密码";
const char txt_wifi_otap[] PROGMEM = "OTA密码";

//Page Control
const char txt_ctrl_title[] PROGMEM = "控制单元";
const char txt_ctrl_temp[] PROGMEM = "温度";
const char txt_ctrl_power[] PROGMEM = "电源";
const char txt_ctrl_mode[] PROGMEM = "模式";
const char txt_ctrl_fan[] PROGMEM = "风速";
const char txt_ctrl_vane[] PROGMEM = "上下送风";
const char txt_ctrl_wvane[] PROGMEM = "左右送风";
const char txt_ctrl_ctemp[] PROGMEM = "当前温度";

//Page Unit
const char txt_unit_title[] PROGMEM = "单元设置";
const char txt_unit_temp[] PROGMEM = "温度单位";
const char txt_unit_maxtemp[] PROGMEM = "最大温度";
const char txt_unit_mintemp[] PROGMEM = "最小温度";
const char txt_unit_steptemp[] PROGMEM = "温度步长";
const char txt_unit_modes[] PROGMEM = "支持模式";
const char txt_unit_update_interval[] PROGMEM = "更新间隔";
const char txt_unit_password[] PROGMEM = "网页密码";

//Page Login
const char txt_login_title[] PROGMEM = "授权";
const char txt_login_password[] PROGMEM = "密码";
const char txt_login_sucess[] PROGMEM = "登录成功, 即将重定向.";
const char txt_login_fail[] PROGMEM = "错误的账户/密码! 请重试.";

//Page Upgrade
const char txt_upgrade_title[] PROGMEM = "升级";
const char txt_upgrade_info[] PROGMEM = "通过上传的bin文件进行固件OTA升级";
const char txt_upgrade_start[] PROGMEM = "开始上传";

//Page Upload
const char txt_upload_nofile[] PROGMEM = "未选中文件";
const char txt_upload_filetoolarge[] PROGMEM = "文件大小超过闲置空间";
const char txt_upload_fileheader[] PROGMEM = "文件头不是0xE9";
const char txt_upload_flashsize[] PROGMEM = "文件刷写容量超过设备闪存空间";
const char txt_upload_buffer[] PROGMEM = "文件上传缓存不匹配";
const char txt_upload_failed[] PROGMEM = "上传失败. 开启日志选项3获取详细信息";
const char txt_upload_aborted[] PROGMEM = "上传中止";
const char txt_upload_code[] PROGMEM = "上传错误码 ";
const char txt_upload_error[] PROGMEM = "上传错误码 (参见 Updater.cpp) ";
const char txt_upload_sucess[] PROGMEM = "成功";
const char txt_upload_refresh[] PROGMEM = "刷新";

//Page Init
const char txt_init_title[] PROGMEM = "初始化设置";
const char txt_init_reboot_mes[] PROGMEM = "重启并连接至你的WiFi网络! 你将在访问点列表中见到本机.";
const char txt_init_reboot[] PROGMEM = "重启中...";
