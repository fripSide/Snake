
//#include <conio.h>
#include <windows.h>
#include <iostream>
#include <cassert>
#include "Snake.h"

using namespace std;

/*
http://cmdblock.blog.51cto.com/415170/585894

cosole 80¸ñ

*/


//-----------------------------------------------
//ÌØÊâ×Ö·û£º1~30
//-----------------------------------------------

int main(int argc,char* argv[])
{
	cout<<""<<endl;

	Snake snake;
	snake.Game();

	system("pause");
	return 0;
}