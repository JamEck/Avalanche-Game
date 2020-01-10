#ifndef BlockManager_hpp
#define BlockManager_hpp

#include <stdio.h>
#include "Block.hpp"
#include "Window.hpp"
#include "FpsLimiter.hpp"
#include "List.hpp"

class BlockManager{
private:
//    struct BlockNode{
//        Block b;
//        BlockNode* ptr;
//    };
    
    FpsLimiter bps;

    List<Block> falling;
    List<Block> grounded;
    
    int highest = 0;

    Block ground;
    float lavaspeed;
public:
    Block lava;
    
    BlockManager();
    ~BlockManager();

    
    void spawnBlock(int spawnHeight);
    
    void land(Block& b, float y);
    
    void checkGroundCollide();
    void checkCollide();

    
    void update(int spawnHeight);
    void display();
    
    void reset();
    
    List<Block>& getFalling();
    List<Block>& getGrounded();
};

#endif /* BlockManager_hpp */
