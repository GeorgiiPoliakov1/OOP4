#ifndef PLAYING_FIELD
#define PLAYING_FIELD
#include <vector>
#include "../ships/Ship.h"
#include "Cell.h"
#include "../exceptions/Exceptions.h"
#include <iostream>
#include "../save/nlohmann/json.hpp"
using json = nlohmann::json;
class PlayingField {
private:
  int width, height;
  std::vector<Cell> area;
  bool checkCells(int x, int y, int length, enum Layout layout, bool isEnemyPlacing);
public:
  PlayingField(int width, int height);
  bool placeShip(Ship* ship, Layout layout, int x, int y, bool isEnemyPlacing);
  int getWidth();
  int getHeight();
  std::vector<Cell> getArea();
  bool hitCell(int x, int y, bool isDoubleDamage, bool isEnemyHitting);
  bool checkNotDestroyedShip(int x, int y);
  PlayingField(const PlayingField& other);
  PlayingField& operator=(const PlayingField& other);
  PlayingField(PlayingField&& other) noexcept;
  PlayingField& operator=(PlayingField&& other) noexcept;
  json toJson() const;
  PlayingField fromJsonField(const json& jsonFile);
  void fromJsonCoordinates(const json& jsonFile);
};
#endif