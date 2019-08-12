#include "Window.hpp"

Pixel::Pixel(Uint32 inp):val(inp){}
Pixel::Pixel(Uint8 r, Uint8 g, Uint8 b, Uint8 a):
                 r(r),    g(g),    b(b),    a(a){}
void Pixel::operator= (int      inp){val=inp;}
void Pixel::operator= (Uint32   inp){val=inp;}


Pixel Pixel::interpolate(Pixel& color1, Pixel& color2, float percent){
    if(percent < 0) percent = 0; else
        if(percent > 1) percent = 1; // clamp [0,1]
    Pixel ans;
    bool bigger[4];
    for(int i = 1; i < 4; i++){
        bigger[i] = (color1.abgr[i] > color2.abgr[i]);
        ans.abgr[i] = (bigger[i])?
        (color1.abgr[i] - color2.abgr[i]):
        (color2.abgr[i] - color1.abgr[i]);
        ans.abgr[i] = color1.abgr[i] + ((bigger[i])?-ans.abgr[i]:ans.abgr[i])*percent;
    }
    ans.abgr[0] = 0xFF;
    return ans;
}

Pixel Pixel::interpolate(Uint32 color1, Uint32 color2, float percent){
    Pixel p1 = color1; Pixel p2 = color2;
    return interpolate(p1, p2, percent);
}

std::ostream& operator<< (std::ostream& os, const Pixel& p){
    os
    << "0x"
    << std::setfill('0') << std::setw(8) << std::hex
    << p.val
    << std::endl;
    return os;
}

void PaneManager::attachToWindow(Window* window){
    win = window;
}


void PaneManager::setNumberOfPanes(int num){
    num = (num>2)?2:num;
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
    paneWidth = win->w/numOfPanes;
    for(auto iter = panes.getIter(); !iter.atEnd(); iter.next(), i++){
        Pane& p = iter.data();
        p.pos = {(float)(paneWidth*i), 0.0f};
        p.dim = {(float)(paneWidth),(float)(win->h)};
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
            SDL_Rect r = {(int)p.pos.x-2, 0, 4, win->h};
            SDL_SetRenderDrawColor(win->ren, 0, 0, 0, 0xFF);
            SDL_RenderFillRect(win->ren, &r);
        }
    }
}

Window::Window(int hpix, int wpix, int ypos, int xpos)
:h(hpix),  w(wpix),  y(ypos),  x(xpos){
    length = w*h;
    
    win  = SDL_CreateWindow("Avalanche v1.3",x,y,w,h,SDL_WINDOW_SHOWN);
    ren  = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(ren);
    
    surf = SDL_CreateRGBSurface(0, w, h, 32,REDMASK,GREENMASK,BLUEMASK,ALPHAMASK); // in case you want a surface to manip.
    pixels = (Uint32*)(surf->pixels);

    pm.attachToWindow(this);
    pm.setNumberOfPanes(1);

    if(win == nullptr){
        printf("Problem Creating Window.\n");
        printf("%s\n", SDL_GetError());
    }
    
    if (ren == nullptr){
        printf("Problem Creating Renderer.\n");
        printf("%s\n", SDL_GetError());
    }
    
    if(surf == nullptr){
        printf("Problem Getting Window Surface.\n");
        printf("%s", SDL_GetError());
    }
    
    if(!win || !ren || !surf){
        win  = nullptr;
        ren  = nullptr;
        surf = nullptr;
    }
    
//    cam.pos = {0.0, (float)h};
}

void Window::resize(int height, int width){
    x -= (width - w)/2;
    SDL_SetWindowPosition(win, x, y);
    SDL_SetWindowSize(win, width, height);
    
    w = width, h = height;
    SDL_FreeSurface(surf);
    surf = SDL_CreateRGBSurface(0, w, h, 32,REDMASK,GREENMASK,BLUEMASK,ALPHAMASK); // in case you want a surface to manip.

    pm.attachToWindow(this);
    pm.setNumberOfPanes(pm.panes.len());
}

Window::~Window(){
    SDL_DestroyRenderer(ren);
    SDL_FreeSurface(surf);
    SDL_DestroyWindow(win);
}

void Window::clear(Pixel p){
    SDL_SetRenderDrawColor(ren, p.r, p.g, p.b, p.a);
    SDL_RenderClear(ren);
}
void Window::clear(Uint32 color){
    Pixel p(color);
    clear(p);
}

void Window::blit(SDL_Surface* surf, int y, int x, float scale, Uint32 colorMod){
    
    
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren,surf);
    
    {
        colorMod |= 0xFF;
        Uint8* c = (Uint8*)&colorMod;
        SDL_SetTextureColorMod(tex, c[3], c[2], c[1]);
    }
    
    if(tex == nullptr){
        printf("Could Not Generate Texture.\n");
        return;
    }
    
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surf->w*scale;
    rect.h = surf->h*scale;
    
    SDL_RenderCopy(ren, tex, NULL, &rect);
    SDL_DestroyTexture(tex);
}

bool Window::applyPixel(int row, int col, Uint32 color){
    int ind;
    if(col < w && col >= 0 && row < h && row >= 0){
        ind = row * w + col;
        pixels[ind] = color;
        return true;
    }
    return false;
}

int clamp(int inp, int min, int max){
    if(inp < min) inp = min;
    if(inp > max) inp = max;
    return inp;
}

void Window::drawLine(int x1, int y1, int x2, int y2, Uint32 color){
    float slope = 0;    
    if(x1 != x2 && y1 != y2){
        slope = (y2 - y1)/(float)(x2 - x1);
        if(slope*slope>1){
            int uppery = (y2>y1)?y2:y1;
            int lowery = (y2>y1)?y1:y2;
            uppery = clamp(uppery, 0, h);
            lowery = clamp(lowery, 0, h);
            
            for(int y = lowery, x; y < uppery; y++){
                x = (y - y1)/slope + x1;
                applyPixel(y, x, color);
            }
        }else{
            int upperx = (x2>x1)?x2:x1;
            int lowerx = (x2>x1)?x1:x2;
            upperx = clamp(upperx, 0, w);
            lowerx = clamp(lowerx, 0, w);
            
            for(int x = lowerx, y; x < upperx; x++){
                y = (x - x1)*slope + y1;
                applyPixel(y, x, color);
            }
        }
    }

    if(x1 == x2 && y1 == y2){
        return;
    }
    if(y1 == y2){
        int upperx = (x2>x1)?x2:x1;
        int lowerx = (x2>x1)?x1:x2;
        upperx = clamp(upperx, 0, w);
        lowerx = clamp(lowerx, 0, w);

        for(int x = lowerx; x < upperx; x++)
            applyPixel(y1, x, color);
        return;
    }
    if(x1 == x2){
        int uppery = (y2>y1)?y2:y1;
        int lowery = (y2>y1)?y1:y2;
        uppery = clamp(uppery, 0, h);
        lowery = clamp(lowery, 0, h);

        for(int y = lowery; y < uppery; y++)
            applyPixel(y, x1, color);
        return;
    }
    

}


void Window::update(){
    if(pm.getNumOfPanes() > 1){
        pm.drawDividers();
    }
    blit(surf, 0, 0);
    SDL_RenderPresent(ren);
    SDL_FillRect(surf, nullptr, 0x0);
}
