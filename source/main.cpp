#include <iostream>
#include <SDL.h>
#include "Window.hpp"
#include "BlockManager.hpp"
#include "EventManager.hpp"
#include "GameManager.hpp"
#include "vec2.hpp"
#include "FpsLimiter.hpp"
#include "Player.hpp"
#include "Text.hpp"

// v1.4

void cleanUp(){
    Window::free();
    SDL_Quit();
}

int main(int argc, char* argv[]){
    printf("Start of Game!\n");
    GameManager gm;
    while(!gm.em.quit){
        if(gm.fps.limit()){
            gm.update();
        }
    }
    cleanUp();
    return 0;
}