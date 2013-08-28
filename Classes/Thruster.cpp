//
//  Thruster.cpp
//  Tilter2dx
//
//  Created by Sean on 4/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Thruster.h"


Thruster::Thruster(b2World* world, int force, cocos2d::Point p, float width, float height, float angle, uint16 categoryBits, uint16 maskBits){
	type = ENT_THRUSTER;
	body = NULL;
	m_angle = angle*DEGTORAD;
	m_force = force;
	//set up dynamic body, store in class variable
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(p.x / RATIO, p.y / RATIO);
	myBodyDef.angle = m_angle;
	body = world->CreateBody(&myBodyDef);
	body->SetUserData((Entity*) this);
	//add circle fixture
	b2PolygonShape shape;
	vert[0].Set(0, (width / 2) / RATIO);
	vert[1].Set(0, (-width / 2) / RATIO);
	vert[2].Set(height / RATIO, 0);
	shape.Set(vert, 3);


	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &shape;
	myFixtureDef.isSensor = true;
	myFixtureDef.filter.categoryBits = categoryBits;
	myFixtureDef.filter.maskBits = maskBits;
	body->CreateFixture(&myFixtureDef);

}

void Thruster::applyThrust(Ball* ball){
	ball->body->ApplyLinearImpulse(b2Vec2(m_force*cos(m_angle), m_force*sin(m_angle)), ball->body->GetWorldCenter());
}

void Thruster::render(GLESDebugDraw *draw){
	b2Vec2 p = body->GetPosition();
	kmGLPushMatrix();
	kmGLTranslatef(p.x*RATIO, p.y*RATIO, 0);
	kmGLRotatef(m_angle * RADTODEG, 0, 0, 1);//OpenGL uses degrees here
	draw->DrawSolidPolygon(vert, 3, b2Color(1, 1, 0), b2Color(1, 1, 0), .5, 1);
	kmGLPopMatrix();
}

