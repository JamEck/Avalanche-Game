#include "GameManager.hpp"

GameManager::GameManager(){
    fillBgcs();
    {
        unsigned int temp[] = {SDLK_w,SDLK_a,SDLK_s,SDLK_d,SDLK_SPACE};
        addKeyboard(temp);
    }
    addPlayer();
    {
        unsigned int temp[] = {SDLK_UP,SDLK_LEFT,SDLK_DOWN,SDLK_RIGHT,SDLK_COMMA};
        addKeyboard(temp);
    }

}

GameManager::~GameManager(){
    if(bgcs) delete [] bgcs;
}

void GameManager::update(){
    playerheight = maxHeightOfPlayers();
    getBackgroundColor();
    Window::clear(background);
    em.update();

    if(em.playerAdd.pressed()){
        addPlayer();
    }
    if(em.playerRem.pressed()){
        remPlayer();
    }
    
    bm.update(playerheight);
    
    updatePlayers();
    updateCameras();
    
    bm.display();
    displayPlayers();
    
    displayScore();
    
    Window::update();
}

void GameManager::addKeyboard(unsigned int* bindings){
    keyboards.append();
    keyboards.back().setBindings(bindings);
}
void GameManager::remKeyboard(){
    keyboards.popEnd();
}

void GameManager::addPlayer(){
    if(numOfPlayers >= playerLimit) return;

    // get unique greyscale color
    Uint8 grey = 0xFF * (1 - (float)numOfPlayers/playerLimit);
    Uint32 color = grey;
    for(int i = 0; i < 3; i++){
        color <<= 8;
        color |= grey;
    }
    color |= 0xFF;

    players.append();
    players.back().assignKeyboard(keyboards.back());
    em.assignKeyboard(keyboards.back(), numOfPlayers);
    numOfPlayers++;
    Player& p = players.back();
    p.defaultColor = color;
    p.color = color;
    p.pos = players.front().pos;

    Window::pm.setNumberOfPanes(numOfPlayers);
    Window::resize(DEF_WIN_HEIGHT,DEF_WIN_WIDTH*numOfPlayers);
}

void GameManager::remPlayer(){
    if(numOfPlayers <= 1) return;

    players.popEnd();
    numOfPlayers--;
    Window::resize(DEF_WIN_HEIGHT,DEF_WIN_WIDTH*numOfPlayers);
    Window::pm.setNumberOfPanes(numOfPlayers);
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
            background = Color::interpolate(bgcs[i], bgcs[i+1], height/tierHeight);
            break;
        }
        height -= tierHeight;
    }
}

void GameManager::updatePlayers(){
    foreach(players){
        iter.data().move();
        iter.data().update(bm);
    }
    deathHandling();
}

void GameManager::displayPlayers(){
    foreach(players){
        iter.data().display();
    }
    //displayPlayerInfo();
}

void GameManager::displayScore(float scale){
    Text::setColor(0xFFFFFF00 - background.abgr);
    Text::setScale(scale);
    int pw = Window::pm.getPaneWidth();
    foreach2(players, Window::pm.panes){
        Pane& p = iter2.data();
        Text::drawInt(iter1.data().highest, iter2.data().pos.x + pw - scale*5 - 10, 10);
    }
}

void GameManager::displayPlayerInfo(){
    foreach2(players, Window::pm.panes){
        Player& p  = iter1.data();
        Pane& pane = iter2.data();

        Text::setScale(3);
        Text::setColor(0xFFFFFF00 - background.abgr);
        Text::drawInt(p.pos.x, 40, pane.pos.x + 10);
    }
}

void GameManager::updateCameras(){
    foreach2(Window::pm.panes, players){
        iter1.data().pos.y = -iter2.data().pos.y + Window::height()/3;
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