//
//  Hole.h
//  Tilter2dx
//
//  Created by Sean on 4/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Tilter2dx_Hole_h
#define Tilter2dx_Hole_h

#include "cocos2d.h"
#include "Box2D/Box2D.h"


#include "Entity.h"


class Hole : public Entity{
public:
    b2Body *body;
    float m_radius;
    virtual void render(GLESDebugDraw* draw);
    Hole(b2World* world,cocos2d::Point position, float radius, uint16 categoryBits, uint16 maskBits);
    
};

#endif
