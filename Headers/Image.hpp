#ifndef Image_hpp
#define Image_hpp

#include <stdio.h>
#include <stdint.h>
#include "SDL2.hpp"
#include "Utils.hpp"
#include "vec2.hpp"
#include "Window.hpp"
#include "Path.hpp"

class Image{
public:
    struct ImageProps{
        int memManagerID = 0; // 0 - Image, 1 - Animation, 2 - Character
        Color tint;
        float scale;
        ImageProps();
        ImageProps(Uint32 color, float scale);
    };
private:
    SDL_Surface* surf = nullptr;
    Uint32 w, h;
    ImageProps* props = nullptr;

    void setup();

    void makeEmpty(Uint32 w, Uint32 h);
public:
    
    Image();
    Image(const char* path);
    Image(Path& path);
    Image(Uint32 w, Uint32 h);
    Image(SDL_Surface* img);
    ~Image();

    bool loadBMP(const char* path);
    bool loadBMP(Path& path);
    void free();
    void draw(int x, int y, bool fliplr = false);

    SDL_Surface* get();
    Uint32 width();
    Uint32 height();

    Color& getTint();
    void setTint(Color& inp);
    void setTint(Uint32 inp);

    float getScale();
    void setScale(float scale);
    Uint32* getPixels();

    void setProps(ImageProps* newProps);
};

#endif /* Image_hpp */
