//
//  Entity.h
//  Tilter2d
//
//  Created by Sean on 4/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Tilter2d_Entity_h
#define Tilter2d_Entity_h



#include "Definitions.h"
#include "GLES-Render.h"

class Entity
{
    public: int type;
    virtual void render(GLESDebugDraw* draw){
        return;
    };
    
};


#endif
