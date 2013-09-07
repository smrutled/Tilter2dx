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
#include "cocos2d.h"
#include "GLES-Render.h"

class MainMenuLayer : public cocos2d::Layer {
public:
	~MainMenuLayer();
	MainMenuLayer();

	void menuCallback(Object* pSender);
	void menuExitCallback(Object* pSender);
	static cocos2d::Scene* scene();
	virtual void draw();
	GLESDebugDraw* gdraw;
};


#endif
