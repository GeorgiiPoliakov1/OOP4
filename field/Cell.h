#ifndef CELL
#define CELL
#include "../ships/Ship.h"

enum CellValue {
    UNKNOWN = '?',
    DEFEATED = '.',
    EMPTY = '~',
    EMPTYENEMY = '0',
    HIT = 'X',
    SHIP = '1'
};

class Cell {
public:
    Cell(CellValue value);
    Ship* getShip();
    CellValue getValue();
    int getSegmentIndex();
    void setShipAndSegment(Ship* newShip, int newSegmentIndex);
    void setValue(CellValue newValue);

private:
    CellValue value;
    Ship* ship = nullptr;
    int segmentIndex = -1;
    bool flagHitByShelling = false;
};
#endif