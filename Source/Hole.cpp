//
//  Hole.cpp
//  Tilter2dx
//
//  Created by Sean on 4/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Hole.h"
#include "Ball.h"

Hole::Hole(b2World* world, Point p, float radius, uint16 categoryBits, uint16 maskBits){
	type = ENT_HOLE;
	body = nullptr;
	m_radius = radius / RATIO;
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

void Hole::render(DrawNode *draw){

     // Convert Box2D position to Cocos2d-x position
    Vec2 position = Vec2(body->GetPosition().x * RATIO, body->GetPosition().y * RATIO);
     // Define the color of the hole
     Color4F fillColor(0.0f, 0.0f, 0.0f, 1.0f);  // Black color for the hole
    Color4F borderColor(1.0f, 0.0f, 1.0f, 1.0f);  // Magenta border color
    // Draw a solid circle for the hole

      draw->drawSolidCircle(position, m_radius * RATIO, AX_DEGREES_TO_RADIANS(360), 30, 1.0f, 1.0f, fillColor, 1.0f,
                          borderColor);
}
