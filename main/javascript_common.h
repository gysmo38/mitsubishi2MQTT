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
