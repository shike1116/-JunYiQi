#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Grid : public CCObject
{
public:
	Grid(int _id);
	int id;
	int x,y;//�У���
	int num;//���������ӵ�����
	int stondid[3];//���������ӵ�id
	void idToXY(int _id, int &_x, int &_y);
	void xyToID(int _x, int _y,int &_id);

};