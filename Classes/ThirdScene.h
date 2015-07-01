//�������
#pragma once

#include "cocos2d.h"
#include "Stone.h"
#include "Grid.h"

extern Stone*  _s1[50];
extern Grid*  _g1[81];


USING_NS_CC;


class ThirdScene : public cocos2d::Layer
{
public:
 
    static cocos2d::Scene* createScene();
    virtual bool init();      
    CREATE_FUNC(ThirdScene);
	
	//���̲���
	Vec2 origin;
	Size visibleSize; 
	
	//����Ƿ�Ϊ�ڷ�
	bool black;

	//����������ת��Ϊ��������
	//һ��������ʾ�ض����������
	Vec2 changeStonePos(int x, int y, int z);
	
	//��ȡ�崦����ת��Ϊ��������
	//һ�����ڳ�ʼ��ʱ����ʾ��е�����
	Vec2 changeHePos(int x, int y, bool isblack);

	Vec2 changeMiPos(int mID, bool isblack);

	//�õ�������������ϵ������
	//���������λ���������ⷵ��false
	//ͨ��������������������
	bool getPanPos(Vec2 ptInWin, int &x, int &y);	
	//��ú���λ��
	//�õ������������ϵ������
	bool getHePos(Vec2 ptInWin, int &id, bool &blackMi);
	//������̵�λ��
	bool getMiPos(Vec2 ptInWin, bool &blackMi);
	//50������
	Stone* _s[50];
	//���ӵ�ֱ��
    float _d;
	//���ӵ�ƫ����
    cocos2d::Vec2 _stoneOffset; 
	bool stoneMoveable(int keyid,int toX,int toY);	
	//��¼��˭���壨�Ƿ��Ǻڷ����壩
	bool isBlack;
	//�Ƿ�ѡ�����ӣ���ѡ��
	bool _isSeleted;
	//��ѡ�����ӵ�id
	int _sID;	
	//������ȥ����
	void stoneMoveToPan(int keyid,int toX,int toY);
	//������ȥ����
	void stoneMoveToMi(int keyid, bool blackMi);
	//�����ӵ�����
	int wMiNum;
	//�����ӵ�����
	int bMiNum;
	//������ȥ����(������������������)
	void stoneMoveToPan(int keyid,int toX,int toY,int num);
	//(x��y)�������ӣ�������������
	int getStone(int x,int y);
	//�õ�(x��y)����ȫ�����ӵ�id
	void getStoneId(int x,int y,int num);

	int gridAllStone[2];
	void hadFinish();

	int stepNum;

	//81������
	Grid* _g3[81];



	



};


