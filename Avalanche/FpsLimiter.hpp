#ifndef FpsLimiter_hpp
#define FpsLimiter_hpp

#include "Timer.hpp"

class FpsLimiter{
private:
    Timer t;
    double targetFrameTime;
    double targetFps;
    double currFps;
public:
    
    FpsLimiter(double fps = 60.0);
    
    void setTargetFps(double fps);
    double getTargetFps();
    double reportFps();

    bool limit();
};

#endif /* FpsLimiter_hpp */
