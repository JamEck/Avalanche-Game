#include "FpsLimiter.hpp"


FpsLimiter::FpsLimiter(double fps){
    t.start();
    setTargetFps(fps);
}

void FpsLimiter::setTargetFps(double fps){
    targetFps = fps;
    targetFrameTime = 1/fps;
}

double FpsLimiter::getTargetFps(){
    return targetFps;
}

double FpsLimiter::reportFps(){
    return currFps;
}

bool FpsLimiter::limit(){
    t.stop();
    
    if(t.elapsed() >= targetFrameTime){
        currFps = 1/t.elapsed();
        t.start();
        return true;
    }
    return false;
}