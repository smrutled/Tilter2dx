//
//  Level1LayerScene.cpp
//  Tilter2dx
//
//  Created by Sean on 4/15/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//
#include "LevelLayer.h"
#include "MainMenuLayer.h"
#include "SimpleAudioEngine.h"
#include "AContactListener.h"
#include "Hole.h"
#include "ABlock.h"
#include "Thruster.h"
#include "AntiAccel.h"
#include "cocos-ext.h"
#include <fstream>

using namespace cocos2d;
using namespace CocosDenshion;



LevelLayer::LevelLayer() : world(nullptr)
{
	this->setTouchEnabled(true);
	this->setAccelerometerEnabled(true);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_PLATFORM_MAC) 
	this->setKeyboardEnabled(true);
#endif

	if(!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		SimpleAudioEngine::getInstance()->playBackgroundMusic("backround.mp3", true);
	
	this->initWorld();
	
	//Pause button
	MenuItemFont::setFontName("fonts/Mark Felt.ttf");
	MenuItemFont* item = MenuItemFont::create("||", CC_CALLBACK_1(LevelLayer::menuPauseCallback, this));
	Menu* menu = Menu::create(item, nullptr);
	menu->setPosition(scaledWidth * 1 / 20, scaledHeight * 9 / 10);
	this->addChild(menu, -1);

	this->schedule(schedule_selector(LevelLayer::tick));
}
void LevelLayer::initWorld(){
	
	// Define the gravity vector.
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);

	paused = false;
	// Do we want to let bodies sleep?
	bool doSleep = true;

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(gravity);
	world->SetAllowSleeping(doSleep);
	world->SetContinuousPhysics(true);

	m_debugDraw = new GLESDebugDraw(RATIO);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	m_debugDraw->SetFlags(flags);

	AContactListener* mycontact = new AContactListener();
	world->SetContactListener(mycontact);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(screenWidth / 2 / RATIO,
		screenHeight / 2 / RATIO); // bottom-left corner



	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	b2FixtureDef groundfix;
	groundfix.shape = &groundBox;
	groundfix.filter.categoryBits = BOUNDARY;
	groundfix.filter.maskBits = A_BALL;

	// bottom
	groundBox.SetAsBox(screenWidth / 2 / RATIO, 0, b2Vec2(0, -screenHeight / 2 / RATIO), 0);
	groundBody->CreateFixture(&groundfix);

	// top
	groundBox.SetAsBox(screenWidth / 2 / RATIO, 0, b2Vec2(0, screenHeight / 2 / RATIO), 0);
	groundBody->CreateFixture(&groundfix);

	// left
	groundBox.SetAsBox(0, screenHeight / 2 / RATIO, b2Vec2(-screenWidth / 2 / RATIO, 0), 0);
	groundBody->CreateFixture(&groundfix);

	// right
	groundBox.SetAsBox(0, screenHeight / 2 / RATIO, b2Vec2(screenWidth / 2 / RATIO, 0), 0);
	groundBody->CreateFixture(&groundfix);


	CSJson::Value root;
	CSJson::Reader reader;
	char filename[20];
	unsigned long filesize;
	sprintf(filename, "level%d.JSON", currentLevel);
	string levelepath = FileUtils::getInstance()->fullPathForFilename(filename);
	unsigned char* data = FileUtils::getInstance()->getFileData(levelepath.c_str(), "r", &filesize);
	bool parsingSuccessful = reader.parse((const char*) data, root);
	CSJson::Value gameOb = root["gameObjects"];

	//Parse level objects
	for (CSJson::Value obs : gameOb){
		float width = obs.get("width", 0).asFloat();
		float height = obs.get("height", 0).asFloat();
		float radius = obs.get("radius", 0).asFloat();
		int force = obs.get("force", 0).asInt();
		float angle = obs.get("angle", 0).asFloat();
		Point point = Point(obs.get("x", 0).asFloat(), obs.get("y", 0).asFloat());
		string go = obs.get("type", "Invalid").asString();
		if (go == "ball")
			balls.push_back(new Ball(world, Point(factorX*point.x, factorY * point.y), radius * factorY, A_BALL, A_SENSOR | BOUNDARY | A_BALL));
		else if (go == "wall")
			gameObjects.push_back((Entity*) new ABlock(world, Point(factorX*point.x, factorY * point.y), factorX * width, factorY * height, BOUNDARY, A_BALL));
		else if (go == "thruster")
			gameObjects.push_back((Entity*) new Thruster(world, force, Point(factorX * point.x, factorY * point.y), width * factorX, height * factorY, angle, A_SENSOR, A_BALL));
		else if (go == "hole")
			gameObjects.push_back((Entity*) new Hole(world, Point(factorX*point.x, factorY * point.y), radius * factorY, A_SENSOR, A_BALL));
		else if (go == "endzone")
			endzones.push_back((EndZone*) new EndZone(world, Point(factorX*point.x, factorY * point.y), radius * factorY, A_SENSOR, A_BALL));
		else if (go == "antiaccel")
			gameObjects.push_back((Entity*) new AntiAccel(world, Point(factorX*point.x, factorY * point.y), factorX * width, factorY*height, A_SENSOR, A_BALL));
	}
}
LevelLayer::~LevelLayer()
{
	CC_SAFE_DELETE(world);

	gameObjects.clear();
	endzones.clear();
	balls.clear();
	delete m_debugDraw;
}

void LevelLayer::draw()
{
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);

	kmGLPushMatrix();

	for (int i = 0; i < designWidth; i += designWidth / 20)
		m_debugDraw->DrawSegment(b2Vec2(i / RATIO*factorX, 0), b2Vec2(i / RATIO*factorX, screenHeight / RATIO), b2Color(0, 1, 1), .2);
	for (int i = 0; i < designHeight; i += designHeight / 20)
		m_debugDraw->DrawSegment(b2Vec2(0, i / RATIO*factorY), b2Vec2(screenWidth / RATIO, i / RATIO*factorY), b2Color(0, 1, 1), .2);

	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects[i]->render(m_debugDraw);
	for (int i = 0; i < balls.size(); i++)
		balls[i]->render(m_debugDraw);

	for (int i = 0; i < endzones.size(); i++)
		endzones[i]->render(m_debugDraw);


	kmGLPopMatrix();

	CHECK_GL_ERROR_DEBUG();
}



void LevelLayer::tick(float dt)
{

	int velocityIterations = 8;
	int positionIterations = 1;

	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	if (!paused){
		world->Step(dt, velocityIterations, positionIterations);
		
		//Iterate over the bodies in the physics world
		//Currently not need since objects self update
	/*	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
		{
			if (b->GetUserData() != NULL) {
			}
		}
	*/
		
		for (int i = 0; i < balls.size(); i++)
			if (!balls[i]->isAlive) {
				balls[i]->sendToStart();
			}

			bool complete = true;
			for (int i = 0; i < endzones.size(); i++)
				if (endzones[i]->hasBall == 0)
					complete = false;
			if (complete){
				this->unschedule(schedule_selector(LevelLayer::tick));
				Director::getInstance()->replaceScene(LevelLayer::scene(++currentLevel));
			}
	}
}


void LevelLayer::onAcceleration(Acceleration* acceleration, Event* event)
{
	static float prevX = 0, prevY = 0;
	const float kFilterFactor = 0.8f;
	float accelX = (float) acceleration->x * kFilterFactor + (1 - kFilterFactor)*prevX;
	float accelY = (float) acceleration->y * kFilterFactor + (1 - kFilterFactor)*prevY;

	prevX = accelX;
	prevY = accelY;

	// accelerometer values are in "Portrait" mode. Change them to Landscape left
	// multiply the gravity by 10
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	b2Vec2 gravity( -accelY*10, accelX*10);    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)      
	b2Vec2 gravity( accelX*10, accelY*10);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_PLATFORM_MAC)      
	b2Vec2 gravity(accelX * 10, accelY * 10);
#endif

	world->SetGravity(gravity);
}

void LevelLayer::menuPauseCallback(Object* pSender){
	if (!paused){
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		pauseMenu();
	}
	else{
		this->removeChildByTag(10, true);
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

	}

	paused = !paused;
}

void LevelLayer::menuExitCallback(Object* pSender){
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->end();
	Director::getInstance()->replaceScene(MainMenuLayer::scene());
}


void LevelLayer::pauseMenu(){
	MenuItemFont::setFontSize(50 * factorY);
	MenuItemFont* item1 = MenuItemFont::create("Exit", CC_CALLBACK_1(LevelLayer::menuExitCallback, this));
	Menu* menu1 = Menu::create(item1, nullptr);
	menu1->setTag(10);
	this->addChild(menu1, 0);
	menu1->alignItemsVertically();
	menu1->setPosition(scaledWidth / 2 , scaledHeight / 2);
}


Scene* LevelLayer::scene(int level){
	
	Scene *scene = Scene::create();
	currentLevel = level;
	// add layer as a child to scene
	auto layer = new LevelLayer();
	scene->addChild(layer);
	layer->release();

	return TransitionMoveInR::create(0.2f, scene);;
}
