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


const char html_page_reboot[] PROGMEM =
"<p>_TXT_M_REBOOT_ <span id='count'>10s</span>...</p>"
;

const char html_page_reset[] PROGMEM =
"<p>_TXT_M_RESET_ _SSID_...</p>"
;


const char html_page_save_reboot[] PROGMEM =
"<p>_TXT_M_SAVE_ <span id='count'>10s</span>...</p>"
;

const char html_page_mqtt[] PROGMEM =
"<div id='l1' name='l1'>"
    "<fieldset>"
        "<legend><b>&nbsp; _TXT_MQTT_TITLE_ &nbsp;</b></legend>"
        "<form method='post'>"
            "<p><b>_TXT_MQTT_FN_</b>"
                "<br/>"
                "<input id='fn' name='fn' "
                "autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false' "
                "placeholder=' ' value='_MQTT_FN_'>"
            "</p>"
            "<p><b>_TXT_MQTT_HOST_</b>"
                "<br/>"
                "<input id='mh' name='mh' "
                "autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false' "
                "placeholder=' ' value='_MQTT_HOST_'>"
            "</p>"
            "<p><b>_TXT_MQTT_PORT_</b>"
                "<br/>"
                "<input id='ml' name='ml' type='numeric' placeholder='1883' value='_MQTT_PORT_'>"
            "</p>"
            "<p><b>_TXT_MQTT_USER_</b>"
                "<br/>"
                "<input id='mu' name='mu' "
                "autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false' "
                "placeholder='DVES_USER' value='_MQTT_USER_'>"
            "</p>"
            "<p><b>_TXT_MQTT_PASSWORD_</b>"
                "<br/>"
                "<input id='mp' name='mp' type='password' placeholder='Password' value='_MQTT_PASSWORD_'>"
            "</p>"
            "<p><b>_TXT_MQTT_TOPIC_</b>"
                "<br/>"
                "<input id='mt' name='mt' "
                "autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false' "
                "placeholder='topic' value='_MQTT_TOPIC_'>"
            "</p>"
            "<br/>"
            "<button name='save' type='submit' class='button bgrn'>_TXT_SAVE_</button>"
        "</form>"
    "</fieldset>"
    "<p>"
        "<a class='button back' href='/setup'>_TXT_BACK_</a>"
    "</p>"
"</div>"
;

const char html_page_others[] PROGMEM =
"<div id='l1' name='l1'>"
    "<fieldset>"
        "<legend><b>&nbsp; _TXT_OTHERS_TITLE_ &nbsp;</b></legend>"
        "<form method='post'>"
            "<p><b>_TXT_OTHERS_HAAUTO_</b>"
                "<select name='HAA'>"
                    "<option value='ON' _HAA_ON_>_TXT_F_ON_</option>"
                    "<option value='OFF' _HAA_OFF_>_TXT_F_OFF_</option>"
                "</select>"
            "</p>"
            "<p><b>_TXT_OTHERS_HATOPIC_</b> ()"
                "<br/>"
                "<input id='haat' name='haat' "
                "autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false' "
                "placeholder=' ' value='_HAA_TOPIC_'>"
            "</p>"
            "<p><b>_TXT_OTHERS_DEBUG_LOGS_</b>"
                "<select name='DebugLogs'>"
                    "<option value='ON' _DEBUG_LOGS_ON_>_TXT_F_ON_</option>"
                    "<option value='OFF' _DEBUG_LOGS_OFF_>_TXT_F_OFF_</option>"
                "</select>"
            "</p>"
            "<p><b>_TXT_OTHERS_DEBUG_PCKTS_</b>"
                "<select name='DebugPckts'>"
                    "<option value='ON' _DEBUG_PCKTS_ON_>_TXT_F_ON_</option>"
                    "<option value='OFF' _DEBUG_PCKTS_OFF_>_TXT_F_OFF_</option>"
                "</select>"
            "</p>"
            "<br/>"
            "<button name='save' type='submit' class='button bgrn'>_TXT_SAVE_</button>"
        "</form>"
    "</fieldset>"
    "<p>"
        "<a class='button back' href='/setup'>_TXT_BACK_</a>"
    "</p>"
"</div>"
;

const char html_page_status[] PROGMEM =
"<div id='l1' name='l1'>"
    "<fieldset>"
    "<legend><b>&nbsp; _TXT_STATUS_TITLE_ &nbsp;</b></legend>"
    "<p><b>_TXT_STATUS_HVAC_</b>"
        " ==> "
        "_HVAC_STATUS_"
    "</p>"
     "<p><b>_TXT_RETRIES_HVAC_</b>"
        " ==> "
        "_HVAC_RETRIES_"
    "</p>"
     "<p><b>_TXT_STATUS_MQTT_</b>"
        " ==> " 
        "_MQTT_STATUS_ ( _MQTT_REASON_ )"
    "</p>"
     "<p><b>_TXT_STATUS_WIFI_</b>"
        " ==> "
        "_WIFI_STATUS_ dBm"
    "</p>"
    "</fieldset>"
    "<br />"
    "<p>"
        "<a class='button back' href='/'>_TXT_BACK_</a>"
    "</p>"
"</div>"
;

const char html_page_wifi[] PROGMEM =
"<div id='l1' name='l1'>"
    "<fieldset>"
        "<legend><b>&nbsp; _TXT_WIFI_TITLE_ &nbsp;</b></legend>"
        "<form method='post'>"
            "<p><b>_TXT_WIFI_HOST_</b>"
                "<br/>"
                "<input id='hn' "
                "autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false' "
                " name='hn' placeholder=' ' value='_UNIT_NAME_'>"
            "</p>"
            "<p><b>_TXT_WIFI_SSID_</b>"
                "<br/>"
                "<input id='ssid' "
                "autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false' "
                "name='ssid' placeholder=' ' value='_SSID_'>"
            "</p>"
            "<p><b>_TXT_WIFI_PSK_</b>"
                "<br/>"
                "<input id='psk' type='password' name='psk' placeholder=' ' value='_PSK_'>"
            "</p>"
            "<p><b>_TXT_WIFI_OTAP_</b>"
                "<br/>"
                "<input id='otapwd' "
                "autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false' "
                "name='otapwd' placeholder=' ' value='_OTA_PWD_'>"
            "</p>"
            "<br/>"
            "<button name='save' type='submit' class='button bgrn'>_TXT_SAVE_</button>"
        "</form>"
    "</fieldset>"
    "<p>"
        "<a class='button back' href='/setup'>_TXT_BACK_</a>"
    "</p>"
"</div>"
;


const char html_page_control[] PROGMEM =
"<h2>_TXT_CTRL_CTEMP_ _ROOMTEMP_&#176;</h2>"
"<div id='l1' name='l1'>"
    "<fieldset>"
        "<legend><b>&nbsp; _TXT_CTRL_TITLE_ &nbsp;</b></legend>"
        "<p style='display: inline;'><b> _TXT_CTRL_TEMP_ </b>(<span id='tempScale'>&#176;_TEMP_SCALE_</span>)"
            "<br/>"
            "<button onclick='setTemp(0)' class='temp bgrn' style='text-align:center;width:30px;margin-left: 5px;margin-right: 2px;'>-</button>"
            "<form id='FTEMP_' style='display:inline'>"
                "<input name='TEMP' id='TEMP' type='text' value='_TEMP_' style='text-align:center;width:60px;margin-left: 5px;margin-right: 2px;' />"
            "</form>"
            "<button onclick='setTemp(1)' class='temp bgrn' style='text-align:center;width:30px;margin-left: 5px;margin-right: 2px;'>+</button>"
        "</p>"
        "<p>"
            "<b>_TXT_CTRL_POWER_</b>"
            "<form onchange='this.submit()' method='POST'>"
                "<select name='POWER'>"
                    "<option value='ON' _POWER_ON_>_TXT_F_ON_</option>"
                    "<option value='OFF' _POWER_OFF_>_TXT_F_OFF_</option>"
                "</select>"
            "</form>"
        "</p>"
        "<p><b>_TXT_CTRL_MODE_</b>"
            "<form onchange='this.submit()' method='POST'>"
                "<select name='MODE' id='MODE'>"
                    "<option value='AUTO' _MODE_A_>&#9851; _TXT_F_AUTO_</option>"
                    "<option value='DRY' _MODE_D_>&#128167; _TXT_F_DRY_</option>"
                    "<option value='COOL' _MODE_C_>&#10052;&#65039; _TXT_F_COOL_</option>"
                    "<option value='HEAT' _MODE_H_>&#9728;&#65039; _TXT_F_HEAT_</option>"
                    "<option value='FAN' _MODE_F_>&#10051; _TXT_F_FAN_</option>"
                "</select>"
            "</form>"
        "</p>"
        "<p><b>_TXT_CTRL_FAN_</b>"
            "<form onchange='this.submit()' method='POST'>"
                "<select name='FAN'>"
                    "<option value='AUTO' _FAN_A_>&#9851; _TXT_F_AUTO_</option>"
                    "<option value='QUIET' _FAN_Q_>.... _TXT_F_QUIET_</option>"
                    "<option value='1' _FAN_1_>...: _TXT_F_SPEED_ 1</option>"
                    "<option value='2' _FAN_2_>..:: _TXT_F_SPEED_ 2</option>"
                    "<option value='3' _FAN_3_>.::: _TXT_F_SPEED_ 3</option>"
                    "<option value='4' _FAN_4_>:::: _TXT_F_SPEED_ 4</option>"
                "</select>"
            "</form>"
        "</p>"
        "<p><b>_TXT_CTRL_VANE_</b>"
            "<form onchange='this.submit()' method='POST'>"
                "<select name='VANE'>"
                    "<option value='AUTO' _VANE_A_>&#9851; _TXT_F_AUTO_</option>"
                    "<option value='SWING' _VANE_S_>&#9887; _TXT_F_SWING_</option>"
                    "<option value='1' _VANE_1_>&#10143; _TXT_F_POS_ 1</option>"
                    "<option value='2' _VANE_2_>&#10143; _TXT_F_POS_ 2</option>"
                    "<option value='3' _VANE_3_>&#10143; _TXT_F_POS_ 3</option>"
                    "<option value='4' _VANE_4_>&#10143; _TXT_F_POS_ 4</option>"
                    "<option value='5' _VANE_5_>&#10143; _TXT_F_POS_ 5</option>"
                "</select>"
            "</form>"
        "</p>"
        "<p><b>_TXT_CTRL_WVANE_</b>"
            "<form onchange='this.submit()' method='POST'>"
                "<select name='WIDEVANE'>"
                    "<option value='SWING' _WVANE_S_>&#9887; _TXT_F_SWING_</option>"
                    "<option value='<<' _WVANE_1_><< _TXT_F_POS_ 1</option>"
                    "<option value='<' _WVANE_2_>< _TXT_F_POS_ 2</option>"
                    "<option value='|' _WVANE_3_>| _TXT_F_POS_ 3</option>"
                    "<option value='>' _WVANE_4_>> _TXT_F_POS_ 4</option>"
                    "<option value='>>' _WVANE_5_>>> _TXT_F_POS_ 5</option>"
                    "<option value='<>' _WVANE_6_><> _TXT_F_POS_ 6</option>"
                "</select>"
            "</form>"
        "</p>"
    "</fieldset>"
    "<p>"
        "<a class='button back' href='/'>_TXT_BACK_</a>"
    "</p>"
"</div>"
"<script>"
"const queryParams = (window.location.search.split('?')[1] || '')"
        ".split('&')"
        ".reduce((QS, current) => {"
            "const [key, value] = current.split('=');"
            "return Object.assign(QS, {[key]: value !== undefined ? value : ''});"
        "}, {});"

"function setTemp(b) {"
    "var t = document.getElementById('TEMP');"
    "if (b && t.value < _MAX_TEMP_) {"
        "t.value = Number(t.value) + _TEMP_STEP_;"
    "} else if (!b && t.value > _MIN_TEMP_) {"
        "t.value = Number(t.value) - _TEMP_STEP_;"
    "}"
    "document.getElementById('FTEMP_').submit();"
"}"

"if (queryParams['TEMP']) {"
    "document.getElementById('TEMP').value = queryParams['TEMP'];"
"}"

"if (!_HEAT_MODE_SUPPORT_) {"
    "var options = document.getElementById('MODE').options;"
    "options[3].disabled = (options[3].value == 'HEAT');"
"}"
"</script>"
;

const char html_page_unit[] PROGMEM =
"<div id='l1' name='l1'>"
    "<fieldset>"
        "<legend><b>&nbsp; _TXT_UNIT_TITLE_ &nbsp;</b></legend>"
        "<form method='post'>"
            "<p>"
                "<b>_TXT_UNIT_TEMP_</b>"
                "<select name='tu'>"
                    "<option value='cel' _TU_CEL_>_TXT_F_CELSIUS_</option>"
                    "<option value='fah' _TU_FAH_>_TXT_F_FH_</option>"
                "</select>"
            "</p>"
            "<p><b>_TXT_UNIT_MINTEMP_</b>"
                "<br/>"
                "<input type='number' id='min_temp' name='min_temp' placeholder=' ' value='_MIN_TEMP_'>"
            "</p>"
            "<p><b>_TXT_UNIT_MAXTEMP_</b>"
                "<br/>"
                "<input type='number' id='max_temp' name='max_temp' placeholder=' ' value='_MAX_TEMP_'>"
            "</p>"
            "<p><b>_TXT_UNIT_STEPTEMP_</b>"
                "<br/>"
                "<input type='number' id='temp_step' step='0.1' name='temp_step' placeholder=' ' value='_TEMP_STEP_'>"
            "</p>"
            "<p>"
                "<b>_TXT_UNIT_MODES_</b>"
                "<select name='md'>"
                    "<option value='all' _MD_ALL_>_TXT_F_ALLMODES_</option>"
                    "<option value='nht' _MD_NONHEAT_>_TXT_F_NOHEAT_</option>"
                "</select>"
            "</p>"
            "<p><b>_TXT_UNIT_PASSWORD_</b>"
                "<br/>"
                "<input id='lpw' name='lpw' type='password' placeholder=' ' value='_LOGIN_PASSWORD_'>"
            "</p>"
            "<br/>"
            "<button name='save' type='submit' class='button bgrn'>_TXT_SAVE_</button>"
        "</form>"
    "</fieldset>"
    "<p>"
        "<a class='button' href='/setup' class='back'>_TXT_BACK_</a>"
    "</p>"
"</div>"
;

const char html_page_login[] PROGMEM =
"<script>"
    "var loginSucess = _LOGIN_SUCCESS_;"
    "document.onreadystatechange = function() {"
        "if (document.readyState === 'complete') {"
            "if (loginSucess == 1) {"
                "var element = document.getElementById('login_form');"
                "element.parentNode.removeChild(element);"
            "}"
        "}"
    "}"
"</script>"
"<div id='login_form' name='login_form'>"
    "<fieldset>"
        "<legend><b>&nbsp; _TXT_LOGIN_TITLE_ &nbsp;</b></legend>"
        "<form action='/login' method='post'>"
            "<!--<p>To log in, enter user: <b>admin</b> and password</p>"
            "<p><b>User</b>-->"
                "<input type='hidden' name='USERNAME' placeholder='user name' value='admin'>"
            "</p>"
            "<p><b>_TXT_LOGIN_PASSWORD_</b>"
                "<input type='password' name='PASSWORD' placeholder='_TXT_LOGIN_PASSWORD_'>"
            "</p>"
            "<br/>"
            "<button name='SUBMIT' type='submit' class='button bgrn'>_TXT_LOGIN_</button>"
        "</form>"
        "<!-- <br> You can go to <a href='/status'>status page</a>-->"
        "<br>"
    "</fieldset>"
"</div>"
"<div>"
    "_LOGIN_MSG_"
"</div>"
;

const char html_page_upgrade[] PROGMEM =
"<script>"
    "function eb(s) {"
        "return document.getElementById(s);"
    "}"
"</script>"
    "<div id='f1' style='display:block;'>"
        "<fieldset>"
            "<legend><b>&nbsp; _TXT_UPGRADE_TITLE_ &nbsp;</b></legend>"
            "<form method='post' action='upload' enctype='multipart/form-data'>"
                "<p><span>_TXT_UPGRADE_INFO_</span></p>"
                "<p><span>_TXT_UPGRADE_BOARD_.bin</span></p>"
                "<br>"
                "<input type='file' accept='.bin' name='upload'>"
                "<br>"
                "<br>"
                "<button type='submit' onclick=\"eb('f1').style.display='none';eb('f2').style.display='block';this.form.submit();\" class='button bgrn'>_TXT_B_UPGRADE_</button>"
            "</form>"
        "</fieldset>"
        "<p>"
            "<a class='button back' href='/'>_TXT_BACK_</a>"
        "</p>"
    "</div>"
    "<div id='f2' style='display:none;text-align:center;'><b>_TXT_UPGRADE_START_ ...</b></div>"
;


const char html_page_upload[] PROGMEM =
"<div id='l1' name='l1'>"
    "<br>_UPLOAD_MSG_"
    "<p>"
        "<a class='button back' href='/upgrade'>_TXT_BACK_</a>"
    "</p>"
"</div>"
;
