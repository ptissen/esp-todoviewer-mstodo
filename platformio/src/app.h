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
#include <WiFi.h>

#include "battery/upesybattery.h"
#include "wifihandler.h"
#include "timehandler.h"
#include "msToDO.h"
#include "displayhandler.h"

class App {
public:
    App(void){}

    void ini();

private:
    bool isBootReasonOk();
    void activateDeepSleep(bool forever, TimeHandler &t);

    UPesyBattery m_battery;

    #if BOARD_NAME == UPESY
    #elif BOARD_NAME == FIREBEETLE2
        // TODO
    #else
    //    Battery m_battery;
    #endif

    MSToDo m_todo;

    WifiHandler m_wifiHandler;
    TimeHandler m_timeHandler;
    DisplayHandler m_displayHandler;
};