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
 
const char html_init_setup[] PROGMEM = ""
        "<div style='text-align:center;'>"
            "<h2>_TXT_INIT_TITLE_</h2>"
        "</div>"
        "<div id='l1' name='l1'></div>"
            "<form method='get' action='save'>"
                "<p><b>_TXT_UNIT_LANGUAGE_</b>"
                    "<br/>"
                    "<select id='language' name='language' onchange=\"sendLanguage(this)\">"
                       "_LANGUAGE_OPTIONS_"
                    "</select>"
                "</p>"
                "<fieldset>"
                "<legend><b>&nbsp; _TXT_WIFI_TITLE_ &nbsp;</b></b></legend>"
                "<p><b>_TXT_WIFI_SSID_</b> _TXT_WIFI_SSID_ENTER_"
                    "<br/>"
                    "<input id='ssid' name='ssid' placeholder=' ' autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false'>"
                    "<br/>"
                    "<label for='network'>_TXT_WIFI_SSID_SELECT_</label>"
                    "<select id='network' name='network'>"
                        "_WIFI_OPTIONS_"
                    "</select>"
                "</p>"
                "<p><b>_TXT_WIFI_PSK_</b>"
                    "<br/>"
                    "<input type='password' id='psk' name='psk' placeholder=' '>"
                "</p>"
                "</fieldset>"
                "<fieldset>"
                "<legend><b>&nbsp; _TXT_MQTT_TITLE_ &nbsp;</b><br/></legend>"
                    "<p><b>_TXT_MQTT_HOST_</b>"
                        "<br/>"
                        "<input id='mh' name='mh' placeholder=' ' value='_MQTT_HOST_' autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false'>"
                    "</p>"
                    "<p><b>_TXT_MQTT_PORT_</b> _TXT_MQTT_PORT_DESC"
                        "<br/>"
                        "<input id='ml' name='ml' placeholder='1883' value='_MQTT_PORT_' autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false'>"
                    "</p>"
                    "<p><b>_TXT_MQTT_USER_</b>"
                        "<br/>"
                        "<input id='mu' name='mu' placeholder='_TXT_MQTT_PH_USER_' value='_MQTT_USER_' autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false'>"
                    "</p>"
                    "<p><b>_TXT_MQTT_PASSWORD_</b>"
                        "<br/>"
                        "<input id='mp' name='mp' type='password' placeholder='_TXT_MQTT_PH_PWD_' value='_MQTT_PASSWORD_' autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false'>"
                    "</p>"
                "</fieldset>"
                "<br/>"
                "<button name='submit' type='submit' class='button bgrn'>_TXT_SAVE_</button>"
            "</form>"
            "<div class='ctrlrow' _FIRMWARE_UPLOAD_>"
            "<form method='get' action='/upgrade'>"
                "<br/>"
                "<button type='submit' class='button bgrn'>_TXT_FIRMWARE_UPGRADE_</button>"
            "</form>"
            "</div>";

const char html_init_save[] PROGMEM = 
        "<p>_TXT_INIT_REBOOT_MES_"
        " <b>_CONFIG_ADDR_</b>"
        "<br>"
        "_TXT_INIT_REBOOT_MES_1_"
        " <span id='count'>10s</span>...</p>";

const char html_init_reboot[] PROGMEM = 
        "<p>_TXT_INIT_REBOOT_</p>";