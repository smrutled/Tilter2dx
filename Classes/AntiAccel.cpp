//
//  AntiAccel.cpp
//  Tilter2dx
//
//  Created by Sean on 4/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "AntiAccel.h"

AntiAccel::AntiAccel(b2World* world, cocos2d::Point p, float width, float height, uint16 categoryBits, uint16 maskBits){
	type = ENT_ANTIACCEL;
	body = nullptr;

	b2Vec2 center = b2Vec2(p.x + width / 2, p.y + height / 2);

	//set up dynamic body, store in class variable
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(center.x / RATIO, center.y / RATIO);
	body = world->CreateBody(&myBodyDef);
	body->SetUserData((Entity*) this);

	b2PolygonShape shape;
	shape.SetAsBox((width / 2) / RATIO, (height / 2) / RATIO);
	vertcount = shape.m_vertexCount;
	for (int i = 0; i < vertcount; i++)
		vert[i] = shape.m_vertices[i];
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &shape;
	myFixtureDef.isSensor = true;
	myFixtureDef.filter.categoryBits = categoryBits;
	myFixtureDef.filter.maskBits = maskBits;
	body->CreateFixture(&myFixtureDef);
}

void AntiAccel::setNormalGravity(Ball *ball){
	ball->body->SetGravityScale(1);
}
void AntiAccel::setReverseGravity(Ball *ball){
	ball->body->SetGravityScale(-1);
}

void AntiAccel::render(GLESDebugDraw *draw){
	b2Vec2 p = body->GetPosition();
	kmGLPushMatrix();
	kmGLTranslatef(p.x*RATIO, p.y*RATIO, 0);
	draw->DrawSolidPolygon(vert, vertcount, b2Color(1, 1, 1), b2Color(1, 1, 1), .3, 0);
	kmGLPopMatrix();
}
