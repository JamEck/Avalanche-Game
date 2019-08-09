#ifndef Window_hpp
#define Window_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include <iomanip>
#include "Camera.hpp"
#include "List.hpp"

#define DEF_WIN_WIDTH  480
#define DEF_WIN_HEIGHT 640

#define REDMASK   0xFF000000
#define GREENMASK 0x00FF0000
#define BLUEMASK  0x0000FF00
#define ALPHAMASK 0x000000FF

union Pixel{
    struct{
        Uint32 val;
    };
    struct{
        Uint8 a;
        Uint8 b;
        Uint8 g;
        Uint8 r;
    };
    struct{
        Uint8 abgr[4];
    };
    
    Pixel(Uint32 inp = 0xFF);
    Pixel(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xFF);
    void operator= (int     val);
    void operator= (Uint32   val);
    
    static Pixel interpolate(Pixel& pixel1, Pixel& pixel2, float percent);
    static Pixel interpolate(Uint32 color1, Uint32 color2, float percent);

    friend std::ostream& operator<< (std::ostream& os, const Pixel& p);
};

class Window;

struct Pane{
    Camera cam;
    vec2 pos;
    vec2 dim;
    int id;
};

class PaneManager{
    Window* win = nullptr;
    int numOfPanes;
    int paneWidth;
public:
    List<Pane> panes;

    void attachToWindow(Window* window);
    void setNumberOfPanes(int num);
    void setDims();
    int  getPaneWidth();
};

class Window{
public:
    SDL_Window* win = nullptr;
    SDL_Renderer *ren = nullptr;
    SDL_Surface *surf = nullptr;
    Uint32* pixels = nullptr;
    
    int x, y;
    int w, h;
    unsigned int length;
    
    float zs = 1.0; // distance from screen
    
    Window(int hpix = DEF_WIN_HEIGHT, int wpix = DEF_WIN_WIDTH, int ypos = 0, int xpos = 400);
    ~Window();
    
    void resize(int width, int height);
    
    PaneManager pm;
    
//    Camera cam;
    void clear(Uint32 color = 0x000000FF);
    void clear(Pixel  p     = 0x000000FF);
    void blit(SDL_Surface* surf, int y, int x, float scale = 1.0f, Uint32 colorMod = 0xFFFFFFFF);
    void update();
    bool applyPixel(int row, int col, Uint32 color);
    void drawLine(int x1, int y1, int x2, int y2, Uint32 color = 0xFFFFFFFF);
};


#endif /* Window_hpp */
