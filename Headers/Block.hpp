#ifndef Block_hpp
#define Block_hpp

#include <iostream>
#include "Entity.hpp"
#include "Window.hpp"
#include "Keyboard.hpp"

class Block : public Entity{
protected:
    SDL_Rect rect;
public:
    enum URDL{UP, RIGHT, DOWN, LEFT};

    Color color;
    int w, h;
    
    Block(int size = 10);
    Block(Block& inp);
    Block(Block&& inp);

    void copy(Block& inp);
    void copy(Block&& inp);
    
    void operator= (Block& inp);
    void operator= (Block&& inp);
    
    float left();
    float right();
    float top();
    float bottom();
    
    vec2 topleft    ();
    vec2 topright   ();
    vec2 bottomleft ();
    vec2 bottomright();
    
    vec2 center();
    
    bool checkCollide(Block& other);
    URDL getCollideDirection(Block& other);
    
    Block::URDL stopOnEdge(Block& b);

    void update();
    
    void display();
    void displayAbsolute();
    
};

#endif
