#ifndef SIDELED_H_ /* Include guard */
#define SIDELED_H_

#include <Arduino.h>
#include <M5Core2.h>
#include <Arduino.h>
#include <lvgl.h>
#include <Wire.h>
#include <SPI.h>
#include <VL53L0X.h>

void send_park_state(bool isOccupied, int parkSpace);

#endif /* SIDELED_H_ */