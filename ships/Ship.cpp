#include "Ship.h"

Ship::Ship(int length, enum Layout layout) : length(length), layout(layout) {
    for (int i = 0; i < length; i++){
        segments.push_back(new Segment(INTACT));
    }
}

int Ship::getLength() {
    return length;
}

enum Layout Ship::getLayout() {
    return layout;
}

void Ship::setLayout(Layout newLayout) {
    layout = newLayout;
}

std::vector<Segment*>& Ship::getSegments() {
    return segments;
}

void Ship::setSegments(std::vector<Segment*> newSegments){
    segments = newSegments;
}

bool Ship::hitSegment(int index) {
    if (segments[index]->getValue() == INTACT) {
        segments[index]->setValue(DAMAGED);
        return true;
    } else if (segments[index]->getValue() == DAMAGED) {
        segments[index]->setValue(DESTROYED);
        return true;
    }
    return false;
}

bool Ship::isDestroyed() {
    for (auto segment:segments){
        if (segment->getValue() != DESTROYED){
            return false;
        }
    }
    return true;
}