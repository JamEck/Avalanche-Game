#ifndef Player_hpp
#define Player_hpp

#include <iostream>
#include "BlockManager.hpp"
#include "Timer.hpp"

class Player : public Block{
private:
    URDL onedge;
    bool ffall;
    Keyboard* k = nullptr;

public:
    Pixel defaultColor = 0xFFFFFFFF;
    int highest = 0;
    Timer klok;
    bool dead;
    Player();
    void wrapPos(Window&);
    void move(Window&);
    
    void groundCollide(Block& lava);
    bool collide(BlockManager&);
    
    void checkHighest();
    void update(BlockManager&);

    void assignKeyboard(Keyboard& k);
    void platformingMove();
};


#endif 
