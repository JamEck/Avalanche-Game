#include "Entity.hpp"

void Entity::applyAcc(){
    vel += acc;
}

void Entity::applyVel(){
    pos += vel;
}
void Entity::applyFric(bool hori, bool vert){
    if(hori){
        vel.x *= inair? props.airdrag : props.friction;
    }
    if(vert){
        vel.y *= inair? props.airdrag : props.friction;
    }
}
void Entity::applyGrav(){
    acc.y = -props.grav;
    applyAcc();
}
void Entity::applyGrav(float intens){
    acc.y = -intens;
    applyAcc();
}

void Entity::land(float y){
    inair = false;
    canJump = true;
    pos.y = y;
    vel.y = 0;
}

void Entity::simpleMove(Keyboard& k){
    if(k.left() ) vel.x = -props.maxspeed;
    else
    if(k.right()) vel.x =  props.maxspeed;
    else          vel.x = 0;
    
    if(k.up()  ) vel.y =  props.maxspeed;
    else
    if(k.down()) vel.y = -props.maxspeed;
    else         vel.y = 0;

    applyAcc(); // in case theres an acceleration loaded
}

void Entity::spaceMove(Keyboard& k){
    if(k.left() ) acc.x = -props.thrust;
    else
    if(k.right()) acc.x =  props.thrust;
    else          acc.x = 0;
    
    if(k.up()  ) acc.y =  props.thrust;
    else
    if(k.down()) acc.y = -props.thrust;
    else         acc.y = 0;

    applyAcc();
}

void Entity::momentumMove(Keyboard& k){
    spaceMove(k);
    applyFric();
    vel.clamp(props.maxspeed);
}

void Entity::platformingMove(Keyboard& k){
    if(k.left() ) acc.x = inair ? -props.airThrust : -props.thrust;
    else
    if(k.right()) acc.x = inair ?  props.airThrust :  props.thrust;
    else          acc.x = 0;
    applyAcc();
    if(inair){
        applyGrav();
    }
    applyFric(k.no_x(), false);
    
    if((!inair || canJump) && k[K::JUMP].pressed()){
        vel.y = props.jumpSpeed;
        inair = true;
        canJump = false;
    }
    
    if(inair){
        vel.clamp(props.aerialMaxspeed, -1);
    }else{
        vel.clamp(props.maxspeed);
    }
    
}

void Entity::inputMove(Keyboard& k, MovementType type){
    switch(type){
        case SIMPLE:
            simpleMove(k);
            break;
        case SPACE:
            spaceMove(k);
            break;
        case MOMENTUM:
            momentumMove(k);
            break;
        case PLATFORMING:
            platformingMove(k);
            break;
    }
}

void Entity::update(){
    applyVel();
}
