#pragma once

#include "cocos2d.h"
USING_NS_CC;
class Stone :
	public cocos2d::Sprite
{
public:
	
	Stone();
	//棋子的类型
	//王1 忍1 砦1 大1 马2 筒2 炮2 弓2 小2 中2 兵9 
	enum TYPE{WANG,REN,ZHAI,DA,MA,TONG,PAO,GONG,XIAO,ZHONG,BING};

	//创建棋子
	//第一个参数：棋子的类型
	//第二个参数：棋子的颜色
	static Stone* create (int id, bool black);

	//初始化棋子
	bool init(int id, bool black);

	//摆棋子
	void reset(bool black);

	//保存每个棋子的初始位置
	static struct InitPos
	{
		int _x;
		int _y;
		int _z;
		Stone::TYPE _type;

	}_initPos1[25];
/*上面修改过 25变成 50*/
	CC_SYNTHESIZE(TYPE , _type, Type);
	CC_SYNTHESIZE(int , _x, X);
	CC_SYNTHESIZE(int , _y, Y);
	CC_SYNTHESIZE(int , _z, Z);
	//棋子的ID（0-31）
	CC_SYNTHESIZE(int , _id, ID);
	//棋子是否被吃
	CC_SYNTHESIZE(bool , _dead, Dead);
	//棋子的颜色
	CC_SYNTHESIZE(bool , _black, Black);

	//创建棋子
	//第一个参数：棋子的类型
	//第二个参数：棋子的颜色
	static Stone* create2 (int id, bool black);

	//初始化棋子
	bool init2(int id, bool black);
	


};