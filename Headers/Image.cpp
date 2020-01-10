#include "Image.hpp"

Image::ImageProps::ImageProps():
tint(0xFFFFFFFF),scale(1.0f){}

Image::ImageProps::ImageProps(Uint32 color, float _scale):
    tint(color),
    scale(_scale){}

void Image::setup(){
    free();
    w = 0; h = 0;
    surf = nullptr;
    props = new ImageProps();
}

Image::Image(){setup();}

Image::Image(const char* path){
    setup();
    loadBMP(path);
}
Image::Image(Path& path){
    setup();
    loadBMP(path);
}
Image::Image(Uint32 _w, Uint32 _h){
    makeEmpty(_w, _h);
    SDL_FillRect(surf, NULL, props->tint.abgr);
}

Image::Image(SDL_Surface* img){
    makeEmpty(img->w, img->h);
    if(img == nullptr) return;
    SDL_BlitSurface(img, NULL, surf, NULL);
    w = surf->w; h = surf->h;
}

Image::~Image(){
    free();
}

void Image::makeEmpty(Uint32 _w, Uint32 _h){
    setup();
    surf = SDL_CreateRGBSurface(
                                0, _w, _h, 32,
                                0xFF000000,
                                0x00FF0000,
                                0x0000FF00,
                                0x000000FF
                                );
    w = _w; h = _h;
}


bool Image::loadBMP(Path& path){
    setup();
    surf = SDL_LoadBMP(path.c_str());
    if(!surf){
        printf("Error Loading BMP Image: %s\n", path.c_str());
        return false;
    }
    w = surf->w; h = surf->h;
    return true;
}
bool Image::loadBMP(const char* _path){
    Path path(_path);
    return loadBMP(path);
}

void Image::free(){
    if(surf){
        SDL_FreeSurface(surf);
        surf = nullptr;
    }
    if(props){
        if(props->memManagerID == 0){
            delete props;
        }
        props = nullptr;
    }
}

void Image::draw(int x, int y, bool fliplr){
    if(surf == nullptr) return;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Window::getRen(), surf);
    SDL_Rect r = {x, y, (int) (w * props->scale), (int) (h * props->scale)};
    SDL_SetTextureColorMod(tex, props->tint.r, props->tint.g, props->tint.b);
    SDL_RenderCopyEx(Window::getRen(), tex, NULL, &r, 0, NULL, fliplr?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
    SDL_DestroyTexture(tex);
}

SDL_Surface* Image::get(){
    return surf;
}
uint32_t Image::width(){
    return w;
}
uint32_t Image::height(){
    return h;
}

Color& Image::getTint(){
    return props->tint;
}
void Image::setTint(Color& inp){
    props->tint.abgr = inp.abgr;
}
void Image::setTint(Uint32 inp){
    props->tint.abgr = inp;
}

float Image::getScale(){
    return props->scale;
}
void Image::setScale(float scale){
    props->scale = scale;
}
Uint32* Image::getPixels(){
    return (Uint32*)surf->pixels;
}

void Image::setProps(ImageProps* newProps){
    if(props) delete props;
    props = newProps;
}
