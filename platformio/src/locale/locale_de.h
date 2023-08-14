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
#pragma once

#include <Arduino.h>
#include <vector>

#ifdef __cplusplus
extern "C"
{
#endif

// --------------------------------------------------------------------------
// --- ERRORS ---
extern const char *TXT_ERROR_UNKNOWN;
extern const char *TXT_ERROR_BATTERY_LOW;
extern const char *TXT_ERROR_WIFI;
extern const char *TXT_ERROR_API;
extern const char *TXT_ERROR_TIME;
extern const char *TXT_ERROR_SYSTEM;

// --------------------------------------------------------------------------
// --- TIME ---
extern const char *TXT_DATETIME_LONG;
extern const char *TXT_DATE;
extern const char *TXT_TIME;
extern const char *TXT_TIME_SHORT;

// --------------------------------------------------------------------------
// --- WIFI ---
extern const char *TXT_WIFI_EXCELLENT;
extern const char *TXT_WIFI_VERYGOOD;
extern const char *TXT_WIFI_GOOD;
extern const char *TXT_WIFI_FAIR;
extern const char *TXT_WIFI_WEAK;
extern const char *TXT_WIFI_NO_CONNECTION;

// --------------------------------------------------------------------------
extern const char *TXT_UNKNOWN;

#ifdef __cplusplus
}
#endif