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
 
const char html_page_reboot[] PROGMEM = R"====(
<body>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
        </div>
        <p>Rebooting... Refresh in 10s... <span id='count'>10s</span>...</p>
        <script>
            var count = 10;
            (function countDown() {
                document.getElementById('count').innerHTML = count + 's';
                setTimeout(function() {
                    if(count > 0) {
                        count --;
                        return countDown();
                    } else {
                        window.location.href = '/';
                    }
                }, 1000);
            })();
        </script>
    </div>
)====";

const char html_page_reset[] PROGMEM = R"====(
<body>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
        </div>
        <p>Resetting... Connect to SSID HVAC_XXXX...</p>
    </div>
)====";


const char html_page_save_reboot[] PROGMEM = R"====(
<body>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
        </div>
        <p>Saving configuration and rebooting... Refresh in <span id='count'>10s</span>...</p>
        <script>
            var count = 10;
            (function countDown() {
                document.getElementById('count').innerHTML = count + 's';
                setTimeout(function() {
                    if(count > 0) {
                        count --;
                        return countDown();
                    } else {
                        window.location.href = '/';
                    }
                }, 1000);
            })();
        </script>
    </div>
)====";

const char html_page_mqtt[] PROGMEM = R"====(
<body>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
            <h2>Config</h2>
        </div>
        <div id='l1' name='l1'>
            <fieldset>
                <legend><b>&nbsp;MQTT Parameters&nbsp;</b></legend>
                <form method='post'>
                    <p><b>Friendly name</b>
                        <br/>
                        <input id='fn' name='fn' placeholder=' ' value='_UNIT_NAME_'>
                    </p>
                    <p><b>Host</b> ()
                        <br/>
                        <input id='mh' name='mh' placeholder=' ' value='_MQTT_HOST_'>
                    </p>
                    <p><b>Port</b> (default 1883)
                        <br/>
                        <input id='ml' name='ml' placeholder='1883' value='_MQTT_PORT_'>
                    </p>
                    <p><b>User</b>
                        <br/>
                        <input id='mu' name='mu' placeholder='DVES_USER' value='_MQTT_USER_'>
                    </p>
                    <p><b>Password</b>
                        <br/>
                        <input id='mp' name='mp' type='password' placeholder='Password' value='_MQTT_PASSWORD_'>
                    </p>
                    <p><b>Topic</b>
                        <br/>
                        <input id='mt' name='mt' placeholder='topic' value='_MQTT_TOPIC_'>
                    </p>
                    <br/>
                    <button name='save' type='submit' class='button bgrn'>Save & Reboot</button>
                </form>
            </fieldset>
            <p>
                <a class="button" href="/setup" class="back">Back</a>
            </p>
        </div>
    </div>
)====";

const char html_page_others[] PROGMEM = R"====(
<body>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
            <h2>Config</h2>
        </div>
        <div id='l1' name='l1'>
            <fieldset>
                <legend><b>&nbsp;Others Parameters&nbsp;</b></legend>
                <form method='post'>
                    <p><b>HA Autodiscovery</b>
                        <select name="HAA">
                            <option value="ON" _HAA_ON_>ON</option>
                            <option value="OFF" _HAA_OFF_>OFF</option>
                        </select>
                    </p>
                    <p><b>Home Assistant Autodiscovery topic</b> ()
                        <br/>
                        <input id='haat' name='haat' placeholder=' ' value='_HAA_TOPIC_'>
                    </p>
                    <p><b>Debug</b>
                        <select name="Debug">
                            <option value="ON" _DEBUG_ON_>ON</option>
                            <option value="OFF" _DEBUG_OFF_>OFF</option>
                        </select>
                    </p>
                    <br/>
                    <button name='save' type='submit' class='button bgrn'>Save & Reboot</button>
                </form>
            </fieldset>
            <p>
                <a class="button" href="/setup" class="back">Back</a>
            </p>
        </div>
    </div>
)====";

const char html_page_status[] PROGMEM = R"====(
<body>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
            <h2>Status</h2>
        </div>
        <div id='l1' name='l1'>
            HVAC Status => _HVAC_STATUS_
            <br /> MQTT Status => _MQTT_STATUS_ ( _MQTT_REASON_ )
            <br /> WIFI Rssi => _WIFI_STATUS_ dBm
            <br />
            <p>
                <a class="button" href="/" class="back">Back</a>
            </p>
        </div>
    </div>
)====";

const char html_page_wifi[] PROGMEM = R"====(
<body>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
        </div>
        <div id='l1' name='l1'>
            <fieldset>
                <legend><b>&nbsp;WIFI Parameters&nbsp;</b></legend>
                <form method='post'>
                    <p><b>Hostname</b>
                        <br/>
                        <input id='hn' name='hn' placeholder=' ' value='_UNIT_NAME_'>
                    </p>
                    <p><b>SSID</b> ()
                        <br/>
                        <input id='ssid' name='ssid' placeholder=' ' value='_SSID_'>
                    </p>
                    <p><b>Password</b> ()
                        <br/>
                        <input id='psk' name='psk' placeholder=' ' value='_PSK_'>
                    </p>
                    <p><b>OTA Password</b>
                        <br/>
                        <input id='otapwd' name='otapwd' placeholder=' ' value='_OTA_PWD_'>
                    </p>
                    <br/>
                    <button name='save' type='submit' class='button bgrn'>Save & Reboot</button>
                </form>
            </fieldset>
            <p>
                <a class="button" href="/setup" class="back">Back</a>
            </p>
        </div>
    </div>
)====";


const char html_page_control[] PROGMEM = R"====(
<body>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
            <h2>Current temp _ROOMTEMP_&#176;</h2>
        </div>
        <div id='l1' name='l1'>
            <fieldset>
                <legend><b>&nbsp;Control Unit&nbsp;</b></legend>
                <p style="display: inline;"><b>Temp</b>(<span id="tempScale">&#176;_TEMP_SCALE_</span>)
                    <br/>
                    <button onclick="setTemp(0)" class='temp bgrn' style="text-align:center;width:30px;margin-left: 5px;margin-right: 2px;">-</button>
                    <form id="FTEMP_" style="display:inline">
                        <input name="TEMP" id="TEMP" type="text" value="_TEMP_" style="text-align:center;width:60px;margin-left: 5px;margin-right: 2px;" />
                    </form>
                    <button onclick="setTemp(1)" class='temp bgrn' style="text-align:center;width:30px;margin-left: 5px;margin-right: 2px;">+</button>
                </p>
                <p>
                    <b>Power</b>
                    <form onchange="this.submit()">
                        <select name="POWER">
                            <option value="ON" _POWER_ON_>ON</option>
                            <option _POWER_OFF_>OFF</option>
                        </select>
                    </form>
                </p>
                <p><b>Mode</b>
                    <form onchange="this.submit()">
                        <select name="MODE" id="MODE">
                            <option value="AUTO" _MODE_A_>&#9851; AUTO</option>
                            <option value="DRY" _MODE_D_>&#128167; DRY</option>
                            <option value="COOL" _MODE_C_>&#10052;&#65039; COOL</option>
                            <option value="HEAT" _MODE_H_>&#9728;&#65039; HEAT</option>
                            <option value="FAN" _MODE_F_>&#10051; FAN</option>
                        </select>
                    </form>
                </p>
                <p><b>Fan</b>
                    <form onchange="this.submit()">
                        <select name="FAN">
                            <option value="AUTO" _FAN_A_>&#9851; AUTO</option>
                            <option value="QUIET" _FAN_QUIET_>.... QUIET</option>
                            <option value="1" _FAN_1_>...: SPEED 1</option>
                            <option value="2" _FAN_2_>..:: SPEED 2</option>
                            <option value="3" _FAN_3_>.::: SPEED 3</option>
                            <option value="4" _FAN_4_>:::: SPEED 4</option>
                        </select>
                    </form>
                </p>
                <p><b>Vane</b>
                    <form onchange="this.submit()">
                        <select name="VANE">
                            <option value="AUTO" _VANE_A_>&#9851; AUTO</option>
                            <option value="SWING" _VANE_S_>&#9887; SWING</option>
                            <option value="1" _VANE_1_>&#10143; POS 1</option>
                            <option value="2" _VANE_2_>&#10143; POS 2</option>
                            <option value="3" _VANE_3_>&#10143; POS 3</option>
                            <option value="4" _VANE_4_>&#10143; POS 4</option>
                            <option value="5" _VANE_5_>&#10143; POS 5</option>
                        </select>
                    </form>
                </p>
                <p><b>Wide Vane</b>
                    <form onchange="this.submit()">
                        <select name="WIDEVANE">
                            <option value="AUTO" _WVANE_A_>&#9851; AUTO</option>
                            <option value="SWING" _WVANE_S_>&#9887; SWING</option>
                            <option value="<<" _WVANE_1_><< POS 1</option>
                            <option value="<" _WVANE_2_>< POS 2</option>
                            <option value="|" _WVANE_3_>| POS 3</option>
                            <option value=">" _WVANE_4_>> POS 4</option>
                            <option value=">>" _WVANE_5_>>> POS 5</option>
                            <option value="<>" _WVANE_6_><> POS 6</option>
                        </select>
                    </form>
                </p>
            </fieldset>
            <p>
                <a class="button" href="/" class="back">Back</a>
            </p>
        </div>
    </div>
    <script>
        const queryParams = (window.location.search.split('?')[1] || '')
                .split('&')
                .reduce((QS, current) => {
                    const [key, value] = current.split('=');
                    return Object.assign(QS, {[key]: value !== undefined ? value : ''});
                }, {});

        function setTemp(b) {
            var t = document.getElementById('TEMP');
            if (b && t.value < _MAX_TEMP_) {
                t.value = Number(t.value) + _TEMP_STEP_;
            } else if (!b && t.value > _MIN_TEMP_) {
                t.value = Number(t.value) - _TEMP_STEP_;
            }
            document.getElementById("FTEMP_").submit();
        }

        if (queryParams['TEMP']) {
            document.getElementById('TEMP').value = queryParams['TEMP'];
        }

        if (!_HEAT_MODE_SUPPORT_) {
            var options = document.getElementById("MODE").options;
            options[3].disabled = (options[3].value == "HEAT");
        }
    </script>
)====";

const char html_page_advance[] PROGMEM = R"====(
<body>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
        </div>
        <div id='l1' name='l1'>
            <fieldset>
                <legend><b>&nbsp;Advance configuration&nbsp;</b></legend>
                <form method='post'>
                    <p>
                        <b>Temperature Unit</b>
                        <select name="tu">
                            <option value="cel" _TU_CEL_>Celsius</option>
                            <option value="fah" _TU_FAH_>Fahrenheit</option>
                        </select>
                    </p>
                    <p><b>Ninimum temperture</b>
                        <br/>
                        <input type='number' id='min_temp' name='min_temp' placeholder=' ' value='_MIN_TEMP_'>
                    </p>
                    <p><b>Maximum temperture</b>
                        <br/>
                        <input type='number' id='max_temp' name='max_temp' placeholder=' ' value='_MAX_TEMP_'>
                    </p>
                    <p><b>Temperture step</b>
                        <br/>
                        <input type='number' id='temp_step' step="0.1" name='temp_step' placeholder=' ' value='_TEMP_STEP_'>
                    </p>
                    <p>
                        <b>Mode Support</b>
                        <select name="md">
                            <option value="all" _MD_ALL_>All mode</option>
                            <option value="nht" _MD_NONHEAT_>Not support heat mode</option>
                        </select>
                    </p>
                    <p><b>Login Password</b>
                        <br/>
                        <input id='lpw' name='lpw' type='password' placeholder=' ' value='_LOGIN_PASSWORD_'>
                    </p>
                    <p>Note: Default login user is <b>admin</b></p>
                    <br/>
                    <button name='save' type='submit' class='button bgrn'>Save & Reboot</button>
                </form>
            </fieldset>
            <p>
                <a class="button" href="/setup" class="back">Back</a>
            </p>
        </div>
    </div>
)====";

const char html_page_login[] PROGMEM = R"====(
<body>
    <script>
        var loginSucess = _LOGIN_SUCCESS_;
        document.onreadystatechange = function() {
            if (document.readyState === "complete") {
                if (loginSucess == 1) {
                    var element = document.getElementById("login_form");
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
        <div id='login_form' name='login_form'>
            <fieldset>
                <legend><b>&nbsp;LOGIN&nbsp;</b></legend>
                <form action='/login' method='post'>
                    <p>To log in, enter user: <b>admin</b> and password</p>
                    <p><b>User</b>
                        <input type='text' name='USERNAME' placeholder='user name'>
                    </p>
                    <p><b>Password</b>
                        <input type='password' name='PASSWORD' placeholder='password'>
                    </p>
                    <br/>
                    <button name='SUBMIT' type='submit' class='button bgrn'>SUBMIT</button>
                </form>
                <br> You can go to <a href='/status'>status page</a>
                <br>
            </fieldset>
        </div>
        <div
        _LOGIN_MSG_
        </div>
    </div>
)====";

const char html_page_upgrade[] PROGMEM = R"====(
<body>
    <script>
        function eb(s) {
            return document.getElementById(s);
        }
    </script>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
        </div>
        <div id="f1" style="display:block;">
            <fieldset>
                <legend><b>&nbsp;Firmware OTA upgrade by bin file upload&nbsp;</b></legend>
                <form method='post' action='upload' enctype='multipart/form-data'>
                    <br>
                    <input type='file' accept='.bin' name='upload'>
                    <br>
                    <br>
                    <button type='submit' onclick='eb("f1").style.display="none";eb("f2").style.display="block";this.form.submit();' class='button bgrn'>Start upgrade</button>
                </form>
            </fieldset>
            <p>
                <a class="button" href="/" class="back">Back</a>
            </p>
        </div>
        <div id='f2' style='display:none;text-align:center;'><b>Upload started ...</b></div>
    </div>
)====";


const char html_page_upload[] PROGMEM = R"====(
<body>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
        </div>
        <div id='l1' name='l1'>
            <br>_UPLOAD_MSG_
            <p>
                <a class="button" href="/upgrade" class="back">Back</a>
            </p>
        </div>
    </div>
)====";
