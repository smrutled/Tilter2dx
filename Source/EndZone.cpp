//
//  EndZone.cpp
//  Tilter2dx
//
//  Created by Sean on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "EndZone.h"

EndZone::EndZone(b2World* world, Point p, float radius, uint16 categoryBits, uint16 maskBits){
	type = ENT_ENDZONE;
	body = nullptr;
	m_radius = radius / RATIO;
	hasBall = 0;
	//set up dynamic body, store in class variable
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(p.x / RATIO, p.y / RATIO);
	body = world->CreateBody(&myBodyDef);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
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


void EndZone::render(DrawNode* draw){

    // Convert Box2D position to Cocos2d-x position
    auto position = Vec2(body->GetPosition().x * RATIO, body->GetPosition().y * RATIO);
    // Define the color of the ball
    Color4F fillColor(0.0f, 1.0f, 0.0f, 0.2f);  // Green color
    Color4F borderColor(0.0f, 1.0f, 0.0f, 1.0f);  // Green border color

    draw->drawSolidCircle(position, m_radius, AX_DEGREES_TO_RADIANS(360), 30, RATIO, RATIO, fillColor, 1.0f, borderColor);

}
