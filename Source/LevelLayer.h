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

#include "Definitions.h"
#include "extensions/axmol-ext.h"
#include "Box2D/Box2D.h"

#include "EndZone.h"
#include "Entity.h"


class LevelLayer : public Layer {
public:
	~LevelLayer();
	LevelLayer();

	void initWorld();

	// returns a Scene that contains the Level1Layer as the only child
	static Scene* scene(int lvl);
    virtual void draw(Renderer* renderer, const Mat4& transform, uint32_t flags);
	virtual void onAcceleration(Acceleration* acceleration, Event* event);
	void tick(float dt);

	void pauseMenu();
	void menuExitCallback(Object* psender);
	void menuPauseCallback(Object* pSender);

private:
	b2World* world;
	bool paused;
    // Debug stuff
    ax::DrawNode* debugDrawNode;
    ax::extension::PhysicsDebugNodeBox2D g_debugDraw;
	std::vector<Ball*> balls;
    std::vector<EndZone*> endzones;
    std::vector<Entity*> gameObjects;

	
};

#endif
