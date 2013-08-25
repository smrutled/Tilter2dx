//
//  Level3Layer.cpp
//  Tilter2dx
//
//  Created by Sean on 4/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Level3Layer.h"
#include "MainMenuLayer.h"
#include "SimpleAudioEngine.h"
#include "AContactListener.h"
#include "ABlock.h"
using namespace cocos2d;
using namespace CocosDenshion;



Level3Layer::Level3Layer()
{
	setTouchEnabled( true );
	setAccelerometerEnabled( true );



	Size screenSize = Director::getInstance()->getWinSize();


	// Define the gravity vector.
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	designWidth=480;
	designHeight=320;
	//Scale screen to resolution
	factorX = screenSize.width / designWidth;
	factorY = screenSize.height / designHeight;
	paused=false;

	// Do we want to let bodies sleep?
	bool doSleep = true;

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(gravity);
	world->SetAllowSleeping(doSleep);    
	world->SetContinuousPhysics(true);

	m_debugDraw = new GLESDebugDraw( RATIO);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	m_debugDraw->SetFlags(flags);		

	AContactListener* mycontact=new AContactListener();
	world->SetContactListener(mycontact);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(screenSize.width/2/RATIO, 
		screenSize.height/2/RATIO); // bottom-left corner



	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	b2FixtureDef groundfix;
	groundfix.shape=&groundBox;
	groundfix.filter.categoryBits=BOUNDARY;
	groundfix.filter.maskBits=A_BALL;	

	// bottom
	groundBox.SetAsBox(screenSize.width/2/RATIO, 0, b2Vec2(0, -screenSize.height/2/RATIO), 0);
	groundBody->CreateFixture(&groundfix);

	// top
	groundBox.SetAsBox(screenSize.width/2/RATIO, 0, b2Vec2(0, screenSize.height/2/RATIO), 0);
	groundBody->CreateFixture(&groundfix);

	// left
	groundBox.SetAsBox(0, screenSize.height/2/RATIO, b2Vec2(-screenSize.width/2/RATIO, 0), 0);
	groundBody->CreateFixture(&groundfix);

	// right
	groundBox.SetAsBox(0, screenSize.height/2/RATIO, b2Vec2(screenSize.width/2/RATIO, 0), 0);
	groundBody->CreateFixture(&groundfix);


	//Level objects

	gameObjects.push_back((Entity*) new ABlock(world,Point(0*factorX, (designHeight-50)*factorY), 200*factorX, 20*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(230*factorX, (designHeight-50)*factorY), 75*factorX, 20*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(335*factorX, (designHeight-50)*factorY), 145*factorX, 20*factorY, BOUNDARY, A_BALL)); 
	gameObjects.push_back((Entity*) new ABlock(world,Point(180*factorX, (designHeight-30)*factorY), 20*factorX, 30*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(230*factorX, (designHeight-30)*factorY), 20*factorX, 30*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(285*factorX, (designHeight-30)*factorY), 20*factorX, 30*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(335*factorX, (designHeight-30)*factorY), 20*factorX, 30*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(0*factorX, 100*factorY), 40*factorX, 20*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(90*factorX, 100*factorY), 100*factorX, 20*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(240*factorX, 100*factorY), 100*factorX, 20*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(390*factorX, 100*factorY), 90*factorX, 20*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(40*factorX, 155*factorY), 50*factorX, 20*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(190*factorX, 155*factorY), 50*factorX, 20*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(20*factorX, 120*factorY), 20*factorX, 55*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(90*factorX, 120*factorY), 20*factorX, 55*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(170*factorX, 120*factorY), 20*factorX, 55*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(240*factorX, 120*factorY), 20*factorX, 55*factorY, BOUNDARY, A_BALL));


	balls.push_back(new Ball(world, Point(25*factorX,10*factorY), 10*factorY, A_BALL,A_SENSOR|BOUNDARY|A_BALL ));
	balls.push_back(new Ball(world, Point(50*factorX,10*factorY), 10*factorY, A_BALL,A_SENSOR|BOUNDARY|A_BALL ));
	balls.push_back(new Ball(world, Point(25*factorX,180*factorY), 20*factorY, A_BALL,A_SENSOR|BOUNDARY|A_BALL ));
	balls.push_back(new Ball(world, Point(75*factorX,180*factorY), 20*factorY, A_BALL,A_SENSOR|BOUNDARY|A_BALL ));
	endpoints.push_back(new EndZone(world, Point(215*factorX,(designHeight-15)*factorY), 10*factorY, A_SENSOR,A_BALL ));
	endpoints.push_back(new EndZone(world, Point(320*factorX,(designHeight-15)*factorY), 10*factorY, A_SENSOR,A_BALL ));
	endpoints.push_back(new EndZone(world, Point(65*factorX,130*factorY), 20*factorY, A_SENSOR,A_BALL ));
	endpoints.push_back(new EndZone(world, Point(215*factorX,130*factorY), 20*factorY, A_SENSOR,A_BALL ));


	//Pause button
	MenuItemFont* item= MenuItemFont::create("||", CC_CALLBACK_1(Level3Layer::menuPauseCallback,this));
	Menu* menu = Menu::create( item, NULL);
	addChild(menu,-1);
	menu->alignItemsVertically();
	menu->setPosition(designWidth*1/20*factorX , designHeight*9/10*factorY);


	schedule( schedule_selector(Level3Layer::tick) );
}

Level3Layer::~Level3Layer()
{
	delete world;
	world = NULL;
	gameObjects.clear();
	endpoints.clear();
	balls.clear();

	delete m_debugDraw;
}

void Level3Layer::draw()
{
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states:  GL_VERTEX_ARRAY, 
	// Unneeded states: GL_TEXTURE_2D, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	GL::enableVertexAttribs(  GL::VERTEX_ATTRIB_FLAG_POSITION );

	kmGLPushMatrix();

	for(int i=0; i<designWidth;i+=designWidth/20)
		m_debugDraw->DrawSegment(b2Vec2(i/RATIO*factorX, 0), b2Vec2(i/RATIO*factorX,designHeight/RATIO*factorY), b2Color(0, 1,1),.2);
	for(int i=0; i<designHeight; i+=designHeight/20)
		m_debugDraw->DrawSegment(b2Vec2(0, i/RATIO*factorY), b2Vec2(designWidth/RATIO*factorX ,i/RATIO*factorY), b2Color(0, 1, 1),.2);

	for(int i=0; i<gameObjects.size(); i++)
		gameObjects[i]->render(m_debugDraw);    
	for(int i=0; i<balls.size(); i++)
		balls[i]->render(m_debugDraw);

	for(int i=0; i<endpoints.size(); i++)
		endpoints[i]->render(m_debugDraw);


	kmGLPopMatrix();

	CHECK_GL_ERROR_DEBUG();	
}



void Level3Layer::tick(float dt)
{

	int velocityIterations = 8;
	int positionIterations = 1;

	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	if(!paused){
		world->Step(dt, velocityIterations, positionIterations);
		//Iterate over the bodies in the physics world
		for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
		{
			if (b->GetUserData() != NULL) {

			}
			for(int i=0; i<balls.size(); i++)        
				if (!balls[i]->isAlive) {
					balls[i]->sendToStart();
				}

				bool complete=true;
				for(int i=0; i<endpoints.size(); i++)
					if(endpoints[i]->hasBall==0)
						complete=false;
				if(complete)
					Director::getInstance()->replaceScene(MainMenuLayer::scene()); 

		}
	}
}

void Level3Layer::onTouchesEnded(Set* touches, Event* event)
{
	//Add a new body/atlas sprite at the touched location
	SetIterator it;
	Touch* touch;

	for( it = touches->begin(); it != touches->end(); it++) 
	{
		touch = (Touch*)(*it);

		if(!touch)
			break;

		Point location = touch->getLocationInView();

		location = Director::getInstance()->convertToGL(location);

	}
}

void Level3Layer::didAccelerate(Acceleration* acceleration)
{
	static float prevX=0, prevY=0;
	const float kFilterFactor = 0.8f;
	float accelX = (float) acceleration->x * kFilterFactor + (1- kFilterFactor)*prevX;
	float accelY = (float) acceleration->y * kFilterFactor + (1- kFilterFactor)*prevY;

	prevX = accelX;
	prevY = accelY;

	// accelerometer values are in "Portrait" mode. Change them to Landscape left
	// multiply the gravity by 10
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	b2Vec2 gravity( -accelY*10, accelX*10);    
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)      
	b2Vec2 gravity( accelX*10, accelY*10);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)      
	b2Vec2 gravity( accelX*10, accelY*10);
#endif

	world->SetGravity( gravity );}

void Level3Layer::menuPauseCallback(Object* pSender){
	if(!paused){
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		pauseMenu();
	}
	else{
		this->removeChildByTag(10, true);
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

	}

	paused=!paused;
}

void Level3Layer::menuExitCallback(Object* pSender){
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->end();
	Director::getInstance()->replaceScene(MainMenuLayer::scene());
}


void Level3Layer::pauseMenu(){
	MenuItemFont::setFontSize(50*factorY);
	MenuItemFont* item1= MenuItemFont::create("Exit", CC_CALLBACK_1(Level3Layer::menuExitCallback,this));    
	Menu* menu1 = Menu::create( item1, NULL);
	menu1->setTag(10);
	this->addChild(menu1,0);
	menu1->alignItemsVertically();
	menu1->setPosition(designWidth/2*factorX, designHeight/2*factorY);
}


Scene* Level3Layer::scene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// add layer as a child to scene
	Layer* layer = new Level3Layer();
	scene->addChild(layer);
	layer->release();

	return scene;
}