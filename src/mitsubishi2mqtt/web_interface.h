String html_header = R"====(
    <html lang="fr" class="">
    <head><meta charset='utf-8'>
    <meta name="viewport" content="width=device-width,initial-scale=1,user-scalable=no"/>
    <title>Mitsubishi2MQTT - _UNIT_NAME_</title>
    <style>
    div,fieldset,input,select{padding:5px;font-size:1em;}
    fieldset{background-color:#f2f2f2;}
    p{margin:0.5em 0;}
    input{width:100%;box-sizing:border-box;-webkit-box-sizing:border-box;-moz-box-sizing:border-box;}
    input[type=checkbox],input[type=radio]{width:1em;margin-right:6px;vertical-align:-1px;}
    select{width:100%;}
    textarea{resize:none;width:98%;height:318px;padding:5px;overflow:auto;}
    body{text-align:center;font-family:verdana;}
    td{padding:0px;}button{text-shadow: 2px 2px 5px black;box-shadow: 0 15px 6px -6px grey;border:0;border-radius:25px;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;-webkit-transition-duration:0.4s;transition-duration:0.8s;cursor:pointer;}button:hover{background-color:#0e70a4;}.bred{background-color:#d43535;}.bred:hover{background-color:#931f1f;}.bgrn{background-color:#47c266;}.bgrn:hover{background-color:#5aaf6f;}a{text-decoration:none;}.p{float:left;text-align:left;}.q{float:right;text-align:right;}
  </style>
  </head>
)====";

String html_footer = R"====(
  <br/>
    <div style='text-align:right;font-size:10px;color: grey;'>
      <hr/>Mitsubishi2MQTT _VERSION_ by Gysmo</div></div></body></html>
)====";


String html_init_save =  R"====(
  <body>
  <div style='text-align:left;display:inline-block;min-width:340px;'>
    <div style='text-align:center;'>
      <noscript>To user Mitsubishi2MQTT, you need to activate Javascript<br/></noscript>
      <h3>_UNIT_NAME_</h3>
    </div>

  <p>Rebooting and connecting to your WiFi network! You should see it listed in on your access point.</p>

)====";

String html_root = R"====(
  <body>
  <div style='text-align:left;display:inline-block;min-width:340px;'>
    <div style='text-align:center;'>
      <noscript>To user Mitsubishi2MQTT, you need to activate Javascript<br/></noscript>
      <h3>_UNIT_NAME_</h3>
    </div>

  <p><form action='/control' method='get'><button>Control</button></form></p>
  <p><form action='/setup' method='get'><button>Setup</button></form></p>
  <p><form><button type='submit' name='REBOOT' class='button bred'>Reboot</button></form></p>
)====";


String html_setup = R"====(
  <body>
  <div style='text-align:left;display:inline-block;min-width:340px;'>
    <div style='text-align:center;'>
      <noscript>To user Mitsubishi2MQTT, you need to activate Javascript<br/></noscript>
      <h3>_UNIT_NAME_</h3>
    </div>
  <p><form action='/mqtt' method='get'><button>MQTT</button></form></p>
  <p><form action='/wifi' method='get'><button>WIFI</button></form></p>
  <p><form><button type='submit' name='RESET' class='button bred'>Reset configuration</button></form></p>
  <p><form action='/' method='get'><button>Back</button></form></p>
)====";

String html_reboot = R"====(
  <body>
  <div style='text-align:left;display:inline-block;min-width:340px;'>
    <div style='text-align:center;'>
      <noscript>To user Mitsubishi2MQTT, you need to activate Javascript<br/></noscript>
      <h3>_UNIT_NAME_</h3>
    </div>

  <p>Rebooting... Refresh in 10s...</p>
  <script>
  setTimeout(function () {
   window.location.href= '/';
  }, 10000);
</script>
)====";

String html_reset = R"====(
  <body>
  <div style='text-align:left;display:inline-block;min-width:340px;'>
    <div style='text-align:center;'>
      <noscript>To user Mitsubishi2MQTT, you need to activate Javascript<br/></noscript>
      <h3>_UNIT_NAME_</h3>
    </div>

  <p>Resetting... Connect to SSID HVAC_XXXX...</p>

)====";


String html_save_reboot = R"====(
  <body>
  <div style='text-align:left;display:inline-block;min-width:340px;'>
    <div style='text-align:center;'>
      <noscript>To user Mitsubishi2MQTT, you need to activate Javascript<br/></noscript>
      <h3>_UNIT_NAME_</h3>
    </div>

  <p>Saving configuration and rebooting... Refresh in 10s...</p>
  <script>
  setTimeout(function () {
   window.location.href= '/';
  }, 10000);
</script>

)====";

String html_mqtt = R"====(<!DOCTYPE html>
  <body>
  <div style='text-align:left;display:inline-block;min-width:340px;'>
    <div style='text-align:center;'>
      <noscript>To user Mitsubishi2MQTT, you need to activate Javascript<br/></noscript>
      <h3>_UNIT_NAME_</h3>
      <h2>Config</h2>
    </div>
    <div id='l1' name='l1'></div>
      <fieldset>
    <legend><b>&nbsp;MQTT Parameters&nbsp;</b></legend>
    <form method='get'>
      <p><b>Friendly name</b><br/><input id='fn' name='fn' placeholder=' ' value='_UNIT_NAME_'></p>
      <p><b>Host</b> ()<br/><input id='mh' name='mh' placeholder=' ' value='_MQTT_HOST_'></p>
      <p><b>Port</b> (1883)<br/><input id='ml' name='ml' placeholder='1883' value='_MQTT_PORT_'></p>
      <p><b>User</b> <br/><input id='mu' name='mu' placeholder='DVES_USER' value='_MQTT_USER_'></p>
      <p><b>Password</b><br/><input id='mp' name='mp' type='password' placeholder='Password' value='_MQTT_PASSWORD_'></p>
      <p><b>Topic</b><br/><input id='mt' name='mt' placeholder='topic' value='_MQTT_TOPIC_'></p>
    </p><br/><button name='save' type='submit' class='button bgrn'>Save & Reboot</button>
    </form>
  </fieldset>
    <div>
  </div>
  <p><form action='/setup' method='get'><button>Back</button></form></p>
)====";

String html_console = R"====(<!DOCTYPE html>
  <body>
  <div style='text-align:left;display:inline-block;min-width:340px;'>
    <div style='text-align:center;'>
      <noscript>To user Mitsubishi2MQTT, you need to activate Javascript<br/></noscript>
      <h3>_UNIT_NAME_</h3>
      <h2>Console</h2>
    </div>
    <div id='l1' name='l1'>_CONSOLE_</div>
     <div>
  </div>
  <p><form action='/' method='get'><button>Back</button></form></p>
)====";

String html_wifi = R"====(
  <body>
  <div style='text-align:left;display:inline-block;min-width:340px;'>
    <div style='text-align:center;'>
      <noscript>To user Mitsubishi2MQTT, you need to activate Javascript<br/></noscript>
      <h3>_UNIT_NAME_</h3>
    </div>
    <div id='l1' name='l1'></div>
      <fieldset>
    <legend><b>&nbsp;WIFI Parameters&nbsp;</b></legend>
    <form method='get'>
      <p><b>Hostname</b><br/><input id='hn' name='hn' placeholder=' ' value='_UNIT_NAME_'></p>
      <p><b>SSID</b> ()<br/><input id='ssid' name='ssid' placeholder=' ' value='_SSID_'></p>
      <p><b>Password</b> ()<br/><input id='psk' name='psk' placeholder=' ' value='_PSK_'></p>
      <p><b>OTA Password</b><br/><input id='otapwd' name='otapwd' placeholder=' ' value='_OTA_PWD_'></p>
    </p><br/><button name='save' type='submit' class='button bgrn'>Save & Reboot</button>
    </form>
    <p><form action='/setup' method='get'><button>Back</button></form></p>
  </fieldset>
)====";

String html_init_setup = R"====(
  <body>
  <div style='text-align:left;display:inline-block;min-width:340px;'>
    <div style='text-align:center;'>
      <noscript>To user Mitsubishi2MQTT, you need to activate Javascript<br/></noscript>
      <h3>_UNIT_NAME_</h3>
    </div>
    <div id='l1' name='l1'></div>
      <fieldset>
    <legend><b>&nbsp;Initial setup&nbsp;</b></legend>
    <form method='get' action='save'>
      <p><b>Hostname</b><br/><input id='hn' name='hn' placeholder=' ' value='_UNIT_NAME_'></p>
      <p><b>SSID</b> ()<br/><input id='ssid' name='ssid' placeholder=' '></p>
      <p><b>PSK</b> ()<br/><input id='psk' name='psk' placeholder=' '></p>
      <p><b>OTA Password</b><br/><input id='otapwd' name='otapwd' placeholder=' '></p>
    </p><br/><button name='submit' type='submit' class='button bgrn'>Save & Reboot</button>
    </form>
  </fieldset>
)====";

  
const char* html_control = R"====(<!DOCTYPE html>
<html>
<head>
<meta name='viewport' content='width=device-width, initial-scale=1, user-scalable=yes'/>
<meta http-equiv='refresh' content='_RATE_; url=control'/>
  <style>
    div,fieldset,input,select{padding:5px;font-size:1em;}
    fieldset{background-color:#f2f2f2;}
    p{margin:0.5em 0;}
    input{width:100%;box-sizing:border-box;-webkit-box-sizing:border-box;-moz-box-sizing:border-box;}
    input[type=checkbox],input[type=radio]{width:1em;margin-right:6px;vertical-align:-1px;}
    select{width:100%;}
    textarea{resize:none;width:98%;height:318px;padding:5px;overflow:auto;}
    body{text-align:center;font-family:verdana;}
    button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;-webkit-transition-duration:0.4s;transition-duration:0.4s;cursor:pointer;}
    button:hover{background-color:#0e70a4;}
    .bred{background-color:#d43535;}
    .bred:hover{background-color:#931f1f;}
    .bgrn{background-color:#47c266;}
    .bgrn:hover{background-color:#5aaf6f;}
    a{text-decoration:none;}
    .p{float:left;text-align:left;}
    .q{float:right;text-align:right;}

    
span {
  display: inline-block;
}

.back{
    border: none;
    color: white;
    padding: 5px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 25px;
    width: 100%;
}

.button {
    background-color: #4CAF50; /* Green */
    border: none;
    color: white;
    padding: 5px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 25px;
    width: 100%;
}
.switch {
  position: relative;
  display: inline-block;
  height: 34px;
}
.sliderWidth{  width: 60px;}
.switch input, .dropdown input {display:none;}
.selected {
-webkit-filter: grayscale(100%);
filter: grayscale(100%);
text-align:center;}
input:checked + .selected {
-webkit-filter: grayscale(0%);
filter: grayscale(0%);}
.fan, .auto{color:#0C0}
.qspeed {width:20px;height:5px;}
.speed{color:#c55;}
.speedbar{width:20px; background:#c55; display:inline-block;}
.speed1{height:05px;}
.speed2{height:15px}
.speed3{height:25px}
.speed4{height:35px}
.slider {
  position: absolute;
  cursor: pointer;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #ccc;
  -webkit-transition: .4s;
  transition: .4s;
}
.slider:before {
  position: absolute;
  content: "";
  height: 26px;
  width: 26px;
  left: 4px;
  bottom: 4px;
  background-color: white;
  -webkit-transition: .4s;
  transition: .4s;
}
input:checked + .slider {
  background-color: #0c0;
}
input:focus + .slider {
  box-shadow: 0 0 1px #2196F3;
}
input:checked + .slider:before {
  -webkit-transform: translateX(26px);
  -ms-transform: translateX(26px);
  transform: translateX(26px);
}
/* Rounded sliders */
.slider.round {
  border-radius: 34px;
}

.slider.round:before {
  border-radius: 50%;
}
.hidden {visibility:hidden}
.dropbtn {
    background-color: transparent;
    color: white;
    border: none;
    cursor: pointer;
}
.dropdown {
    position: relative;
    display: inline-block;
}
.dropdown-content {
    display: none;
    position: absolute;
    background-color: #333;
    padding: 5px;
    box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);
    z-index: 1;
}
.dropdown-content label {
    color: white;
    text-decoration: none;
    display: block;
}
.dropdown:hover .dropdown-content {
    display: block;
}
</style>
<script>



function $_GET(param) {
  var vars = {};
  window.location.href.replace( location.hash, '' ).replace( 
    /[?&]+([^=&]+)=?([^&]*)?/gi, // regexp
    function( m, key, value ) { // callback
      vars[key] = value !== undefined ? value : '';
    }
  );

  if ( param ) {
    return vars[param] ? vars[param] : null;  
  }
  return vars;
}

function setTemp(b)
{
  var t = document.getElementById('TEMP');
  if(b && t.value < 31)
   { t.value++; }
  else if(!b && t.value > 16)
   { t.value--; }
  document.getElementById("FTEMP_").submit();
}

window.onload=function(){
    if($_GET('TEMP')) {
    document.getElementById('TEMP').value=$_GET('TEMP');
  }
}
</script>
<title>Mitsubishi2mqtt - _UNIT_NAME_</title>
</head>
<body>
  <div style='text-align:left;display:inline-block;min-width:340px;'>
    <div style='text-align:center;'>
      <noscript>To user Mitsubishi2MQTT, you need to activate Javascript<br/></noscript>
      <h3>_UNIT_NAME_</h3>
      <h2>Current temp _ROOMTEMP_</h2>
      <fieldset>
    <legend><b>&nbsp;Control Unit&nbsp;</b></legend>
      <p style="display: inline;"><b>Temp</b>(celsius)<br/>
         
         <span><button onclick="setTemp(0)" class='temp bgrn'>-</button>
          <form id="FTEMP_" style="display:inline"><input name="TEMP" id="TEMP" type="text" value="_TEMP_" style="text-align:center;width:40px;margin-left: 5px;margin-right: 2px;"/></form> 
          <button onclick="setTemp(1)" class='temp bgrn'>+</button></span>
      </p>
      <p>
        <b>Power</b>
          <form onchange="this.submit()">
        <select name="POWER">
          <option value="ON" _POWER_ON_>ON</option>
          <option _POWER_OFF_>OFF</option>
        </select></form>
      </p>

      <p><b>Mode</b>
      <form onchange="this.submit()">    
        <select name="MODE">
          <option value="AUTO" _MODE_A_>&#9851; AUTO</option>
          <option value="DRY" _MODE_D_>&#128167; DRY</option>
          <option value="COOL" _MODE_C_>&#10052;&#65039; COOL</option>
          <option value="HEAT" _MODE_H_>&#9728;&#65039; HEAT</option>
          <option value="FAN" _MODE_F_>&#10051; FAN</option>
        </select> </form></p>
     
      <p><b>Fan</b>
      <form onchange="this.submit()">    
        <select name="FAN">
          <option value="AUTO" _FAN_A_>&#9851; AUTO</option>
          <option value="QUIET" _FAN_QUIET_>.... QUIET</option>
          <option value="1" _FAN_1_>...: SPEED 1</option>
          <option value="2" _FAN_2_>..:: SPEED 2</option>
          <option value="3" _FAN_3_>.::: SPEED 3</option>
          <option value="4" _FAN_4_>:::: SPEED 4</option>
       
        </select></form></p>


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
       
        </select></form></p>
      <p><b>Wide Vane</b>
      <form onchange="this.submit()">
        <select name="WIDEVANE">
          <option value="AUTO" _WVANE_A_>&#9851; AUTO</option>
          <option value="SWING" _WVANE_S_>&#9887; SWING</option>
          <option value="<<" _WVANE_1_><< POS 1</option>
          <option value="<" _WVANE_2_><  POS 2</option>
          <option value="|" _WVANE_3_>|  POS 3</option>
          <option value=">" _WVANE_4_>>  POS 4</option>
          <option value=">>" _WVANE_5_>>> POS 5</option>
          <option value="<>" _WVANE_6_><> POS 6</option>
        </select></form></p>
    </p><br/><form><button name='save' type='submit' name='CONNECT' value='Re-Connect' class='button bgrn'>Re-Connect</button></form>
    </form>
  </fieldset>
  <p><form action='/' method='get'><button class="back">Back</button></form></p>
)====";
