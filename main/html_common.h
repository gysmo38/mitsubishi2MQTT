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
const char html_common_header[] PROGMEM = R"====(<!DOCTYPE html>
<html lang="en" class="">

<head>
    <meta charset='utf-8' />
    <meta name="viewport" content="width=device-width,initial-scale=1,user-scalable=no" />
    <title>Mitsubishi2MQTT - _UNIT_NAME_</title>
    <style>
        div,fieldset,input,select {
            padding: 5px;
            font-size: 1em;
        }

        .main {
            text-align:left;
            display: inline-block;
            min-width:340px;
            color: #eaeaea;
        }
        
        fieldset {
            background-color: #4f4f4f;
        }
        
        p {
            margin: 0.5em 0;
        }
        
        input[type=checkbox],input[type=radio] {
            width: 1em;
            margin-right: 6px;
            vertical-align: -1px;
        }

        input[type=range] {
            width: 99%;
        }

        input:not([type]),input[type=password],input[type=number]  {
            width: 100%;
            box-sizing: border-box;
            -webkit-box-sizing: border-box;
            -moz-box-sizing: border-box;
            background: #dddddd;
            color: #000000;
        }

        select {
            width: 100%;
            background: #dddddd;
            color: #000000;
            block-size: 40px;
        }

        textarea {
            resize: none;
            width: 98%;
            height: 318px;
            padding: 5px;
            overflow: auto;
            background: #1f1f1f;
            color: #65c115;
        }
        
        body {
            text-align: center;
            font-family: verdana,sans-serif;
            background: #252525;
        }
        
        td {
            padding: 0px;
        }
        
        button, a.button {
            display: inline-block;
            text-align: center;
            border: 0;
            border-radius: 0.3rem;
            background: #1fa3ec;
            color: #faffff;
            line-height: 2.4rem;
            font-size: 1.2rem;
            width: 100%;
            -webkit-transition-duration: 0.4s;
            transition-duration: 0.4s;
            cursor: pointer;
        }
        
        button:hover, a.button:hover {
            background: #0e70a4;
        }
        
        .bred {
            background-color: #d43535;
        }
        
        .bred:hover {
            background-color: #931f1f;
        }
        
        .bgrn {
            background-color: #47c266;
        }
        
        .bgrn:hover {
            background-color: #5aaf6f;
        }
        
        a {
            text-decoration: none;
        }
        
        .p {
            float: left;
            text-align: left;
        }
        
        .q {
            float: right;
            text-align: right;
        }

        a {
            color: #1fa3ec;
            text-decoration: none;
        }

        .p {
            float: left;
            text-align: left;
        }

        .q {
            float: right;
            text-align: right;
        }

        .r {
            border-radius: 0.3em;
            padding: 2px;
            margin: 6px 2px;
        }
        
        span {
            display: inline-block;
        }

        h2, h3 {
            text-align: center;
        }
    </style>
</head>
<body>
    <div class="main">
        <div style='text-align:center;'>
            <noscript>To use Mitsubishi2MQTT, you need to activate Javascript<br/></noscript>
            <h3>_UNIT_NAME_</h3>
        </div>
)====";

const char html_common_footer[] PROGMEM = R"====(
        <br/>
        <div style='text-align:right;font-size:10px;color: grey;'>
            <hr/>Mitsubishi2MQTT _VERSION_
        </div>
    </div>
</body>

</html>
)====";
