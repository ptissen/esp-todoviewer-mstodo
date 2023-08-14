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
#include "wifihandler.h"

#include "config/config.h"
#include "config/secrets.h"
#include "logging.h"

WifiHandler::WifiHandler()
{
}

void WifiHandler::ini()
{
    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);
}

void WifiHandler::update()
{
    bool isConnected = false;
    logI.println("\n------------ WIFI ------------");
    logI.printf("  Connecting to '%s' ", SECRET_WIFI_SSID);

    WiFi.begin(SECRET_WIFI_SSID, SECRET_WIFI_PASSWORD);
    unsigned long timeout = millis() + WIFI_TIMEOUT_MILLIS;

    while (!isConnected && millis() < timeout) {
        logI.print(".");
        delay(1000);

        if (WL_CONNECTED == WiFi.status()){
            isConnected = true;
        }
    }

    logI.println();

    if (isConnected) {
        m_rssi = rssi();
        logI.printf("  IP: '%s'\n", WiFi.localIP().toString().c_str());
        logI.printf("  RSSI: '%i'\n", m_rssi);
    }
    else {
        logI.printf("  Connection failed to '%s'\n", SECRET_WIFI_SSID);
    }
}

void WifiHandler::kill()
{
    WiFi.disconnect(true, true);
    WiFi.mode(WIFI_OFF);
}

bool WifiHandler::isConnected() const { 
    return WiFi.status() == WL_CONNECTED; 
};

int WifiHandler::rssi() const {
    return WiFi.RSSI();
}
