#ifndef Entity_hpp
#define Entity_hpp

#include <stdio.h>
#include "vec2.hpp"
#include "Keyboard.hpp"

class Entity{
protected:
    void applyAcc();
    void applyVel();
    void applyFric(bool hori = true, bool vert = false);
    void applyGrav();
    void applyGrav(float intensity);
    
    void land(float y);
    
    void simpleMove(Keyboard& k);
    void spaceMove(Keyboard& k);
    void momentumMove(Keyboard& k);
    void platformingMove(Keyboard& k);

public:
    enum MovementType{SIMPLE, SPACE, MOMENTUM, PLATFORMING};
    
    vec2 pos;
    vec2 vel;
    vec2 acc;
    
    bool canJump;
    
    struct{
        float maxspeed = 2;
        float aerialMaxspeed = 1;
        float thrust;
        float airThrust;
        float friction;
        float airdrag;
        float grav = 1;
        float ffgrav = 1.5;
        float jumpSpeed;
    }props;
    
    bool inair;
    
    virtual void inputMove(Keyboard& k, MovementType type);
    virtual void update();
};

#endif /* Entity_hpp */
