#ifndef SHIP_CLASS
#define SHIP_CLASS
#include <vector>
#include "Segment.h"
enum Layout{
  HORIZONTAL = 0,
  VERTICAL = 1,
};

class Ship{
 public:
  Ship(int length, enum Layout layout);
  int getLength();
  enum Layout getLayout();
  void setLayout(Layout newLayout);
  void setSegments(std::vector<Segment*> newSegments);
  std::vector<Segment*>& getSegments();
  bool hitSegment(int index);
  bool isDestroyed();
 private:
  int length;
  enum Layout layout;
  std::vector<Segment*> segments;
};
#endif