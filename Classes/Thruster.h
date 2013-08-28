//
//  Thruster.h
//  Tilter2dx
//
//  Created by Sean on 4/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Tilter2dx_Thruster_h
#define Tilter2dx_Thruster_h

#include "cocos2d.h"
#include "Box2D/Box2D.h"


#include "Entity.h"
#include "Ball.h"

class  Thruster : public Entity{

public:
	b2Body *body;
	float m_angle;
	int m_force;
	b2Color m_color;
	b2Vec2 vert[3];
	virtual void render(GLESDebugDraw* draw);
	Thruster(b2World* world, int force, cocos2d::Point position, float width, float height, float angle, uint16 categoryBits, uint16 maskBits);

	void applyThrust(Ball* ball);

};

#endif
