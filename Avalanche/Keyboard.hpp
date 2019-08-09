#ifndef Keyboard_hpp
#define Keyboard_hpp

#include <stdio.h>
#include "bool2.hpp"
#include "Button.hpp"

#define K Keyboard

class Keyboard{
public:
    enum KeyCode{
        UP,LEFT,DOWN,RIGHT,JUMP,TOTAL
    };

private:
    Button keys[TOTAL];
    unsigned int bindings[TOTAL];
public:
    
    Keyboard();
    
    bool up();
    bool left();
    bool down();
    bool right();
    bool no_x();
    bool no_y();
    
    void update();
    
    void setBindings(unsigned int* bind);
    unsigned int getBinding(int n);
    
    Button& getKey(KeyCode k);
    Button& getKey(int n);
    
    Button& operator[](KeyCode k);
};

#endif /* Keyboard_hpp */
