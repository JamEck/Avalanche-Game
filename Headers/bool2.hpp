#ifndef bool2_hpp
#define bool2_hpp

struct bool2{
private:
    bool act = false;
    bool wait = false;
public:
    bool pop(bool inp);
    bool output();
    operator bool();
};
#endif /* bool2_hpp */
