#include "EventManager.hpp"


EventManager::EventManager(){
    pk1 = nullptr;
    pk2 = nullptr;
}
EventManager::~EventManager(){
    pk1 = nullptr;
    pk2 = nullptr;
}

void EventManager::assignKeyboard(Keyboard& k, int id){
    id = (id > 0)?1:0;
    if(id == 0){pk1 = &k; return;}
    if(id == 1){pk2 = &k; return;}
}

bool EventManager::updateKey(SDL_Event* e, Keyboard* k, bool press){
    for(int i = 0; i < K::TOTAL; i++){
        if(e->key.keysym.sym == k->getBinding(i)){
            k->getKey(i).down = press;
            return true;
        }
    }
    return false;
}

void EventManager::removeKeyboard2(){
    pk2 = nullptr;
}


void EventManager::update(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            quit = true;
            break;
        }
        if(e.type == SDL_KEYDOWN){
            if(e.key.keysym.sym == SDLK_ESCAPE){
                quit = true;
                break;
            }
            if(e.key.keysym.sym == SDLK_1){
                playerRem.down = true;
                break;
            }else
            if(e.key.keysym.sym == SDLK_2){
                playerAdd.down = true;
                break;
            }
            
            // logical operators used for control flow            
            pk1 && !updateKey(&e, pk1, true) &&
            pk2 &&  updateKey(&e, pk2, true);
            
        }
        if(e.type == SDL_KEYUP){
            if(e.key.keysym.sym == SDLK_1){
                playerRem.down = false;
                break;
            }else
            if(e.key.keysym.sym == SDLK_2){
                playerAdd.down = false;
                break;
            }
            
            pk1 && !updateKey(&e, pk1, false) &&
            pk2 &&  updateKey(&e, pk2, false);
        }
    }
    playerRem.update();
    playerAdd.update();
    if(pk1) pk1->update();
    if(pk2) pk2->update();
}