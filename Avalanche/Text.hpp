#ifndef Text_hpp
#define Text_hpp

#include "Window.hpp"
#include "stdio.h"
#include <vector>

class Text{
private:
    static Text* t;
    Text();
    static std::string path;
    
public:
    static std::vector<SDL_Surface*> img;
    ~Text();
    
    static char letterDim;
    
    static int charMap(char);
    void loadImgs();
    
    static void dispText(Window& win, std::string&  str, int posy, int posx, float scale, Uint32 color = 0xFF);
    static void dispText(Window& win, std::string&& str, int posy, int posx, float scale, Uint32 color = 0xFF);
    static void dispInt (Window& win, int number, int posy, int posx, float scale, Uint32 color = 0xFF);
    
    int test(int);
    static Text* get();
};



#endif /* Text_hpp */
