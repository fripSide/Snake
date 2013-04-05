#ifndef Snake_h__
#define Snake_h__
/***********************************************
* @file      Snake.h
* @brief     ��Ҫ˵��
*
* ����������
*	1.��������������snake����ʵ��ԭ��
*	2.���ƽ���͹���
*	3.�Ľ�
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
//���Ͻ�Ϊԭ�㣬x��������Ϊ���ң�y��������Ϊ����
//������� = ������ - 1������ - 1��
//-----------------------------------------------
extern void setPos(unsigned x,unsigned y);

//-----------------------------------------------
//���ÿ���̨�����ɫ���������������
//-----------------------------------------------
extern void setColor(WORD);

struct Body
{
	unsigned x;
	unsigned y;
	std::string shape;
	Body* next;
	Body():next(NULL),x(11),y(15),shape("��"){
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
//��ͼ������:30*13
//��ͼ�ڲ���Ч���꣺
//	�У�3 <= x <= 57,���Ϊ2
//	�У�2 <= y <= 24,���Ϊ1
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
//��Ϸ��������
//-----------------------------------------------
class GameScene
{

};
#endif // Snake_h__
