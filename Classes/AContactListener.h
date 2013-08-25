//
//  AContactListener.h
//  Tilter2d
//
//  Created by Sean on 4/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#ifndef Tilter2dx_ContactListener_h
#define Tilter2dx_ContactListener_h

#include "cocos2d.h"

#include "Box2D/Box2D.h"




class AContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact);
    
    void EndContact(b2Contact* contact);

};

#endif
