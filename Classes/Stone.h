#pragma once

#include "cocos2d.h"
USING_NS_CC;
class Stone :
	public cocos2d::Sprite
{
public:
	
	Stone();
	//���ӵ�����
	//��1 ��1 ��1 ��1 ��2 Ͳ2 ��2 ��2 С2 ��2 ��9 
	enum TYPE{WANG,REN,ZHAI,DA,MA,TONG,PAO,GONG,XIAO,ZHONG,BING};

	//��������
	//��һ�����������ӵ�����
	//�ڶ������������ӵ���ɫ
	static Stone* create (int id, bool black);

	//��ʼ������
	bool init(int id, bool black);

	//������
	void reset(bool black);

	//����ÿ�����ӵĳ�ʼλ��
	static struct InitPos
	{
		int _x;
		int _y;
		int _z;
		Stone::TYPE _type;

	}_initPos1[25];
/*�����޸Ĺ� 25��� 50*/
	CC_SYNTHESIZE(TYPE , _type, Type);
	CC_SYNTHESIZE(int , _x, X);
	CC_SYNTHESIZE(int , _y, Y);
	CC_SYNTHESIZE(int , _z, Z);
	//���ӵ�ID��0-31��
	CC_SYNTHESIZE(int , _id, ID);
	//�����Ƿ񱻳�
	CC_SYNTHESIZE(bool , _dead, Dead);
	//���ӵ���ɫ
	CC_SYNTHESIZE(bool , _black, Black);

	//��������
	//��һ�����������ӵ�����
	//�ڶ������������ӵ���ɫ
	static Stone* create2 (int id, bool black);

	//��ʼ������
	bool init2(int id, bool black);
	


};