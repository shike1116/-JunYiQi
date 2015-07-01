
#include "FourthScene.h"
#include <iostream>


USING_NS_CC;
using namespace std;



Scene* FourthScene::createScene()
{
    auto scene = Scene::create();
    auto layer = FourthScene::create();
    scene->addChild(layer);

    return scene;
}


bool FourthScene::init()
{
	
  
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();//返回以点为单位的 OpenGL 视图的大小.
    origin = Director::getInstance()->getVisibleOrigin();//returns 以点为单位的 OpenGL 视图的初始化时的可见大小

	//设置初始参数
	this->black=true;		//玩家为黑方
	this->isBlack=true;		//黑方先下
	_isSeleted = false;
	//设置棋盘
	qiPan = Sprite::create("JunYi_QiPan2.png");
    qiPan->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	this->addChild(qiPan, 1);

	
	

	//初始化81个格子
	for(int i = 0;i<81;i++)
	{
		_g4[i] = new Grid(i);
		//CCLog("i=%1d,x=%1d,y=%1d",i,_g4[i]->x ,_g4[i]->y);
	}


	//摆棋子
	
	for(int i = 0;i <50 ;i++)
	{
		_s4[i] = Stone::create2(i, black);
		_s4[i]->setX(_s1[i] ->getX());
		_s4[i]->setY(_s1[i] ->getY());
		_s4[i]->setZ(_s1[i] ->getZ());
		_s4[i] -> setPosition(this->getStonePos(_s4[i]->getX(), _s4[i]->getY(),_s4[i]->getZ()));
		//CCLog("i=%1d,_s[i].z=%1d",i ,_s4[i]->getZ());
		//CCLog("_s[i].x=%1d,_s[i].y=%1d", _s4[i]->getX(),_s4[i]->getY());
		_s4[i] ->setScale(_qiPanCanShu[_s4[i]->getY()-1].qiZhiDaXiao);
		int j = (_s4[i]->getY()-1)*9 + _s4[i]->getX()-1;
		int a5 = _g4[j]->num ;
		_g4[j]->num = a5 + 1;
		_g4[j]->stondid[a5] = i;
		_s4[i]->setVisible(true);
		this->addChild(_s4[i],(_s4[i]->getZ()+3));
	}
	
	/*
	int c=49;
	for(int i = 1;i <= 9 ;i++)
	{
		for(int j = 1; j <= 9 ; j++)
		{
			_s[c] = Stone::create(c, black);
			_s[c] -> setPosition(this->getStonePos(i,j,1));
			_s[c]->setVisible(true);
			_s[c] ->setScale(_qiPanCanShu[j-1].qiZhiDaXiao);
			this->addChild(_s[c],10);
		}
	}
	*/
	/*
	for(int i = 1;i <= 9 ;i++)
	{
		_s[1] = Stone::create(1, black);
		_s[1] -> setPosition(this->getStonePos(i,1,1));
		_s[1]->setVisible(true);
		_s[1] ->setScale(0.5f);
		this->addChild(_s[1],10);
	}
	*/
	


	//选择框的显示
	selector = Sprite::create("JunYi_Select2.png");
	selector ->setPosition(Vec2(100,100));
	this->addChild(selector,20);
	selector ->setScale(.3f);
	selector ->setVisible(true);
	selector->setAnchorPoint(ccp(0.5,1));
	this->_isSeleted = false;
	selector ->setPositionZ(21);
/*
	for(int i = 0;i<81;i++)
	{
		
		CCLog("g=%1d,num=%1d",i,_g4[i]->num );
	}
*/

	auto dispatcher4 = Director::getInstance()->getEventDispatcher(); 
	// 创建一个事件监听器类型为 OneByOne 的单点触摸
    auto listener4 = EventListenerTouchOneByOne::create();
    // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
    listener4->setSwallowTouches(true); 


	listener4->onTouchBegan = [=](Touch* touch,Event* event)  
    {  
    	//获得触摸点的位置(坐标)
    	Vec2 ptClick = touch->getLocation();
		//测试：输出触摸点的坐标
		//CCLog("x=%1f,y=%1f" ,ptClick.x,ptClick.y);

		//保存触摸点的棋盘坐标
		int _tID;
		int _tX,_tY;
		bool blackHe;	//被选择盒子的类型
		
		if(getClickPos(ptClick,_tX,_tY))
		{
			//CCMoveTo* moveTo5 = CCMoveTo::create(.2f,getStonePos(_tX,_tY,1));
			//selector->runAction(moveTo5);
			//qiPan->setPositionZ(10); 
			CCLog("x=%1d,y=%1d" ,_tX,_tY);
			return walkStone(_tX,_tY);
			//CCLog("x=%1d,y=%1d" ,_tX,_tY);
			//return true;
		}
		
		return false;

		
    	
    };  
  
    listener4->onTouchMoved = [=](Touch* touch,Event* event)  
    {  
     
    };  
  
    listener4->onTouchEnded = [=](Touch* touch,Event* event)  
    {  
    //do something  
    }; 

	dispatcher4 ->addEventListenerWithSceneGraphPriority(listener4 ,_s4[0]); 
	for(int i=1; i<50; i++)
	{
		dispatcher4->addEventListenerWithSceneGraphPriority(listener4->clone(),_s4[i]);
	}
	
 
    return true;
}
	
//将棋盘坐标转化为窗口坐标
//一般用于显示特定坐标的棋子
Vec2 FourthScene::getStonePos(int x, int y, int z)
{ 
    int xx = 0.5 * visibleSize.width + (x-5)*(_qiPanCanShu[y-1].jianGe);
	
    int yy = _qiPanCanShu[y-1].gaoDu + (z-1)*_qiPanCanShu[y-1].dieJiaGao;
	//int yy = _qiPanCanShu[y-1].gaoDu;
	//CCLog("x=%1d,y=%1d", x,y);
	//CCLog("xx=%1d,yy=%1d" ,xx,yy);

   return Vec2(xx, yy);
}

//判断棋子是否符合行棋规则
bool FourthScene::canMove(int ids,int x ,int y)
{
	//获得选中的棋子
    Stone* s = _s4[ids];
	

    //棋子的类型
    switch(s->getType())
    {
        //王的走棋规则
        case Stone::WANG:
        {
            return canMoveWang(ids, x, y);
        }
        break;

        //忍的走棋规则
        case Stone::REN:
        {
            return canMoveRen(ids, x, y);
        }
        break;

        //寨的走棋规则
        case Stone::ZHAI:
        {
            return canMoveZhai(ids, x, y);
        }
        break;
       
        //大的走棋规则
        case Stone::DA:
        {
            return canMoveDa(ids, x, y);
        }
        break;
       
        //马的走棋规则
        case Stone::MA:
        {
            return canMoveMa(ids, x, y);
        }
        break;
    
        //筒的走棋规则
        case Stone::TONG:
        {
            return canMoveTong(ids, x, y);
        }
        break;
     
        //炮的走棋规则
        case Stone::PAO:
        {
            return canMovePao(ids, x, y);
        }
        break;

		//弓的走棋规则
		case Stone::GONG:
        {
            return canMoveGone(ids, x, y);
        }
        break;
    
        //小的走棋规则
        case Stone::XIAO:
        {
            return canMoveXiao(ids, x, y);
        }
        break;
     
        //中的走棋规则
        case Stone::ZHONG:
        {
            return canMoveZhong(ids, x, y);
        }
        break;
		//兵的走棋规则
		case Stone::BING:
        {
            return canMoveBing(ids, x, y);
        }
        break;
        default:
        {
            break;
        }
    }

    return false;
}

//得到鼠标点击在棋盘上的坐标点
//当鼠标点击的位置在棋盘外返回false
//通过窗口坐标获得棋盘坐标
bool FourthScene::getClickPos(Vec2 ptInWin, int &x, int &y)
{
    
        
	for(x=1; x<=9; x++)
    {
        for(y=1; y<=9; y++)
        {
            //计算棋盘上的格子在窗口上的位置
            Vec2  ptInPlate = getStonePos(x, y ,1);

           //CCLog("ptInPlate.x=%lf   ptInPlate.y=%lf", ptInPlate.x,  ptInPlate.y);

            //寻找与鼠标点击的位置距离小于棋子的半径的格子
            //如果找到了,return true,否则返回 return false
            if(ptInWin.getDistance(ptInPlate) < 0.5*(_qiPanCanShu[y-1].jianGe))
            {
                return true;
            }
        }
    }

    return false;
}

FourthScene::QiPanCanShu FourthScene::_qiPanCanShu[9] =
{
	{145, 95, 0.53f, 13},
	{221, 90, 0.50f, 12},
	{291, 86, 0.47f, 12},
	{355, 82, 0.44f, 11},
	{415, 78, 0.41f, 11},
	{469, 75, 0.38f, 10},
	{518, 73, 0.35f, 10},
	{565, 71, 0.32f, 9},
	{609, 68, 0.29f, 9},
};


//(x，y)上有棋子，返回棋子数量

int FourthScene::getStone(int x,int y)
{
	int g_id;
	
	g_id = (y-1)*9 + x-1;
	return _g4[g_id]->num;


}
//返回(x，y)最上面棋子的id
int FourthScene::getStoneId(int x,int y,int num)
{
	int g_id;	
	g_id = (y-1)*9 + x-1;
	return _g4[g_id]->stondid[num-1];


}

//走棋
bool FourthScene::walkStone(int x,int y)
{
	
	int num;
	num = getStone(x,y);
	CCLog("num=%ld", num);
	if(_isSeleted)
	{
		if(num == 0)
			{
				if(canMove(seletedKeyId,x,y))
				{
					this->keyMoveToFree(this->seletedKeyId,x,y);
				    return true;
				}
				else
				{
					return false;
				}

			}
		else if(num == 3)
		{
			
			if(_s4[getStoneId(x,y,num)]->getBlack()==isBlack)
				{
					
				    return false;
				}
				else
				{
					if(canMove(seletedKeyId,x,y))
					{
						this->keyMoveTo(this->seletedKeyId,x,y);
						return true;
					}
					else
					{
						return false;
					}
				}
		}
		else
			{				
				if(canMove(seletedKeyId,x,y))
				{
					this->keyMoveTo(this->seletedKeyId,x,y);
					return true;
				}
				else
				{					
					return false;		
				}
			}
	}else
		{
			if(num == 0)
			{
				return false;
			}
			else
			{
				int g_id = (y-1)*9 + x-1;
				CCLog("g_id=%ld", g_id);
				int clickid = _g4[g_id]->stondid[num-1];
				CCLog("num-1=%ld", num-1);

				CCLog("clickid=%ld", clickid);
				if(_s4[clickid]->getBlack() == isBlack)
				{
					seletedMoveTo(x,y);
					return true;
				}
				else
				{
					return false;
				}
			}

		}

}
void FourthScene::keyMoveToFree(int keyid,int toX,int toY){
	int g_id2 = (toY-1)*9 + toX-1;
	_s4[keyid]->setPositionZ(4);
	//_s4[keyid] ->setScale(_qiPanCanShu[_s4[keyid]->getY()-1].qiZhiDaXiao);
	CCMoveTo* moveTo6 = CCMoveTo::create(.2f, getStonePos(toX,toY,1));
	CCScaleTo*  scaleTo6 = CCScaleTo::create(.2f, _qiPanCanShu[toY-1].qiZhiDaXiao);
	//CCMoveTo* moveTo6 = CCMoveTo::create(.2f, getStonePos(toX,toY,numTo+1));
	CCSpawn*	spawn6   = CCSpawn::create(moveTo6, scaleTo6 , NULL);
	_s4[keyid]->runAction(spawn6);
	_s4[keyid]->setX(toX);
	_s4[keyid]->setY(toY);
	_s4[keyid]->setZ(1);

	_g4[seletedGridId]->stondid[_g4[seletedGridId]->num-1]=0;
	_g4[seletedGridId]->num--;
	int a7 = _g4[seletedGridId]->num;
	//CCLog("_g4[seletedGridId]-num=%ld, num=%ld,num-1=%ld,", 
	//	a7,_g4[seletedGridId]->stondid[a7],_g4[seletedGridId]->stondid[a7-1]);

	_g4[g_id2]->stondid[0]=seletedKeyId;
	_g4[g_id2]->num = 1;
	//CCLog("g_id2=%ld",g_id2);
	this->_isSeleted = false;
	this->selector->setVisible(false);
	this->isBlack = !isBlack;

}

void FourthScene::keyMoveTo(int keyid,int toX,int toY)
{
	int g_id2 = (toY-1)*9 + toX-1;
	int numTo = _g4[g_id2]->num;
	int clickid = _g4[g_id2]->stondid[numTo-1];

	if(_s4[clickid]->getBlack() == isBlack)
	{
		_s4[keyid]->setPositionZ(numTo+4);
		//_s4[keyid] ->setScale(_qiPanCanShu[_s4[keyid]->getY()-1].qiZhiDaXiao);
		CCScaleTo*  scaleTo5 = CCScaleTo::create(.2f, _qiPanCanShu[toY-1].qiZhiDaXiao);
		CCMoveTo* moveTo5 = CCMoveTo::create(.2f, getStonePos(toX,toY,numTo+1));
		CCSpawn*	spawn5   = CCSpawn::create(moveTo5, scaleTo5 , NULL);
		_s4[keyid]->runAction(spawn5);
		
		_s4[keyid]->setZ(numTo+1);
		//改变棋盘参数
		
		_g4[seletedGridId]->stondid[_g4[seletedGridId]->num-1]=0;
		_g4[seletedGridId]->num--;

		_g4[g_id2]->stondid[_g4[g_id2]->num]=seletedKeyId;
		_g4[g_id2]->num++;
		

	}
	else
	{
		_s4[keyid]->setPositionZ(numTo+3);
		
		CCScaleTo*  scaleTo4 = CCScaleTo::create(.2f, _qiPanCanShu[toY-1].qiZhiDaXiao);
		CCMoveTo*   moveTo4  = CCMoveTo:: create(.2f,getStonePos(toX,toY,numTo));
		CCSpawn*	spawn4   = CCSpawn::create(moveTo4, scaleTo4 , NULL);
		_s4[keyid]->runAction(spawn4);	
		_s4[keyid]->setZ(numTo);

		_s4[clickid] ->setDead(true);
		_s4[clickid] ->setVisible(false);
		

		_g4[seletedGridId]->stondid[_g4[seletedGridId]->num-1]=0;
		_g4[seletedGridId]->num--;

		_g4[g_id2]->stondid[_g4[g_id2]->num-1]=seletedKeyId;
		

	}
	_s4[keyid]->setX(toX);
	_s4[keyid]->setY(toY);
	
	this->_isSeleted = false;
	this->selector->setVisible(false);
	this->isBlack = !isBlack;
	
}
void FourthScene::seletedMoveTo(int toX,int toY)
{
	CCMoveTo* moveTo5 = CCMoveTo::create(.2f,  getStonePos(toX,toY,1));
	selector->runAction(moveTo5);
	int g_id2 = (toY-1)*9 + toX-1;
	int numTo = _g4[g_id2]->num;
	int clickid = _g4[g_id2]->stondid[numTo-1];
	this->selector->setVisible(true);
	
	this->_isSeleted = true;
	this->seletedKeyId = clickid;
	this->seletedGridId = g_id2;
	CCLog("seletedKeyId=%ld", seletedKeyId);

}



//王的走棋规则
bool canMoveWang(int ids,int x,int  y)
{
	return true;
}
//忍的走棋规则
bool canMoveRen(int ids,int  x,int  y){
	return true;
}
//寨的走棋规则
bool canMoveZhai(int ids,int  x,int  y){
	return true;
}
//大的走棋规则
bool canMoveDa(int ids,int  x,int  y){
	return true;
}
//马的走棋规则
bool canMoveMa(int ids,int  x,int  y){
	return true;
}
//筒的走棋规则
bool canMoveTong(int ids,int  x,int  y){
	return true;
}
//炮的走棋规则
 bool canMovePao(int ids,int  x,int  y){
	return true;
}
//弓的走棋规则
bool canMoveGone(int ids,int  x,int  y){
	return true;
}
//小的走棋规则
bool canMoveXiao(int ids,int  x,int  y){
	return true;
}
//中的走棋规则
bool canMoveZhong(int ids,int  x,int  y){
	return true;
};
//兵的走棋规则
bool canMoveBing(int ids,int  x,int  y){
	return true;
}
