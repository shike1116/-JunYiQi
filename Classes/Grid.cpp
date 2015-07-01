#include "Grid.h"

Grid::Grid(int _id)
{
	this->id = _id;
	idToXY(id,this->x,this->y);
	this->num = 0;

}

void Grid:: idToXY(int _id, int &_x, int &_y)
{
	if((_id+1)%9 ==0)
	{
		_x = 9;
		_y = (_id+1)/9;
	}else
	{
		_x = (_id+1)%9;
		_y = (_id+1)/9+1;
	}
}



void Grid::xyToID(int _x,int _y,int &_id)
{
	_id = (_y-1)*9 + _x;
}
