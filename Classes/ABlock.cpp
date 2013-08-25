//
//  ABlock.cpp
//  Tilter2dx
//
//  Created by Sean on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "ABlock.h"

ABlock::ABlock(b2World* world, cocos2d::Point position, float width, float height, uint16 categoryBits, uint16 maskBits){
    type=ENT_BLOCK;
    body = NULL;
    
    cocos2d::Point center=cocos2d::Point(position.x+width/2, position.y + height/2);
    
    //set up dynamic body, store in class variable
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(center.x/RATIO, center.y/RATIO);
    body = world->CreateBody(&myBodyDef);
    body->SetUserData((Entity*) this );
    
    b2PolygonShape shape;
    shape.SetAsBox((width/2)/RATIO,(height/2)/RATIO);
    vertcount=shape.m_vertexCount;
    for(int i=0; i<vertcount;i++)
        vert[i]=shape.m_vertices[i];
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &shape;
    myFixtureDef.filter.categoryBits = categoryBits;
    myFixtureDef.filter.maskBits = maskBits;
    body->CreateFixture(&myFixtureDef);
}

void ABlock::render(GLESDebugDraw *draw){
    b2Vec2 p= body->GetPosition();
    kmGLPushMatrix();
    kmGLTranslatef( p.x*RATIO, p.y*RATIO, 0 );
    draw->DrawSolidPolygon(vert, vertcount, b2Color(0, 0, 1),b2Color(0,0,1),.4,1);
    kmGLPopMatrix(); 
}