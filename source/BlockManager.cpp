#include "BlockManager.hpp"

#define fori(x) for(int i = 0; i < x; i++)
#define forj(x) for(int j = 0; j < x; j++)

BlockManager::BlockManager(){
    srand(time(NULL));
    bps.setTargetFps(4);
    reset();
}

BlockManager::~BlockManager(){
}

void BlockManager::spawnBlock(int spawnHeight){
    if(spawnHeight > highest){
        highest = spawnHeight;
    }
    
    falling.append();
    Block& b = falling.back();
    b.w = (rand()%2)?60:80;
    b.h = b.w;
    b.pos.x = rand() % (Window::pm.getPaneWidth() - b.w);
    b.pos.y = highest + Window::height();
    b.vel.y = -((rand()%20)/10.0+3);
    
    b.inair = true;
    
    for(int i = 1; i < 4; i++){ // skip alpha
        b.color.channel[i] = rand()%200 + 55;
    }
}

void BlockManager::land(Block &b, float y){
    b.inair = false;
    b.pos.y = y;
    b.vel = {0,0};
    b.acc = {0,0};
    grounded.append(b);
    falling.remove(&b);
    
    if(y > highest){
        highest = y;
    }
}

void BlockManager::checkGroundCollide(){
    auto iter = falling.getIter();
    while(!iter.atEnd()){
        Block& b = iter.data();
        iter.next();
        if(b.pos.y <= 0){
            land(b, 0.0f);
        }
    }
}

void BlockManager::checkCollide(){
    {
        auto iter_fall   = falling .getIter();
        auto iter_ground = grounded.getIter();
        
        while(!iter_fall.atEnd()){
            Block& fb = iter_fall.data();
            iter_fall.next();
            
            iter_ground.reset();
            while(!iter_ground.atEnd()){
                Block& gb = iter_ground.data();
                iter_ground.next();

                if(fb.checkCollide(gb)){
                    land(fb, gb.top());
                    break;
                    // break prevents this fb from
                    // checking against its copy
                    // newly added to the grounded list
                }
            }
        }
    }
    // check falling blocks against other
    // falling blocks to make sure they dont
    // overlap in the air
    {
        auto iter_fall1 = falling.getIter();
        
        while(!iter_fall1.atEnd()){
            Block& fb1 = iter_fall1.data();
            iter_fall1.next();
            
            auto iter_fall2 = iter_fall1;
            while(!iter_fall2.atEnd()){
                Block& fb2 = iter_fall2.data();
                iter_fall2.next();
                
                if(fb1.checkCollide(fb2)){
                    if(fb1.pos.y > fb2.pos.y){
                        fb1.pos.y = fb2.top();
                    }else{
                        fb2.pos.y = fb1.top();
                    }
                }
                
            }
            
        }
    }
}

void BlockManager::update(int spawnHeight){
    if(bps.limit()){
        spawnBlock(spawnHeight);
    }
    
    lava.pos.y += lavaspeed;
    
    for(auto iter = falling.getIter(); !iter.atEnd(); iter.next()){
        iter.data().update();
    }
    checkGroundCollide();
    checkCollide();
}

void BlockManager::display(){
    lava.display();
    ground.display();
    foreach(falling){
        iter.data().display();
    }
    foreach(grounded){
        iter.data().display();
    }
}

List<Block>& BlockManager::getFalling(){
    return falling;
}
List<Block>& BlockManager::getGrounded(){
    return grounded;
}


void BlockManager::reset(){
    highest = Window::height() + 10;
    falling .wipe();
    grounded.wipe();
    
    lavaspeed = 0.8;
    lava.pos = {0,-800};
    ground.pos = {0,0};
    
    lava.w   = Window::pm.getPaneWidth();
    ground.w = Window::pm.getPaneWidth()-10;
    
    lava.h   = -(int)Window::height()/2;
    ground.h = -(int)Window::height()*2/5;
    
    lava.color   = 0xFF3300FF; // red
    ground.color = 0x000000FF; // black
}

