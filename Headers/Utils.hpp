#ifndef Utils_hpp
#define Utils_hpp

#include <stdint.h>

struct bool2{
private:
    bool act = false;
    bool wait = false;
public:
    bool pop(bool inp);
    bool output();
    operator bool();
};

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
#endif /* Utils_hpp */
