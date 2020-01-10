#ifndef Window_hpp
#define Window_hpp

#include "SDL2.hpp"
#include <stdio.h>
#include "Utils.hpp"
#include "Camera.hpp"
#include "List.hpp"

#ifdef __APPLE__
#define DEF_WIN_WIDTH  640
#define DEF_WIN_HEIGHT 840
#else
#define DEF_WIN_WIDTH  960
#define DEF_WIN_HEIGHT 1280
#endif

extern void initSDL();

union Color{
    uint32_t abgr;
    uint8_t channel[4];
    struct{
        uint8_t a;
        uint8_t b;
        uint8_t g;
        uint8_t r;
    };

    Color();
    Color(uint32_t Color);
    static Color interpolate(Color&, Color&, float);
    static Color interpolate(Uint32, Uint32, float);
};

struct Pane{
    Camera cam;
    vec2 pos;
    vec2 dim;
    int id;
};

class PaneManager{
    int numOfPanes;
    int paneWidth;
public:
    List<Pane> panes;

    void setNumberOfPanes(int num);
    void setDims();
    int  getPaneWidth();
    int  getNumOfPanes();
    void drawDividers();
};

class Window{
private:
    static Uint32 mHeight;
    static Uint32 mWidth;
    static SDL_Window*   mWin;
    static SDL_Renderer* mRen;
    static bool success;
public:
    static bool create();
    static void clear(Color color);
    static void update();
    static void free();

    static PaneManager pm;

    static int mPosx, mPosy;

    static void drawRect(int x, int y, int w, int h, Color color);
    static void blitSurface(SDL_Surface* surf, int x, int y, float scale = 1);
    static void blitTexture(SDL_Texture*  tex, int x, int y, float scale = 1);
    static void drawDividers();

    static void resize(int height, int width);

    static SDL_Renderer* getRen();
    static SDL_Window*   getWin();
    static Uint32 height();
    static Uint32 width ();
};

#endif /* Window_hpp */
