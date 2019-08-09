#include "Player.hpp"

Player::Player(){
    w = 20;
    h = w*3/2;
    props.maxspeed = 5;
    props.aerialMaxspeed = 5;
    props.jumpSpeed = 8;
    props.friction = 0.7;
    props.airdrag = 0.8;
    props.thrust = 1;
    props.airThrust = 0.3;
    props.grav = 0.12;
    props.ffgrav = 0.5;
    inair = false;
    ffall = false;
    pos = {100,-10};
    canJump = false;
    onedge = UP;
    dead = false;
}

void Player::wrapPos(Window& win){
    if(pos.x > win.pm.getPaneWidth()){
        pos.x = -w;
    }
    if(pos.x < -w){
        pos.x = win.pm.getPaneWidth();
    }
}

void Player::move(Window& win){
    platformingMove();
    wrapPos(win);
}

void Player::groundCollide(Block& lava){
    if(pos.y <= 0){
        land(0);
    }
    if(pos.y <= lava.pos.y){
        dead = true;
    }
}

bool Player::collide(BlockManager& bm){
    bool foundCollision = false;
    bool ceil = false;

    if(!dead){
        for(auto iter = bm.getFalling().getIter(); !iter.atEnd(); iter.next()){
            Block& b = iter.data();
            if(checkCollide(b)){
                onedge = stopOnEdge(b);
                foundCollision = true;
                if(onedge == UP){ inair = false;}
                if(onedge == DOWN){ ceil = true;}
            }
        }
        for(auto iter = bm.getGrounded().getIter(); !iter.atEnd(); iter.next()){
            Block& b = iter.data();
            if(checkCollide(b)){
                onedge = stopOnEdge(b);
                foundCollision = true;
                if(onedge == UP){ inair = false;}
                if(onedge == DOWN){ ceil = true;}
            }
        }
    }else{
        onedge = DOWN;
    }
    if(!foundCollision){inair = true;}
    
    groundCollide(bm.lava);
    
    if(!inair && ceil){
        dead = true;
    }
    return foundCollision;
}

void Player::platformingMove(){
    if(k->left() ) acc.x = inair ? -props.airThrust : -props.thrust;
    else
    if(k->right()) acc.x = inair ?  props.airThrust :  props.thrust;
    else          acc.x = 0;
    
    applyAcc();
    
    if(inair){
        if((*k)[K::DOWN].pressed() && !ffall){
            ffall = true;
        }
        (ffall)?applyGrav(props.ffgrav):applyGrav();
    }
    if(canJump){
        ffall = false;
    }
    
    applyFric(k->no_x(), false);
    
    if((!inair || canJump) && (*k)[K::JUMP].pressed()){
        if(onedge == LEFT){
            vel.x = -2;
        }else
        if(onedge == RIGHT){
            vel.x = 2;
        }
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

void Player::checkHighest(){
    if(pos.y > highest) highest = pos.y;
}

void Player::update(BlockManager& bm){
    applyVel();
    collide(bm);
    checkHighest();
}

void Player::assignKeyboard(Keyboard& keyboard){
    k = &keyboard;
}



