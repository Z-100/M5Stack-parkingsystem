#include "application_state.h"

bool left_spot_occupied = false;
bool right_spot_occupied = false;

long next_sensor_read_time = 0;

/**
 * Changes which sensor is selected
 * True:   The top sensor
 * False:  The side sensor
*/
bool isTopM5Stack() {
    return false;
}

bool hasLeftStateChanged(bool newState) {
    return left_spot_occupied == newState;
}

bool hasRightStateChanged(bool newState) {
    return right_spot_occupied == newState;
}

void switchLeftSpotOccupied() {
    left_spot_occupied = true;
}

void switchRightSpotOccupied() {
    right_spot_occupied = true;
}

void switchLeftSpotUnOccupied() {
    left_spot_occupied = false;
}

void switchRightSpotUnOccupied() {
    right_spot_occupied = false;
}

bool isLeftSpotOccupied() {
    return left_spot_occupied;
}

bool isRightSpotOccupied() {
    return right_spot_occupied;
}

int numOfSpotsOccupied() {
    if (left_spot_occupied && right_spot_occupied) {
        return 0;
    } else if (left_spot_occupied && !right_spot_occupied || !left_spot_occupied && right_spot_occupied) {
        return 1;
    } else {
        return 2;
    }
}

long nextSensorRead() {
    return next_sensor_read_time;
}

void addToSensorRead(long millies) {
    next_sensor_read_time = millies + 500;
}