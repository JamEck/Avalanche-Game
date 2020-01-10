#ifndef Text_hpp
#define Text_hpp

#include <map>
#include "Image.hpp"
#include "Window.hpp"
#include <string>

#define TEXT_ASSETS_PATH "../../../Resources/alphabet/"

class Text{
public:
    static std::map<char, Image*> load();
    static std::map<char, Image*> letterMap;
    static Image::ImageProps* props;
    static void free();
public:
    static void drawLetter(char inp,          int x, int y);
    static void drawString(const char* inp,   int x, int y);
    static void drawString(std::string& inp,  int x, int y);
    static void drawInt   (int inp,           int x, int y);
    static void drawFloat (float inp,         int x, int y, int prec  = 2);
    static void drawHex   (unsigned int  inp, int x, int y, int bytes = 4);
    static void drawByte  (unsigned char inp, int x, int y);

    static void setScale(float scale);
    static void setColor(Uint32 color);
    static void setColor(Color& color);
};


#endif
