//
//  Level1LayerScene.h
//  Tilter2dx
//
//  Created by Sean on 4/15/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//
#ifndef Tilter2dx_Level1Layer_h
#define Tilter2dx_Level1Layer_h

// When you import this file, you import all the cocos2d classes

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "GLES-Render.h"

#include "EndZone.h"
#include "Entity.h"



class Level1Layer : public cocos2d::Layer {
public:
	~Level1Layer();
	Level1Layer();

	// returns a Scene that contains the Level1Layer as the only child
	static cocos2d::Scene* scene();

	virtual void draw();
	virtual void onTouchesEnded(cocos2d::Set* touches, cocos2d::Event* event);
	virtual void didAccelerate(cocos2d::Acceleration* acceleration);
	void tick(float dt);

	void pauseMenu();
	void menuExitCallback(Object* psender);
	void menuPauseCallback(Object* pSender);

private:
	b2World* world;
	float factorX;
	float factorY;
	float designHeight;
	float designWidth;
	bool paused;

	GLESDebugDraw *m_debugDraw;
	vector<Ball*> balls;
	vector<EndZone*>endpoints;
	vector<Entity*>gameObjects;
};

#endif
