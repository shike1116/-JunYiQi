//�������(����ͼ)
#pragma once

#include "cocos2d.h"
#include "Stone.h"
#include "Grid.h"
#include "ThirdScene.h"
USING_NS_CC;


class FourthScene : public cocos2d::Layer
{
public:
 
    static cocos2d::Scene* createScene();
    virtual bool init();      
    CREATE_FUNC(FourthScene);
	
	//��������
	Vec2 origin;
	Size visibleSize; 
	cocos2d::Sprite* selector;
	cocos2d::Sprite* qiPan ;

	//��������
	static struct QiPanCanShu
	{
		int gaoDu;
		int jianGe;
		float qiZhiDaXiao;
		int dieJiaGao;
	}_qiPanCanShu[9];


	int gaoDu;
	int jianGe;
	float qiZhiDaXiao;
	int dieJiaGao;
	
	//����Ƿ�Ϊ�ڷ�
	bool black;

	//����������ת��Ϊ��������
	//һ��������ʾ�ض����������
	Vec2 getStonePos(int x, int y, int z);

	//�õ�������������ϵ������
	//���������λ���������ⷵ��false
	//ͨ��������������������
	bool getClickPos(Vec2 ptInWin, int &x, int &y);
	
	//�Ƿ��Ǻڷ�����
	bool isBlack;

	//�Ƿ�ѡ��
	bool _isSeleted;
	//��ѡ�����ӵ�ID
	int seletedKeyId;
	//��ѡ�����̵�ID
	int seletedGridId;

	//50������
	Stone* _s4[50];
	
	//�ж������Ƿ�����������
	bool canMove(int ids,int x ,int y);

	//�����������
    bool canMoveWang(int ids,int x,int  y);
    //�̵��������
    bool canMoveRen(int ids,int  x,int  y);
    //կ���������
    bool canMoveZhai(int ids,int  x,int  y);
    //����������
    bool canMoveDa(int ids,int  x,int  y);
    //����������
    bool canMoveMa(int ids,int  x,int  y);
     //Ͳ���������
    bool canMoveTong(int ids,int  x,int  y);
    //�ڵ��������
    bool canMovePao(int ids,int  x,int  y);
	//�����������
	bool canMoveGone(int ids,int  x,int  y);
	//С���������
	bool canMoveXiao(int ids,int  x,int  y);
	//�е��������
	bool canMoveZhong(int ids,int  x,int  y);
	//�����������
	bool canMoveBing(int ids,int  x,int  y);




	//81������
	Grid* _g4[81];

	//(x��y)�������ӣ�������������
	int getStone(int x,int y );
	bool walkStone(int x,int y);
	void keyMoveTo(int keyid,int toX,int toY);

	void keyMoveToFree(int keyid,int toX,int toY);
	void seletedMoveTo(int toX,int toY);
	int getStoneId(int x,int y,int num);



};


