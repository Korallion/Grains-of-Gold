#include "classes/Rectangle.h"

Rectangle::Rectangle(){
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

Rectangle::Rectangle(float x_pos, float y_pos, float width, float height){
    x = x_pos;
    y = y_pos;
    w = width;
    h = height;
}

Rectangle::~Rectangle(){

}