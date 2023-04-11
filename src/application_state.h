#ifndef APPLICATION_STATE_H_
#define APPLICATION_STATE_H_

bool isTopM5Stack();

void switchLeftSpotOccupied();

void switchRightSpotOccupied();

void switchLeftSpotUnOccupied();

void switchRightSpotUnOccupied();

bool isLeftSpotOccupied();

bool isRightSpotOccupied();

int numOfSpotsOccupied();

long nextSensorRead();

void addToSensorRead(long newSensorRead);

#endif