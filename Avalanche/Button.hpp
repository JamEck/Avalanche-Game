#ifndef Button_hpp
#define Button_hpp

#include "bool2.hpp"

struct Button{
private:
    bool2 press;
    bool2 release;
public:
    bool down = false;
    
    Button();
    
    void update();
    
    bool pressed();
    bool released();
    bool triggered();
};

#endif /* Button_hpp */
