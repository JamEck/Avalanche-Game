#include "Text.hpp"

char Text::letterDim = 0;
std::string Text::path = "../Resources/alphabet/";
std::vector<SDL_Surface*> Text::img = std::vector<SDL_Surface*>();
Text* Text::t = new Text();


Text::Text(){
    loadImgs();
}

Text::~Text(){
    for (int i = 0; i < 40; i++){
        delete [] Text::img[i];
    }
    delete [] t;
}

Text* Text::get(){
    return t;
}

int Text::test(int inp){
    return inp*2;
}

void Text::loadImgs(){
    Text::img.assign(40, 0);
    for(int i = 0; i < 10; i++){
        Text::img[i] = SDL_LoadBMP((Text::path + std::to_string(i) + ".bmp").c_str());
    }
    for(char c = 65, i = 10; c < 91; c++, i++){
        Text::img[i] = SDL_LoadBMP((Text::path + c + ".bmp").c_str());
    }
        
    Text::img[36] = SDL_LoadBMP((Text::path + "period.bmp").c_str());
    Text::img[37] = SDL_LoadBMP((Text::path + "fslash.bmp").c_str());
    Text::img[38] = SDL_LoadBMP((Text::path + "negative.bmp").c_str());
    Text::img[39] = SDL_LoadBMP((Text::path + "colon.bmp").c_str());

    Text::letterDim = Text::img[0]->w;
}

int Text::charMap(char inp){
    if(inp >= 'a' && inp <= 'z'){
        return inp - 'a' + 10;
    }else
    if (inp >= 'A' && inp <= 'Z'){
        return inp - 'A' + 10;
    }else
    if (inp >= '0' && inp <= '9'){
        return inp - '0';
    }else
    if(inp == '.'){
        return 36;
    }else
    if(inp == '/'){
        return 37;
    }else
    if(inp == '-'){
        return 38;
    }else{
    if(inp == ':'){
        return 39;
    }else
        return -1;
    }
}



void Text::dispText(Window& win, std::string& str, int posy, int posx, float scale, Uint32 color){
    int dx = (Text::letterDim+1)*scale;
    for(int i = 0, ind; str[i] && i < 100; i++){
        ind = charMap(str[i]);
        if(ind >= 0)
            win.blit(Text::img[ind], posy, posx + i*dx, scale, color);
    }
}
void Text::dispText(Window& win, std::string&& str, int posy, int posx, float scale, Uint32 color){
    dispText(win, str, posy, posx, scale, color);
}

void Text::dispInt(Window& win, int num, int posy, int posx, float scale, Uint32 color){
    std::string inp = std::to_string(num);
    if(inp[0] == '-') posx -= (Text::letterDim+1)*scale;
    
    dispText(win, inp, posy, posx, scale, color);
}