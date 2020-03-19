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
 
const char html_menu_root[] PROGMEM = R"====(
<body>
    <script>
        var showLogout = _SHOW_LOGOUT_;
        var showControl = _SHOW_CONTROL_;
        document.onreadystatechange = function() {
            if (document.readyState === "complete") {
                if (showLogout == 0) {
                    var element = document.getElementById("logout");
                    element.parentNode.removeChild(element);
                }
                if (showControl == 0) {
                    var element = document.getElementById("control");
                    element.parentNode.removeChild(element);
                }
            }
        }
    </script>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
        </div>
        <div id="control">
            <form action='/control' method='get'>
                <button>Control</button>
            </form>
        </div>
        <div>
            <form action='/setup' method='get'>
                <button>Setup</button>
            </form>
        </div>
        <div>
            <form action='/status' method='get'>
                <button>Status</button>
            </form>
        </div>
        <div>
            <form action='/upgrade' method='get'>
                <button>Firmware Upgrade</button>
            </form>
        </div>
        <div>
            <form>
                <button type='submit' name='REBOOT' class='button bred'>Reboot</button>
            </form>
        </div>
        <div id="logout">
            <form action='/login?LOGOUT=YES' method='post'>
                <button type='submit' name='Logout' class='button bred'>Logout</button>
            </form>
        </div>
)====";


const char html_menu_setup[] PROGMEM = R"====(
<body>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
        </div>
        <p>
            <form action='/mqtt' method='get'>
                <button>MQTT</button>
            </form>
        </p>
        <p>
            <form action='/wifi' method='get'>
                <button>WIFI</button>
            </form>
        </p>
        <p>
            <form action='/advance' method='get'>
                <button>ADVANCE</button>
            </form>
        </p>
        <p>
            <form>
                <button type='submit' name='RESET' class='button bred'>Reset configuration</button>
            </form>
        </p>
        <p>
            <form action='/' method='get'>
                <button>Back</button>
            </form>
        </p>
)====";
