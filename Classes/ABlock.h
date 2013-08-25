//
//  ABlock.h
//  Tilter2dx
//
//  Created by Sean on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Tilter2dx_ABlock_h
#define Tilter2dx_ABlock_h


#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Entity.h"


class ABlock: public Entity{
    public:
    ABlock(b2World* world, cocos2d::Point position, float width, float height, uint16 categoryBits, uint16 maskBits);
    b2Body *body;
    b2Vec2 vert[8];
    int vertcount;
    
    virtual void render(GLESDebugDraw* draw);
};


#endif
