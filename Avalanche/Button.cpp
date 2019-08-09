#include "Button.hpp"

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