#ifndef vec2_hpp
#define vec2_hpp

#include <iostream>

struct vec2{
    float x;
    float y;
    
    vec2(float x = 0, float y = 0);
    vec2(const vec2& other);
//    vec2(const vec2&& other);
    void set(float x, float y);
    
    vec2  operator+ (vec2&  v);
    vec2  operator- (vec2&  v);
    float operator* (vec2&  v);
    vec2  operator+ (vec2&& v);
    vec2  operator- (vec2&& v);
    float operator* (vec2&& v);
    
    bool operator== (vec2&  v);
    bool operator!= (vec2&  v);
    bool operator== (vec2&& v);
    bool operator!= (vec2&& v);
    
    vec2 operator+ (float a);
    vec2 operator- (float a);
    vec2 operator* (float a);
    vec2 operator/ (float a);
    
    void operator+= (vec2& v);
    void operator-= (vec2& v);
    void operator+= (vec2&& v);
    void operator-= (vec2&& v);
    
    void operator+= (float a);
    void operator-= (float a);
    void operator*= (float a);
    void operator/= (float a);
    
    vec2 mult(vec2&  v);
    vec2 div (vec2&  v);
    vec2 mult(vec2&& v);
    vec2 div (vec2&& v);
    
    float sum();
    float prod();
    
    float dist(vec2&  v);
    float dist(vec2&& v);
    float operator>> (vec2&  v);
    float operator>> (vec2&& v);
    
    float magsq();
    float mag();
    vec2 norm();
    vec2 abs();
    
    void clamp(float bound);
    void clamp(float boundX, float boundY);
    
    friend vec2 operator+ (float a, const vec2&  v);
    friend vec2 operator- (float a, const vec2&  v);
    friend vec2 operator* (float a, const vec2&  v);
    friend vec2 operator/ (float a, const vec2&  v);
    friend vec2 operator+ (float a, const vec2&& v);
    friend vec2 operator- (float a, const vec2&& v);
    friend vec2 operator* (float a, const vec2&& v);
    friend vec2 operator/ (float a, const vec2&& v);
    
    void print();
    friend std::ostream& operator<< (std::ostream& os, const vec2& v);
};



#endif /* vec2_hpp */
