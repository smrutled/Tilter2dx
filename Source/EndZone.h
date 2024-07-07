//
//  EndZone.h
//  Tilter2d
//
//  Created by Sean on 4/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Tilter2d_End_h
#define Tilter2d_End_h

#include "Definitions.h"
#include "Entity.h"
#include "Ball.h"

class EndZone : public Entity{
public:
	b2Body *body;
	float m_radius;
	b2Color m_color;
	int hasBall;
	void ballEnter(Ball* ball);
	void ballExit(Ball* ball);
	virtual void render(DrawNode* draw);

	EndZone(b2World* world, Point position, float radius, uint16 categoryBits, uint16 maskBits);


};

#endif


