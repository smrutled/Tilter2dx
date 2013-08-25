//
//  Ball.m
//  Tilter2d
//
//  Created by Sean on 4/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Ball.h"


Ball::Ball(b2World* world,cocos2d::Point p, float radius, uint16 categoryBits, uint16 maskBits){
    type=ENT_BALL;
    body = NULL;
    m_radius = radius/RATIO;
    start=p;
    isAlive=true;
    //set up dynamic body, store in class variable
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.allowSleep=false;
    myBodyDef.position.Set(p.x/RATIO, p.y/RATIO);
    myBodyDef.linearDamping=.1;
    body = world->CreateBody(&myBodyDef);
    body->SetUserData((Entity*) this );
    //add circle fixture
    b2CircleShape circleShape;
    circleShape.m_radius = m_radius; //use class variable
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &circleShape;
    myFixtureDef.density = 1;
    myFixtureDef.restitution=0.1f;
    myFixtureDef.filter.categoryBits = categoryBits;
    myFixtureDef.filter.maskBits = maskBits;
    body->CreateFixture(&myFixtureDef);
    
}

void Ball::sendToStart(){
    body->SetTransform(b2Vec2(start.x/RATIO,start.y/RATIO), 0);
    isAlive=true;
}

void Ball::render(GLESDebugDraw* draw){
    draw->DrawSolidCircle(body->GetPosition(), m_radius, b2Color(1, 0, 0), b2Color(1,0,0), .5, 1);
}

Ball::~Ball(){
}

