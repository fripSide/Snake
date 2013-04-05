#include "Snake.h"

//using namespace std;

namespace{
	std::string GetShape(){
		std::random_device rv;
		switch (rv() % 5)
		{
		case 0:
			return "��";
			break;
		case 1:
			return "��";
			break;
		case 2:
			return "��";
			break;
		case 3:
			return "��";
			break;
		case 4:
			return "��";
			break;
		default:
			return " ";
			break;
		}
	}
}

void setPos(unsigned x,unsigned y)
{
	assert(x >=1 && y >= 1);
	COORD point = {x-1, y-1};
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(console,point);
}

void setColor(WORD color)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, 
		color|FOREGROUND_INTENSITY);
}

Snake::Snake():m_map(new Map),foodlist(),Length(1),head(new Body)
{
	eatFood = false;
	m_map->PaintMap();
	dirt = Right;
	Body* node;
	for (int i = 1; i < 4; ++i) {
		node = new Body;
		node->x = head->x + 2;
		node->next = head;
		head = node;
	}
}

void Snake::Game()
{
	PaintSnake();
	char key = 0;
	//��ѭ��
	while (true) {
		if (_kbhit()) { //����м��̲���
			key = _getch();
		}

		if ((key == 'A' || key == 'a') && dirt != Right) { //left
			dirt = Left;
		} else if ((key == 'D' || key == 'd') && dirt != Left) {
			dirt = Right;
		} else if ((key == 'W' || key == 'w') && dirt != Down){
			dirt = Up;
		} else if ((key == 'S' || key == 's') && dirt != Up) {
			dirt = Down;
		} 
		while (_kbhit()) {
			_getch();
		}
		Eat();
		Move();
		if (!GameOver()) {
			system("cls");
			std::cout<<"Game Over";
			return;
		}
		PaintSnake();
		Sleep(300);
	} 
}

void Snake::Move()
{
	Body* node = new Body;
	Length++;
	switch (dirt){
	case Snake::Right:
		node->x = head->x + 2;
		node->y = head->y;
		break;

	case Snake::Left:
		node->x = head->x - 2;
		node->y = head->y;
		
		break;

	case Snake::Up:
		node->x = head->x;
		node->y = head->y - 1;
		break;

	case Snake::Down:
		node->x = head->x;
		node->y = head->y + 1;
		break;
	default:
		assert(0);//"should never get here"
		break;
	}
	node->shape = head->shape;
	node->next  = head;
	head = node;

	if (eatFood) {
		eatFood = false;
		return;
	}

	//ɾ����β
	node = head;
	if (node->next == NULL) {
		return;
	}
	while (node->next->next != NULL) {
		node = node->next;
	}
	setPos(node->next->x,node->next->y);
	std::cout<<" ";
	delete node->next;
	Length--;
	node->next = NULL;
}

void Snake::AddFood()
{
	unsigned lx;
	unsigned ly;
	std::random_device rv;
	Body food;
	int xnums = m_map->width - 2; //28
	int ynums = m_map->height * 2 - 3; //23

	lx = (rv() % xnums) * 2 + 3;//3~57
	ly = (rv() % ynums) + 2;	//2~24
	food.x = lx;
	food.y = ly;
	food.shape = GetShape();
	foodlist.push_back(food);
	setPos(lx,ly);
	setColor(FOREGROUND_BLUE | FOREGROUND_GREEN);
	std::cout<<food.shape;
}

void Snake::Eat()
{
	if (foodlist.size() <= 0) {
		std::random_device rv;
		int i = rv() % 7;
		for (; i > 0; --i) {
			AddFood();
		}
	}
	auto fiter = std::find(foodlist.begin(),foodlist.end(),*head);
	if (fiter != foodlist.end()) {
		foodlist.erase(fiter);
		eatFood = true;
	} else{
		eatFood = false;
	}

	//�ػ�food
	fiter = foodlist.begin();
	setColor(FOREGROUND_BLUE | FOREGROUND_GREEN);
	while (fiter != foodlist.end()) {
		setPos(fiter->x,fiter->y);
		std::cout<<fiter->shape;
		++fiter;
	}
}

bool Snake::GameOver()
{
	if (head->x >= 59 || head->x <= 1 ||
		head->y <= 1 || head->y >= 25) {
		return false;
	} 
	//�ж��Ƿ�ײ������
	Body* node = new Body;
	node = head;
	while (node->next != NULL) {
		node = node->next;
		if (node->x == head->x && node->y == head->y) {
			return false;
		}
	}

	return true;
}

void Snake::PaintSnake()
{
	if (head == NULL) {
		return;
	}
	setColor(FOREGROUND_GREEN);
	Body* node = head;
	while (node != NULL) {
		setPos(node->x,node->y);
		std::cout<<node->shape;
		node = node->next;
	}
}

//-----------------------------------------------
//"��"Ϊ���ַ���ռ2��,60 * 26
//-----------------------------------------------
void Map::PaintMap()
{
	unsigned i = 0;
	setColor(FOREGROUND_RED);
	for (i = 1; i <= width; ++i) { //�ϱ߿�
		setPos(2*i - 1,1);
		std::cout<<"��";
	}
	for (i = 1; i <= height * 2 - 1; ++i) {//��߿�
		setPos(1,i);
		std::cout<<"��";
	}
	for (i = 1; i <= width; ++i) {//�±߿�
		setPos(2*i - 1,height * 2 - 1);
		std::cout<<"��";
	}
	for (i = 1; i <= height * 2 - 1; ++i) {//�ұ߿�
		setPos(width * 2 - 1,i);
		std::cout<<"��";
	}
}