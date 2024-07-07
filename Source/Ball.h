//
//  Ball.h
//  Tilter2d
///Users/sean/Documents/Tilter2d/Tilter2d/Ball.h
//  Created by Sean on 4/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//


#ifndef Tilter2d_Ball_h
#define Tilter2d_Ball_h

#include "axmol.h"
#include "Box2D/Box2D.h"
#include "extensions/axmol-ext.h"
#include "Entity.h"

using namespace ax;

class  Ball : public Entity{

public:
	b2Body *body;
	float m_radius;
	b2Color m_color;
	Point start;
	bool isAlive;
	~Ball();
	Ball(b2World* world, Point position, float radius, uint16 categoryBits, uint16 maskBits);

	void sendToStart();
    virtual void render(DrawNode* draw);

};

#endif
