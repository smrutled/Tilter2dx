//
//  AntiAccel.h
//  Tilter2dx
//
//  Created by Sean on 4/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Tilter2dx_AntiAccel_h
#define Tilter2dx_AntiAccel_h
#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "Entity.h"
#include "Ball.h"

class  AntiAccel : public Entity{

public:
	b2Body *body;
	b2Color m_color;
	virtual void render(GLESDebugDraw* draw);
	AntiAccel(b2World* world, cocos2d::Point position, float width, float height, uint16 categoryBits, uint16 maskBits);
	b2Vec2 vert[8];
	int vertcount;
	void setReverseGravity(Ball* ball);
	void setNormalGravity(Ball* ball);

};
#endif
