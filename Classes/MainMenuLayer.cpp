//
//  MainMenuLayer.cpp
//  Tilter2dx
//
//  Created by Sean on 4/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "MainMenuLayer.h"
#include "SimpleAudioEngine.h"
#include "LevelLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

MainMenuLayer::MainMenuLayer()
{
	setTouchEnabled(true);
	// Font Item

	gdraw = new GLESDebugDraw();

	setTouchEnabled(true);
	setAccelerometerEnabled(true);


	MenuItemFont::setFontSize(40);
	MenuItemFont::setFontName("Courier New");


	MenuItemFont* item = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenuLayer::menuCallback, this));
	MenuItemFont* item1 = MenuItemFont::create("Exit", CC_CALLBACK_1(MainMenuLayer::menuExitCallback, this));
	Menu* menu = Menu::create(item, item1, NULL);
	addChild(menu, -1);
	menu->alignItemsVertically();
	menu->setPosition(screenWidth / 2, screenHeight / 2);


	LabelTTF *label = LabelTTF::create("Tilter 2D", "Marker Felt", 50);
	addChild(label, -1);
	label->setColor(Color3B(255, 0, 0));
	label->setPosition(Point(screenWidth / 2, screenHeight - 50));
}

MainMenuLayer::~MainMenuLayer()
{

}

void MainMenuLayer::draw()
{
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states:  GL_VERTEX_ARRAY, 
	// Unneeded states: GL_TEXTURE_2D, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);

	kmGLPushMatrix();


	for (int i = 0; i < designWidth; i += designWidth / 20)
		gdraw->DrawSegment(b2Vec2(i*factorX, 0), b2Vec2(i*factorX, scaledHeight), b2Color(0, 1, 1), .2);
	for (int i = 0; i < designHeight; i += designHeight / 20)
		gdraw->DrawSegment(b2Vec2(0, i*factorY), b2Vec2(scaledWidth, i*factorY), b2Color(0, 1, 1), .2);

	// restore default GL states

	kmGLPopMatrix();

	CHECK_GL_ERROR_DEBUG();
}

void MainMenuLayer::menuCallback(Object *pSender){
	Director::getInstance()->replaceScene(LevelLayer::scene(1));
}

void MainMenuLayer::menuExitCallback(Object *pSender){
	Director::getInstance()->end();
}

Scene* MainMenuLayer::scene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// add layer as a child to scene
	auto layer = new MainMenuLayer();
	scene->addChild(layer);
	layer->autorelease();;

	return scene;
}
