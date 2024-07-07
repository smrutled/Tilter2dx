//
//  ABlock.h
//  Tilter2dx
//
//  Created by Sean on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Tilter2dx_ABlock_h
#define Tilter2dx_ABlock_h
#include "Definitions.h"
#include "Box2D/Box2D.h"
#include "Entity.h"


class ABlock : public Entity{
public:
	ABlock(b2World* world, Point position, float width, float height, uint16 categoryBits, uint16 maskBits);
	b2Body *body;
    Vec2 vert[8];
	int vertcount;

	virtual void render(DrawNode* draw);
};


#endif
