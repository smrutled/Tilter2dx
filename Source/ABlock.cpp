//
//  ABlock.cpp
//  Tilter2dx
//
//  Created by Sean on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "ABlock.h"

ABlock::ABlock(b2World* world, Point position, float width, float height, uint16 categoryBits, uint16 maskBits)
{
    type = ENT_BLOCK;
    body = nullptr;

    Point center = Point(position.x + width / 2, position.y + height / 2);

    // set up dynamic body, store in class variable
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(center.x / RATIO, center.y / RATIO);
    body                        = world->CreateBody(&myBodyDef);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    b2PolygonShape shape;
    shape.SetAsBox((width / 2) / RATIO, (height / 2) / RATIO);
    vertcount = shape.m_count;
    for (int i = 0; i < vertcount; i++)
        vert[i] = Vec2(shape.m_vertices[i].x * RATIO, shape.m_vertices[i].y * RATIO);

    b2FixtureDef myFixtureDef;
    myFixtureDef.shape               = &shape;
    myFixtureDef.filter.categoryBits = categoryBits;
    myFixtureDef.filter.maskBits     = maskBits;
    body->CreateFixture(&myFixtureDef);

     // Get vertices relative to the position of the block
    for (int i = 0; i < vertcount; i++)
        vert[i] = vert[i] + center;
}

void ABlock::render(DrawNode *draw){
    // Define the color of the block
    Color4F fillColor(0.0f, 0.0f, 1.0f, 0.4f);  // blue color for the block
    Color4F borderColor(0.0f, 0.0f, 1.0f, 1.0f);  // blue border color

    draw->drawPolygon(vert, vertcount, fillColor, 1.0f, borderColor);
}
