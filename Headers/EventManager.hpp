#ifndef EventManager_hpp
#define EventManager_hpp

#include <stdio.h>
#include <SDL.h>
#include "Keyboard.hpp"

class EventManager{
private:
    Keyboard* pk1 = nullptr;
    Keyboard* pk2 = nullptr;
    //Mouse* pm;
    
    bool updateKey(SDL_Event* e, Keyboard* k, bool press);
public:
    bool quit = false;
    Button playerAdd;
    Button playerRem;
    EventManager();
    ~EventManager();
    
    void assignKeyboard(Keyboard& k, int id);
    void removeKeyboard2();
    
    void update();
};

#endif /* EventManager_hpp */
