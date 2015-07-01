#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Grid : public CCObject
{
public:
	Grid(int _id);
	int id;
	int x,y;//行，列
	int num;//格子上棋子的数量
	int stondid[3];//格子上棋子的id
	void idToXY(int _id, int &_x, int &_y);
	void xyToID(int _x, int _y,int &_id);

};