#include "setup.h"

// Common
TFT_eSPI tft = TFT_eSPI();

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors(&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

void set_up_m5stack_defaults()
{
    M5.begin(true, true, true, true);
    tft.begin();
    tft.setRotation(1);
    M5.Axp.SetLcdVoltage(2800);
    M5.Axp.SetLcdVoltage(3300);
    M5.Axp.SetBusPowerMode(0);
    M5.Axp.SetCHGCurrent(AXP192::kCHG_190mA);
    M5.Axp.SetLDOEnable(3, true);
    delay(150);
    M5.Axp.SetLDOEnable(3, false);
    M5.Axp.SetLed(1);
    delay(100);
    M5.Axp.SetLed(0);
    M5.Axp.SetLDOVoltage(3, 3300);
    M5.Axp.SetLed(1);
}