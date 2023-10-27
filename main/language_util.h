/*
  mitsubishi2mqtt - Mitsubishi Heat Pump to MQTT control for Home Assistant.
  Copyright (c) 2023 by Pham Viet Dzung @dzungpv. All right reserved.
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
// code originally written by Paul Derbyshire - https://github.com/emsesp/EMS-ESP
#ifdef ESP32 //With ESP32 Flash string FPSTR only for compatible, if it is const default store in flash

#ifdef FPSTR
#undef FPSTR
#endif
// clang-format off
#define FPSTR(pstr_pointer) pstr_pointer

#endif

#define MAKE_WORD_CUSTOM(string_name, string_literal) const char __pstr__##string_name[] PROGMEM = string_literal;
#define MAKE_WORD(string_name) MAKE_WORD_CUSTOM(string_name, #string_name)

#define F_(string_name) (__pstr__##string_name)
#define FL_(list_name) (__pstr__L_##list_name)

#if defined(MITSU2MQTT_TEST) || defined(MITSU2MQTT_EN_ONLY)
// In testing just take one language (en) to save on Flash space
#define MAKE_WORD_TRANSLATION(list_name, en, ...)       static const char * const __pstr__L_##list_name[] PROGMEM = {en, nullptr};
#define MAKE_TRANSLATION(list_name, shortname, en, ...) static const char * const __pstr__L_##list_name[] PROGMEM = {shortname, en, nullptr};
#elif defined(MITSU2MQTT_VI_ONLY)
#define MAKE_WORD_TRANSLATION(list_name, en, vi, ...)       static const char * const __pstr__L_##list_name[] PROGMEM = {vi, nullptr};
#define MAKE_TRANSLATION(list_name, shortname, en, vi, ...) static const char * const __pstr__L_##list_name[] PROGMEM = {shortname, vi, nullptr};
#else
#define MAKE_WORD_TRANSLATION(list_name, ...) static const char * const __pstr__L_##list_name[] PROGMEM = {__VA_ARGS__, nullptr};
#define MAKE_TRANSLATION(list_name, ...)      static const char * const __pstr__L_##list_name[] PROGMEM = {__VA_ARGS__, nullptr};
#endif

#define MAKE_NOTRANSLATION(list_name, ...) static const char * const __pstr__L_##list_name[] PROGMEM = {__VA_ARGS__, nullptr};

// fixed strings, no translations
#define MAKE_ENUM_FIXED(enum_name, ...) static const char * const __pstr__L_##enum_name[] PROGMEM = {__VA_ARGS__, nullptr};

// with translations
#define MAKE_ENUM(enum_name, ...)       static const char * const * __pstr__L_##enum_name[] PROGMEM = {__VA_ARGS__, nullptr};

// clang-format on

uint8_t countItems(const char *const **list);
const char *translatedWord(const char *const *strings, const bool force_en = false);
// count number of items in a list of lists
// the end of a list has a nullptr
uint8_t countItems(const char *const *list)
{
  uint8_t list_size = 0;
  if (list != nullptr)
  {
    while (list[list_size])
    {
      list_size++;
    }
  }
  return list_size;
}

char buffer[200]; // buffer for reading the string to (needs to be large enough to take the longest string) for ESP8266 only

// returns char pointer to translated description or fullname
// if force_en is true always take the EN non-translated word
const char *translatedWord(const char *const *strings, const bool force_en)
{
  uint8_t language_index = system_language_index; // default 0 for English
  uint8_t index = 0;

  if (!strings)
  {
    return ""; // no translations
  }
#ifdef ESP32
  // see how many translations we have for this entity. if there is no translation for this, revert to EN
  // if (!force_en && (countItems(strings) >= language_index + 1 && strlen(strings[language_index])))
  // {
  //   index = language_index;
  // }
  return strings[language_index];
#endif

#ifdef ESP8266
  //get PROGMEM array data https://arduino-esp8266.readthedocs.io/en/latest/PROGMEM.html
  strcpy_P(buffer, (char *)pgm_read_dword(&(strings[language_index])));
  return buffer;
#endif
}
// load translations
#include "language_translations.h"