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
