#include "Cell.h"
Cell::Cell(CellValue value) : value(value) {}

void Cell::setShipAndSegment(Ship* newShip, int newSegmentIndex) {
    ship = newShip;
    segmentIndex = newSegmentIndex;
}

void Cell::setValue(CellValue newValue) {
    value = newValue;
}

Ship* Cell::getShip() {
    return ship;
}

CellValue Cell::getValue() {
    return value;
}

int Cell::getSegmentIndex() {
    return segmentIndex;
}
