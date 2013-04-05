#ifndef Snake_h__
#define Snake_h__
/***********************************************
* @file      Snake.h
* @brief     简要说明
*
* 迭代开发：
*	1.蛇能跑起来，在snake类中实现原型
*	2.完善界面和功能
*	3.改进
* 
* @author    snk
* @version   0.1
* @date      2013/04/04
***********************************************/
#include <windows.h>
#include <iostream>
#include <cassert>
#include <memory>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "conio.h"

//-----------------------------------------------
//左上角为原点，x轴正方向为向右，y轴正方向为向下
//点的坐标 = （列数 - 1，行数 - 1）
//-----------------------------------------------
extern void setPos(unsigned x,unsigned y);

//-----------------------------------------------
//设置控制台输出颜色，红绿蓝自由组合
//-----------------------------------------------
extern void setColor(WORD);

struct Body
{
	unsigned x;
	unsigned y;
	std::string shape;
	Body* next;
	Body():next(NULL),x(11),y(15),shape("■"){
	}
	Body(unsigned lx,unsigned ly,std::string s):next(NULL),
		x(lx),y(ly),shape(s){
	}
	Body(const Body& body):next(body.next),x(body.x),
		y(body.y),shape(body.shape){
	}
	bool operator == (const Body& body){
		return (x == body.x) && (y == body.y);
	}
};


class Map;
class Snake
{
public:
	Snake();
	~Snake(){}
	enum Direction{
		Right = 1,
		Left,
		Up,
		Down
	};


	void Game();
	void Move();
	void PaintSnake();
	void AddFood();
	void Eat();
	bool GameOver();
	
private:
	int Length;
	Body* head;
	Direction dirt;
	bool  eatFood;
	std::vector<Body> foodlist;
	std::shared_ptr<Map> m_map;
};

//-----------------------------------------------
//地图管理类:30*13
//地图内部有效坐标：
//	行：3 <= x <= 57,间隔为2
//	列：2 <= y <= 24,间隔为1
//-----------------------------------------------
class Map
{
public:
	Map():height(13),width(30){}
	~Map(){}
	void PaintMap();

	//unsigned** mappoints;
	unsigned height; //13
	unsigned width;  //30
};

//-----------------------------------------------
//游戏场景控制
//-----------------------------------------------
class GameScene
{

};
#endif // Snake_h__
