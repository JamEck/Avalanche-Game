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
    for(auto iter = players.getIter(); !iter.atEnd(); iter.next()){
        if(iter.data().pos.y > ans){
            ans = iter.data().pos.y;
        }
    }
    return ans;
}

void GameManager::fillBgcs(){
    Uint32 colors[] = {0x7F4411FF, 0x7F5F00FF, 0x7F0000FF, 0x7F007FFF, 0x00007FFF, 0xFF};
    int num = sizeof(colors)/4;
    
    if(bgcs) delete [] bgcs;
    bgcs = new Uint32[num];
    
    for(int i = 0; i < num; i++){
        bgcs[i] = colors[i];
    }
}

void GameManager::getBackgroundColor(){
    if(playerheight < tierHeight){
        background = Pixel::interpolate(bgcs[0], bgcs[1], playerheight/tierHeight);
    }else
    if(playerheight < tierHeight*2){
        background = Pixel::interpolate(bgcs[1], bgcs[2], (playerheight-tierHeight)/tierHeight);
    }else
    if(playerheight < tierHeight*3){
        background = Pixel::interpolate(bgcs[2], bgcs[3], (playerheight-tierHeight*2)/tierHeight);
    }else
    if(playerheight < tierHeight*4){
        background = Pixel::interpolate(bgcs[3], bgcs[4], (playerheight-tierHeight*3)/tierHeight);
    }else
    if(playerheight < tierHeight*5){
        background = Pixel::interpolate(bgcs[4], bgcs[5], (playerheight-tierHeight*4)/tierHeight);
    }
}

void GameManager::updatePlayers(){
    for(auto iter = players.getIter(); !iter.atEnd(); iter.next()){
        iter.data().move(win);
        iter.data().update(bm);
    }
    deathHandling();
}

void GameManager::displayPlayers(){
    for(auto iter = players.getIter(); !iter.atEnd(); iter.next()){
        iter.data().display(win);
    }
}

void GameManager::displayScore(){
    auto paneIter   = win.pm.panes.getIter();
    auto playerIter =      players.getIter();
    
    for(; !(paneIter.atEnd() || playerIter.atEnd());
            paneIter.next()  ,  playerIter.next()){
        Player& player = playerIter.data();
        Pane&   pane   =   paneIter.data();
        
        Text::dispInt(win, player.highest, 10, pane.pos.x + 10, 4, 0xFFFFFF00 - background.val);
    }
}


void GameManager::updateCameras(){
    auto piter = players.getIter();
    for(auto iter = win.pm.panes.getIter();
        !iter.atEnd() && !piter.atEnd();
        iter.next(), piter.next()){
        
        iter.data().pos.y = -piter.data().pos.y + win.h/3;
    }
}

void GameManager::deathHandling(){
    int numOnGround = 0;
    for(auto iter = players.getIter(); !iter.atEnd(); iter.next()){
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
        for(auto iter = players.getIter(); !iter.atEnd(); iter.next()){
            Player& p = iter.data();
            if(p.dead){
                p.klok.setAlarm(1.0);
                p.dead = false;
            }
        }
        
    }
    for(auto iter = players.getIter(); !iter.atEnd(); iter.next()){
        Player& p = iter.data();
        if(p.klok.checkAlarm()){
            p.color = p.defaultColor;
            p.highest = 0;
            p.klok.clearAlarm();
        }
    }
}