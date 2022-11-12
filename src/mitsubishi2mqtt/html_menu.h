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

const char html_menu_root[] PROGMEM = R"====(
<div id="control" style="display:none">
    <form action='/control' method='get'>
        <button>_TXT_CONTROL_</button>
    </form>
</div>
<div>
    <form action='/setup' method='get'>
        <button>_TXT_SETUP_</button>
    </form>
</div>
<div>
    <form action='/status' method='get'>
        <button>_TXT_STATUS_</button>
    </form>
</div>
<div>
    <form action='/upgrade' method='get'>
        <button>_TXT_FW_UPGRADE_</button>
    </form>
</div>
<div>
    <form>
        <button type='submit' name='REBOOT' class='button bred'>_TXT_REBOOT_</button>
    </form>
</div>
<div id="logout" style="display:none">
    <form action='/login?LOGOUT=YES' method='post'>
        <button type='submit' name='Logout' class='button bred'>_TXT_LOGOUT_</button>
    </form>
</div>
<script>
    if (_SHOW_LOGOUT_) {
        document.getElementById("logout").style.display = "";
    }
    if (_SHOW_CONTROL_) {
        document.getElementById("control").style.display = "";
    }
</script>
)====";


const char html_menu_setup[] PROGMEM = R"====(
<p>
    <form action='/mqtt' method='get'>
        <button>_TXT_MQTT_</button>
    </form>
</p>
<p>
    <form action='/wifi' method='get'>
        <button>_TXT_WIFI_</button>
    </form>
</p>
<p>
    <form action='/unit' method='get'>
        <button>_TXT_UNIT_</button>
    </form>
</p>
<p>
    <form action='/others' method='get'>
        <button>_TXT_OTHERS_</button>
    </form>
</p>
<p>
    <form onsubmit="return confirm(' _TXT_RESETCONFIRM_ ');">
        <button type='submit' name='RESET' class='button bred'>_TXT_RESET_</button>
    </form>
</p>
<p>
    <form action='/' method='get'>
        <button>_TXT_BACK_</button>
    </form>
</p>
)====";
