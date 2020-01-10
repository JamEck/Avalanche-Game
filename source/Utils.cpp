#include "Utils.hpp"

bool bool2::pop(bool inp){
    act = inp && !wait;
    wait = inp;
    return act;
}
bool bool2::output(){
    return act;
}
bool2::operator bool() {
    return act;
}


Button::Button(){
    release.pop(true);
}
void Button::update(){
    press.pop(down);
    release.pop(!down);
}
bool Button::pressed(){
    return press.output();
}
bool Button::released(){
    return release.output();
}
bool Button::triggered(){
    return press.output() || release.output();
}