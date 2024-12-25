#ifndef SHIP_MANAGER
#define SHIP_MANAGER
#include <vector>
#include "Ship.h"
#include "../save/nlohmann/json.hpp"
using json = nlohmann::json;
class ShipManager{
 private:
  std::vector<Ship*> ships;
  std::vector<int> shipSizes;
  int shipCount;
  int destroyedShipCount = 0;

 public:
  ShipManager(int shipCount, std::vector<int> shipSizes);
  std::vector<Ship*>& getShips();
  int getShipCount();
  void addShip(int length);
  bool isShipWasDestroyed();
  bool isAllShipsDestroyed();
  ShipManager& operator=(const ShipManager& other);
  ShipManager& operator=(const ShipManager&& other);
  ShipManager(ShipManager&& other) noexcept;
  ShipManager& operator=(ShipManager&& other) noexcept;
  void fromJson(const json& jsonFile);
  ~ShipManager();
};
#endif