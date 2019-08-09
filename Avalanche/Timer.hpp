#ifndef Timer_hpp
#define Timer_hpp

#include <chrono>

struct Timer{
private:
    decltype(std::chrono::high_resolution_clock::now()) s;
    decltype(s) e;
    std::chrono::duration<double> d;
    
    void update(decltype(s)&);
    
    double timerLength = 0;
public:
    decltype(s) start();
    
    decltype(e) stop();
    
    double elapsed();
    
    void setAlarm(double time);
    bool checkAlarm();
    void clearAlarm();

};

#endif /* Timer_hpp */
