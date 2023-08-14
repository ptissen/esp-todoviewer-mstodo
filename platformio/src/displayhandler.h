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
#include <Adafruit_GFX.h>

#include "mstododata.h"

class DisplayHandler
{
public:
    /***
        Aligments:
        LT       CT       RT
            +-----------+
            |           |
        LC  |    CC     | RC
            |           |
            +-----------+
        LB      CB        RB
    */
    typedef enum
    {
        ALIGN_LT,
        ALIGN_LC,
        ALIGN_LB,
        
        ALIGN_CT,
        ALIGN_CC,
        ALIGN_CB,
        
        ALIGN_RT,
        ALIGN_RC,
        ALIGN_RB
    } ALIGN_t;

    typedef enum
    {
        ERR_NOT,
        ERR_BATTERY,
        ERR_WIFI,
        ERR_API,
        ERR_TIME,
        ERR_SYSTEM
    } ERROR_t;

    DisplayHandler(void) = default;

    void update();
    void drawError(ERROR_t err);
    bool isInit() { return m_isInit; };

private:
    bool m_isInit = false;

    void ini();
    void off();
    
    void drawToDos();
    void drawStatusBar();

    void drawText(int16_t x0, int16_t y0, String text, ALIGN_t align = ALIGN_LB);
    uint16_t getTextWidth(String text);

    const char *TEXT_getWiFidesc(int rssi);

};