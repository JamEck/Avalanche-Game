#include "Timer.hpp"
#include <stdio.h>
void Timer::update(decltype(s)& inp){
    inp = std::chrono::high_resolution_clock::now();
}

decltype(Timer::s) Timer::start(){
    update(s);
    return s;
}

decltype(Timer::e) Timer::stop(){
    update(e);
    d = e - s;
    return e;
}

double Timer::elapsed(){
    return d.count();
}

void Timer::setAlarm(double time){
    timerLength = time;
    start();
}
bool Timer::checkAlarm(){
    stop();
    return timerLength && elapsed() > timerLength;
}
void Timer::clearAlarm(){
    timerLength = 0;
}