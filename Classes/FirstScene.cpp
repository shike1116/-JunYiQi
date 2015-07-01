#include "FirstScene.h"
#include <iostream>

USING_NS_CC;
using namespace std;



Scene* FirstScene::createScene()
{
    
    auto scene = Scene::create();
    auto layer = FirstScene::create();
    scene->addChild(layer);

    return scene;
}


bool FirstScene::init()
{
  
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();//返回以点为单位的 OpenGL 视图的大小.
    auto origin = Director::getInstance()->getVisibleOrigin();//returns 以点为单位的 OpenGL 视图的初始化时的可见大小

	auto bg = Sprite::create("FirstSceneBg.png");
    bg->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	this->addChild(bg, 1);

	auto space = 100;

	auto startItem = MenuItemImage::create( "ButtonStart.png","ButtonStart.png",
                                           CC_CALLBACK_1(FirstScene::gamestart, this));
	//startItem ->setScale(0.5);
	startItem->setPosition(Vec2(640,300));

	auto ruleItem = MenuItemImage::create( "ButtonRule.png","ButtonRule.png",
                                           CC_CALLBACK_1(FirstScene::gamerule, this));
	//ruleItem  ->setScale(0.5);
	ruleItem ->setPositionX(startItem ->getPositionX());
	ruleItem ->setPositionY(startItem ->getPositionY() - space);

	auto aboutItem = MenuItemImage::create( "ButtonAbout.png","ButtonAbout.png",
                                           CC_CALLBACK_1(FirstScene::gameabout, this));
	//aboutItem  ->setScale(0.5);
	aboutItem ->setPositionX(startItem ->getPositionX());
	aboutItem ->setPositionY(startItem ->getPositionY() - 2*space);

	 auto menu = Menu::create(startItem,ruleItem,aboutItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 3);
	
	
 
    return true;
}


void FirstScene::gamestart(Ref* pSender)
{
	CCDirector::sharedDirector()->replaceScene(ThirdScene::createScene());
}

void FirstScene::gamerule(Ref* pSender)
{

}

void FirstScene::gameabout(Ref* pSender)
{
}