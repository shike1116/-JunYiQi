#include "Stone.h"

Stone::Stone(void)
{
}

Stone* Stone::create (int id, bool black)
{
	Stone* s = new Stone();

	s ->init(id, black);
    s ->autorelease();

	return s;
}

bool Stone:: init(int id, bool black)
{
	_id = id;
	_black = _id < 25;
	if(_id < 25)
	{
		_type = _initPos1[_id]._type;
	}
	else
	{
		_type = _initPos1[_id-25]._type;
	}

	
//需修改	
	const char* stonePic1[22] =
	{
		"JunYi_BWang1.png",
		"JunYi_BRen1.png",
		"JunYi_BZhai1.png",
		"JunYi_BDa1.png",
		"JunYi_BMa1.png",
		"JunYi_BTong1.png",
		"JunYi_BPao1.png",
		"JunYi_BGong1.png",
		"JunYi_BXiao1.png",
		"JunYi_BZhong1.png",
		"JunYi_BBing1.png",

		"JunYi_WWang1.png",
		"JunYi_WRen1.png",
		"JunYi_WZhai1.png",
		"JunYi_WDa1.png",
		"JunYi_WMa1.png",
		"JunYi_WTong1.png",
		"JunYi_WPao1.png",
		"JunYi_WGong1.png",
		"JunYi_WXiao1.png",
		"JunYi_WZhong1.png",
		"JunYi_WBing1.png",
	};


	const char* stonePic2[22] =
	{
		"JunYi_BWang2.png",
		"JunYi_BRen2.png",
		"JunYi_BZhai2.png",
		"JunYi_BDa2.png",
		"JunYi_BMa2.png",
		"JunYi_BTong2.png",
		"JunYi_BPao2.png",
		"JunYi_BGong2.png",
		"JunYi_BXiao2.png",
		"JunYi_BZhong2.png",
		"JunYi_BBing2.png",

		"JunYi_WWang2.png",
		"JunYi_WRen2.png",
		"JunYi_WZhai2.png",
		"JunYi_WDa2.png",
		"JunYi_WMa2.png",
		"JunYi_WTong2.png",
		"JunYi_WPao2.png",
		"JunYi_WGong2.png",
		"JunYi_WXiao2.png",
		"JunYi_WZhong2.png",
		"JunYi_WBing2.png",
	};

	int idx = (_black ? 0 : 1 )* 11 + _type;

	Sprite::initWithFile(stonePic1[idx]);
	reset(black);
	//setScale(.53f);
	return true;
}
/*下面面修改过*/
void Stone::reset(bool black)
{
    //刚摆棋子的时候棋子没被吃掉
   this->setDead(false);
    
   if(black)
   {
	   /*
	   原本
	   */
	   if(_id < 25)
	   {
			//设置棋子的x坐标
			this->setX(_initPos1[_id]._x);
			//设置棋子的y坐标
			this->setY(_initPos1[_id]._y);
			//设置棋子的z坐标
			this->setZ(_initPos1[_id]._z);            
	   }
	   else
	   {
		   //设置棋子的x坐标
			this->setX(_initPos1[_id-25]._x);
			//设置棋子的y坐标
			this->setY(_initPos1[_id-25]._y);
			//设置棋子的z坐标
			this->setZ(_initPos1[_id-25]._z); 
	   
	   }

	   /*
       //改为
	   //设置棋子的x坐标
		this->setX(_initPos[_id]._x);
		//设置棋子的y坐标
		this->setY(_initPos[_id]._y);
		//设置棋子的z坐标
		this->setZ(_initPos[_id]._z);
		*/
   }
 
         
    
}


Stone::InitPos Stone::_initPos1[25] =
{
    {10, 1, 0, Stone::WANG},
 
    {10, 2, 0, Stone::REN},

	{10, 3, 0, Stone::ZHAI},
 
    {10, 4, 0, Stone::DA},
	
	{10, 5, 0, Stone::MA},
	{10, 6, 0, Stone::MA},
 
    {10, 7, 0, Stone::TONG},
	{10, 8, 0, Stone::TONG},
	
	{10, 9, 0, Stone::PAO},
	{10, 10, 0, Stone::PAO},
 
    {10, 11, 0, Stone::GONG},
	{10, 12, 0, Stone::GONG},
	
	{10, 13, 0, Stone::XIAO},
	{10, 14, 0, Stone::XIAO},
 
    {10, 15, 0, Stone::ZHONG},
	{10, 16, 0, Stone::ZHONG},

	{10, 17, 0, Stone::BING},
	{10, 18, 0, Stone::BING},
	{10, 19, 0, Stone::BING},
	{10, 20, 0, Stone::BING},
	{10, 21, 0, Stone::BING},
	{10, 22, 0, Stone::BING},
	{10, 23, 0, Stone::BING},
	{10, 24, 0, Stone::BING},
	{10, 25, 0, Stone::BING},
    
};

/*
Stone::InitPos Stone::_initPos[50] =
{
  
    { 1, 1, 1, Stone::WANG}, 
	{ 1, 2, 1, Stone::WANG},
	{ 1, 3, 1, Stone::WANG},
	{ 1, 4, 1, Stone::WANG},
	{ 1, 5, 1, Stone::WANG},

    { 1, 6, 1, Stone::WANG}, 
	{ 1, 7, 1, Stone::WANG},
	{ 1, 8, 1, Stone::WANG},
	{ 1, 9, 1, Stone::WANG},
	{ 1, 4, 2, Stone::WANG},

    { 2, 1, 1, Stone::WANG}, 
	{ 2, 2, 1, Stone::WANG},
	{ 2, 3, 1, Stone::WANG},
	{ 2, 4, 1, Stone::WANG},
	{ 2, 5, 1, Stone::WANG},

    { 2, 6, 1, Stone::WANG}, 
	{ 2, 7, 1, Stone::WANG},
	{ 2, 8, 1, Stone::WANG},
	{ 2, 9, 1, Stone::WANG},
	{ 2, 5, 2, Stone::WANG},

	{ 3, 2, 1, Stone::WANG}, 
	{ 3, 3, 1, Stone::WANG},
	{ 3, 4, 1, Stone::WANG},
	{ 3, 5, 1, Stone::WANG},
	{ 3, 6, 1, Stone::WANG},

	{ 9, 1, 1, Stone::WANG}, 
	{ 9, 2, 1, Stone::WANG},
	{ 9, 3, 1, Stone::WANG},
	{ 9, 4, 1, Stone::WANG},
	{ 9, 5, 1, Stone::WANG},

    { 9, 6, 1, Stone::WANG}, 
	{ 9, 7, 1, Stone::WANG},
	{ 9, 8, 1, Stone::WANG},
	{ 9, 9, 1, Stone::WANG},
	{ 9, 4, 2, Stone::WANG},

    { 7, 1, 1, Stone::WANG}, 
	{ 7, 2, 1, Stone::WANG},
	{ 7, 3, 1, Stone::WANG},
	{ 7, 4, 1, Stone::WANG},
	{ 7, 5, 1, Stone::WANG},

    { 7, 6, 1, Stone::WANG}, 
	{ 5, 7, 1, Stone::WANG},
	{ 5, 8, 1, Stone::WANG},
	{ 5, 9, 1, Stone::WANG},
	{ 5, 5, 2, Stone::WANG},

	{ 5, 2, 1, Stone::WANG}, 
	{ 5, 3, 1, Stone::WANG},
	{ 5, 4, 1, Stone::WANG},
	{ 5, 5, 1, Stone::WANG},
	{ 5, 6, 1, Stone::WANG},
    
};
*/
/*
Stone::InitPos Stone::_initPos[25] =
{
  
    { 10, 1, 0, Stone::WANG}, 
	{ 10, 2, 0, Stone::WANG},
	{ 10, 3, 0, Stone::WANG},
	{ 10, 4, 0, Stone::WANG},
	{ 10, 5, 0, Stone::WANG},

    { 10, 6, 0, Stone::WANG}, 
	{ 10, 7, 0, Stone::WANG},
	{ 10, 8, 0, Stone::WANG},
	{ 10, 9, 0, Stone::WANG},
	{ 10, 10, 0, Stone::WANG},

    { 10, 11, 0, Stone::WANG}, 
	{ 10, 12, 0, Stone::WANG},
	{ 10, 13, 0, Stone::WANG},
	{ 10, 14, 0, Stone::WANG},
	{ 10, 15, 0, Stone::WANG},

    { 10, 16, 0, Stone::WANG}, 
	{ 10, 17, 0, Stone::WANG},
	{ 10, 18, 0, Stone::WANG},
	{ 10, 19, 0, Stone::WANG},
	{ 10, 20, 0, Stone::WANG},

	{ 10, 21, 0, Stone::WANG}, 
	{ 10, 22, 0, Stone::WANG},
	{ 10, 23, 0, Stone::WANG},
	{ 10, 24, 0, Stone::WANG},
	{ 10, 25, 0, Stone::WANG},


	
};
*/
/*上面修改过 25变成 50*/

Stone* Stone::create2 (int id, bool black)
{
	Stone* s = new Stone();

	s ->init(id, black);
    s ->autorelease();

	return s;
}

bool Stone:: init2(int id, bool black)
{
	_id = id;
	_black = _id < 25;
	if(_id < 25)
	{
		_type = _initPos1[_id]._type;
	}
	else
	{
		_type = _initPos1[_id-25]._type;
	}

	



	const char* stonePic2[22] =
	{
		"JunYi_BWang2.png",
		"JunYi_BRen2.png",
		"JunYi_BZhai2.png",
		"JunYi_BDa2.png",
		"JunYi_BMa2.png",
		"JunYi_BTong2.png",
		"JunYi_BPao2.png",
		"JunYi_BGong2.png",
		"JunYi_BXiao2.png",
		"JunYi_BZhong2.png",
		"JunYi_BBing2.png",

		"JunYi_WWang2.png",
		"JunYi_WRen2.png",
		"JunYi_WZhai2.png",
		"JunYi_WDa2.png",
		"JunYi_WMa2.png",
		"JunYi_WTong2.png",
		"JunYi_WPao2.png",
		"JunYi_WGong2.png",
		"JunYi_WXiao2.png",
		"JunYi_WZhong2.png",
		"JunYi_WBing2.png",
	};

	int idx = (_black ? 0 : 1 )* 11 + _type;

	Sprite::initWithFile(stonePic2[idx]);
	
	//setScale(.53f);
	return true;
}