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
#include "mstodo.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "mstododata.h"
#include "logging.h"
#include "config/config.h"

void MSToDo::update() {
    m_isError = false;
    logI.println("--- MSToDO update() start ---");

    m_client.setCACert(cert);

    authenticate();
    if (m_isError)
        return;

    getLists();
    if (m_isError)
        return;

    getToDos();
    if (m_isError)
        return;

    logI.println("--- MSToDO update() finished ---");
}

void MSToDo::authenticate() {
    logI.println("--- authenticate() ---");
    m_client.available();

    //m_client.setInsecure();
    HTTPClient http;

    String body = "client_id=" + String(clientId) +
                "&grant_type=" + grantType +
                "&scope=" + scope +
                "&refresh_token=" + refreshToken;

    http.useHTTP10(true);
    http.begin(m_client, urlAuth);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpCode = http.POST(body);

    if (httpCode != HTTP_CODE_OK) {
        logW.println("Failed to get access token:");
        logW.printf("  Error code: %d\n", httpCode);
        logW.printf("  Error string: %s\n", http.errorToString(httpCode).c_str());
        m_isError = true;
        return;
    }

    try {
        DynamicJsonDocument doc(4000);
        deserializeJson(doc, http.getStream());

        const char* token = doc["access_token"].as<const char*>();
        strccopy(m_accessToken, token, sizeof(m_accessToken));
    } catch (const std::exception &e) {
        m_isError = true;
        logW.print("Exception caught while parsing JSON data: ");
        logW.println(e.what());
    }
    http.end();
}

void MSToDo::getLists() {
    logI.println("--- getLists() ---");

    HTTPClient http;
    http.useHTTP10(true);
    http.begin(m_client, urlLists);
    http.addHeader("Authorization", "Bearer \"" + String(m_accessToken) + "\"");

    int httpCode = http.GET();
    if (httpCode != HTTP_CODE_OK) {
        logW.println("Failed to read task lists:");
        logW.printf("  Error code: %d\n",httpCode);
        logW.printf("  Error string: %s\n", http.errorToString(httpCode).c_str());
        m_isError = true;
        return;
    }

    try {
        DynamicJsonDocument json(4000);
        DeserializationError error;
        error = deserializeJson(json, http.getStream());
        if (error) {
            logD.print("Error parsing JSON data: ");
            logD.println(error.c_str());
            m_isError = true;
            return;
        }

        JsonArray array = json["value"];
        if (array.isNull() || !json["value"].is<JsonArray>()) {
            logW.println("Invalid or missing value array in the JSON");
            m_isError = true;
            return;
        }

        todo_data.list_count_available = array.size();
        todo_data.list_count = min(array.size(), (size_t) MSTODO_LISTS_MAX);
        
        logI.printf("Get lists ( %i from %i total available)\n", 
                    todo_data.list_count, todo_data.list_count_available);

        for (int i = 0; i < todo_data.list_count; i++) {
            JsonVariant taskList = array[i];
            const char* taskListId = taskList["id"].as<const char*>();
            const char* taskListName = taskList["displayName"].as<const char*>();
            if (taskListId == nullptr || taskListName == nullptr) {
                logW.println("Invalid or missing task list ID or name in the JSON");
                m_isError = true;
                continue;
            }

            strccopy(todo_data.lists[i].id, taskListId, sizeof(todo_data.lists[i].id));
            strccopy(todo_data.lists[i].name, taskListName, sizeof(todo_data.lists[i].name));
            logI.printf("  %-2i : %s\n", i + 1, todo_data.lists[i].name);
        }

    } catch (const std::exception &e) {
        m_isError = true;
        logW.print("Exception caught while parsing JSON data: ");
        logW.println(e.what());
        return;
    }
    http.end();
}

void MSToDo::getToDos() {
    logI.println("--- getToDos() ---");

    for(int i = 0; i < todo_data.list_count; i++)
    {
        HTTPClient http;
        http.useHTTP10(true);
        DynamicJsonDocument json(4000);

        try {
            String url = urlTasks + String(todo_data.lists[i].id) + "/tasks";
            http.begin(m_client, url);
            http.addHeader("Authorization", "Bearer \"" + String(m_accessToken) + "\"");

            int httpCode = http.GET();
            if (httpCode != HTTP_CODE_OK) {
                logW.printf("Failed to read task lists. Error code: %d\n", httpCode);
                logW.printf("  Error code: %d\n",httpCode);
                logW.printf("  Error string: %s\n", http.errorToString(httpCode).c_str());
                m_isError = true;
                return;
            }

            DeserializationError error;
            error = deserializeJson(json, http.getStream());
            if (error) {
                logD.print("Error parsing JSON data: ");
                logD.println(error.c_str());
                m_isError = true;
                return;
            }

            JsonArray array = json["value"];
            if (array.isNull() || !json["value"].is<JsonArray>()) {
                logD.println("Invalid or missing value array in the JSON");
                m_isError = true;
                continue;
            }

            todo_data.lists[i].todo_count = min(array.size(), (size_t) MSTODO_LIST_TODOS_MAX); 
            todo_data.lists[i].todo_count_available = array.size();
           
            logI.printf("List: %s ( Tasks %i from %i available )\n", 
                        todo_data.lists[i].name,
                        todo_data.lists[i].todo_count,
                        todo_data.lists[i].todo_count_available);

            for (int t = 0; t < todo_data.lists[i].todo_count_available; t++) {
                JsonVariant task = array[t];
                if (!task.is<JsonObject>()) {
                    logW.println("Invalid JSON object in the array");
                    continue;
                }

                const char* title = task["title"].as<const char*>();
                if (title == nullptr) {
                    logW.println("Invalid or missing title field in the JSON object");
                    continue;
                }

                const char* status = task["status"].as<const char*>();
                if (status == nullptr) {
                    logW.println("Invalid or missing status field in the JSON object");
                    continue;
                }

                strccopy(todo_data.lists[i].todo[t].title, title, sizeof(todo_data.lists[i].todo[t].title));
                strccopy(todo_data.lists[i].todo[t].status, status, sizeof(todo_data.lists[i].todo[t].status));
                logI.printf("  %02i : %s : %s\n", t, title, status);
            }
        }
        catch (const std::exception& e) {
            m_isError = true;
            logW.print("Exception caught while parsing JSON data: ");
            logW.println(e.what());
            logW.print("Todo:  ");
            logW.println(i);
            return;
        }
        http.end();
    }
}   

void MSToDo::strccopy(char *dest, const char *src, size_t n) {
    // Copy with termination character
    if (strlen(src) <= n - 1) {
        strncpy(dest, src, n - 1);
        dest[n - 1] = '\0';
    } else {
        // Copy with truncation and termination character
        strncpy(dest, src, n - 4);
        dest[n - 4] = '.';
        dest[n - 3] = '.';
        dest[n - 2] = '.';
        dest[n - 1] = '\0';
    }
}