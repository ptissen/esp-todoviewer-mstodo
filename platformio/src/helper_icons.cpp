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
#include "helper_icons.h"

#include <map>
#include <vector>
#include "logging.h"

const std::map<const char *, const uint8_t *> ICONS_MAPPING_48x48 = {
    // Google
    {"Schule", IMG_assignment_black_24dp_48x48},
    {"Events", IMG_event_black_24dp_48x48},
    {"Info", IMG_info_black_24dp_48x48},
    {"Liste", IMG_list_black_24dp_48x48},
    {"Schule", IMG_school_black_24dp_48x48},
    {"Shopping", IMG_shopping_cart_black_24dp_48x48},
    {"Arbeit", IMG_work_black_24dp_48x48},

    // Fontawesome
    {"Termine", IMG_calendar_days_solid_48x48},
    {"Kalender", IMG_calendar_days_solid_48x48},
    {"Veranstaltungen", IMG_calendar_days_solid_48x48},
    {"Uni", IMG_school_solid_48x48},
    {"Einkaufen", IMG_bag_shopping_solid_48x48},
    {"Shoppen", IMG_bag_shopping_solid_48x48},
    {"Buy", IMG_bag_shopping_solid_48x48}
};

bool areStringsEqualIgnoreCase(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (std::toupper(*str1) != std::toupper(*str2)) {
            return false;
        }
        str1++;
        str2++;
    }
    return (*str1 == *str2);
}

const uint8_t * ICONS_getCategory48x48( const char * const category){
    for (const auto &entry : ICONS_MAPPING_48x48) {
        if (areStringsEqualIgnoreCase(category, entry.first)) {
            return entry.second;
        }
    }

    logI.print("Icon not in Category list. Use default Icon. Category: ");
    logI.println(category);
    return IMG_list_solid_48x48;
}

const uint8_t *ICONS_getBattery24(int percent)
{
    if (percent >= 93)
        return IMG_battery_full_90_deg_24x24;
    else if (percent >= 79)
        return IMG_battery_6_bar_90deg_24x24;
    else if (percent >= 65)
        return IMG_battery_5_bar_90deg_24x24;
    else if (percent >= 50)
        return IMG_battery_4_bar_90deg_24x24;
    else if (percent >= 36)
        return IMG_battery_3_bar_90deg_24x24;
    else if (percent >= 22)
        return IMG_battery_2_bar_90deg_24x24;
    else if (percent >= 10)
        return IMG_battery_1_bar_90deg_24x24;

    return IMG_battery_0_bar_90deg_24x24;
}

const uint8_t *ICONS_getWifi16(int dbm)
{
    if (dbm == 0)
        return IMG_wifi_off_16x16;
    else if (dbm >= -50)
        return IMG_wifi_3_16x16;
    else if (dbm >= -60)
        return IMG_wifi_2_16x16;
    else if (dbm >= -70)
        return IMG_wifi_1_16x16;

    return IMG_wifi_0_16x16;
}