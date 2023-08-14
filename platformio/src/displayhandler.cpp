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

 #include "displayhandler.h"
 
#include <Arduino.h>
#include <math.h>
#include "config/config.h"
#include "version/version.h"
#include "locale/locale_de.h"

#include "../lib/GxEPD2/GxEPD2_display_selection_new_style.h"

#include "../gfx-bitmap-fonts/include/fonts.h"
#include "helper_icons.h"
#include "locale/locale_de.h"
#include "logging.h"
#include "globalvar.h"

#define DISP_WIDTH 800
#define DISP_HEIGHT 480

void DisplayHandler::ini() {
    logI.println("\n------------ DISPLAY ------------");
    
    if (m_isInit)
        return;

    display.init(115200, true, 2, false);
    display.setRotation(0);
    display.setTextSize(1);
    display.setTextWrap(false);
    display.setTextColor(GxEPD_BLACK);
    display.setFullWindow();
    m_isInit = true;
    delay(20);
}

void DisplayHandler::off(){
    delay(1);
    display.powerOff();
    delay(10);
    m_isInit = false;
}

void DisplayHandler::drawError(ERROR_t err) {

    logD.println("  Begin draw error");
    const uint8_t *bitmap = IMG_bug_solid_256x256;
    char str[20] = "";

    switch (err)
    {
        case ERR_BATTERY:   
            bitmap = IMG_battery_0_bar_256x256; 
            strncpy ( str, TXT_ERROR_BATTERY_LOW, sizeof(str) );
            break;
        case ERR_WIFI:      
            bitmap = IMG_wifi_off_256x256;
            strncpy ( str, TXT_ERROR_WIFI, sizeof(str) );
            break;
        case ERR_API:       
            bitmap = IMG_cloud_off_256x256;
            strncpy ( str, TXT_ERROR_API, sizeof(str) );
            break;
        case ERR_TIME:      
            bitmap = IMG_cloud_off_256x256;
            strncpy ( str, TXT_ERROR_TIME, sizeof(str) );
            break;
        case ERR_SYSTEM:    
            bitmap = IMG_bug_solid_256x256;
            strncpy ( str, TXT_ERROR_SYSTEM, sizeof(str) );
            break;
        default:
            bitmap = IMG_bug_solid_256x256;
            strncpy ( str, TXT_ERROR_UNKNOWN, sizeof(str) );
    }
    logD.print("  Display error txt: ");
    logD.println(str);

    /** 
     * Calculate spacing for center alignment
     * DISPLAY  : 480
     * TXT_SP   : 16
     * FONT     : 26 pt = 35 px
     * IMG      : 256 
    */
    const int16_t c_txtsp = 36;
    const int16_t c_font = 36;
    const int16_t c_img = 256;
    const int16_t c_sp = (DISP_HEIGHT - c_img - c_txtsp - c_font) / 2;
    const int16_t y_img = c_sp;
    const int16_t y_txt = c_sp + c_img + c_txtsp;

    ini();
    display.firstPage();
    do {
        display.fillScreen(GxEPD_WHITE);
        display.setFont(&FONT_40px);
        drawText(DISP_WIDTH / 2, y_txt, str, ALIGN_CB);

        display.drawInvertedBitmap(DISP_WIDTH / 2 - 256 / 2, y_img,
                                    bitmap, 256, 256, GxEPD_BLACK);
        display.display();
        delay(15000);
    }
    while (display.nextPage());
    off();
    logD.println("  Draw error finished");
}

void DisplayHandler::drawStatusBar() {
    logI.println("  print StatusBar");
    display.setFont(&FONT_8px);

    const int16_t sp = 2;
    const int16_t spl = 4;
    const int16_t spll = 16;

    int16_t pos = DISP_WIDTH - sp;

    // --- Version ---
    drawText(pos, DISP_HEIGHT - sp, VERSION_INFO, ALIGN_RB);
    pos -= getTextWidth(VERSION_INFO) + spl + 12;
    display.drawInvertedBitmap(pos, DISP_HEIGHT - 1 - 12, IMG_code_branch_solid_12x12, 12, 12, GxEPD_BLACK);
    pos -= spll;

    // --- BATTERY ---
    String txt = String(GL_BAT_PERCENTAGE) + "% (" + String( round(100.0 * GL_BAT_VOLTAGE) / 100.0, 2 ) + "v)";
    drawText(pos, DISP_HEIGHT - 1 - 2, txt, ALIGN_RB);
    pos -= getTextWidth(txt) + spl + 24;
    display.drawInvertedBitmap(pos, DISP_HEIGHT - 1 - 17,
                                ICONS_getBattery24(GL_BAT_PERCENTAGE), 24, 24, GxEPD_BLACK);
    pos -= spll;

    // --- WiFi ---
    int16_t dbm = GL_WIFI_DBM;
    txt = String(TEXT_getWiFidesc(dbm));

    if (dbm != 0)
    {
        txt += " (" + String(dbm) + "dBm)";
    }
    drawText(pos, DISP_HEIGHT - 1 - 2, txt, ALIGN_RB);
    pos -= getTextWidth(txt) + spl + 16;
    display.drawInvertedBitmap(pos, DISP_HEIGHT - 1 - 13, ICONS_getWifi16(dbm),
                                16, 16, GxEPD_BLACK);
    pos -= spll;

    //  --- Last Refresh ---
    char t[20] = "";
    strftime(t, 20, "%d.%m.%Y %H:%M", GL_TIME_LASTUPDATE);
    drawText(pos, DISP_HEIGHT - 1 - 2, t, ALIGN_RB);
    pos -= getTextWidth(t) + 12 + spl;
    display.drawInvertedBitmap(pos, DISP_HEIGHT - 1 - 12, IMG_sync_12x12, 12, 12, GxEPD_BLACK);
    pos -= spll;
}

void DisplayHandler::drawToDos(){
    display.setFont(&FONT_40px);
    drawText(0, 48, "ToDoViewer", ALIGN_LB);

    int x0 = 0;
    int y0 = 48;
    for(int l = 0; l < todo_data.list_count; l++){

        if(todo_data.lists[l].todo_count <= 0)
            continue;
        if( y0 + 56 + (l - todo_data.lists[l].todo_count) * 16 >=  400 ) {
            x0 = 400;
            y0 = 48;
        } 

        if(y0 + 32 >= 400 && x0 >= 300){
            return;
        }
        y0 += 16;      

        const uint8_t *img = ICONS_getCategory48x48(todo_data.lists[l].name);
        display.drawInvertedBitmap(x0, y0, img,
                                48, 48, GxEPD_BLACK);
        y0 += 56;
        display.setFont(&FONT_16px);

        char buf[100];
        snprintf(buf, 100, "%s (%d of %d)",
                todo_data.lists[l].name,
                todo_data.lists[l].todo_count,
                todo_data.lists[l].todo_count_available);

        drawText(x0 + 56, y0 - 20, buf , ALIGN_LB);

        display.setFont(&FONT_12px);
        for(int t = 0; t < todo_data.lists[l].todo_count; t++){
            if( strcmp (todo_data.lists[l].todo[t].status, "completed")  == 0)
                continue;

            y0 += 16;

            char buf[MSTODO_LIST_TODO_TITLE + 4];
            snprintf(buf, sizeof(buf), "- %s", todo_data.lists[l].todo[t].title);

            drawText(x0 + 5 , y0, buf , ALIGN_LB);
            logD.println(buf);
            if(y0 + 32 >= 400 && x0 >= 300){
                return;
            }
            if(y0 >= 400){
                x0 = 400;
                y0 = 48;
            }
        }  
    }
}

void DisplayHandler::update() {
    ini();
    display.firstPage();
    do {
        drawStatusBar();
        drawToDos();
    }
    while (display.nextPage());
    off();
}

void DisplayHandler::drawText(int16_t x0, int16_t y0, String text, ALIGN_t align)
{
    int16_t tx, ty;
    uint16_t w, h;
    int16_t x;
    int16_t y;
    
    display.getTextBounds(text, x0, y0, &tx, &ty, &w, &h);

    if(h == 0){
        h = 1;
    }
    if(w == 0){
        w = 1;
    }

    switch (align)
    {
    case ALIGN_LB:
        x = x0;
        y = y0;
        break;
    case ALIGN_LT:
        x = x0;
        y = y0 - h;
        break;
    case ALIGN_LC:
        x = x0;
        y = y0 - h / 2;
        break;
    case ALIGN_CB:
        x = x0 - w / 2;
        y = y0;
        break;
    case ALIGN_CT:
        x = x0 - w / 2;
        y = y0 - h;
        break;
    case ALIGN_CC:
        x = x0 - w / 2;
        y = y0 - h / 2;
        break;
    case ALIGN_RB:
        x = x0 - w;
        y = y0;
        break;
    case ALIGN_RT:
        x = x0 - w;
        y = y0 - h;
        break;
    case ALIGN_RC:
        x = x0 - w;
        y = y0 - h / 2;
        break;
    default:
        x = x0;
        y = y0;
        break;
    }

    display.setCursor(x, y);
    display.print(text);
}

uint16_t DisplayHandler::getTextWidth(String text)
{
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    return w;
}


const char *DisplayHandler::TEXT_getWiFidesc(int rssi)
{
  if (rssi == 0)            return TXT_WIFI_NO_CONNECTION;
  else if (rssi >= -50)     return TXT_WIFI_EXCELLENT;
  else if (rssi >= -60)     return TXT_WIFI_GOOD;
  else if (rssi >= -70)     return TXT_WIFI_FAIR;
  else                      return TXT_WIFI_WEAK;
}