//行棋界面(侧视图)
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
	
	//棋盘属性
	Vec2 origin;
	Size visibleSize; 
	cocos2d::Sprite* selector;
	cocos2d::Sprite* qiPan ;

	//棋子属性
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
	
	//玩家是否为黑方
	bool black;

	//将棋盘坐标转化为窗口坐标
	//一般用于显示特定坐标的棋子
	Vec2 getStonePos(int x, int y, int z);

	//得到鼠标点击在棋盘上的坐标点
	//当鼠标点击的位置在棋盘外返回false
	//通过窗口坐标获得棋盘坐标
	bool getClickPos(Vec2 ptInWin, int &x, int &y);
	
	//是否是黑方行棋
	bool isBlack;

	//是否被选择
	bool _isSeleted;
	//被选中棋子的ID
	int seletedKeyId;
	//被选中棋盘的ID
	int seletedGridId;

	//50个棋子
	Stone* _s4[50];
	
	//判断棋子是否符合行棋规则
	bool canMove(int ids,int x ,int y);

	//王的走棋规则
    bool canMoveWang(int ids,int x,int  y);
    //忍的走棋规则
    bool canMoveRen(int ids,int  x,int  y);
    //寨的走棋规则
    bool canMoveZhai(int ids,int  x,int  y);
    //大的走棋规则
    bool canMoveDa(int ids,int  x,int  y);
    //马的走棋规则
    bool canMoveMa(int ids,int  x,int  y);
     //筒的走棋规则
    bool canMoveTong(int ids,int  x,int  y);
    //炮的走棋规则
    bool canMovePao(int ids,int  x,int  y);
	//弓的走棋规则
	bool canMoveGone(int ids,int  x,int  y);
	//小的走棋规则
	bool canMoveXiao(int ids,int  x,int  y);
	//中的走棋规则
	bool canMoveZhong(int ids,int  x,int  y);
	//兵的走棋规则
	bool canMoveBing(int ids,int  x,int  y);




	//81个格子
	Grid* _g4[81];

	//(x，y)上有棋子，返回棋子数量
	int getStone(int x,int y );
	bool walkStone(int x,int y);
	void keyMoveTo(int keyid,int toX,int toY);

	void keyMoveToFree(int keyid,int toX,int toY);
	void seletedMoveTo(int toX,int toY);
	int getStoneId(int x,int y,int num);



};


