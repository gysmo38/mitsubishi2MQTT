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

const char count_down_script[] PROGMEM = 
"<script>"
    "var count = 30;"
    "(function countDown() {"
        "document.getElementById('count').innerHTML = count + 's';"
        "setTimeout(function() {"
            "if(count > 0) {"
                "count --;"
                "return countDown();"
            "} else {"
                "window.location.href = '/';"
            "}"
        "}, 1000);"
    "})();"
"</script>"
;
const char count_down_script_init[] PROGMEM = 
"<script>"
    "var count = 30;"
    "(function countDown() {"
        "document.getElementById('count').innerHTML = count + 's';"
        "setTimeout(function() {"
            "if(count > 0) {"
                "count --;"
                "return countDown();"
            "} else {"
                "window.location.href = 'http://_HOST_NAME_/status';"
            "}"
        "}, 1000);"
    "})();"
"</script>"
;


const char fw_check_script_events[] PROGMEM = 
"<script>"
"if (!!window.EventSource) {"
 "var source = new EventSource('/events');"
 "source.addEventListener('open', function(e) {"
  "console.log('Events Connected');"
 "}, false);"
 "source.addEventListener('error', function(e) {"
  "if (e.target.readyState != EventSource.OPEN) {"
    "console.log('Events Disconnected');"
  "}"
 "}, false);"
 "source.addEventListener('message', function(e) {"
  "console.log('message', e.data);"
 "}, false);"
 "source.addEventListener('fw_check_status', function(e) {"
  "console.log('fw_check_status', e.data);"
  "document.getElementById('status').innerHTML = e.data;"
 "}, false);"
 "source.addEventListener('wifiOptions', function(e) {"
  "console.log('wifiOptions', e.data);"
  "document.getElementById('network').innerHTML = e.data;"
 "}, false);"
 "source.addEventListener('fw_check_reboot', function(e) {"
  "console.log('fw_check_status', e.data);"
  "document.getElementById('status').innerHTML = e.data;"
  "var count = 20;"
  "(function countDown() {"
        "document.getElementById('count').innerHTML = count + 's';"
        "setTimeout(function() {"
            "if(count > 0) {"
                "count --;"
                "return countDown();"
            "} else {"
                "window.location.href = '/status';"
            "}"
        "}, 1000);"
    "})();"
 "}, false);"
"}"
"</script>";

const char unit_script_ws[] PROGMEM = 
"<script>"
    "var websocket;"
    "function initWebSocket() {"
      "console.log('Trying to open a WebSocket connection...');"
      "var gateway = 'ws://${window.location.hostname}/ws';"
      "websocket = new WebSocket(\"ws://\" + location.host + \"/ws\");"
      "websocket.onopen    = onOpen;"
      "websocket.onclose   = onClose;"
      "websocket.onmessage = onMessage;"
    "}"

    "function onOpen(event) {"
      "console.log('Connection opened');"
    "}"

    "function onClose(event) {"
      "console.log('Connection closed');"
      "setTimeout(initWebSocket, 4000);"
    "}"

    "function onMessage(event) {"
      "console.log('onMessage: ' + event.data);"
      "if (event.data == 'REFRESH'){"
        "location.reload();"
      "}"
    "}"
    "window.addEventListener('load', onLoad);"

    "function onLoad(event) {"
      "initWebSocket();"
    "}"

    "function sendLanguage(obj){"
      "var lang_index = document.getElementById('language').value;"
      "console.log('send language: ' + lang_index);"
      "websocket.send('language;'+lang_index);"
    "}"
    
    "function matchPassword() {"  
      "var pw1 = document.getElementById('lpw').value;"  
      "var pw2 = document.getElementById('lpwc').value;"  
      "if(pw1 != pw2)"  
      "{"   
        "document.getElementById('message_not_match').innerHTML = '_TXT_UNIT_PASSWORD_NOT_MATCH_';"
        "return false;" 
      "}"
      "document.getElementById('message_not_match').innerHTML = '';"
      "return true;"
    "}"  
"</script>";

const char control_script_events[] PROGMEM = 
    "<script>"
        "function $_GET(param) {"
            "var vars = {};"
            "window.location.href.replace(location.hash, '').replace("
                "/[?&]+([^=&]+)=?([^&]*)?/gi, /*regexp*/"
                "function(m, key, value) { /*callback*/"
                    "vars[key] = value !== undefined ? value : '';"
                "}"
            ");"
 
            "if (param) {"
                "return vars[param] ? vars[param] : null;"
            "}"
            "return vars;"
        "};"

        "function setTemp(b) {"
            "var t = document.getElementById('TEMP');"
            "if (b && t.value < _MAX_TEMP_) {"
                "t.value = Number(t.value) + _TEMP_STEP_;"
            "} else if (!b && t.value > _MIN_TEMP_) {"
                "t.value = Number(t.value) - _TEMP_STEP_;"
            "}"
            "document.getElementById('FTEMP_').submit();"
        "}"
 
        "window.onload = function() {"
         "if ($_GET('TEMP')) {"
          "document.getElementById('TEMP').value = $_GET('TEMP');"
         "}"
        "};"
 
        "document.onreadystatechange = function() {"
         "if (document.readyState === 'complete') {"
          "if (_HEAT_MODE_SUPPORT_ == 0) {"
           "var options = document.getElementById('MODE').options;"
           "options[3].hide = (options[3].value == 'HEAT');"
          "}"
          "/*web event*/"
          "if (!!window.EventSource) {"
           "var source = new EventSource('/events');"
 
           "source.addEventListener('open', function(e) {"
            "console.log('Events Connected');"
           "}, false);"
           "source.addEventListener('error', function(e) {"
            "if (e.target.readyState != EventSource.OPEN) {"
             "console.log('Events Disconnected');"
            "}"
           "}, false);"
 
           "source.addEventListener('message', function(e) {"
            "console.log('message', e.data);"
           "}, false);"
 
           "source.addEventListener('temperature', function(e) {"
            "console.log('temperature', e.data);"
            "document.getElementById('TEMP').value = e.data;"
           "}, false);"
 
           "source.addEventListener('room_temperature', function(e) {"
            "console.log('Room temperature', e.data);"
            "document.getElementById('room_temperature').innerHTML = e.data;"
           "}, false);"
 
            "source.addEventListener('preset', function(e) {"
            "console.log('Preset', e.data);"
            "document.getElementById('PRESET').value = e.data;"
           "}, false);"

            "source.addEventListener('power', function(e) {"
            "console.log('POWER', e.data);"
            "document.getElementById('POWER').checked = (e.data == 'ON' ? true: false);"
           "}, false);"

            "source.addEventListener('mode', function(e) {"
            "console.log('Mode', e.data);"
            "document.getElementById('MODE').value = e.data;"
           "}, false);"
 
            "source.addEventListener('fan', function(e) {"
            "console.log('Fan', e.data);"
            "document.getElementById('FAN').value = e.data;"
           "}, false);"

           "source.addEventListener('vane', function(e) {"
            "console.log('Vane', e.data);"
            "document.getElementById('VANE').value = e.data;"
           "}, false);"

            "source.addEventListener('wideVane', function(e) {"
            "console.log('Wide vane', e.data);"
            "document.getElementById('WIDEVANE').value = e.data;"
           "}, false);"
          "}"
         "}"
        "}"
 
    "</script>";
