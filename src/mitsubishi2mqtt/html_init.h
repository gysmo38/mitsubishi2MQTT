const char html_init_setup[] PROGMEM = R"====(
<body>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
        </div>
        <div id='l1' name='l1'></div>
        <fieldset>
            <legend><b>&nbsp;Initial setup&nbsp;</b></legend>
            <form method='get' action='save'>
                <p><b>Hostname</b>
                    <br/>
                    <input id='hn' name='hn' placeholder=' ' value='_UNIT_NAME_'>
                </p>
                <p><b>SSID</b> ()
                    <br/>
                    <input id='ssid' name='ssid' placeholder=' '>
                </p>
                <p><b>PSK</b> ()
                    <br/>
                    <input id='psk' name='psk' placeholder=' '>
                </p>
                <p><b>OTA Password</b>
                    <br/>
                    <input id='otapwd' name='otapwd' placeholder=' '>
                </p>
                </p>
                <br/>
                <button name='submit' type='submit' class='button bgrn'>Save & Reboot</button>
            </form>
        </fieldset>
        <fieldset>
            <form method='get' action='reboot'>
                <br/>
                <button name='reboot' type='submit' class='button bgrn'>Reboot</button>
            </form>
        </fieldset>
)====";

const char html_init_save[] PROGMEM =  R"====(
<body>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
        </div>
        <p>Rebooting and connecting to your WiFi network! You should see it listed in on your access point.</p>
)====";

const char html_init_reboot[] PROGMEM =  R"====(
<body>
    <div style='text-align:left;display:inline-block;min-width:340px;'>
        <div style='text-align:center;'>
            <noscript>To user Mitsubishi2MQTT, you need to activate Javascript
                <br/>
            </noscript>
            <h3>_UNIT_NAME_</h3>
        </div>
        <p>Rebooting</p>
)====";
