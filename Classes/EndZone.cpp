//
//  EndZone.cpp
//  Tilter2dx
//
//  Created by Sean on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "EndZone.h"

EndZone::EndZone(b2World* world, cocos2d::Point p, float radius, uint16 categoryBits, uint16 maskBits){
	type = ENT_ENDZONE;
	body = NULL;
	m_radius = radius / RATIO;
	hasBall = 0;
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

void EndZone::ballEnter(Ball* ball){
	hasBall += 1;
	ball->body->SetGravityScale(.5);
}

void EndZone::ballExit(Ball* ball){
	hasBall -= 1;
	ball->body->SetGravityScale(1);
}


void EndZone::render(GLESDebugDraw* draw){
	draw->DrawSolidCircle(body->GetPosition(), m_radius, b2Color(0, 1, 0), b2Color(0, 1, 0), .2, 1);
}