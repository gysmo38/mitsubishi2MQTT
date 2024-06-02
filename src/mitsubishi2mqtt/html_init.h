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
 
const char html_init_setup[] PROGMEM = R"====(
<script>
function check(){
    var friendlyName = document.getElementById('fn').value;
    if(/^[a-zA-Z0-9_-]+$/.test(friendlyName)){
        document.getElementById("text_invalid_name").style.display = "none";
        document.initForm.submit();
       return true;
    }
    console.log('Invalid mqtt parameters');
    alert('Invalid MQTT friendly name. Alphabet(a-z), Underscore(_), or Dash (-) only.');
    document.getElementById("text_invalid_name").style.display = "block";
    return false;
}
</script>
<div id='l1' name='l1'></div>
<fieldset>
    <legend><b>&nbsp; _TXT_INIT_TITLE_ &nbsp;</b> </legend>

    <form method='post' action='save' name='initForm'>
        <p><b>_TXT_INIT_HOST_</b>
            <br/>
            <input id='hn' name='hn' placeholder=' ' value='_UNIT_NAME_'>
        </p>
        <p><b>_TXT_INIT_SSID_</b> ()
            <br/>
            <input id='ssid' name='ssid' placeholder=' '>
        </p>
        <p><b>_TXT_INIT_PSK_</b> ()
            <br/>
            <input id='psk' name='psk' placeholder=' '>
        </p>
        <p><b>_TXT_INIT_OTA_</b>
            <br/>
            <input id='otapwd' name='otapwd' placeholder=' '>
        </p>
        </p>
        <br/>
</fieldset>

<br>
<fieldset>
    <legend><b>&nbsp; _TXT_MQTT_TITLE_ &nbsp;</b></legend>

    <b>_TXT_MQTT_FN_</b>
            <br/>
            <input id='fn' name='fn' 
            autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false' 
            placeholder=' ' value='_MQTT_FN_'>
        </p>
        <p id="text_invalid_name" style="color:red; display:none;">Invalid Name!</p>
        <p><b>_TXT_MQTT_HOST_</b>
            <br/>
            <input id='mh' name='mh' 
            autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false' 
            placeholder='192.168.x.xxx' value='_MQTT_HOST_'>
        </p>
        <p><b>_TXT_MQTT_PORT_</b>
            <br/>
            <input id='ml' name='ml' type='numeric' placeholder='1883' value='_MQTT_PORT_'>
        </p>
        <p><b>_TXT_MQTT_USER_</b>
            <br/>
            <input id='mu' name='mu' 
            autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false' 
            placeholder='username' value='_MQTT_USER_'>
        </p>
        <p><b>_TXT_MQTT_PASSWORD_</b>
            <br/>
            <input id='mp' name='mp' type='password' placeholder='password' value='_MQTT_PASSWORD_'>
        </p>
        <p><b>_TXT_MQTT_TOPIC_</b>
            <br/>
            <input id='mt' name='mt' 
            autocomplete='off' autocorrect='off' autocapitalize='off' spellcheck='false' 
            placeholder='topic' value='_MQTT_TOPIC_'>
        </p>

    </form>
</fieldset>
<fieldset>
    <button name='submit'  onclick='check()' class='button bgrn'> _TXT_SAVE_ </button>
    <!-- <a class="button" href="/reboot" class="back"> _TXT_REBOOT_ </a> -->
</fieldset>
)====";

const char html_init_save[] PROGMEM =  R"====(
<p> _TXT_INIT_REBOOT_MESS_ </p>
)====";

const char html_init_reboot[] PROGMEM =  R"====(
<p> _TXT_INIT_REBOOT_ </p>
)====";
