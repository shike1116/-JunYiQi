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
	//��ʼ��ť
	void gamestart(Ref* pSender);
	//����ť
	void gamerule(Ref* pSender);
	//���ڰ�ť
	void gameabout(Ref* pSender);
	
	


};


