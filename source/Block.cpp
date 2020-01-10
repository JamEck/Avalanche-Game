#include "Block.hpp"

Block::Block(int size){
    pos.x  = 0; pos.y  = 0;
    rect.x = 0; rect.y = 0;
         w = size;   h = size;
    rect.w = w; rect.h = h;
    color  = 0xffffffff;
}

Block::Block(Block& inp){
    copy(inp);
}
Block::Block(Block&& inp){
    copy(inp);
}

void Block::operator= (Block& inp){
    copy(inp);
}
void Block::operator= (Block&& inp){
    copy(inp);
}

float Block::left  (){return pos.x    ;}
float Block::right (){return pos.x + w;}
float Block::bottom(){return pos.y    ;}
float Block::top   (){return pos.y + h;}

vec2 Block::topleft    (){return vec2(left (), top());}
vec2 Block::topright   (){return vec2(right(), top());}
vec2 Block::bottomleft (){return vec2(left (), bottom());}
vec2 Block::bottomright(){return vec2(right(), bottom());}

vec2 Block::center(){return vec2((left()+right())/2, (top()+bottom())/2);}

void Block::copy(Block& inp){
    pos .x = inp.pos .x; pos .y = inp.pos .y;
    rect.x = inp.rect.x; rect.y = inp.rect.y;
    rect.w = inp.rect.w; rect.h = inp.rect.h;
    color = inp.color;
    w = inp.w;
    h = inp.h;
}

void Block::copy(Block&& inp){
    copy(inp);
}

void Block::update(){
    applyVel();
}

bool Block::checkCollide(Block& other){
    if((right() > other.left() ) &&
       (left()  < other.right())){ // horizontal overlap
        if((top()    > other.bottom()) &&
           (bottom() < other.top()   )){ //vertical overlap
            return true;
        }
    }
    return false;
}

Block::URDL Block::getCollideDirection(Block& other){
    vec2 cenDisp = other.center() - center();
    bool xneg = cenDisp.x<0;
    bool yneg = cenDisp.y<0;
    cenDisp = cenDisp.abs();
    
    if(cenDisp.x > cenDisp.y)
        return xneg? RIGHT:LEFT;
    return yneg? UP:DOWN;
}

Block::URDL Block::stopOnEdge(Block& b){
    URDL side = getCollideDirection(b);
    switch(side){
        case UP:
            pos.x -= vel.x/2;
            vel.y = b.vel.y;
            acc = {0,0};
            pos.y = b.top()-0.5;
            canJump = true;
            inair = false;
            return UP;
        case RIGHT:
            pos.y -= vel.y/2;
            vel.x = 0;
            vel.y += ((b.vel.y-0.5) - vel.y)*0.1;
            acc = {0,0};
            pos.x = b.right();
            canJump = true;
            return RIGHT;
        case DOWN:
            pos.x -= vel.x/2;
            vel.y = b.vel.y-1;
            acc = {0,0};
            pos.y = b.bottom() - h + 0.5;
            return DOWN;
        case LEFT:
            pos.y -= vel.y/2;
            vel.x = 0;
            vel.y += ((b.vel.y-0.5) - vel.y)*0.1;
            acc = {0,0};
            pos.x = b.left() - w;
            canJump = true;
            return LEFT;
    }
}

void Block::display(){
    int pw = Window::pm.getPaneWidth();
    foreach(Window::pm.panes){
        Pane& p = iter.data();

        rect.x =  pos.x + p.pos.x - p.cam.pos.x;
        rect.y = -pos.y - p.pos.y + p.cam.pos.y;

        rect.w =  w;
        if(pos.x < 0){
            if(pos.x > - w){
                rect.w  = w + pos.x;
                rect.x -= pos.x;
            }else{
                rect.w = 0;
            }
        }else
        if (right() > pw){
            if(pos.x < pw){
                rect.w = pw - pos.x;
            }else{
                rect.w = 0;
            }
        }
        rect.h = -h;
    
        SDL_SetRenderDrawColor(Window::getRen(),
            color.r, color.g, color.b, color.a
        );
        SDL_RenderFillRect(Window::getRen(), &rect);
    }
    
}

void Block::displayAbsolute(){
    rect.w = w;
    rect.h = h;
    rect.x = pos.x;
    rect.y = pos.y;

    SDL_SetRenderDrawColor(Window::getRen(),color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(Window::getRen(), &rect);
}
