
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
    
    visibleSize = Director::getInstance()->getVisibleSize();//�����Ե�Ϊ��λ�� OpenGL ��ͼ�Ĵ�С.
    origin = Director::getInstance()->getVisibleOrigin();//returns �Ե�Ϊ��λ�� OpenGL ��ͼ�ĳ�ʼ��ʱ�Ŀɼ���С

	//���ó�ʼ����
	this->black=true;		//���Ϊ�ڷ�
	this->isBlack=true;		//�ڷ�����
	_isSeleted = false;
	//��������
	qiPan = Sprite::create("JunYi_QiPan2.png");
    qiPan->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	this->addChild(qiPan, 1);

	
	

	//��ʼ��81������
	for(int i = 0;i<81;i++)
	{
		_g4[i] = new Grid(i);
		//CCLog("i=%1d,x=%1d,y=%1d",i,_g4[i]->x ,_g4[i]->y);
	}


	//������
	
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
	


	//ѡ������ʾ
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
	// ����һ���¼�����������Ϊ OneByOne �ĵ��㴥��
    auto listener4 = EventListenerTouchOneByOne::create();
    // �����Ƿ���û�¼����� onTouchBegan �������� true ʱ��û
    listener4->setSwallowTouches(true); 


	listener4->onTouchBegan = [=](Touch* touch,Event* event)  
    {  
    	//��ô������λ��(����)
    	Vec2 ptClick = touch->getLocation();
		//���ԣ���������������
		//CCLog("x=%1f,y=%1f" ,ptClick.x,ptClick.y);

		//���津�������������
		int _tID;
		int _tX,_tY;
		bool blackHe;	//��ѡ����ӵ�����
		
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
	
//����������ת��Ϊ��������
//һ��������ʾ�ض����������
Vec2 FourthScene::getStonePos(int x, int y, int z)
{ 
    int xx = 0.5 * visibleSize.width + (x-5)*(_qiPanCanShu[y-1].jianGe);
	
    int yy = _qiPanCanShu[y-1].gaoDu + (z-1)*_qiPanCanShu[y-1].dieJiaGao;
	//int yy = _qiPanCanShu[y-1].gaoDu;
	//CCLog("x=%1d,y=%1d", x,y);
	//CCLog("xx=%1d,yy=%1d" ,xx,yy);

   return Vec2(xx, yy);
}

//�ж������Ƿ�����������
bool FourthScene::canMove(int ids,int x ,int y)
{
	//���ѡ�е�����
    Stone* s = _s4[ids];
	

    //���ӵ�����
    switch(s->getType())
    {
        //�����������
        case Stone::WANG:
        {
            return canMoveWang(ids, x, y);
        }
        break;

        //�̵��������
        case Stone::REN:
        {
            return canMoveRen(ids, x, y);
        }
        break;

        //կ���������
        case Stone::ZHAI:
        {
            return canMoveZhai(ids, x, y);
        }
        break;
       
        //����������
        case Stone::DA:
        {
            return canMoveDa(ids, x, y);
        }
        break;
       
        //����������
        case Stone::MA:
        {
            return canMoveMa(ids, x, y);
        }
        break;
    
        //Ͳ���������
        case Stone::TONG:
        {
            return canMoveTong(ids, x, y);
        }
        break;
     
        //�ڵ��������
        case Stone::PAO:
        {
            return canMovePao(ids, x, y);
        }
        break;

		//�����������
		case Stone::GONG:
        {
            return canMoveGone(ids, x, y);
        }
        break;
    
        //С���������
        case Stone::XIAO:
        {
            return canMoveXiao(ids, x, y);
        }
        break;
     
        //�е��������
        case Stone::ZHONG:
        {
            return canMoveZhong(ids, x, y);
        }
        break;
		//�����������
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

//�õ�������������ϵ������
//���������λ���������ⷵ��false
//ͨ��������������������
bool FourthScene::getClickPos(Vec2 ptInWin, int &x, int &y)
{
    
        
	for(x=1; x<=9; x++)
    {
        for(y=1; y<=9; y++)
        {
            //���������ϵĸ����ڴ����ϵ�λ��
            Vec2  ptInPlate = getStonePos(x, y ,1);

           //CCLog("ptInPlate.x=%lf   ptInPlate.y=%lf", ptInPlate.x,  ptInPlate.y);

            //Ѱ�����������λ�þ���С�����ӵİ뾶�ĸ���
            //����ҵ���,return true,���򷵻� return false
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


//(x��y)�������ӣ�������������

int FourthScene::getStone(int x,int y)
{
	int g_id;
	
	g_id = (y-1)*9 + x-1;
	return _g4[g_id]->num;


}
//����(x��y)���������ӵ�id
int FourthScene::getStoneId(int x,int y,int num)
{
	int g_id;	
	g_id = (y-1)*9 + x-1;
	return _g4[g_id]->stondid[num-1];


}

//����
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
		//�ı����̲���
		
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



//�����������
bool canMoveWang(int ids,int x,int  y)
{
	return true;
}
//�̵��������
bool canMoveRen(int ids,int  x,int  y){
	return true;
}
//կ���������
bool canMoveZhai(int ids,int  x,int  y){
	return true;
}
//����������
bool canMoveDa(int ids,int  x,int  y){
	return true;
}
//����������
bool canMoveMa(int ids,int  x,int  y){
	return true;
}
//Ͳ���������
bool canMoveTong(int ids,int  x,int  y){
	return true;
}
//�ڵ��������
 bool canMovePao(int ids,int  x,int  y){
	return true;
}
//�����������
bool canMoveGone(int ids,int  x,int  y){
	return true;
}
//С���������
bool canMoveXiao(int ids,int  x,int  y){
	return true;
}
//�е��������
bool canMoveZhong(int ids,int  x,int  y){
	return true;
};
//�����������
bool canMoveBing(int ids,int  x,int  y){
	return true;
}
