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
 
const char html_common_header[] PROGMEM = 
"<!DOCTYPE html>"
"<html lang='en' class=''>"

"<head>"
    "<meta charset='utf-8'>"
    "<meta name='viewport' content='width=device-width,initial-scale=1,user-scalable=no' />"
    "<title>_APP_NAME_ - _UNIT_NAME_</title>"
    "<style>"
        "*{"
            "font-family: verdana,sans-serif;"
        "}"
        "body {"
            "text-align: center;"
        "}"
        "div,"
        "fieldset,"
        "input,"
        "select {"
            "padding: 5px;"
            "font-size: 1em;"
        "}"
        ".main {"
            "text-align:left;"
            "display: inline-block;"
            "min-width:340px;"
        "}"

        "fieldset {"
            "background-color: #f2f2f2;"
        "}"

        "p {"
            "margin: 0.5em 0;"
        "}"
        ".ctrlrow {"
           "padding: 0px !important;"
           "margin: 0.5em 0 !important;"
        "}"

        "input {"
            "width: 100%;"
            "box-sizing: border-box;"
            "-webkit-box-sizing: border-box;"
            "-moz-box-sizing: border-box;"
        "}"

        "input[type=checkbox],"
        "input[type=radio] {"
            "width: 1em;"
            "margin-right: 6px;"
            "vertical-align: -1px;"
        "}"

        "select {"
            "width: 100%;"
            "background: #dddddd;"
            "color: #000000;"
            "block-size: 40px;"
        "}"

        "textarea {"
            "resize: none;"
            "width: 98%;"
            "height: 318px;"
            "padding: 5px;"
            "overflow: auto;"
        "}"

        "td {"
            "padding: 0px;"
        "}"

        "button {"
            "border: 0;"
            "border-radius: 0.3rem;"
            "background-color: #1fa3ec;"
            "color: #fff;"
            "line-height: 2.4rem;"
            "font-size: 1.2rem;"
            "width: 100%;"
            "-webkit-transition-duration: 0.4s;"
            "transition-duration: 0.4s;"
            "cursor: pointer;"
        "}"

        "button:hover {"
            "background-color: #0e70a4;"
        "}"

        ".bred {"
            "background-color: #d43535;"
        "}"

        ".bred:hover {"
            "background-color: #931f1f;"
        "}"

        ".bgrn {"
            "background-color: #47c266;"
        "}"

        ".bgrn:hover {"
            "background-color: #5aaf6f;"
        "}"

        "a {"
            "text-decoration: none;"
        "}"

        ".p {"
            "float: left;"
            "text-align: left;"
        "}"

        ".q {"
            "float: right;"
            "text-align: right;"
        "}"

        "pan {"
            "display: inline-block;"
        "}"

        "/* ON/OFF switch */"
        "/* The switch - the box around the slider */"
        ".switch {"
            "position: relative;"
            "display: inline-block;"
            "width: 60px;"
            "height: 34px;"
        "}"

        "/* Hide default HTML checkbox */"
        ".switch input {"
            "opacity: 0;"
            "width: 0;"
            "height: 0;"
        "}"

        "/* The slider */"
        ".slider {"
            "position: absolute;"
            "cursor: pointer;"
            "top: 0;"
            "left: 0;"
            "right: 0;"
            "bottom: 0;"
            "background-color: #ccc;"
            "-webkit-transition: 0.4s;"
            "transition: 0.4s;"
        "}"

        ".slider:before {"
            "position: absolute;"
            "content: '';"
            "height: 26px;"
            "width: 26px;"
            "left: 4px;"
            "bottom: 4px;"
            "background-color: white;"
            "-webkit-transition: 0.4s;"
            "transition: 0.4s;"
        "}"

        "input:checked + .slider {"
            "background-color: #0c0;"
        "}"

        "input:focus + .slider {"
            "box-shadow: 0 0 1px #2196f3;"
        "}"

        "input:checked + .slider:before {"
            "-webkit-transform: translateX(26px);"
            "-ms-transform: translateX(26px);"
            "transform: translateX(26px);"
        "}"

        "/* Rounded sliders */"
        ".slider.round {"
            "border-radius: 34px;"
        "}"

        ".slider.round:before {"
            "border-radius: 50%;"
        "}"
    "</style>"
"</head>"
"<body>"
  "<div class='main'>"
    "<div style='text-align:center;'>"
        "<noscript>To user _APP_NAME_, you need to activate Javascript"
                "<br/>"
        "</noscript>"
        "<h3>_UNIT_NAME_</h3>"
     "</div>";

const char html_common_footer[] PROGMEM = 
    "<br/>"
    "<div style='text-align:right;font-size:10px;color: grey;'>"
       "<hr/>_APP_NAME_ _VERSION_</div>"
    "</div>"
  "</div>"
"</body>"
"</html>";