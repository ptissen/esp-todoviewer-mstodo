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

#define MSTODO_LIST_TODO_TITLE      60
#define MSTODO_LIST_TOOD_STATUS     20
#define MSTODO_LIST_TODOS_MAX       30
#define MSTODO_LIST_NAME            30
#define MSTODO_LIST_ID              128
#define MSTODO_LISTS_MAX            10

typedef struct {
    struct {
        struct {
            char title[MSTODO_LIST_TODO_TITLE];
            char status[MSTODO_LIST_TOOD_STATUS];
        } todo[MSTODO_LIST_TODOS_MAX];
        uint32_t todo_count;
        uint32_t todo_count_done;
        uint32_t todo_count_available;
        char name[MSTODO_LIST_NAME];
        char id[MSTODO_LIST_ID];
    } lists[MSTODO_LISTS_MAX];
    uint32_t list_count;   
    uint32_t list_count_available;
} todo_data_t;

extern todo_data_t todo_data;
