#include "PlayingField.h"
#include <iostream>

PlayingField::PlayingField(int width, int height) : width(width), height(height), area(width*height, Cell(CellValue::EMPTY)){}

bool PlayingField::checkCells(int x, int y, int length, enum Layout layout, bool isEnemyPlacing){
  try{
    if (x<0 || y<0 || y>=height || x>=width || (layout == HORIZONTAL && x+length>width) || (layout == VERTICAL && y+length>height)){
      throw GoingOutOfBordersException("You are placing the ship out of borders. ", width, height);
    }
    if (layout == HORIZONTAL){
      for (int index = std::max(0, x-1); index<=std::min(width-1, x+length); index++){
        for (int count = std::max(0, y-1); count<=std::min(height-1, y+1); count++){
          if (area[index+count*width].getShip() != nullptr){
            throw InсorrectShipPositioningException("There is already a ship in this area. You can't put it at ", x, y);
          }
        }
      }
    }else{
      for (int count = std::max(0, y-1); count<=std::min(height-1, y+length); count++){
        for (int index = std::max(0, x-1); index<=std::min(width-1, x+1); index++){
          if (area[index+count*width].getShip() != nullptr){
            throw InсorrectShipPositioningException("There is already a ship in this area. You can't put it at ", x, y);
          }
        }
      }
    }
  }catch (GoingOutOfBordersException& exception){
    if (isEnemyPlacing == false){
      std::cerr << exception.what() << "Width - "<< exception.getWidth() << " and height - " << exception.getWidth() << std::endl;
    }
    return false;
  }catch(InсorrectShipPositioningException& exception){
    if (isEnemyPlacing == false){
      std::cerr << exception.what() << exception.getX() << ' ' << exception.getY() << std::endl;
    }
    return false;
  }
  return true;
}

bool PlayingField::placeShip(Ship* ship, Layout layout, int x, int y, bool isEnemyPlacing){
  try{
    int length = ship->getLength();
    if (!(checkCells(x, y, length, layout, isEnemyPlacing))){
      return false;
    }
    if (layout != HORIZONTAL && layout != VERTICAL){
      throw InсorrectShipLayoutException("Ship layout should be horizontal or vertical");
    }
    ship->setLayout(layout);
    if (layout == HORIZONTAL){
      for (int ind = x; ind<x+length; ind++){
        area[width*y+ind].setShipAndSegment(ship, ind-x);
        area[width*y+ind].setValue(SHIP);
      } 
    }else{
      for (int count = y; count<y+length; count++){
        area[width*count+x].setShipAndSegment(ship, count-y);
        area[width*count+x].setValue(SHIP);
      }
    }
  }catch(InсorrectShipLayoutException& exception){
    if (isEnemyPlacing == false){
      std::cerr << exception.what() << std::endl;
    }
    return false;
  }
  return true;
}

int PlayingField::getWidth() {
  return width;
}

int PlayingField::getHeight(){
  return height;
}

std::vector<Cell> PlayingField::getArea(){
  return area;
}

bool PlayingField::hitCell(int x, int y, bool isDoubleDamage, bool isEnemyHitting){
  try{
    if (x>=0 && x<width && y>=0 && y<height){
      Ship* ship = area[y*width+x].getShip();
      int segmentIndex = area[y*width+x].getSegmentIndex();
      if (ship!=nullptr){
        ship->hitSegment(segmentIndex);
        ship->getSegments()[segmentIndex]->setFlagHitByShelling(false);
      }else{
        area[y*width+x].setValue(EMPTYENEMY);
      }
      if (isDoubleDamage){
        hitCell(x,y,false, false);
      }
      return true;
    }else{
      throw GoingOutOfBordersException("You are attacking out of borders. ", width, height);
    }
  }catch (GoingOutOfBordersException& exception){
    if (isEnemyHitting == false){
      std::cerr << exception.what() << "Field has width - " << exception.getWidth() << " and height - " << exception.getWidth() << std::endl;
    }
  }
  return false;
}

bool PlayingField::checkNotDestroyedShip(int x, int y){
  Ship* ship = area[y*width+x].getShip();
  if (ship != nullptr){
    int segmentIndex = area[y*width+x].getSegmentIndex();
    Segment* segment = ship->getSegments()[segmentIndex];
    if (segment->getValue() != DESTROYED){
      return true;
    }
  }
  return false;
}

PlayingField::PlayingField(const PlayingField& other): width(other.width), height(other.height), area(other.area) {}

PlayingField& PlayingField::operator=(const PlayingField& other) {
  if (this == &other) {
    return *this;
  }
  width = other.width;
  height = other.height;
  area = other.area;
  return *this;
}

PlayingField::PlayingField(PlayingField&& other) noexcept : width(other.width), height(other.height), area(std::move(other.area)) {
  other.width = 0;
  other.height = 0;
}

PlayingField& PlayingField::operator=(PlayingField&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  width = other.width;
  height = other.height;
  area = std::move(other.area);
  other.width = 0;
  other.height = 0;

  return *this;
}

json PlayingField::toJson() const {
  json jsonFile;
  jsonFile["width"] = width;
  jsonFile["height"] = height;
  for (int i = 0; i < height*width; ++i) {
    Cell cell = area[i];
    vector<int> jsonCell;
    jsonCell.push_back(cell.getValue());
    jsonFile["cellValues"].push_back(cell.getValue());
    Ship* ship = cell.getShip();
    if (ship != nullptr){
      int segmentIndex = cell.getSegmentIndex();
      std::vector<int> jsonShip; 
      if (segmentIndex == 0){
        jsonShip.push_back(i);
        Layout shipLayout = ship->getLayout();
        int shipLength = ship->getLength();
        jsonShip.push_back(shipLength);
        jsonShip.push_back(shipLayout);
        vector<Segment*>& segments = ship->getSegments();
        for (int i = 0; i<shipLength; i++){
          jsonShip.push_back(segments[i]->getValue());
          jsonShip.push_back(segments[i]->getFlagHitByShelling());
        }
        jsonFile["ships"].push_back(jsonShip);
      }
    }
  }
  return jsonFile;
}

PlayingField PlayingField::fromJsonField(const json& jsonFile) {
    PlayingField field(jsonFile["width"], jsonFile["height"]);
    return field;
}

void PlayingField::fromJsonCoordinates(const json& jsonFile) {
  for (int i = 0; i < height*width; i++) {
    area[i].setValue(jsonFile["cellValues"][i]);
  }
}