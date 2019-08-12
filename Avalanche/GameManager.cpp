#include "GameManager.hpp"

GameManager::GameManager(){
    fillBgcs();
    bm.bindWindow(win);
    unsigned int temp[] = {SDLK_w,SDLK_a,SDLK_s,SDLK_d,SDLK_SPACE};
    addKeyboard(temp);
    addPlayer(keyboards.back());
}

GameManager::~GameManager(){
    if(bgcs) delete [] bgcs;
}

void GameManager::update(){
    playerheight = maxHeightOfPlayers();
    getBackgroundColor();
    win.clear(background);
    em.update();
    
    if(em.p2Toggle.pressed()){
        toggle2Player();
    }
    
    bm.update(playerheight);
    
    updatePlayers();
    updateCameras();
    
    bm.display();
    displayPlayers();
    
    displayScore();
    
    win.update();
}

void GameManager::addKeyboard(unsigned int* bindings){
    keyboards.append();
    keyboards.back().setBindings(bindings);
}
void GameManager::remKeyboard(){
    keyboards.popEnd();
}

void GameManager::addPlayer(Keyboard& k){
    players.append();
    players.back().assignKeyboard(k);
    em.assignKeyboard(k, numOfPlayers);
    numOfPlayers++;
}

void GameManager::remPlayer(){
    players.popEnd();
    numOfPlayers--;
}

void GameManager::toggle2Player(){
    if(numOfPlayers < 2){
        unsigned int temp[] = {SDLK_UP,SDLK_LEFT,SDLK_DOWN,SDLK_RIGHT,SDLK_COMMA};
        addKeyboard(temp);
        addPlayer(keyboards.back());
        Player& p = players.back();
        p.defaultColor = 0x7F7F7FFF;
        p.color = 0x7F7F7FFF;
        p.pos = players.front().pos;

    }else{
        remPlayer();
        remKeyboard();
        em.removeKeyboard2();
    }
    win.pm.setNumberOfPanes(numOfPlayers);
    win.resize(DEF_WIN_HEIGHT,DEF_WIN_WIDTH*numOfPlayers);
    
}

float GameManager::maxHeightOfPlayers(){
    float ans = 0;
    foreach(players){
        if(iter.data().pos.y > ans){
            ans = iter.data().pos.y;
        }
    }
    return ans;
}

void GameManager::fillBgcs(){
    Uint32 colors[] = {0x5f6F9FFF, 0xAF5F00FF, 0x7F0000FF, 0x5F005FFF, 0x00006FFF, 0xFF};
    bgcolen = sizeof(colors)/4;
    
    if(bgcs) delete [] bgcs;
    bgcs = new Uint32[bgcolen];
    
    for(int i = 0; i < bgcolen; i++){
        bgcs[i] = colors[i];
    }
}

void GameManager::getBackgroundColor(){
    float height = playerheight;
    for(int i = 0; i < bgcolen-1; i++){
        if(height < tierHeight){
            background = Pixel::interpolate(bgcs[i], bgcs[i+1], height/tierHeight);
            break;
        }
        height -= tierHeight;
    }
}

void GameManager::updatePlayers(){
    foreach(players){
        iter.data().move(win);
        iter.data().update(bm);
    }
    deathHandling();
}

void GameManager::displayPlayers(){
    foreach(players){
        iter.data().display(win);
    }
    //displayPlayerInfo();
}

void GameManager::displayScore(){
    foreach2(players, win.pm.panes){
        Text::dispInt(win, iter1.data().highest, 10, iter2.data().pos.x + 10, 4, 0xFFFFFF00 - background.val);
    }
}

void GameManager::displayPlayerInfo(){
    foreach2(players, win.pm.panes){
        Player& p  = iter1.data();
        Pane& pane = iter2.data();
        
        Text::dispInt(win, p.pos.x, 40, pane.pos.x + 10, 3, 0xFFFFFF00 - background.val);
    }
}

void GameManager::updateCameras(){
    foreach2(win.pm.panes, players){
        iter1.data().pos.y = -iter2.data().pos.y + win.h/3;
    }
}

void GameManager::deathHandling(){
    int numOnGround = 0;
    foreach(players){
        Player& p = iter.data();
        if(p.dead){
            p.inair = true;
            p.color = 0x7F0000FF;
            if(p.pos.y <= 0){
                numOnGround++;
            }
        }
    }
    if(numOnGround == numOfPlayers){
        bm.reset();
        foreach(players){
            Player& p = iter.data();
            if(p.dead){
                p.klok.setAlarm(1.0);
                p.dead = false;
            }
        }
        
    }
    foreach(players){
        Player& p = iter.data();
        if(p.klok.checkAlarm()){
            p.color = p.defaultColor;
            p.highest = 0;
            p.klok.clearAlarm();
        }
    }
}