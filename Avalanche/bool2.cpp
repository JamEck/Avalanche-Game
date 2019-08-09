#include "bool2.hpp"


bool bool2::pop(bool inp){
    act = inp && !wait;
    wait = inp;
    return act;
}

bool bool2::output(){
    return act;
}
bool2::operator bool() {
    return act;
}
