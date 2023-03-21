#ifndef SIDELED_H_ /* Include guard */
#define SIDELED_H_

#include <Arduino.h>
#include <M5Core2.h>
#include <Arduino.h>
#include <lvgl.h>
#include <Wire.h>
#include <SPI.h>
#include <VL53L0X.h>

// Common
extern TFT_eSPI tft = TFT_eSPI();

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);

void set_up_m5stack_defaults();

#endif /* SIDELED_H_ */