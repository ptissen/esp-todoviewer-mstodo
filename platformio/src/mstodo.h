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

#include <WiFiClientSecure.h>

#define MSTODO_ACCESSTOKEN      1200
class MSToDo
{
public:
    MSToDo() = default;
    void update();
    bool isError() { return m_isError; };

private:
    void authenticate();
    void getLists();
    void getToDos();
    
    void strccopy(char *dest, const char *src, size_t n);

    bool m_isError = false;
    char m_accessToken[MSTODO_ACCESSTOKEN];
    WiFiClientSecure m_client;
};