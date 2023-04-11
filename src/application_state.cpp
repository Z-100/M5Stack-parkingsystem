bool left_spot_occupied = false;
bool right_spot_occupied = false;

void switchLeftSpotOccupied() {
    left_spot_occupied = !left_spot_occupied;
}

void switchRightSpotOccupied() {
    right_spot_occupied = !right_spot_occupied;
}

bool leftSpotOccupied() {
    return left_spot_occupied;
}

bool rightSpotOccupied() {
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