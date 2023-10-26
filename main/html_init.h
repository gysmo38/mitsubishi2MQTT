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
 
const char html_init_setup[] PROGMEM = R"====(
<div id='l1' name='l1'></div>
<fieldset>
    <legend><b>&nbsp; _TXT_INIT_TITLE_ &nbsp;</b></legend>
    <form method='post' action='save'>
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
        <button name='submit' type='submit' class='button bgrn'> _TXT_SAVE_ </button>
    </form>
</fieldset>
<fieldset>
    <a class="button" href="/reboot" class="back"> _TXT_REBOOT_ </a>
</fieldset>
)====";

const char html_init_save[] PROGMEM =  R"====(
<p> _TXT_INIT_REBOOT_MESS_ </p>
)====";

const char html_init_reboot[] PROGMEM =  R"====(
<p> _TXT_INIT_REBOOT_ </p>
)====";
