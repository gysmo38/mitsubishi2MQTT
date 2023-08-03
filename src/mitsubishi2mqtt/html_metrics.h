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

const char html_metrics[] PROGMEM = R"====(
# HELP mitsubishi2mqtt_version Mitsubishi2MQTT version
# TYPE mitsubishi2mqtt_version gauge
mitsubishi2mqtt_version{hostname="_UNIT_NAME_",version="_VERSION_"} 1
# HELP mitsubishi_power Heat pump power setting
# TYPE mitsubishi_power gauge
mitsubishi_power{hostname="_UNIT_NAME_"} _POWER_
# HELP mitsubishi_temperature_room_celsius Current room temperature
# TYPE mitsubishi_temperature_room_celsius gauge
mitsubishi_temperature_room_celsius{hostname="_UNIT_NAME_"} _ROOMTEMP_
# HELP mitsubishi_temperature_target_celsius Target room temperature
# TYPE mitsubishi_temperature_target_celsius gauge
mitsubishi_temperature_target_celsius{hostname="_UNIT_NAME_"} _TEMP_
# HELP mitsubishi_fan_speed Heat pump fan speed
# TYPE mitsubishi_fan_speed gauge
mitsubishi_fan_speed{hostname="_UNIT_NAME_"} _FAN_
# HELP mitsubishi_vane Heat pump vane setting
# TYPE mitsubishi_vane gauge
mitsubishi_vane{hostname="_UNIT_NAME_"} _VANE_
# HELP mitsubishi_widevane Heat pump wide vane setting
# TYPE mitsubishi_widevane gauge
mitsubishi_widevane{hostname="_UNIT_NAME_"} _WIDEVANE_
# HELP mitsubishi_mode Heat pump operating mode
# TYPE mitsubishi_mode gauge
mitsubishi_mode{hostname="_UNIT_NAME_"} _MODE_
# HELP mitsubishi_operating Heat pump operational status
# TYPE mitsubishi_operating gauge
mitsubishi_operating{hostname="_UNIT_NAME_"} _OPER_
# HELP mitsubishi_compressor_frequency Heat pump compressor frequency
# TYPE mitsubishi_compressor_frequency gauge
mitsubishi_compressor_frequency{hostname="_UNIT_NAME_"} _COMPFREQ_
)====";
