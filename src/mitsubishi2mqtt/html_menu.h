String html_menu_root = R"====(
  <body>
  <div style='text-align:left;display:inline-block;min-width:340px;'>
    <div style='text-align:center;'>
      <noscript>To user Mitsubishi2MQTT, you need to activate Javascript<br/></noscript>
      <h3>_UNIT_NAME_</h3>
    </div>
  <p><form action='/control' method='get'><button>Control</button></form></p>
  <p><form action='/setup' method='get'><button>Setup</button></form></p>
  <p><form action='/status' method='get'><button>Status</button></form></p>
  <p><form><button type='submit' name='REBOOT' class='button bred'>Reboot</button></form></p>
)====";


String html_menu_setup = R"====(
  <body>
  <div style='text-align:left;display:inline-block;min-width:340px;'>
    <div style='text-align:center;'>
      <noscript>To user Mitsubishi2MQTT, you need to activate Javascript<br/></noscript>
      <h3>_UNIT_NAME_</h3>
    </div>
  <p><form action='/mqtt' method='get'><button>MQTT</button></form></p>
  <p><form action='/wifi' method='get'><button>WIFI</button></form></p>
  <p><form action='/advance' method='get'><button>ADVANCE</button></form></p>
  <p><form><button type='submit' name='RESET' class='button bred'>Reset configuration</button></form></p>
  <p><form action='/' method='get'><button>Back</button></form></p>
)====";
