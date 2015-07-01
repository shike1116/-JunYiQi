#include "ThirdScene.h"
#include "FourthScene.h"
#include <iostream>

USING_NS_CC;
using namespace std;

Stone*  _s1[50];
Grid*  _g1[81];

Scene* ThirdScene::createScene()
{
    
    auto scene = Scene::create();
    auto layer = ThirdScene::create();
    scene->addChild(layer);

    return scene;
}


bool ThirdScene::init()
{
  
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();//返回以点为单位的 OpenGL 视图的大小.
    origin = Director::getInstance()->getVisibleOrigin();//returns 以点为单位的 OpenGL 视图的初始化时的可见大小

	//设置初始参数
	stepNum =0;
	this->black=true;		//玩家为黑方
	this->isBlack=true;	//黑方先下
	this->wMiNum=0;		//白色密子数量为0
	this->bMiNum=0;		//黑色密子数量为0

	//设置棋盘
	auto qiPan = Sprite::create("JunYi_QiPan1.png");
    qiPan->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	this->addChild(qiPan, 1);
		
	//设置棋子显示的参数
	this->_d = 60;
	this->_stoneOffset = cocos2d::Point(340,60);

	for(int i = 0;i<81;i++)
	{
		_g3[i] = new Grid(i);
		//CCLog("i=%1d,x=%1d,y=%1d",i,_g4[i]->x ,_g4[i]->y);
	}

/*
	//摆棋子
	_s[2] = Stone::create(1, black);
	_s[2] -> setPosition(this->getStonePos(_s[2]->getX(), _s[2]->getY(),_s[2]->getZ()));
	_s[2] ->setScale(0.25f);
	this->addChild(_s[2],(_s[2]->getZ()+1));
*/
/*
	//摆棋子
	for(int i = 0; i< 25; i++)
	{
		_s[i] = Stone::create(i, black);
		_s[i] -> setPosition(this->getStonePos(_s[i]->getX(), _s[i]->getY(),_s[i]->getZ()));
		_s[i] ->setScale(0.25f);
		this->addChild(_s[i],(_s[i]->getZ()+1));
	}
*/

	for(int i=0; i<25; i++)
	{
		_s[i] = Stone::create(i, black);
		_s[i] -> setPosition(this->changeHePos(_s[i]->getX(), _s[i]->getY(),true));
		_s[i] ->setScale(0.15f);
		this->addChild(_s[i],(_s[i]->getZ()+3));
	}

	
	for(int i=25; i<50; i++)
	{
		_s[i] = Stone::create(i, black);
		_s[i] -> setPosition(this->changeHePos(_s[i]->getX(), _s[i]->getY(),false));
		_s[i] ->setScale(0.15f);
		this->addChild(_s[i],(_s[i]->getZ()+1));
	}
	
	/*
	_s[30] = Stone::create(30, black);
	_s[30] -> setPosition(this->changeHePos(_s[30]->getX(), _s[30]->getY(),false));
	_s[30] ->setScale(0.15f);
	this->addChild(_s[30],(_s[30]->getZ()+1));
	*/
	//选择框的显示
	auto selector = Sprite::create("JunYi_Select1.png");
	selector ->setPosition(Vec2(200,200));
	this->addChild(selector,10);
	selector ->setScale(.4f);
	selector ->setVisible(false);
	this->_isSeleted = false;

	auto dispatcher2 = Director::getInstance()->getEventDispatcher(); 
	// 创建一个事件监听器类型为 OneByOne 的单点触摸
    auto listener2 = EventListenerTouchOneByOne::create();
    // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
    listener2->setSwallowTouches(true); 


	listener2->onTouchBegan = [=](Touch* touch,Event* event)  
    {  
    	//获得触摸点的位置(坐标)
    	Vec2 ptClick = touch->getLocation();
		//测试：输出触摸点的坐标
		//CCLog("x=%1f,y=%1f" ,ptClick.x,ptClick.y);

		//保存触摸点的棋盘坐标
		int _tID;
		int _tX,_tY;
		bool blackHe;	//被选择盒子的类型
		//第一步：在棋盒选棋
		if(getHePos(ptClick, _tID, blackHe))
        {
			if(blackHe == isBlack)
			{
				CCMoveTo* moveTo3 = CCMoveTo::create(.2f,_s[_tID]->getPosition());			
				selector->runAction(moveTo3);
				_sID = _tID;
			//CCLog("1111111=%d" ,_tID);
			//CCLog("1111111=%d" ,_sID);
				selector ->setVisible(true);
				_isSeleted = true;
				return true;
			}       
		}
		//第二步：棋子移动到棋盘
		if (getPanPos(ptClick,_tX,_tY) && _isSeleted && stoneMoveable(_sID,_tX,_tY)&&(getStone(_tX,_tY)<3))
		{
			int tNum = getStone(_tX,_tY);
			if(tNum ==0 )
			{
				stoneMoveToPan(_sID,_tX,_tY);
				stepNum++;
				if(stepNum ==50)
				{
					hadFinish();
					return true;
				}
				selector ->setVisible(false);	
				_isSeleted = false;
				isBlack =!isBlack;
				stepNum++;
				return true;
			}else if(tNum ==3)
			{
				return false;
			}
			else
			{
				getStoneId(_tX , _tY, tNum);
				stepNum++;
				if(stepNum ==50)
				{
					hadFinish();
					return true;
				}
				stoneMoveToPan(_sID,_tX,_tY,tNum);
				selector ->setVisible(false);	
				_isSeleted = false;
				isBlack =!isBlack;
				return true;
			}
			
		}

		/*
		暂时取消密盘
		//第二步：棋子可以移动到密盘
		bool blackMi;	//被选择密盘的类型
		if(getMiPos(ptClick, blackMi) && _isSeleted && blackMi==isBlack)
		{		
			stoneMoveToMi(_sID,blackMi);
			selector ->setVisible(false);
			_isSeleted = false;
			isBlack =!isBlack;
			return true;		
		}
		*/

		return false;

    	
    };  
  
    listener2->onTouchMoved = [=](Touch* touch,Event* event)  
    {  
     
    };  
  
    listener2->onTouchEnded = [=](Touch* touch,Event* event)  
    {  
    //do something  
    }; 

	dispatcher2 ->addEventListenerWithSceneGraphPriority(listener2 ,_s[0]); 
	for(int i=1; i<50; i++)
	{
		dispatcher2->addEventListenerWithSceneGraphPriority(listener2->clone(),_s[i]);
	}


	//测试
	auto dian = Sprite::create("Text01.png");
	dian ->setPosition(Vec2(1140,90));
	this->addChild(dian,3);

	//测试得到数据
	//155 105 左下 取棋处 -1，-1
	//305 255 右上 取棋处 -1，-1
	//370 90  左下 棋盘 0，0
	//910 630 右上 棋盘 0，0
	//975-2 465-2 左下 取棋处 1，1
	//1125-2 615-2 右上 取棋处 1，1

	//140 630 左上 -1 1
	//320 630 右上
	//320 450 右下

	//960 270 左上 1 -1
	//1140 90 右下 1 -1

    return true;
}
//棋盘的
//将棋盘坐标转化为窗口坐标
//一般用于显示特定坐标的棋子
Vec2 ThirdScene::changeStonePos(int x, int y, int z)
{ 
	int xx, yy;
	
	xx = x * _d;
	yy = y * _d;
	return Vec2(xx, yy) + _stoneOffset;

}
Vec2 ThirdScene::changeHePos(int x, int y, bool isblack)
{
	int xx,yy;
	if(isblack)
	{
		if(y%5 == 0)
		{
			xx =(y/5)* 30;
			yy = 5* 30;
		}
		else
		{
			xx = (y/5+1)* 30;
			yy = (y%5)* 30;
		}

		return Vec2(xx, yy) + Vec2(140, 90);
	}
	else
	{
		if(y%5 == 0)
		{
			xx =(y/5)* 30;
			yy = 5* 30;
		}
		else
		{
			xx = (y/5+1)* 30;
			yy = (y%5)* 30;
		}

		return  Vec2(1138, 628) - Vec2(xx, yy) ;

	}
		


	
}

Vec2 ThirdScene::changeMiPos(int mID, bool isblack)
{
	int xx,yy;
	if(!isblack)
	{
		if(mID%5 == 0)
		{
			xx =(mID/5)* 36;
			yy = 5* 36;
		}
		else
		{
			xx = (mID/5+1)* 36;
			yy = (mID%5)* 36;
		}

		return Vec2(xx, yy) + Vec2(122, 432);

	}else
	{
		if(mID%5 == 0)
		{
			xx =(mID/5)* 36;
			yy = 5* 36;
		}
		else
		{
			xx = (mID/5+1)* 36;
			yy = (mID%5)* 36;
		}

		return  Vec2(1158, 288) - Vec2(xx, yy) ;

	}
}
 
//获得棋盘上的位置
bool ThirdScene::getPanPos(Vec2 ptInWin, int &x, int &y)
{
    
	
	for(x=1; x<=9; x++)
    {
        for(y=1; y<=9; y++)
        {
            //计算棋盘上的格子在窗口上的位置
            Vec2  ptInPlate = changeStonePos(x, y,1);

           // CCLog("ptInPlate.x=%lf   ptInPlate.y=%lf", ptInPlate.x,  ptInPlate.y);

            //寻找与鼠标点击的位置距离小于棋子的半径的格子
            //如果找到了,return true,否则返回 return false
            if(ptInWin.getDistance(ptInPlate) < 28)
            {
                return true;
            }
        }
    }

    return false;

}
//获得盒子位置
//得到鼠标点击在棋盒上的坐标点
bool ThirdScene::getHePos(Vec2 ptInWin, int &id,bool &blackMi)
{
	if((155<ptInWin.x) &&(305>ptInWin.x) &&(105< ptInWin.y) &&(255>ptInWin.y))
	{
		blackMi = true;
		for(id=0; id<25;id++)
		{
		if(ptInWin.getDistance(_s[id]->getPosition()) < 15)
            {
                return true;
            }
	
		}
	}else if((975<ptInWin.x) &&(1125>ptInWin.x) &&(465<ptInWin.y) &&(615>ptInWin.y))
	{
		blackMi = false;
		for(id=25; id<50;id++)
		{
		if(ptInWin.getDistance(_s[id]->getPosition()) < 15)
            {
                return true;
            }
	
		}
	}
	
	return false;
}

//获得密盘的位置
bool ThirdScene::getMiPos(Vec2 ptInWin,bool &blackMi)
{
	if((140< ptInWin.x) &&(320>ptInWin.x) &&(450< ptInWin.y) &&(630>ptInWin.y))
	{
		blackMi = false;//白色密盘
		return true;
	}else if((960< ptInWin.x) &&(1140>ptInWin.x) &&(90< ptInWin.y) &&(270>ptInWin.y))
	{
		blackMi = true;//黑色密盘
		return true;
	}
	return false;
}
//判断棋子是否可以下
bool ThirdScene::stoneMoveable(int keyid,int toX,int toY)
{
	if((_s[keyid]->getBlack())&&(toY<4))
	{
		return true;
	}
	else if(!(_s[keyid]->getBlack())&&(toY>6))
	{
		return true;
	}else
	{
		return false;
	}
}

//棋子移去棋盘
void ThirdScene::stoneMoveToPan(int keyid,int toX,int toY)
{	
	CCScaleTo*  scaleTo1 = CCScaleTo::create(.2f, .25f);
	CCMoveTo*   moveTo1  = CCMoveTo:: create(.2f,changeStonePos(toX,toY,1));
	CCSpawn*	spawn1   = CCSpawn::create(moveTo1, scaleTo1 , NULL);

	_s[keyid]-> runAction(spawn1);
	_s[keyid]->setX(toX);
	_s[keyid]->setY(toY);
	_s[keyid]->setZ(1);

	_g3[(toY-1)*9 + toX-1]->num=1;
	_g3[(toY-1)*9 + toX-1]->stondid[0]=keyid;
	//CCLog("keyid=%d" ,keyid);
	//CCLog("(toY-1)*9 + toX-1=%d" ,(toY-1)*9 + toX-1);
	
	
}
//棋子移去棋盘(考虑了棋盘上有棋子)
void ThirdScene::stoneMoveToPan(int keyid,int toX,int toY,int num)
{	
	Vec2 toVec2 = (Vec2)changeStonePos(toX,toY,1);
	
	_s[keyid]-> setPositionZ(num+4);
	

	_g3[(toY-1)*9 + toX-1]->num = num+1;
	_g3[(toY-1)*9 + toX-1]->stondid[num]=keyid;
	

	if(num==1)
	{
		
		CCScaleTo*  scaleTo2 = CCScaleTo::create(.2f, .23f);
		CCMoveTo*   moveTo2  = CCMoveTo:: create(.2f,Vec2(toVec2.x,toVec2.y+5));
		CCSpawn*	spawn2   = CCSpawn::create(moveTo2, scaleTo2 , NULL);
		_s[keyid]-> runAction(spawn2);

		CCScaleTo*  scaleTo3 = CCScaleTo::create(.2f, .23f);
		CCMoveTo*   moveTo3  = CCMoveTo:: create(.2f,Vec2(toVec2.x,toVec2.y-5));
		CCSpawn*	spawn3   = CCSpawn::create(moveTo3, scaleTo3 , NULL);
		_s[gridAllStone[0]]-> runAction(spawn3);

	}else if(num == 2)
	{
		
		CCScaleTo*  scaleTo5 = CCScaleTo::create(.2f, .2f);
		CCMoveTo*   moveTo5 = CCMoveTo:: create(.2f,Vec2(toVec2.x,toVec2.y+5));
		CCSpawn*	spawn5   = CCSpawn::create(moveTo5, scaleTo5 , NULL);
		_s[keyid]-> runAction(spawn5);

		CCScaleTo*  scaleTo6 = CCScaleTo::create(.2f, .2f);
		CCMoveTo*   moveTo6  = CCMoveTo:: create(.2f,Vec2(toVec2.x,toVec2.y));
		CCSpawn*	spawn6   = CCSpawn::create(moveTo6, scaleTo6 , NULL);
		_s[gridAllStone[1]]-> runAction(spawn6);

		CCScaleTo*  scaleTo7 = CCScaleTo::create(.2f, .2f);
		CCMoveTo*   moveTo7  = CCMoveTo:: create(.2f,Vec2(toVec2.x,toVec2.y-5));
		CCSpawn*	spawn7   = CCSpawn::create(moveTo7, scaleTo7 , NULL);
		_s[gridAllStone[0]]-> runAction(spawn7);

	}

	//_s[i] ->setScale(0.15f);
	//this->addChild(_s[i],(_s[i]->getZ()+3));

	_s[keyid]->setX(toX);
	_s[keyid]->setY(toY);
	_s[keyid]->setZ(num+1);
	
	
	
}

//棋子移去密盘
void ThirdScene::stoneMoveToMi(int keyid,bool blackMi)
{
	CCScaleTo*  scaleTo1 = CCScaleTo::create(.2f, .16f);
	CCMoveTo*   moveTo1;
	if(blackMi)
	{
		this->bMiNum++;
		moveTo1  = CCMoveTo:: create(.2f,changeMiPos(bMiNum,blackMi));
		_s[keyid]->setY(bMiNum);
	}else
	{
		this->wMiNum++;
		moveTo1  = CCMoveTo:: create(.2f,changeMiPos(wMiNum,blackMi));
		_s[keyid]->setY(wMiNum);
	}
	
	CCSpawn*	spawn1   = CCSpawn::create(moveTo1, scaleTo1 , NULL);

	_s[keyid]-> runAction(spawn1);
	_s[keyid]->setX(11);
	
	
}

//(x，y)上有棋子，返回棋子数量

int ThirdScene::getStone(int x,int y)
{
	int g_id;
	
	g_id = (y-1)*9 + x-1;
	return _g3[g_id]->num;


}
//得到(x，y)上面全部棋子的id
void ThirdScene::getStoneId(int x,int y,int num)
{
	int g_id;	
	g_id = (y-1)*9 + x - 1;
	if(num==1)
	{
		//CCLog("g_id=%d" ,g_id);
		gridAllStone[0] =_g3[g_id]->stondid[0];
		gridAllStone[1] =0;
	}
	else if(num==2)
	{
		gridAllStone[0] =_g3[g_id]->stondid[0];
		gridAllStone[1] =_g3[g_id]->stondid[1];
	}
}

void ThirdScene::hadFinish()
{
	for(int i=0 ;i<50;i++)
	{
		_s1[i] = _s[i];
	}
	for(int j=0 ;j<81;j++)
	{
		_g1[j] = _g3[j];
	}
	CCDirector::sharedDirector()->replaceScene(FourthScene::createScene());
	CCLog("keyid=hahahah" );
}
/*
bool ThirdScene::getStone(int x, int y, int &num)
{
	num = 0;
	bool noZero = false;
	Stone* s;
    //遍历50个棋子
    for(int i=0; i<50; i++)
    {
        s = _s[i];
		
        if(s->getX() == x && s->getY() == y )
        {
            num++;
			noZero = true;
        }
    }
	return noZero;

}
*/