//
//  Thruster.cpp
//  Tilter2dx
//
//  Created by Sean on 4/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Thruster.h"


Thruster::Thruster(b2World* world, int force, Point p, float width, float height, float angle, uint16 categoryBits, uint16 maskBits){
	type = ENT_THRUSTER;
	body = nullptr;
	m_angle = angle*DEGTORAD;
	m_force = force;
	//set up dynamic body, store in class variable
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(p.x / RATIO, p.y / RATIO);
	myBodyDef.angle = m_angle;
	body = world->CreateBody(&myBodyDef);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
	//add circle fixture
	b2PolygonShape shape;
    b2Vec2 bvert[3];

	bvert[0].Set(0, (width / 2) / RATIO);
    bvert[1].Set(0, (-width / 2) / RATIO);
        bvert[2].Set(height / RATIO, 0);
    shape.Set(bvert, 3);

    vert[0] = Vec2(bvert[0].x * RATIO, bvert[0].y * RATIO);
    vert[1] = Vec2(bvert[1].x * RATIO, bvert[1].y * RATIO);
    vert[2] = Vec2(bvert[2].x * RATIO, bvert[2].y * RATIO);
    // Rotate the vertices
    for (int i = 0; i < 3; i++)
    {
        float x   = vert[i].x;
        float y   = vert[i].y;
        vert[i].x = x * cos(m_angle) - y * sin(m_angle);
        vert[i].y = x * sin(m_angle) + y * cos(m_angle);
    }
    // Get vertices relative to the position of the block
    for (int i = 0; i < 3; i++)
        vert[i] = vert[i] + p;

	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &shape;
	myFixtureDef.isSensor = true;
	myFixtureDef.filter.categoryBits = categoryBits;
	myFixtureDef.filter.maskBits = maskBits;
	body->CreateFixture(&myFixtureDef);

}

void Thruster::applyThrust(Ball* ball){

	ball->body->ApplyLinearImpulse(b2Vec2(m_force*cos(m_angle), m_force*sin(m_angle)), ball->body->GetWorldCenter(),true);
}

void Thruster::render(DrawNode *draw){

    // Define the color of the thruster
    Color4F fillColor(1.0f, 1.0f, 0.0f, 0.5f);  // yellow color for the thruster
    Color4F borderColor(1.0f, 1.0f, 0.0f, 1.0f);  // yellow border color

    draw->drawPolygon(vert, _countof(vert), fillColor, 1.0f, borderColor);

	//b2Vec2 p = body->GetPosition();
	//kmGLPushMatrix();
	//kmGLTranslatef(p.x*RATIO, p.y*RATIO, 0);
	//kmGLRotatef(m_angle * RADTODEG, 0, 0, 1);//OpenGL uses degrees here
	//draw->DrawSolidPolygon(vert, 3, b2Color(1, 1, 0), b2Color(1, 1, 0), .5, 1);
	//kmGLPopMatrix();
}

