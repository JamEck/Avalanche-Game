#include <iostream>
#include <SDL2/SDL.h>
#include "Window.hpp"
#include "BlockManager.hpp"
#include "EventManager.hpp"
#include "GameManager.hpp"
#include "vec2.hpp"
#include "FpsLimiter.hpp"
#include "Player.hpp"
#include "Text.hpp"

// v1.2

int main(){
    GameManager gm;
    while(!gm.em.quit){
        if(gm.fps.limit()){
            gm.update();
        }
    }
    SDL_Quit();
}