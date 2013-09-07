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


class LevelLayer : public cocos2d::Layer {
public:
	~LevelLayer();
	LevelLayer();

	void initWorld();

	// returns a Scene that contains the Level1Layer as the only child
	static cocos2d::Scene* scene(int lvl);
	virtual void draw();
	virtual void didAccelerate(cocos2d::Acceleration* acceleration);
	void tick(float dt);

	void pauseMenu();
	void menuExitCallback(Object* psender);
	void menuPauseCallback(Object* pSender);

private:
	b2World* world;
	bool paused;
	GLESDebugDraw *m_debugDraw;
	vector<Ball*> balls;
	vector<EndZone*>endzones;
	vector<Entity*>gameObjects;

	
};

#endif
