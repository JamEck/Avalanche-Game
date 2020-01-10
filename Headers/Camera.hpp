#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include "Entity.hpp"

class Camera : public Entity{
private:
public:
    Camera();
    Camera(vec2& inp);
};

#endif /* Camera_hpp */
