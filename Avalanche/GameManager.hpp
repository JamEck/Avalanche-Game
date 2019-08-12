#ifndef GameManager_hpp
#define GameManager_hpp

#include <iostream>

#include "vec2.hpp"
#include "FpsLimiter.hpp"

#include "List.hpp"
#include "Text.hpp"
#include "Window.hpp"

#include "BlockManager.hpp"
#include "EventManager.hpp"
#include "Player.hpp"



class GameManager{
public:
    Window win;
    BlockManager bm;
    List<Keyboard> keyboards;
    EventManager em;
    List<Player> players;
    FpsLimiter fps;

    int numOfPlayers = 0;
    float highScore = 0;
    
    int tierHeight = 5000;
    
    float playerheight = 0;
    
    Uint32* bgcs = nullptr;
    int bgcolen = 0;
    Pixel background;

    
//public:
    
    GameManager();
    ~GameManager();
    
    void update();
    
    void addKeyboard(unsigned int* bindings);
    void remKeyboard();
    void addPlayer(Keyboard& k);
    void remPlayer();
    void toggle2Player();
    
    float maxHeightOfPlayers();
    
    void fillBgcs();
    void getBackgroundColor();

    void updatePlayers();
    void displayPlayers();
    
    void updateCameras();
    
    void deathHandling();

    void displayScore();
    void displayPlayerInfo();
};

#endif /* GameManager_hpp */
