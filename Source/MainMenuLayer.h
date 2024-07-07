//
//  MainMenuLayer.h
//  Tilter2dx
//
//  Created by Sean on 4/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Tilter2dx_MainMenuLayer_h
#define Tilter2dx_MainMenuLayer_h
#include "Definitions.h"
#include "axmol.h"
#include "extensions/axmol-ext.h"

using namespace ax;
class MainMenuLayer : public ax::Layer {
public:
	~MainMenuLayer();
	MainMenuLayer();
    virtual void draw(ax::Renderer* renderer, const Mat4& transform, uint32_t flags) override;
	void menuCallback(Object* pSender);
	void menuExitCallback(Object* pSender);
	static ax::Scene* scene();
    
        // Debug stuff
    ax::DrawNode* debugDrawNode;
    ax::extension::PhysicsDebugNodeBox2D g_debugDraw;
};


#endif
