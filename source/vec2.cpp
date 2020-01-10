#include "vec2.hpp"
#include <iomanip>
#include <math.h>

vec2::vec2(float _x, float _y){
    x = _x; y = _y;
}
vec2::vec2(const vec2& other){
    x = other.x; y = other.y;
}
//vec2::vec2(const vec2&& other){
//    x = other.x; y = other.y;
//}

void vec2::set(float _x, float _y){
    x = _x; y = _y;
}

vec2 vec2::operator+ (vec2& v){
    return vec2(x + v.x, y + v.y);
}
vec2 vec2::operator- (vec2& v){
    return vec2(x - v.x, y - v.y);
}
float vec2::operator* (vec2& v){
    return x * v.x + y * v.y;
}
vec2 vec2::operator+ (vec2&& v){
    return vec2(x + v.x, y + v.y);
}
vec2 vec2::operator- (vec2&& v){
    return vec2(x - v.x, y - v.y);
}
float vec2::operator* (vec2&& v){
    return x * v.x + y * v.y;
}

bool vec2::operator== (vec2& v){
    return (x == v.x) && (y == v.y);
}
bool vec2::operator!= (vec2& v){
    return !(*this == v);
}
bool vec2::operator== (vec2&& v){
    return (x == v.x) && (y == v.y);
}
bool vec2::operator!= (vec2&& v){
    return !(*this == v);
}

vec2 vec2::operator+ (float a){
    return vec2(x+a, y+a);
}
vec2 vec2::operator- (float a){
    return vec2(x-a, y-a);
}
vec2 vec2::operator* (float a){
    return vec2(x*a, y*a);
}
vec2 vec2::operator/ (float a){
    if(a)
        return vec2(x/a, y/a);
    else
        printf("\n[::ERROR::] no op performed\nvec2/float: Divide by Zero!\n\n");
    return *this;
}

void vec2::operator+= (vec2& v){
    x += v.x; y += v.y;
}
void vec2::operator-= (vec2& v){
    x -= v.x; y -= v.y;
}
void vec2::operator+= (vec2&& v){
    x += v.x; y += v.y;
}
void vec2::operator-= (vec2&& v){
    x -= v.x; y -= v.y;
}

void vec2::operator+= (float a){
    x += a; y += a;
}
void vec2::operator-= (float a){
    x -= a; y -= a;
}
void vec2::operator*= (float a){
    x *= a; y *= a;
}
void vec2::operator/= (float a){
    if(a){
        x/=a; y/=a;
    }else{
        printf("\n[::ERROR::] no op performed\nvec2/=float: Divide by Zero!\n\n");
    }
}

vec2 operator+ (float a, const vec2& v){
    return vec2(a+v.x, a+v.y);
}
vec2 operator- (float a, const vec2& v){
    return vec2(a-v.x, a-v.y);
}
vec2 operator* (float a, const vec2& v){
    return vec2(a*v.x, a*v.y);
}
vec2 operator/ (float a, const vec2& v){
    if(v.x && v.y)
        return vec2(a/v.x, a/v.y);
    else
        printf("\n[::ERROR::] no op performed\nfloat/vec2: Divide by Zero!\n\n");
    return v;
}
vec2 operator+ (float a, const vec2&& v){
    return vec2(a+v.x, a+v.y);
}
vec2 operator- (float a, const vec2&& v){
    return vec2(a-v.x, a-v.y);
}
vec2 operator* (float a, const vec2&& v){
    return vec2(a*v.x, a*v.y);
}
vec2 operator/ (float a, const vec2&& v){
    if(v.x && v.y)
        return vec2(a/v.x, a/v.y);
    else
        printf("\n[::ERROR::] no op performed\nfloat/vec2: Divide by Zero!\n\n");
    return v;
}

vec2 vec2::mult(vec2& v){
    return vec2(x*v.x, y*v.y);
}
vec2 vec2::div(vec2& v){
    return vec2(x/v.x, y/v.y);
}
vec2 vec2::mult(vec2&& v){
    return vec2(x*v.x, y*v.y);
}
vec2 vec2::div(vec2&& v){
    return vec2(x/v.x, y/v.y);
}

float vec2::sum(){
    return x + y;
}
float vec2::prod(){
    return x * y;
}

float vec2::dist(vec2& v){
    return (*this-v).mag();
}float vec2::dist(vec2&& v){
    return (*this-v).mag();
}
float vec2::operator>> (vec2& v){
    return (*this-v).mag();
}
float vec2::operator>> (vec2&& v){
    return (*this-v).mag();
}

float vec2::magsq(){
    return *this**this;
}
float vec2::mag(){
    return sqrt(*this**this);
}
vec2 vec2::norm(){
    return *this/this->mag();
}
vec2 vec2::abs(){
    return vec2((x<0)?-x:x, (y<0)?-y:y);
}


void vec2::clamp(float bound){
    x = (x >  bound)? bound:x;
    x = (x < -bound)?-bound:x;
    y = (y >  bound)? bound:y;
    y = (y < -bound)?-bound:y;
}

void vec2::clamp(float boundX, float boundY){
    if(boundX >= 0){
        x = (x >  boundX)? boundX:x;
        x = (x < -boundX)?-boundX:x;
    }
    if(boundY >= 0){
        y = (y >  boundY)? boundY:y;
        y = (y < -boundY)?-boundY:y;
    }
}

void vec2::print(){
    std::cout << "(" << std::setw(3) << x << ", " << std::setw(3) << y << ")" << std::endl;
}

std::ostream& operator<< (std::ostream& os, const vec2& v){
    os
    << "vec2: " << &v << std::endl
    << "• (" << std::setw(3) << v.x << ", " << std::setw(3) << v.y << ")" << std::endl;
    return os;
}