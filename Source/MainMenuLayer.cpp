//
//  MainMenuLayer.cpp
//  Tilter2dx
//
//  Created by Sean on 4/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "MainMenuLayer.h"
#include "LevelLayer.h"

using namespace ax;
MainMenuLayer::MainMenuLayer()
{
	// Font Item

	debugDrawNode = g_debugDraw.GetDrawNode();
    addChild(debugDrawNode, 100);


    Device::setAccelerometerEnabled(true);


	MenuItemFont::setFontSize(40);
	MenuItemFont::setFontName("fonts/Courier New.ttf");


	MenuItemFont* item = MenuItemFont::create("Play", AX_CALLBACK_1(MainMenuLayer::menuCallback, this));
    MenuItemFont* item1 = MenuItemFont::create("Exit", AX_CALLBACK_1(MainMenuLayer::menuExitCallback, this));
	Menu* menu = Menu::create(item, item1, nullptr);
	addChild(menu, -1);
	menu->alignItemsVertically();
	menu->setPosition(screenWidth / 2, screenHeight / 2);


	auto label = Label::createWithTTF("Tilter 2D", "fonts/Marker Felt.ttf", 50);
	addChild(label, -1);
	label->setColor(Color3B(255, 0, 0));
	label->setPosition(Point(screenWidth / 2, screenHeight - 50));
}

MainMenuLayer::~MainMenuLayer()
{

}

void MainMenuLayer::draw(ax::Renderer* renderer, const Mat4& transform, uint32_t flags)
{
	 //// Ensure debugDrawNode is cleared from previous frame's drawings
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

    // Draw grid lines
   /* for (int i = 0; i < designWidth; i += designWidth / 20)
        debugDrawNode->drawSegment(Vec2(i * factorX, 0), Vec2(i * factorX, scaledHeight), 0.2f, Color4F(0, 1, 1, 1));
    for (int i = 0; i < designHeight; i += designHeight / 20)
        debugDrawNode->drawSegment(Vec2(0, i * factorY), Vec2(scaledWidth, i * factorY), 0.2f, Color4F(0, 1, 1, 1));*/
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
