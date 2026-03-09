#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

const bool black = false;
const bool white = true;

enum direction { UP, LEFT, RIGHT, DOWN };

//蚂蚁结构体
struct ant {
	int x = 250;
	int y = 250;
	direction antDirection = UP;
};
//地块结构体
struct block {
	bool color = white;
};


int main()
{
	int width = 500, length = 500;
	vector<vector<block>>myBolck(length, vector<block>(width));

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			myBolck[i][j].color = white;
		}
	}
	
	ant myAnt;

	srand(time(0));//随机数

	RenderWindow window(VideoMode(width, length), "life game");
	Texture text;
	text.loadFromFile("cell.png");

	Sprite/*指可移动图像*/s(text);
	s.setTextureRect(IntRect(0, 0, 1, 1));


	float tickTime = 0, delay = 0.3;

	Clock clock;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		tickTime += time;

		Event gameEvent;
		while (window.pollEvent(gameEvent))
		{
			if (gameEvent.type == Event::Closed) {
				window.close();
			}

		}


		//下落间隔
		if (tickTime > delay) {

			tickTime = 0;


		}


		delay = 0.3;

		
		//绘制
		window.clear(Color::White);
		
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < width; j++) {
				if (myBolck[i][j].color == black) {
					s.setTextureRect(IntRect(0, 0, 1, 1));//矩形范围
					s.setPosition(j * 1, i * 1);
					window.draw(s);
				}
				else {

				}
				
			}
		}
		window.display();
		if (myAnt.antDirection == UP) {
			if (myAnt.y == 0) {
				if (myBolck[length - 1][myAnt.x].color == black) {
					myBolck[length - 1][myAnt.x].color = white;
					myAnt.x = myAnt.x;
					myAnt.y = length - 1;
					myAnt.antDirection = LEFT;
				}
				else if (myBolck[length - 1][myAnt.x].color == white) {
					myBolck[length - 1][myAnt.x].color = black;
					myAnt.x = myAnt.x;
					myAnt.y = length - 1;
					myAnt.antDirection = RIGHT;
				}
			}
			else {
				if (myBolck[myAnt.y - 1][myAnt.x].color == black) {
					myBolck[myAnt.y - 1][myAnt.x].color = white;
					myAnt.x = myAnt.x;
					myAnt.y--;
					myAnt.antDirection = LEFT;
				}
				else if (myBolck[myAnt.y - 1][myAnt.x].color == white) {
					myBolck[myAnt.y - 1][myAnt.x].color = black;
					myAnt.x = myAnt.x;
					myAnt.y--;
					myAnt.antDirection = RIGHT;
				}
			}
		}
		else if (myAnt.antDirection == LEFT) {
			if (myAnt.x == 0) {
				if (myBolck[myAnt.y][width - 1].color == black) {
					myBolck[myAnt.y][width - 1].color = white;
					myAnt.x = width - 1;
					myAnt.y = myAnt.y;
					myAnt.antDirection = DOWN;
				}
				else if (myBolck[myAnt.y][width - 1].color == white) {
					myBolck[myAnt.y][width - 1].color = black;
					myAnt.x = width - 1;
					myAnt.y = myAnt.y;
					myAnt.antDirection = UP;
				}
			}
			else {
				if (myBolck[myAnt.y][myAnt.x - 1].color == black) {
					myBolck[myAnt.y][myAnt.x - 1].color = white;
					myAnt.x--;
					myAnt.y = myAnt.y;
					myAnt.antDirection = DOWN;
				}
				else if (myBolck[myAnt.y][myAnt.x - 1].color == white) {
					myBolck[myAnt.y][myAnt.x - 1].color = black;
					myAnt.x--;
					myAnt.y = myAnt.y;
					myAnt.antDirection = UP;
				}
			}
		}
		else if (myAnt.antDirection == RIGHT) {
			if (myAnt.x == width - 1) {
				if (myBolck[myAnt.y][0].color == black) {
					myBolck[myAnt.y][0].color = white;
					myAnt.x = 0;
					myAnt.y = myAnt.y;
					myAnt.antDirection = UP;
				}
				else if (myBolck[myAnt.y][0].color == white) {
					myBolck[myAnt.y][0].color = black;
					myAnt.x = 0;
					myAnt.y = myAnt.y;
					myAnt.antDirection = DOWN;
				}
			}
			else {
				if (myBolck[myAnt.y][myAnt.x + 1].color == black) {
					myBolck[myAnt.y][myAnt.x + 1].color = white;
					myAnt.x++;
					myAnt.y = myAnt.y;
					myAnt.antDirection = UP;
				}
				else if (myBolck[myAnt.y][myAnt.x + 1].color == white) {
					myBolck[myAnt.y][myAnt.x + 1].color = black;
					myAnt.x++;
					myAnt.y = myAnt.y;
					myAnt.antDirection = DOWN;
				}
			}
		}
		else if (myAnt.antDirection == DOWN) {
			if (myAnt.y == length - 1) {
				if (myBolck[0][myAnt.x].color == black) {
					myBolck[0][myAnt.x].color = white;
					myAnt.x = myAnt.x;
					myAnt.y = 0;
					myAnt.antDirection = RIGHT;
				}
				else if (myBolck[0][myAnt.x].color == white) {
					myBolck[0][myAnt.x].color = black;
					myAnt.x = myAnt.x;
					myAnt.y = 0;
					myAnt.antDirection = LEFT;
				}
			}
			else {
				if (myBolck[myAnt.y + 1][myAnt.x].color == black) {
					myBolck[myAnt.y + 1][myAnt.x].color = white;
					myAnt.x = myAnt.x;
					myAnt.y++;
					myAnt.antDirection = RIGHT;
				}
				else if (myBolck[myAnt.y + 1][myAnt.x].color == white) {
					myBolck[myAnt.y + 1][myAnt.x].color = black;
					myAnt.x = myAnt.x;
					myAnt.y++;
					myAnt.antDirection = LEFT;
				}
			}
		}
		
	}
	
	return 0;
}
/*#include <iostream>
#include <ctime>   // 用于time()
#include <chrono>
#include <vector>
#include <thread>
#include <windows.h>
#include <cstdlib> // 用于rand()和srand()
using namespace std;

const bool black = false;
const bool white = true;

enum direction{UP,LEFT,RIGHT,DOWN};

//蚂蚁结构体
struct ant {
	int x=25;
	int y=25;
	direction antDirection = UP;
};
//地块结构体
struct block {
	bool color = black;
};


int main()
{
	int width = 50, length = 50;
	vector<vector<block>>myBolck(length, vector<block>(width));
	
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j ++) {
			myBolck[i][j].color = black;
		}
	}
	int turn = 1;
	ant myAnt;
	while (turn < 1000) {
		cout << "the turn is " << turn << endl;
		if (myAnt.antDirection == UP) {
			if (myAnt.y == 0) {
				if (myBolck[length - 1][myAnt.x].color == black) {
					myBolck[length - 1][myAnt.x].color = white;
					myAnt.x = myAnt.x;
					myAnt.y = length - 1;
					myAnt.antDirection = LEFT;
				}
				else if (myBolck[length - 1][myAnt.x].color == white) {
					myBolck[length - 1][myAnt.x].color = black;
					myAnt.x = myAnt.x;
					myAnt.y = length - 1;
					myAnt.antDirection = RIGHT;
				}
			}
			else {
				if (myBolck[myAnt.y-1][myAnt.x].color == black) {
					myBolck[myAnt.y-1][myAnt.x].color = white;
					myAnt.x = myAnt.x;
					myAnt.y--;
					myAnt.antDirection = LEFT;
				}
				else if (myBolck[myAnt.y-1][myAnt.x].color == white) {
					myBolck[myAnt.y-1][myAnt.x].color = black;
					myAnt.x = myAnt.x;
					myAnt.y--;
					myAnt.antDirection = RIGHT;
				}
			}
		}
		else if (myAnt.antDirection == LEFT) {
			if (myAnt.x == 0) {
				if (myBolck[myAnt.y][width - 1].color == black) {
					myBolck[myAnt.y][width - 1].color = white;
					myAnt.x = width - 1;
					myAnt.y = myAnt.y;
					myAnt.antDirection = DOWN;
				}
				else if (myBolck[myAnt.y][width - 1].color == white) {
					myBolck[myAnt.y][width - 1].color = black;
					myAnt.x = width - 1;
					myAnt.y = myAnt.y;
					myAnt.antDirection = UP;
				}
			}
			else {
				if (myBolck[myAnt.y][myAnt.x - 1].color == black) {
					myBolck[myAnt.y][myAnt.x - 1].color = white;
					myAnt.x--;
					myAnt.y = myAnt.y;
					myAnt.antDirection = DOWN;
				}
				else if (myBolck[myAnt.y][myAnt.x - 1].color == white) {
					myBolck[myAnt.y][myAnt.x - 1].color = black;
					myAnt.x--;
					myAnt.y = myAnt.y;
					myAnt.antDirection = UP;
				}
			}
		}
		else if (myAnt.antDirection == RIGHT) {
			if (myAnt.x == width - 1) {
				if (myBolck[myAnt.y][0].color == black) {
					myBolck[myAnt.y][0].color = white;
					myAnt.x = 0;
					myAnt.y = myAnt.y;
					myAnt.antDirection = UP;
				}
				else if (myBolck[myAnt.y][0].color == white) {
					myBolck[myAnt.y][0].color = black;
					myAnt.x = 0;
					myAnt.y = myAnt.y;
					myAnt.antDirection = DOWN;
				}
			}
			else {
				if (myBolck[myAnt.y][myAnt.x + 1].color == black) {
					myBolck[myAnt.y][myAnt.x + 1].color = white;
					myAnt.x++;
					myAnt.y = myAnt.y;
					myAnt.antDirection = UP;
				}
				else if (myBolck[myAnt.y][myAnt.x + 1].color == white) {
					myBolck[myAnt.y][myAnt.x + 1].color = black;
					myAnt.x++;
					myAnt.y = myAnt.y;
					myAnt.antDirection = DOWN;
				}
			}
		}
		else if (myAnt.antDirection == DOWN) {
			if (myAnt.y == length-1) {
				if (myBolck[0][myAnt.x].color == black) {
					myBolck[0][myAnt.x].color = white;
					myAnt.x = myAnt.x;
					myAnt.y = 0;
					myAnt.antDirection = RIGHT;
				}
				else if (myBolck[0][myAnt.x].color == white) {
					myBolck[0][myAnt.x].color = black;
					myAnt.x = myAnt.x;
					myAnt.y = 0;
					myAnt.antDirection = LEFT;
				}
			}
			else {
				if (myBolck[myAnt.y + 1][myAnt.x].color == black) {
					myBolck[myAnt.y + 1][myAnt.x].color = white;
					myAnt.x = myAnt.x;
					myAnt.y++;
					myAnt.antDirection = RIGHT;
				}
				else if (myBolck[myAnt.y + 1][myAnt.x].color == white) {
					myBolck[myAnt.y + 1][myAnt.x].color = black;
					myAnt.x = myAnt.x;
					myAnt.y++;
					myAnt.antDirection = LEFT;
				}
			}
		}
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < width; j++) {
				if (myBolck[i][j].color == white) {
					cout << "#";
				}
				else {
					cout << " ";
				}
			}
			cout << endl;
		}
		turn++;
		this_thread::sleep_for(chrono::milliseconds(32));
		system("cls");
	}
}
*/