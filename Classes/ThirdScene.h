//摆棋界面
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
	
	//棋盘参数
	Vec2 origin;
	Size visibleSize; 
	
	//玩家是否为黑方
	bool black;

	//将棋盘坐标转化为窗口坐标
	//一般用于显示特定坐标的棋子
	Vec2 changeStonePos(int x, int y, int z);
	
	//将取棋处坐标转化为窗口坐标
	//一般用于初始化时，显示棋盒的棋子
	Vec2 changeHePos(int x, int y, bool isblack);

	Vec2 changeMiPos(int mID, bool isblack);

	//得到鼠标点击在棋盘上的坐标点
	//当鼠标点击的位置在棋盘外返回false
	//通过窗口坐标获得棋盘坐标
	bool getPanPos(Vec2 ptInWin, int &x, int &y);	
	//获得盒子位置
	//得到鼠标点击在棋盒上的坐标点
	bool getHePos(Vec2 ptInWin, int &id, bool &blackMi);
	//获得密盘的位置
	bool getMiPos(Vec2 ptInWin, bool &blackMi);
	//50个棋子
	Stone* _s[50];
	//棋子的直径
    float _d;
	//棋子的偏移量
    cocos2d::Vec2 _stoneOffset; 
	bool stoneMoveable(int keyid,int toX,int toY);	
	//记录该谁下棋（是否是黑方行棋）
	bool isBlack;
	//是否选中棋子（被选择）
	bool _isSeleted;
	//被选中棋子的id
	int _sID;	
	//棋子移去棋盘
	void stoneMoveToPan(int keyid,int toX,int toY);
	//棋子移去密盘
	void stoneMoveToMi(int keyid, bool blackMi);
	//白密子的数量
	int wMiNum;
	//黑密子的数量
	int bMiNum;
	//棋子移去棋盘(考虑了棋盘上有棋子)
	void stoneMoveToPan(int keyid,int toX,int toY,int num);
	//(x，y)上有棋子，返回棋子数量
	int getStone(int x,int y);
	//得到(x，y)上面全部棋子的id
	void getStoneId(int x,int y,int num);

	int gridAllStone[2];
	void hadFinish();

	int stepNum;

	//81个格子
	Grid* _g3[81];



	



};


