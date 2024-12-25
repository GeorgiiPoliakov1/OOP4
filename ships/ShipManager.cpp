#include "ShipManager.h"
#include <iostream>
ShipManager::ShipManager(int shipCount, std::vector<int> shipSizes):shipCount(shipCount), shipSizes(shipSizes){
  for (int index = 0; index<shipCount; index++){
    ships.push_back(new Ship(shipSizes[index], HORIZONTAL));
  }
}
std::vector<Ship*>& ShipManager::getShips() {
  return ships;
}

int ShipManager::getShipCount(){
  return shipCount;
}

void ShipManager::addShip(int length){
  ships.push_back(new Ship(length, HORIZONTAL));
}

bool ShipManager::isAllShipsDestroyed(){
  for (int index = 0; index<shipCount; index++){
    if (!ships[index]->isDestroyed()){
      return false;
    }
  }
  return true;
}

bool ShipManager::isShipWasDestroyed(){
  int destroyedShip = 0;
  for (int index = 0; index<shipCount; index++){
    if (ships[index]->isDestroyed()){
      destroyedShip++;
    }
  }
  if (destroyedShip!=destroyedShipCount){
    destroyedShipCount = destroyedShip;
    return true;
  }
  return false;
}

ShipManager& ShipManager::operator=(const ShipManager& other) {
  if (this == &other) {
    return *this;
  }
  ships = std::move(other.ships);
  shipSizes = other.shipSizes;
  shipCount = other.shipCount;
  destroyedShipCount = other.destroyedShipCount;
  return *this;
}
ShipManager::ShipManager(ShipManager&& other) noexcept : shipCount(other.shipCount), shipSizes(other.shipSizes), ships(std::move(other.ships)), destroyedShipCount(other.destroyedShipCount) {
}

ShipManager& ShipManager::operator=(ShipManager&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  ships = std::move(other.ships);
  shipSizes = other.shipSizes;
  shipCount = other.shipCount;
  destroyedShipCount = other.destroyedShipCount;
  return *this;
}
ShipManager::~ShipManager() {
  for (Ship* ship : ships) {
    delete ship;
  }
  ships.clear();
}

void ShipManager::fromJson(const json& jsonFile){
  std::vector<Ship*> newShips;
  for (int i = 0; i < jsonFile["ships"].size(); i++){
    Ship* ship = new Ship(jsonFile["ships"][i][1], jsonFile["ships"][i][2]); 
    std::vector<Segment*> newSegments;
    for (int ind = 3; ind < jsonFile["ships"][i].size(); ind+=2){
      Segment* segment = new Segment(jsonFile["ships"][i][ind]);
      if (jsonFile["ships"][i][ind+1]==1){
        segment->setFlagHitByShelling(true);
      }else{
        segment->setFlagHitByShelling(false);
      }
      newSegments.push_back(segment);
    }
    ship->setSegments(newSegments);
    newShips.push_back(ship);
  }
  ships = newShips;
}