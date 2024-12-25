#ifndef SEGMENT_H
#define SEGMENT_H

enum SegmentValue{
  INTACT = 2,
  DAMAGED = 1,
  DESTROYED = 0
};

class Segment {
public:
    Segment(SegmentValue value);
    SegmentValue getValue();
    bool getFlagHitByShelling();
    void setValue(SegmentValue newValue);
    void setFlagHitByShelling(bool state);
private:
    SegmentValue value;
    int segmentIndex = -1;
    bool flagHitByShelling = false;
};
#endif