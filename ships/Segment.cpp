#include "Segment.h"
Segment::Segment(SegmentValue value) : value(value) {}

void Segment::setValue(SegmentValue newValue) {
    value = newValue;
}

void Segment::setFlagHitByShelling(bool state){
    flagHitByShelling = state;
}

SegmentValue Segment::getValue() {
    return value;
}

bool Segment::getFlagHitByShelling(){
    return flagHitByShelling;
}
