#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#define TIME 100
#define SPEED 0.1
using namespace std;
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
	return;
}

void hideConsoleCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
	return;
}

// 精确延时函数(可以精确到 1ms，精度 ±1ms)
void HpSleep(int ms)
{
	static clock_t oldclock = clock();		// 静态变量，记录上一次 tick

	oldclock += ms * CLOCKS_PER_SEC / 1000;	// 更新 tick

	if (clock() > oldclock)					// 如果已经超时，无需延时
		oldclock = clock();
	else
		while (clock() < oldclock)			// 延时
		{
			Sleep(1);
		}						// 释放 CPU 控制权，降低 CPU 占用率
	return;
}
//参考网上代码 

class SeqStack//定义栈类 
{
public:
	SeqStack()
	{
		top = -1;//初始化 
	}
	void Push(int x, int y)
	{
		if (top == 128)
			return;
		else
		{
			top++;
			data[top][0] = x;
			data[top][1] = y;
		}
	}
	int getTopx()
	{
		return data[top][0];
	}

	int getTopy()
	{
		return data[top][1];
	}

	void Pop()
	{
		if (top == -1)
			return;
		top--;
	}
	int Empty()
	{
		if (top == -1)
			return 1;
		else
			return 0;
	}
private:
	int data[128][2];
	int top;
};

int maze[10][10] = 
{
	{1,1, 1, 1, 1, 1, 1, 1, 1, 1}, 
    {1,0, 0, 0, 0, 0, 0, 0, 0, 1}, 
    {1,1, 0, 1, 1, 0, 1, 1, 0, 1},
    {1,1, 0, 1, 0, 0, 1, 0, 0, 1},
    {1,1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1,0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1,0, 1, 0, 1, 1, 0, 1, 1, 1},
    {1,1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1,1, 0, 1, 0, 1, 0, 1, 3, 1},
    {1,1, 1, 1, 1, 1, 1, 1, 1, 1}, 
};
int maze1[10][10] = 
{
	{1,1, 1, 1, 1, 1, 1, 1, 1, 1}, 
    {1,0, 0, 0, 0, 0, 0, 0, 0, 1}, 
    {1,1, 0, 1, 1, 0, 1, 1, 0, 1},
    {1,1, 0, 1, 0, 0, 1, 0, 0, 1},
    {1,1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1,0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1,0, 1, 0, 1, 1, 0, 1, 1, 1},
    {1,1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1,1, 0, 1, 0, 1, 0, 1, 3, 1},
    {1,1, 1, 1, 1, 1, 1, 1, 1, 1}, 
};
class Game
{
public:

	Game()//构造函数 
	{
		int i, j;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				Maze[i][j] = maze[i][j];
			}
		}
		Maze[4][4] = 2;
		X = 4, Y = 4;
	}
	void draw()//成员函数 
	{
		gotoxy(0, 0);
		int i, j;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (Maze[i][j] == 0)
					cout << "  ";
				else if (Maze[i][j] == 1)
					cout << "■";
				else if (Maze[i][j] == 2)
					cout << "☆";
				else if (Maze[i][j] == 3)
					cout << "●";
			}
			cout << endl;
		}
		return;
	}
	void control()
	{
		char ch;
		if (_kbhit())
			ch = _getch();
		else
			return;
		Maze[Y][X] = 0;

		switch (ch)
		{
		case 'w':
			if (Maze[Y - 1][X] != 1)
			{
				stack.Push(Y, X);
				Y -= 1;
			}

			break;
		case 's':
			if (Maze[Y + 1][X] != 1)
			{
				stack.Push(Y, X);
				Y += 1;
			}

			break;
		case 'a':
			if (Maze[Y][X - 1] != 1)
			{
				stack.Push(Y, X);
				X -= 1;
			}

			break;
		case 'd':
			if (Maze[Y][X + 1] != 1)
			{
				stack.Push(Y, X);
				X += 1;
			}

			break;
		}
		Maze[Y][X] = 2;
	}

	
	int stop()
	{
		if (Y == 8 && X == 8)
			return 1;
		else
			return 0;
	}


	void showPath()
	{
		int i, j;
		while (stack.Empty() != 1)
		{
			int x = stack.getTopx();
			int y = stack.getTopy();
			stack.Pop();
			Maze[x][y] = 2;
		}
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (Maze[i][j] == 0)
					cout << "  ";
				else if (Maze[i][j] == 1)
					cout << "■";
				else if (Maze[i][j] == 2)
					cout << "☆";
                else if (Maze[i][j] == 3)
					cout << "●";
			}
			cout << endl;
		}
	}
	void xiugai()
	{
		char ch;
		int x = 1, y = 1;
		while (1)
		{	
			cout << "e修改地图，q退出修改。\n";
		

			drawagain(x, y);
			ch = _getch();
			switch (ch)
			{
			case 'w':
					x -= 1;
				break;
			case 's':
					x += 1;
				break;
			case 'a':
					y -= 1;
				break;
			case 'd':
					y += 1;
				break;
			case 'e':
				if (maze[x][y] == 1)
					maze[x][y] = 0;
				else if (maze[x][y] == 0)
					maze[x][y] = 1;
				break;
			case 'q':
				refresh();
				system("CLS");
				return;
			}
			system("CLS");
		}
	}
	void drawagain(int x, int y)
	{
		int i, j;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (i == x && j == y)
					cout << "+ ";
				else if (maze[i][j] == 0)
					cout << "  ";
				else if (maze[i][j] == 1)
					cout << "■";
				else if (maze[i][j] == 3)
					cout << "●";
			}
			cout << endl;
		}
		return;
	}	

	void visit(int x, int y)
	{
		int i, j,t=0;
		Maze[x][y] = 2;
		if (x == 8 && y == 8)
		{
			for (i = 0; i < 10; i++)
			{
				for (j = 0; j < 10; j++)
				{
					if (Maze[i][j] == 0)
						cout << "  ";
					else if (Maze[i][j] == 1)
						cout << "■";
					else if (Maze[i][j] == 2)
						{t++;
						cout << "☆";
					}	
					
					else if (Maze[i][j] == 3)
						cout << "●";
				}
				cout <<endl;
			}
			cout<<"路径数："<<t;
			cout <<endl;
		}

		if (Maze[x][y + 1] == 0 || Maze[x][y + 1] == 3)
			visit(x, y + 1);
		if (Maze[x + 1][y] == 0 || Maze[x + 1][y] == 3)
			visit(x + 1, y);
		if (Maze[x][y - 1] == 0 || Maze[x][y - 1] == 3)
			visit(x, y - 1);
		if (Maze[x - 1][y] == 0 || Maze[x - 1][y] == 3)
			visit(x - 1, y);

		Maze[x][y] = 0;
	}
	void compare(int x, int y)
	{
		int i, j;
		Maze[x][y] = 2;
		if (x == 8 && y == 8)
		{
			int temp = 0;//存放路径长度 
			for (i = 0; i < 10; i++)
			{
				for (j = 0; j < 10; j++)
				{
					if (Maze[i][j] == 2)
					{
						str1.Push(i, j);
						temp++;
					}
				}
			}
			if (temp < min)// 选出短的路径 
			{
				min = temp;
				while (str2.Empty()!=1)
				{
					str2.Pop();
				}
				while (str1.Empty()!=1)
				{
					str2.Push(str1.getTopx(), str1.getTopy());
					str1.Pop();
				}
			}
			else//清空之前的路径,便于下次比较 
			{
				while(str1.Empty()!=1)
				str1.Pop();
			}
		}

		if (Maze[x][y + 1] == 0 || Maze[x][y + 1] == 3)
			compare(x, y + 1);
		if (Maze[x + 1][y] == 0 || Maze[x + 1][y] == 3)
			compare(x + 1, y);
		if (Maze[x][y - 1] == 0 || Maze[x][y - 1] == 3)
			compare(x, y - 1);
		if (Maze[x - 1][y] == 0 || Maze[x - 1][y] == 3)
			compare(x - 1, y);

		Maze[x][y] = 0;
	 }
	 void showMin()
	 {
	 	cout << "最短路径长 = " << min << endl;
	 	int i, j;
	 	while (str2.Empty()!=1)
	 	{
	 		int x = str2.getTopx();
	 		int y = str2.getTopy();
	 		str2.Pop();
	 		
	 		Maze[x][y] = 2;
		}
		
	 	for (i = 0; i < 10; i++)
			{
				for (j = 0; j < 10; j++)
				{
					if (Maze[i][j] == 0)
						cout << "  ";
					else if (Maze[i][j] == 1)
						cout << "■";
					else if (Maze[i][j] == 2)
						cout << "☆";
					else if (Maze[i][j] == 3)
						cout << "●";
				}
				cout << endl;
			}
	 }
	 void clearPath()//清空两个栈 
	 {
	 	min = 65535;
	 	while (str1.Empty()!=1)
	 	{
	 		str1.Pop();
		 }
		while (str2.Empty()!=1)
		{
			str2.Pop();
		}
	 }
	void change()
	{
	    gotoxy(0, 0);
		int i, j;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (Maze[i][j] == 0)
					cout << "■";
				else if (Maze[i][j] == 1)
					cout << "  ";
				else if (Maze[i][j] == 2)
					cout << "☆";
				else if (Maze[i][j] == 3)
					cout << "●";
			}
			cout << endl;
		}
		return;
	 } 
	void refresh()
	{
		int i, j;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				Maze[i][j] = maze[i][j];
			}
		}
			X = 4;
			Y = 4;
			Maze[X][Y] = 2;
	}
	void huifu()
	{
		int i, j;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				maze[i][j] = maze1[i][j];
			}
		}
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				Maze[i][j] = maze1[i][j];
			}
		}
			X = 4;
			Y = 4;
			Maze[X][Y] = 2;
	}
private:
int Maze[10][10];
int X, Y;
int min;
SeqStack stack,str1,str2;
};

int menu()
{
	int p;
cout<<"       ╭ ═════════■□■□═══╮"<<endl; 
cout<<"                  简单迷宫游戏                "<<endl;
cout<<"       ╰═══■□■□══════════╯"<<endl;;  
cout<<"        ┌─────────────-┐"<<endl;  
cout<<"        │         1.开始游戏        │"<<endl;  
cout<<"        │                           │"<<endl;  
cout<<"        │      2.所有路径           │"<<endl;  
cout<<"        │                           │"<<endl;  
cout<<"        │         3.最短路径        │"<<endl;  
cout<<"        │                           │"<<endl;  
cout<<"        │      4.修改迷宫           │"<<endl; 
cout<<"        │                           │"<<endl;
cout<<"        │         5.恢复迷宫        │"<<endl; 
cout<<"        │                           │"<<endl; 
cout<<"        │      0.退出游戏           │"<<endl;     
cout<<"        └─────────────-┘"<<endl; 
cin >> p;
return p;

}
int main()
{
	hideConsoleCursor();
	int x ;
	float time = 15;
	Game game;
	while (x != 0)
	{
		x = menu();
		if (x == 6)
		{cout<<"输入错误,请重新输入:"<<endl;
		cin>>x;
		system("cls");
					}			
		switch (x)
		{
		case 1:
			system("cls");
			while (true)
			{

				game.draw();
				game.control();

				if (game.stop() == 1)
				{
					break;
				}
				HpSleep(TIME);
				time -= SPEED;
				cout.width(2);
				if ((int)time != 0)
					cout << (int)time << endl;
				else
					break;
			}
			if ((int)time != 0)
			{
				cout << "闯关成功" << endl;
				if (game.stop() == 1)
					game.showPath();

			}
			else
				cout << "闯关失败" << endl;
			system("PAUSE");
			system("CLS");
			game.refresh();
			time = 15;
			break;

		case 2:
			system("cls");
			cout<<"所有路径："<<endl;
			game.visit(4,4);
			system("PAUSE");
			system("CLS");
			game.refresh();
			break;
		
		case 3:
			game.clearPath();
			system("CLS");
			game.compare(4,4);
			game.showMin();
			system("PAUSE");
			game.refresh();
			system("CLS");
			break;
		case 4:
			system("cls");
		  	game.xiugai();
			game.refresh();
			game.clearPath();
			break;
		case 5:
			game.huifu();
			system("cls");
			break;
		}
	}
	return 0;
}
