//
//  Ball.h
//  Tilter2d
///Users/sean/Documents/Tilter2d/Tilter2d/Ball.h
//  Created by Sean on 4/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//


#ifndef Tilter2d_Ball_h
#define Tilter2d_Ball_h

#include "cocos2d.h"

#include "Box2D/Box2D.h"


#include "Entity.h"

class  Ball: public Entity{
    
    public:
    b2Body *body;
    float m_radius;
    b2Color m_color;
    cocos2d::Point start;
    bool isAlive;
    ~Ball();
    Ball(b2World* world,cocos2d::Point position, float radius, uint16 categoryBits, uint16 maskBits);
    
    void sendToStart();
   virtual void render(GLESDebugDraw* draw);
        
};
    
#endif