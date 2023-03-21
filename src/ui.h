#ifndef SIDELED_H_ /* Include guard */
#define SIDELED_H_

#define SIDELED_NUM_LEDS 10
#define SIDELED_DATA_PIN 25

#define SIDELED_STATE_OFF 0
#define SIDELED_STATE_ON 1
#define SIDELED_STATE_BLINK 2
#define SIDELED_STATE_BLINK_INVERS 3
#define SIDELED_STATE_FADE 4
#define SIDELED_STATE_FADE_RG 5
#define SIDELED_STATE_FADE_GB 6
#define SIDELED_STATE_FADE_BR 7

#include <Arduino.h>
#include <M5Core2.h>
#include <Arduino.h>
#include <lvgl.h>
#include <Wire.h>
#include <SPI.h>
#include <VL53L0X.h>

extern lv_obj_t *label_distance_mm;
extern lv_obj_t *label_car_detected;

bool my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);

void set_up_buttons(lv_obj_t *tab1);

void set_up_labels(lv_obj_t *tab1);

#endif /* SIDELED_H_ */