/*
 *   This file belongs to the Project ESP-ToDoViewer-MSToDo
 *   Copyright (c) 2023 Peter Tißen
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "locale_de.h"

#include <vector>
#include <Arduino.h>

// --------------------------------------------------------------------------
// --- ERRORS ---
const char *TXT_ERROR_UNKNOWN                   = "ERROR";
const char *TXT_ERROR_BATTERY_LOW               = "Battery low";
const char *TXT_ERROR_WIFI                      = "Wifi unavailable";
const char *TXT_ERROR_API                       = "API error";
const char *TXT_ERROR_TIME                      = "Time Error";
const char *TXT_ERROR_SYSTEM                    = "Internal Error";

// --------------------------------------------------------------------------
// --- TIME ---
const char *TXT_DATETIME_LONG                   = "%a %d %b %Y %T %Z";
const char *TXT_DATE                            = "%d.%m.%y";
const char *TXT_TIME                            = "%T";
const char *TXT_TIME_SHORT                      = "%T";

// --------------------------------------------------------------------------
// --- WIFI ---
const char *TXT_WIFI_EXCELLENT                  = "Optimal";
const char *TXT_WIFI_VERYGOOD                   = "Sehr Gut";
const char *TXT_WIFI_GOOD                       = "Gut";
const char *TXT_WIFI_FAIR                       = "Ausreichend";
const char *TXT_WIFI_WEAK                       = "Schwach";
const char *TXT_WIFI_NO_CONNECTION              = "Keine Verbindung";

// --------------------------------------------------------------------------                    
const char *TXT_UNKNOWN                         = "Unbekannt";
