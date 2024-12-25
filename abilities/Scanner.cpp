#include "Scanner.h"

bool Scanner::apply(PlayingField& field, ShipManager& manager, int x, int y) {
    int width = field.getWidth();
    int height = field.getHeight();
    try{
        if (x<width && y<height){
            for (int index = std::max(0, x); index<=std::min(width-1, x+1); index++){
                for (int count = std::max(0, y); count<=std::min(height-1, y+1); count++){
                    if (field.checkNotDestroyedShip(index, count)){
                        return true; 
                    }
                }
            }   
        }else{
            throw GoingOutOfBordersException("You are scanning out of borders. ", field.getWidth(), field.getHeight());
        }
    }catch(GoingOutOfBordersException& exception){
        std::cerr << exception.what() << "Field has width - " << exception.getWidth() << " and height - " << exception.getWidth() << std::endl;
    }
    return false;
}