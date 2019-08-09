#include "Keyboard.hpp"


Keyboard::Keyboard(){}
    
void Keyboard::update(){
    for(int i = 0; i < TOTAL; i++){
        keys[i].update();
    }
}

void Keyboard::setBindings(unsigned int *bind){
    for(int i = 0; i < TOTAL; i++){
        bindings[i] = bind[i];
    }
}
unsigned int Keyboard::getBinding(int n){
    return bindings[n];
}

bool Keyboard::up(){
    return keys[K::UP].down && !keys[K::DOWN].down;
}
bool Keyboard::left(){
    return keys[K::LEFT].down && !keys[K::RIGHT].down;
}
bool Keyboard::down(){
    return keys[K::DOWN].down && !keys[K::UP].down;
}
bool Keyboard::right(){
    return keys[K::RIGHT].down && !keys[K::LEFT].down;
}
bool Keyboard::no_x(){
    return !keys[K::LEFT].down && !keys[K::RIGHT].down;
}
bool Keyboard::no_y(){
    return !keys[K::UP].down && !keys[K::DOWN].down;
}

Button& Keyboard::getKey(KeyCode k){
    return keys[k];
}
Button& Keyboard::getKey(int n){
    return keys[n];
}

Button& Keyboard::operator[](KeyCode k){
    return keys[k];
}