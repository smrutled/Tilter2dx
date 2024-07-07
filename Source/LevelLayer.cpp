//
//  Level1LayerScene.cpp
//  Tilter2dx
//
//  Created by Sean on 4/15/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//
#include "LevelLayer.h"
#include "MainMenuLayer.h"
#include "audio/AudioEngine.h"
#include "AContactListener.h"
#include "Hole.h"
#include "ABlock.h"
#include "Thruster.h"
#include "AntiAccel.h"
#include <fstream>

using namespace ax;



LevelLayer::LevelLayer() : world(nullptr)
{
    debugDrawNode = g_debugDraw.GetDrawNode();
    addChild(debugDrawNode, 100);
    Device::setAccelerometerEnabled(true);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_PLATFORM_MAC) 
	//setKeyboardEnabled(true);
#endif

    if (AudioEngine::getState(backgroundMusicId) != AudioEngine::AudioState::PLAYING)
    {
        AudioEngine::stopAll();
        backgroundMusicId = AudioEngine::play2d("backround.mp3", true);
    }
           
	
	this->initWorld();
	
	//Pause button
	MenuItemFont::setFontName("fonts/Mark Felt.ttf");
	MenuItemFont* item = MenuItemFont::create("||", CC_CALLBACK_1(LevelLayer::menuPauseCallback, this));
	Menu* menu = Menu::create(item, nullptr);
	menu->setPosition(scaledWidth * 1 / 20, scaledHeight * 9 / 10);
	this->addChild(menu, -1);

	this->schedule([this](float dt) { this->tick(dt); }, "tick");
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

	/*uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	m_debugDraw->SetFlags(flags);*/

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



	char filename[20];
	unsigned long filesize;
	sprintf(filename, "level%d.JSON", currentLevel);
	std::string levelepath = FileUtils::getInstance()->fullPathForFilename(filename);
    auto data    =  FileUtils::getInstance()->getDataFromFile(levelepath);
    rapidjson::Document doc;
    doc.Parse((const char*)data.getBytes(),data.getSize());
    rapidjson::Value& gameOb = doc["gameObjects"];

 // Iterate over the gameObjects object
    for (auto itr = gameOb.MemberBegin(); itr != gameOb.MemberEnd(); ++itr) {
        const rapidjson::Value& obs = itr->value;
        std::string go = obs["type"].GetString();
        Point point = Point(obs["x"].GetFloat(), obs["y"].GetFloat());

        if (go == "ball") {
            float radius = obs["radius"].GetFloat();
            balls.push_back(new Ball(world, Point(factorX*point.x, factorY * point.y), radius * factorY, A_BALL, A_SENSOR | BOUNDARY | A_BALL));
        } else if (go == "wall") {
            float width = obs["width"].GetFloat();
            float height = obs["height"].GetFloat();
            gameObjects.push_back((Entity*) new ABlock(world, Point(factorX*point.x, factorY * point.y), factorX * width, factorY * height, BOUNDARY, A_BALL));
        } else if (go == "thruster") {
            float width = obs["width"].GetFloat();
            float height = obs["height"].GetFloat();
            int force = obs["force"].GetInt();
            float angle = obs["angle"].GetFloat();
            gameObjects.push_back((Entity*) new Thruster(world, force, Point(factorX * point.x, factorY * point.y), width * factorX, height * factorY, angle, A_SENSOR, A_BALL));
        } else if (go == "hole") {
            float radius = obs["radius"].GetFloat();
            gameObjects.push_back((Entity*) new Hole(world, Point(factorX*point.x, factorY * point.y), radius * factorY, A_SENSOR, A_BALL));
        } else if (go == "endzone") {
            float radius = obs["radius"].GetFloat();
            endzones.push_back((EndZone*) new EndZone(world, Point(factorX*point.x, factorY * point.y), radius * factorY, A_SENSOR, A_BALL));
        } else if (go == "antiaccel") {
            float width = obs["width"].GetFloat();
            float height = obs["height"].GetFloat();
            gameObjects.push_back((Entity*) new AntiAccel(world, Point(factorX*point.x, factorY * point.y), factorX * width, factorY * height, A_SENSOR, A_BALL));
        }
    }
}
LevelLayer::~LevelLayer()
{
	CC_SAFE_DELETE(world);

	gameObjects.clear();
	endzones.clear();
	balls.clear();
}

void LevelLayer::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
    debugDrawNode->clear();
    for (int i = 0; i < designWidth; i += designWidth / 20)
    {
        Vec2 start(i * factorX, 0);
        Vec2 end(i * factorX, screenHeight);
        debugDrawNode->drawLine(start, end, Color4F(0, 1, 1, .2));  // Cyan color
    }
    for (int i = 0; i < designHeight; i += designHeight / 20)
    {
        Vec2 start(0, i * factorY);
        Vec2 end(screenWidth, i * factorY);
        debugDrawNode->drawLine(start, end, Color4F(0, 1, 1, .2));  // Cyan color
    }
	

	for (int i = 0; i < gameObjects.size(); i++)
        gameObjects[i]->render(debugDrawNode);
	for (int i = 0; i < balls.size(); i++)
		balls[i]->render(debugDrawNode);

	for (int i = 0; i < endzones.size(); i++)
		endzones[i]->render(debugDrawNode);
    Layer::draw(renderer, transform, flags);
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
                            this->unschedule("tick");
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
        AudioEngine::pause(backgroundMusicId);
		pauseMenu();
	}
	else{
		this->removeChildByTag(10, true);
         AudioEngine::resume(backgroundMusicId);
	}

	paused = !paused;
}

void LevelLayer::menuExitCallback(Object* pSender){

    AudioEngine::stopAll();
    AudioEngine::end();
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
