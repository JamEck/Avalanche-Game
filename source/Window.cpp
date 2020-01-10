#include "Window.hpp"

void initSDL(){
    if(!SDL_WasInit(SDL_INIT_EVERYTHING)){
        if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
            printf("Could Not Initialize SDL: %s\n", SDL_GetError());
            exit(0);
        }
    }
}

Color::Color(){
    abgr = 0xFFFFFFFF;
}
Color::Color(uint32_t color){
    abgr = color;
}

void PaneManager::setNumberOfPanes(int num){
    num = (num<1)?1:num;
    numOfPanes = num;
    panes.wipe();
    for(int i = 0; i < numOfPanes; i++){
        panes.append();
        panes[i].id = i;
    }
    setDims();
}

void PaneManager::setDims(){
    int i = 0;
    paneWidth = Window::width()/numOfPanes;
    for(auto iter = panes.getIter(); !iter.atEnd(); iter.next(), i++){
        Pane& p = iter.data();
        p.pos = {(float)(paneWidth*i), 0.0f};
        p.dim = {(float)(paneWidth),(float)(Window::height())};
        p.cam.pos = {0.0f, p.dim.y};
    }
}

int PaneManager::getPaneWidth(){
    return paneWidth;
}
int PaneManager::getNumOfPanes(){
    return numOfPanes;
}

void PaneManager::drawDividers(){
    foreach(panes){
        Pane& p = iter.data();
        if(p.pos.x){
            SDL_Rect r = {(int)p.pos.x-2, 0, 4, (int)Window::height()};
            SDL_SetRenderDrawColor(Window::getRen(), 0, 0, 0, 0xFF);
            SDL_RenderFillRect(Window::getRen(), &r);
        }
    }
}

Uint32 Window::mHeight;
Uint32 Window::mWidth;
int Window::mPosx;
int Window::mPosy;
SDL_Window*   Window::mWin;
SDL_Renderer* Window::mRen;
PaneManager Window::pm;
bool Window::success = Window::create();

void Window::free(){
    SDL_DestroyRenderer(Window::mRen); Window::mRen = nullptr;
    SDL_DestroyWindow  (Window::mWin); Window::mWin = nullptr;
}

bool Window::create(){
    initSDL();
    Window::mHeight = DEF_WIN_HEIGHT;
    Window::mWidth  = DEF_WIN_WIDTH;

    mPosx = 0; mPosy = 100;
    Window::mWin = SDL_CreateWindow("Avalanche v1.4", mPosx, mPosy, Window::mWidth, Window::mHeight, SDL_WINDOW_SHOWN);

    if(!Window::mWin){
        printf("Could Not Create Window: %s\n", SDL_GetError());
        return false;
    }

    Window::mRen = SDL_CreateRenderer(Window::mWin, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    if(!Window::mRen){
        printf("Could Not Create Renderer From Window: %s\n", SDL_GetError());
        return false;
    }

    Window::pm.setNumberOfPanes(1);

    clear(0x000000FF);

    return true;
}


void Window::clear(Color c){
    SDL_SetRenderDrawColor(Window::mRen, c.r, c.g, c.b, 0xFF);
    SDL_RenderClear(Window::mRen);
}

void Window::update(){
    if(pm.getNumOfPanes() > 1){
        pm.drawDividers();
    }
    SDL_RenderPresent(Window::mRen);
}

void Window::drawRect(int x, int y, int w, int h, Color c){
    SDL_SetRenderDrawColor(Window::mRen, c.r, c.g, c.b, 0xFF);
    SDL_Rect r = {x,y,w,h};
    SDL_RenderFillRect(Window::mRen, &r);

}

void Window::blitSurface(SDL_Surface* surf, int x, int y, float scale){
    if(surf == nullptr) return;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Window::mRen, surf);
    SDL_Rect r = {x, y, (int) (surf->w * scale), (int) (surf->h * scale)};
    SDL_RenderCopy(Window::mRen, tex, NULL, &r);
    SDL_DestroyTexture(tex);
}

void Window::blitTexture(SDL_Texture* tex, int x, int y, float scale){
    if(tex == nullptr) return;
    int w, h; SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    SDL_Rect r = {x, y, (int) (w * scale), (int) (h * scale)};
    SDL_RenderCopy(Window::mRen, tex, NULL, &r);
    SDL_DestroyTexture(tex);
}

SDL_Renderer* Window::getRen(){
    return Window::mRen;
}
SDL_Window*   Window::getWin(){
    return Window::mWin;
}

Uint32 Window::height(){
    return Window::mHeight;
}
Uint32 Window::width(){
    return mWidth;
}

Color Color::interpolate(Color& color1, Color& color2, float percent){
    if(percent < 0) percent = 0; else
        if(percent > 1) percent = 1; // clamp [0,1]
    Color ans;
    bool bigger[4];
    for(int i = 1; i < 4; i++){
        bigger[i] = (color1.channel[i] > color2.channel[i]);
        ans.channel[i] = (bigger[i])?
        (color1.channel[i] - color2.channel[i]):
        (color2.channel[i] - color1.channel[i]);
        ans.channel[i] = color1.channel[i] + ((bigger[i])?-ans.channel[i]:ans.channel[i])*percent;
    }
    ans.channel[0] = 0xFF;
    return ans;
}

Color Color::interpolate(Uint32 color1, Uint32 color2, float percent){
    Color p1 = color1; Color p2 = color2;
    return interpolate(p1, p2, percent);
}

void Window::resize(int height, int width){
    SDL_SetWindowSize(mWin, width, height);

    mWidth = width, mHeight = height;

    pm.setNumberOfPanes(pm.panes.len());
}