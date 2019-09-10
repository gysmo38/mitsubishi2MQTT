String html_init_setup = R"====(
  <body>
  <div style='text-align:left;display:inline-block;min-width:340px;'>
    <div style='text-align:center;'>
      <noscript>To user Mitsubishi2MQTT, you need to activate Javascript<br/></noscript>
      <h3>_UNIT_NAME_</h3>
    </div>
  <p><form action='/mqtt' method='get'><button>MQTT</button></form></p>
  <p><form action='/wifi' method='get'><button>WIFI</button></form></p>
  <p><form action='/others' method='get'><button>Others</button></form></p>
  <p><form><button type='submit' name='RESET' class='button bred'>Reset configuration</button></form></p>
  <p><form action='/' method='get'><button>Back</button></form></p>
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