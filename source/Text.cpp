#include "Text.hpp"

Image::ImageProps* Text::props = new Image::ImageProps(0xFFFFFFFF, 1.0F);

std::map<char, Image*> Text::letterMap = Text::load();
std::map<char, Image*> Text::load(){

    const char  chars[] = {
        '0','1','2','3','4','5','6','7','8','9',
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        ':','-','/','.'
    };
    const char* paths[] = {
        "0","1","2","3","4","5","6","7","8","9",
        "A","B","C","D","E","F","G","H","I","J","K","L","M",
        "N","O","P","Q","R","S","T","U","V","W","X","Y","Z",
        "colon","dash","fslash","period"
    };

    std::map<char, Image*> m;

    char path[50]; // hopefully the name won't be longer than 30 ;)
    int max = sizeof(paths)/sizeof(const char*);
    for(int i = 0; i < max; i++){

        strcpy_s(path, TEXT_ASSETS_PATH); // start with text dir
        strcat_s(path, paths[i]);         // append image name
        strcat_s(path, ".bmp");           // append extention

        Image* surf = new Image(path);
        surf->setProps(Text::props);
        
        if(surf->get() == nullptr) printf("Could Not Find Text Asset File: %s\n", path);

        m[chars[i]] = surf;
    }
    return m;
}

void Text::free(){ // in case you don't trust end of main to free mem
    for(auto iter = Text::letterMap.begin(); iter != Text::letterMap.end(); iter++){
        if(iter->second){
            SDL_FreeSurface(iter->second->get());
            delete iter->second; // just in case
        }
        iter->second = nullptr;
    }
}

void Text::drawLetter(char inp, int x, int y){
    if(inp < 123 && inp > 96) inp -= 32; // all upper
    if(letterMap[inp] != nullptr){
        Text::letterMap[inp]->draw(x, y);
    }
}

void Text::drawString(const char* inp, int x, int y){
    int step = 6 * props->scale;
    for(int i = 0, cursor = x; inp[i]; i++, cursor += step){
        Text::drawLetter(inp[i], cursor, y);
    }
}
void Text::drawString(std::string& inp, int x, int y){
    Text::drawString(inp.c_str(), x, y);
}

void Text::drawInt(int inp, int x, int y){
    if(inp == 0){
        Text::drawLetter('0', x, y);
        return;
    }
    char digit;
    bool neg = inp < 0;
    inp = neg?-inp:inp;
    int i;
    int step = 6 * props->scale;
    for(i = 0; inp; i += step){
        digit = inp % 10 + '0';
        inp /= 10;
        Text::drawLetter(digit, x - i, y);
    }
    if(neg){
        Text::drawLetter('-', x - i, y);
    }
}

// fix float: 12. 0, 3. 6
// print zeros between decimal place and least sig figs
// just gen a string, then print the string... future
void Text::drawFloat(float inp, int x, int y, int prec){
    if(prec > 6) prec = 6; // clamp decimal precision to 6 places

    int whole = inp;    // get integer part
    inp -= whole;      // tear off fractional part
    if(inp < 0) inp *= -1; // abs()

    for(int i = 0; i < prec; i++) inp*=10;  // prepare to load into int
    int dec = inp;        // clip off remaining fractional part

    Text::drawInt(dec, x, y); // draw fractional part

    int step   = 6 * props->scale;    // step size
    int cursor = prec * step; // keeps track of where to draw letter

    Text::drawLetter('.', x - cursor, y);  // draw decimal
    cursor += step;
    Text::drawInt(whole, x - cursor, y); // draw int
}

void Text::drawHex(unsigned int inp, int x, int y, int bytes){
    char digit;
    int step = 6*props->scale;
    bytes*=2;
    for(int i = 0, digCount = 0; digCount < bytes; i += step, digCount++){
        digit = inp % 0x10;
        if(digit < 0x0A){
            digit += 48; //'0';
        }else{
            digit += 55; //'A' - 10;
        }
        inp /= 0x10;
        Text::drawLetter(digit, x - i, y);
    }
}

void Text::drawByte(unsigned char inp, int x, int y){
    Text::drawHex(inp, x, y, 1);
}

void Text::setScale(float scale){
    Text::props->scale = scale;
}
void Text::setColor(Uint32 color){
    Text::props->tint.abgr = color;
}
void Text::setColor(Color& color){
    Text::props->tint.abgr = color.abgr;
}



