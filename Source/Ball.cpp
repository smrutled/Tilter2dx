//
//  Ball.m
//  Tilter2d
//
//  Created by Sean on 4/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Ball.h"


Ball::Ball(b2World* world, ax::Point p, float radius, uint16 categoryBits, uint16 maskBits){
	type = ENT_BALL;
	body = nullptr;
	m_radius = radius / RATIO;
	start = p;
	isAlive = true;
	//set up dynamic body, store in class variable
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.allowSleep = false;
	myBodyDef.position.Set(p.x / RATIO, p.y / RATIO);
	myBodyDef.linearDamping = .1;
	body = world->CreateBody(&myBodyDef);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
	//add circle fixture
	b2CircleShape circleShape;
	circleShape.m_radius = m_radius; //use class variable
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &circleShape;
	myFixtureDef.density = 1;
	myFixtureDef.restitution = 0.1f;
	myFixtureDef.filter.categoryBits = categoryBits;
	myFixtureDef.filter.maskBits = maskBits;
	body->CreateFixture(&myFixtureDef);

}

void Ball::sendToStart(){
	body->SetTransform(b2Vec2(start.x / RATIO, start.y / RATIO), 0);
	isAlive = true;
}

void Ball::render(DrawNode* draw)
{
    auto position = Vec2(body->GetPosition().x * RATIO, body->GetPosition().y * RATIO);
    // Define the color of the ball
    Color4F fillColor(1.0f, 0.0f, 0.0f, 0.5f);    // Red color
    Color4F borderColor(1.0f, 0.0f, 0.0f, 1.0f);  // Red border color

  draw->drawSolidCircle(position, m_radius * RATIO, AX_DEGREES_TO_RADIANS(360), 30, 1.0f, 1.0f, fillColor, 1.0f,
                          borderColor);
}

Ball::~Ball(){
}

