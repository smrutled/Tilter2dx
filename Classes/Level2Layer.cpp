//
//  Level2Layer.cpp
//  Tilter2dx
//
//  Created by Sean on 4/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Level2Layer.h"
#include "Level3Layer.h"
#include "MainMenuLayer.h"
#include "SimpleAudioEngine.h"
#include "AContactListener.h"
#include "AntiAccel.h"
#include "Thruster.h"
#include "ABlock.h"

using namespace cocos2d;
using namespace CocosDenshion;



Level2Layer::Level2Layer()
{
	setTouchEnabled( true );
	setAccelerometerEnabled( true );



	Size screenSize = Director::getInstance()->getWinSize();


	//SimpleAudioEngine::getInstance()->playBackgroundMusic("backround.mp3",true);

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

	gameObjects.push_back((Entity*) new AntiAccel(world, Point(0*factorX,designHeight*3/8*factorY), designWidth*factorX,designHeight*2/8*factorY , A_SENSOR, A_BALL));
	gameObjects.push_back((Entity*) new Thruster(world, 30, Point(designWidth*3/4*factorX,0*factorY), 150*factorY, 10*factorX, 90, A_SENSOR, A_BALL));    

	gameObjects.push_back((Entity*) new ABlock(world,Point((designWidth/2 -15)*factorX, 0*factorY), 15*factorX, designHeight*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(0*factorX, 250*factorY), 75*factorX, 20*factorY, BOUNDARY, A_BALL));
	gameObjects.push_back((Entity*) new ABlock(world,Point(55*factorX, 270*factorY), 20*factorX, 20*factorY, BOUNDARY, A_BALL)); 

	gameObjects.push_back((Entity*) new ABlock(world,Point((designWidth-75)*factorX, 50*factorY), 75*factorX, 20*factorY, BOUNDARY, A_BALL));

	balls.push_back(new Ball(world, Point(25*factorX,10*factorY), 10*factorY, A_BALL,A_SENSOR|BOUNDARY|A_BALL ));
	balls.push_back(new Ball(world, Point((designWidth-25)*factorX,(designHeight-10)*factorY), 10*factorY, A_BALL,A_SENSOR|BOUNDARY|A_BALL ));

	endpoints.push_back(new EndZone(world, Point(20*factorX,(designHeight-20)*factorY), 10*factorY, A_SENSOR,A_BALL ));
	endpoints.push_back(new EndZone(world, Point((designWidth-20)*factorX,20*factorY), 10*factorY, A_SENSOR,A_BALL ));


	//Pause button
	MenuItemFont* item= MenuItemFont::create("||", CC_CALLBACK_1(Level2Layer::menuPauseCallback,this));
	Menu* menu = Menu::create( item, NULL);
	addChild(menu,-1);
	menu->alignItemsVertically();
	menu->setPosition(designWidth*1/20*factorX , designHeight*9/10*factorY);


	schedule( schedule_selector(Level2Layer::tick) );
}

Level2Layer::~Level2Layer()
{
	delete world;
	world = NULL;
	gameObjects.clear();
	endpoints.clear();
	balls.clear();

	delete m_debugDraw;
}

void Level2Layer::draw()
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



void Level2Layer::tick(float dt)
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
					Director::getInstance()->replaceScene(Level3Layer::scene()); 

		}
	}
}

void Level2Layer::onTouchesEnded(Set* touches, Event* event)
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

void Level2Layer::didAccelerate(Acceleration* acceleration)
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

void Level2Layer::menuPauseCallback(Object* pSender){
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

void Level2Layer::menuExitCallback(Object* pSender){
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->end();
	Director::getInstance()->replaceScene(MainMenuLayer::scene());
}


void Level2Layer::pauseMenu(){
	MenuItemFont::setFontSize(50*factorY);
	MenuItemFont* item1= MenuItemFont::create("Exit", CC_CALLBACK_1(Level2Layer::menuExitCallback,this));    
	Menu* menu1 = Menu::create( item1, NULL);
	menu1->setTag(10);
	this->addChild(menu1,0);
	menu1->alignItemsVertically();
	menu1->setPosition(designWidth/2*factorX, designHeight/2*factorY);
}


Scene* Level2Layer::scene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// add layer as a child to scene
	Layer* layer = new Level2Layer();
	scene->addChild(layer);
	layer->release();

	return scene;
}