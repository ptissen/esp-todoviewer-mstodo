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
#include "secrets.h"

// --------------------------------------------------------------------------
// --- Main Config ---
#define PROJECT_NAME                    "ESP-ToDoViewer-MSToDo"

// --------------------------------------------------------------------------
// --- Logger ---
// Set Debug Level (Serial Logging decreases performance and battery lifetime)
#define LOG_ERROR                       true
#define LOG_WARNING                     true
#define LOG_INFO                        true
#define LOG_DEBUG                       true
#define LOG_SERIAL_BAUDRATE             115200

// --------------------------------------------------------------------------
// --- Time ---
#define TIME_MAX_TRY                    5
#define TIME_NTP_SERVER1                "pool.ntp.org"
#define TIME_NTP_SERVER2                "time.nist.gov"
#define TIME_DAYLIGHTOFFSET             3600
#define TIME_GMT_OFFSET_SEC             3600

// --------------------------------------------------------------------------
// --- WiFi ---
#define WIFI_TIMEOUT_MILLIS             10000

// --------------------------------------------------------------------------
// --- DeepSleep ---

const int DEEPSLEPP_START_H         = 23;
const int DEEPSLEPP_END_H           = 06;
const int SLEEP_NORM_MIN            = 10;
const int SLEEP_VLOW_MINUTES        = ((60 * 12));

// --------------------------------------------------------------------------
// --- Formating ---
#define FORMAT_TIME                     "%H:%M"
#define FORMAT_HOUR                     "%H"
#define FORMAT_DATE                     "%x"         
#define FORMAT_DATE_TIME                "%x %H:%M"


extern const char* urlAuth;
extern const char* urlLists;
extern const char* urlTasks;
extern const char* scope;
extern const char* grantType;