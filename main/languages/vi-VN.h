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
namespace vi
{
  // Breadcum
  const char txt_setup_page[] PROGMEM = "Trang cài đặt";
  const char txt_upload_fw_page[] PROGMEM = "Tải lên phần mềm";
  const char txt_fw_update_page[] PROGMEM = "Nâng cấp phần mềm";
  const char txt_check_fw_page[] PROGMEM = "Kiểm tra phần mềm mới";
  const char txt_home_page[] PROGMEM = "Trang nhà";

  // Main Menu
  const char txt_control[] PROGMEM = "Điều khiển";
  const char txt_setup[] PROGMEM = "Cài đặt";
  const char txt_status[] PROGMEM = "Trạng thái";
  const char txt_firmware_upgrade[] PROGMEM = "Nâng cấp phần mềm";
  const char txt_reboot[] PROGMEM = "Khởi động lại";

  // Setup Menu
  const char txt_mqtt[] PROGMEM = "MQTT";
  const char txt_wifi[] PROGMEM = "WIFI";
  const char txt_unit[] PROGMEM = "THIẾT BỊ";
  const char txt_others[] PROGMEM = "KHÁC";
  const char txt_reset[] PROGMEM = "Đặt lại cấu hình";
  const char txt_reset_confirm[] PROGMEM = "Bạn có chắc chắn muốn đặt lại cấu hình cho thiết bị này?";

  // Buttons
  const char txt_back[] PROGMEM = "Quay lại";
  const char txt_save[] PROGMEM = "Lưu & Khởi động lại";
  const char txt_logout[] PROGMEM = "Đăng xuất";
  const char txt_upgrade[] PROGMEM = "Bắt đầu nâng cấp";
  const char txt_login[] PROGMEM = "Đăng nhập";

  // Form choices
  const char txt_f_on[] PROGMEM = "BẬT";
  const char txt_f_off[] PROGMEM = "TẮT";
  const char txt_f_auto[] PROGMEM = "TỰ ĐỘNG";
  const char txt_f_heat[] PROGMEM = "SƯỞI";
  const char txt_f_dry[] PROGMEM = "KHÔ";
  const char txt_f_cool[] PROGMEM = "MÁT";
  const char txt_f_fan[] PROGMEM = "QUẠT";
  const char txt_f_quiet[] PROGMEM = "IM LẶNG";
  const char txt_f_speed[] PROGMEM = "TỐC ĐỘ";
  const char txt_f_swing[] PROGMEM = "TẢN";
  const char txt_f_pos[] PROGMEM = "VỊ TRÍ";
  const char txt_f_celsius[] PROGMEM = "Độ C";
  const char txt_f_fh[] PROGMEM = "Độ F";
  const char txt_f_allmodes[] PROGMEM = "Tất cả chế độ";
  const char txt_f_noheat[] PROGMEM = "Tất cả chế độ trừ Sưởi";
  const char txt_f_noquiet[] PROGMEM = "Không có chế độ Im lặng";

  // Page Reboot, save & Resseting
  const char txt_m_reboot[] PROGMEM = "Đang khởi động lại... Làm mới trong";
  const char txt_m_reset[] PROGMEM = "Đang đặt lại trong";
  const char txt_m_reset_1[] PROGMEM = "Bạn có thể kết nối lại với SSID";
  const char txt_m_save[] PROGMEM = "Đang lưu cấu hình và khởi động lại... Làm mới trong";

  // Page MQTT
  const char txt_mqtt_title[] PROGMEM = "Thông số MQTT";
  const char txt_mqtt_fn[] PROGMEM = "Tên thân thiện";
  const char txt_mqtt_fn_desc[] PROGMEM = "(trừ khoảng trống và ký tự lạ)";
  const char txt_mqtt_host[] PROGMEM = "Tên miền hoặc IP";
  const char txt_mqtt_port[] PROGMEM = "Cổng";
  const char txt_mqtt_port_desc[] PROGMEM = "(mặc định 1883, trừ 8883)";
  const char txt_mqtt_user[] PROGMEM = "Tài khoản";
  const char txt_mqtt_password[] PROGMEM = "Mật khẩu";
  const char txt_mqtt_topic[] PROGMEM = "Chủ đề";
  const char txt_mqtt_ph_topic[] PROGMEM = "Nhập chủ đề Mqtt";
  const char txt_mqtt_ph_user[] PROGMEM = "Nhập tài khoản Mqtt";
  const char txt_mqtt_ph_pwd[] PROGMEM = "Nhập mật khẩu Mqtt";

  // Page Others
  const char txt_others_title[] PROGMEM = "Thông số Khác";
  const char txt_others_haauto[] PROGMEM = "Tùy chỉnh HA chủ đề tự động khám phá";
  const char txt_others_hatopic[] PROGMEM = "Chủ đề tự động khám phá";
  const char txt_others_debug_packets[] PROGMEM = "MQTT gỡ lỗi gói tin";
  const char txt_others_debug_log[] PROGMEM = "MQTT gỡ lỗi nhật ký";

  // Page Status
  const char txt_status_title[] PROGMEM = "Trạng thái";
  const char txt_status_hvac[] PROGMEM = "Trạng thái ĐH";
  const char txt_retries_hvac[] PROGMEM = "ĐH thử lại kết nối";
  const char txt_status_mqtt[] PROGMEM = "Trạng thái MQTT";
  const char txt_status_wifi_ip[] PROGMEM = "WIFI IP";
  const char txt_failed_get_wifi_ip[] PROGMEM = "Lỗi khi lấy địa chỉ IP";
  const char txt_status_wifi[] PROGMEM = "WIFI RSSI";
  const char txt_build_version[] PROGMEM = "Phiên bản Dựng";
  const char txt_build_date[] PROGMEM = "Ngày Dựng";
  const char txt_status_freeheap[] PROGMEM = "Bộ nhớ trống";
  const char txt_current_time[] PROGMEM = "Ngày tháng";
  const char txt_boot_time[] PROGMEM = "Thời gian khởi động";
  const char txt_status_connect[] PROGMEM = "KẾT NỐI";
  const char txt_status_disconnect[] PROGMEM = "MẤT KẾT NỐI";

  // Page WIFI
  const char txt_wifi_title[] PROGMEM = "Thông số WIFI";
  const char txt_wifi_hostname[] PROGMEM = "Tên máy chủ";
  const char txt_wifi_hostname_desc[] PROGMEM = "(trừ khoảng trống và ký tự lạ)";
  const char txt_wifi_ssid[] PROGMEM = "Tên mạng Wifi";
  const char txt_wifi_ssid_enter[] PROGMEM = "(Nhập vào tên)";
  const char txt_wifi_ssid_select[] PROGMEM = "hoặc chọn 1 mạng:";
  const char txt_wifi_psk[] PROGMEM = "Mật khẩu Wifi";
  const char txt_wifi_otap[] PROGMEM = "Mật khẩu OTA";

  // Page Control
  const char txt_ctrl_title[] PROGMEM = "Điều khiển Thiết bị";
  const char txt_ctrl_temp[] PROGMEM = "Nhiệt độ";
  const char txt_ctrl_power[] PROGMEM = "Nguồn";
  const char txt_ctrl_mode[] PROGMEM = "Chế độ";
  const char txt_ctrl_fan[] PROGMEM = "Quạt";
  const char txt_ctrl_vane[] PROGMEM = "Cánh";
  const char txt_ctrl_wvane[] PROGMEM = "Cánh rộng";
  const char txt_ctrl_ctemp[] PROGMEM = "Nhiệt độ hiện tại";

  // Page Unit
  const char txt_unit_title[] PROGMEM = "Cấu hình thiết bị";
  const char txt_unit_language[] PROGMEM = "Ngôn ngữ";
  const char txt_unit_temp[] PROGMEM = "Đơn vị nhiệt độ";
  const char txt_unit_maxtemp[] PROGMEM = "Nhiệt độ tối đa";
  const char txt_unit_mintemp[] PROGMEM = "Nhiệt độ tối thiểu";
  const char txt_unit_steptemp[] PROGMEM = "Bước nhiệt độ";
  const char txt_unit_modes[] PROGMEM = "Hỗ trợ Chế độ";
  const char txt_unit_fan_modes[] PROGMEM = "Hỗ trợ Chế độ Quạt";
  const char txt_unit_password[] PROGMEM = "Mật khẩu đăng nhập";
  const char txt_unit_password_confirm[] PROGMEM = "Xác nhận Mật khẩu đăng nhập";
  const char txt_unit_password_not_match[] PROGMEM = "Mật khẩu nhập lại không đúng";
  const char txt_unit_login_username[] PROGMEM = "Ghi chú: Tài khoản đăng nhập mặc định là:";

  // Page Login
  const char txt_login_title[] PROGMEM = "Xác thực";
  const char txt_login_username[] PROGMEM = "Tài khoản";
  const char txt_login_password[] PROGMEM = "Mật khẩu";
  const char txt_login_sucess[] PROGMEM = "Đăng nhập thành công, bạn sẽ được chuyển hướng sau vài giây.";
  const char txt_login_fail[] PROGMEM = "Tên người dùng/mật khẩu sai! Hãy thử lại.";
  const char txt_login_open_status[] PROGMEM = "Mở trang trạng thái";
  const char txt_login_ph_user[] PROGMEM = "Nhập tài khoản";
  const char txt_login_ph_pwd[] PROGMEM = "Nhập mật khẩu";

  // Page Upgrade
  const char txt_upgrade_title[] PROGMEM = "Nâng cấp";
  const char txt_upgrade_info[] PROGMEM = "Nâng cấp OTA bằng cách tải lên tệp bin";
  const char txt_upgrade_start[] PROGMEM = "Đã bắt đầu tải lên";

  // Page Upload
  const char txt_upload[] PROGMEM = "Tải lên";
  const char txt_upload_nofile[] PROGMEM = "Không có tập tin được chọn";
  const char txt_upload_filetoolarge[] PROGMEM = "Kích thước tệp lớn hơn dung lượng trống có sẵn";
  const char txt_upload_fileheader[] PROGMEM = "Tiêu đề ma thuật của tệp không bắt đầu bằng 0xE9";
  const char txt_upload_flashsize[] PROGMEM = "Kích thước flash của tệp lớn hơn kích thước flash của thiết bị";
  const char txt_upload_buffer[] PROGMEM = "So sánh sai bộ đệm tải lên tệp";
  const char txt_upload_failed[] PROGMEM = "Tải lên không thành công. Bật tùy chọn ghi nhật ký 3 để biết thêm thông tin";
  const char txt_upload_aborted[] PROGMEM = "Tải lên bị hủy bỏ";
  const char txt_upload_code[] PROGMEM = "Tải lên mã lỗi ";
  const char txt_upload_error[] PROGMEM = "Cập nhật mã lỗi (xem Updater.cpp) ";
  const char txt_upload_success[] PROGMEM = "Thành công";
  const char txt_upload_refresh[] PROGMEM = "Làm mới trong";

  // Page Init
  const char txt_init_title[] PROGMEM = "Thiết lập ban đầu";
  const char txt_init_reboot_mes[] PROGMEM = "Kết nối với mạng WiFi của bạn bằng địa chỉ cục bộ";
  const char txt_init_reboot_mes_1[] PROGMEM = "Sử dụng địa chỉ này để truy cập thiết bị của bạn sau khi khởi động lại. Khởi động lại trong";
  const char txt_init_reboot[] PROGMEM = "Đang khởi động lại...";
}