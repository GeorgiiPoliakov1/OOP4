#include "FieldDrawer.h"
FieldDrawer::FieldDrawer(){}
void FieldDrawer::printPlayingField(PlayingField field, bool isEnemyField){
  int height = field.getHeight();
  int width = field.getWidth();
  std::vector<Cell> area = field.getArea();
  if (isEnemyField){
    std::cout << ENEMYFIELD << std::endl << "   ";
  }else{
    std::cout << YOURFIELD << std::endl << "   ";
  }
  for (int i = 0; i<width; i++){
    std::cout << i << ' ' ;
  }
  std::cout << '\n' << "   ";
  for (int i = 0; i<width; i++){
    std::cout << '-' << ' ';
  }
  std::cout << std::endl;
  
  for (int str = 0; str<height; str++){
    std::cout << str << '|' << ' ';
    for (int ind = 0; ind<width; ind++){
      Ship* ship = area[str*height+ind].getShip();
      int segmentIndex = area[str*height+ind].getSegmentIndex();
      if (ship!=nullptr){
        Segment* segment = ship->getSegments()[segmentIndex];
        if (segment->getValue() == DAMAGED && !segment->getFlagHitByShelling()){
          std::cout << static_cast<char>(HIT) << ' ';
        }else if (segment->getValue() == DESTROYED && !segment->getFlagHitByShelling()){
          std::cout << static_cast<char>(DEFEATED) << ' ';
        }else if (area[str*height+ind].getValue() == EMPTYENEMY){
          std::cout << EMPTYENEMY << ' ';
        }else{
          if (isEnemyField){
            std::cout << static_cast<char>(UNKNOWN) << ' ';
          }else{
            std::cout << static_cast<char>(SHIP) << ' ';
          }
        }
      }else{
        if (area[str*height+ind].getValue() == EMPTYENEMY){
          std::cout << static_cast<char>(EMPTYENEMY) << ' ';
        }else if (isEnemyField){
          std::cout << static_cast<char>(UNKNOWN) << ' ';
        }else{
          std::cout << static_cast<char>(EMPTY) << ' ';
        }
      }
    }
    std::cout << std::endl;
  }
}