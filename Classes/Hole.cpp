//
//  Hole.cpp
//  Tilter2dx
//
//  Created by Sean on 4/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Hole.h"
#include "Ball.h"

Hole::Hole(b2World* world, cocos2d::Point p, float radius, uint16 categoryBits, uint16 maskBits){
	type = ENT_HOLE;
	body = NULL;
	m_radius = radius / RATIO;
	//set up dynamic body, store in class variable
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(p.x / RATIO, p.y / RATIO);
	body = world->CreateBody(&myBodyDef);
	body->SetUserData((Entity*) this);
	//add circle fixture
	b2CircleShape circleShape;
	circleShape.m_radius = m_radius; //use class variable
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &circleShape;
	myFixtureDef.isSensor = true;
	myFixtureDef.filter.categoryBits = categoryBits;
	myFixtureDef.filter.maskBits = maskBits;
	body->CreateFixture(&myFixtureDef);
}

void Hole::render(GLESDebugDraw *draw){
	draw->DrawSolidCircle(body->GetPosition(), m_radius, b2Color(0, 0, 0), b2Color(1, 0, 1), 1, 1);
}