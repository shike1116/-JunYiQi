#pragma once
#include "ThirdScene.h"
#include "cocos2d.h"

USING_NS_CC;


class FirstScene : public cocos2d::Layer
{
public:
 
    static cocos2d::Scene* createScene();
    virtual bool init();      
    CREATE_FUNC(FirstScene);
	//开始按钮
	void gamestart(Ref* pSender);
	//规则按钮
	void gamerule(Ref* pSender);
	//关于按钮
	void gameabout(Ref* pSender);
	
	


};


