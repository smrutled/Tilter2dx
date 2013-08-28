//
//  Level2Layer.h
//  Tilter2dx
//
//  Created by Sean on 4/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Tilter2dx_Level2Layer_h
#define Tilter2dx_Level2Layer_h

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "GLES-Render.h"
#include "Entity.h"
#include "EndZone.h"
#include "AntiAccel.h"
#include "Thruster.h"
#include "Ball.h"



class Level2Layer : public cocos2d::Layer {
public:
	~Level2Layer();
	Level2Layer();

	// returns a Scene that contains the Level2Layer as the only child
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
