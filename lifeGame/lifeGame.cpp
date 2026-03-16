#include <SFML/Graphics.hpp>
using namespace sf;

//细胞结构体
struct cell {
	int x = 0;
	int y = 0;
	bool alive = false;
};


int main()
{
	int n = 0;
	int  length = 1000, width = 1000;
	//初始化width * length个细胞
	cell* myCell = new cell[width * length];
	cell* myNewCell = new cell[width * length];
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			myCell[n].x = i;
			myCell[n].y = j;
			myCell[n].alive = false;
			myNewCell[n].x = i;
			myNewCell[n].y = j;
			myNewCell[n].alive = false;
			if (i == 50) {
				myCell[n].alive = true;
			}
			if (i == 478) {
				myCell[n].alive = true;
			}
			if (i == 600) {
				myCell[n].alive = true;
			}
			if (j == 50) {
				myCell[n].alive = true;
			}
			if (j == 700) {
				myCell[n].alive = true;
			}
			if (j == 100 && i == 100) {
				myCell[n].alive = true;
			}
			n++;
		}
	}
	int turn = 1;
	n = 0;

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

		n = 0;
        //绘制
        window.clear(Color::White);
		n = 0;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
				if (myCell[n].alive) {
					s.setTextureRect(IntRect(0, 0, 1, 1));//矩形范围
					s.setPosition(j * 1, i * 1);
					window.draw(s);
				}
                else {
                   
                }
				n++;
            }
        }
        window.display();
		n = 0;
		int aroundNum = 0;
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < width; j++) {
				aroundNum = 0;

				if (i == 0) {
					if (j == 0) {
						if (myCell[n + (width - 1)].alive)aroundNum++;
						if (myCell[n + 1].alive)aroundNum++;
						if (myCell[n + width].alive)aroundNum++;
						if (myCell[n + width + (width - 1)].alive)aroundNum++;;
						if (myCell[n + width + 1].alive)aroundNum++;
						if (myCell[n + width * (length - 1)].alive)aroundNum++;
						if (myCell[n + width * (length - 1) + (width - 1)].alive)aroundNum++;
						if (myCell[n + width * (length - 1) + 1].alive)aroundNum++;
					}
					else if (j == (width - 1)) {
						if (myCell[n - (width - 1)].alive)aroundNum++;
						if (myCell[n - 1].alive)aroundNum++;
						if (myCell[n + width].alive)aroundNum++;
						if (myCell[n + width - (width - 1)].alive)aroundNum++;;
						if (myCell[n + width - 1].alive)aroundNum++;
						if (myCell[n + width * (length - 1)].alive)aroundNum++;
						if (myCell[n + width * (length - 1) - (width - 1)].alive)aroundNum++;
						if (myCell[n + width * (length - 1) - 1].alive)aroundNum++;
					}
					else {
						if (myCell[n - 1].alive)aroundNum++;
						if (myCell[n + 1].alive)aroundNum++;
						if (myCell[n + width].alive)aroundNum++;
						if (myCell[n + width - 1].alive)aroundNum++;;
						if (myCell[n + width + 1].alive)aroundNum++;
						if (myCell[n + width * (length - 1)].alive)aroundNum++;
						if (myCell[n + width * (length - 1) - 1].alive)aroundNum++;
						if (myCell[n + width * (length - 1) + 1].alive)aroundNum++;
					}
				}
				else if (i == (length - 1)) {
					if (j == 0) {
						if (myCell[n + (width - 1)].alive)aroundNum++;
						if (myCell[n + 1].alive)aroundNum++;
						if (myCell[n - width].alive)aroundNum++;
						if (myCell[n - width + (width - 1)].alive)aroundNum++;;
						if (myCell[n - width + 1].alive)aroundNum++;
						if (myCell[n - width * (length - 1)].alive)aroundNum++;
						if (myCell[n - width * (length - 1) + (width - 1)].alive)aroundNum++;
						if (myCell[n - width * (length - 1) + 1].alive)aroundNum++;
					}
					else if (j == (width - 1)) {
						if (myCell[n - (width - 1)].alive)aroundNum++;
						if (myCell[n - 1].alive)aroundNum++;
						if (myCell[n - width].alive)aroundNum++;
						if (myCell[n - width - (width - 1)].alive)aroundNum++;;
						if (myCell[n - width - 1].alive)aroundNum++;
						if (myCell[n - width * (length - 1)].alive)aroundNum++;
						if (myCell[n - width * (length - 1) - (width - 1)].alive)aroundNum++;
						if (myCell[n - width * (length - 1) - 1].alive)aroundNum++;
					}
					else {
						if (myCell[n - 1].alive)aroundNum++;
						if (myCell[n + 1].alive)aroundNum++;
						if (myCell[n - width].alive)aroundNum++;
						if (myCell[n - width - 1].alive)aroundNum++;;
						if (myCell[n - width + 1].alive)aroundNum++;
						if (myCell[n - width * (length - 1)].alive)aroundNum++;
						if (myCell[n - width * (length - 1) - 1].alive)aroundNum++;
						if (myCell[n - width * (length - 1) + 1].alive)aroundNum++;
					}
				}
				else {
					if (j == 0) {
						if (myCell[n + (width - 1)].alive)aroundNum++;
						if (myCell[n + 1].alive)aroundNum++;
						if (myCell[n + width].alive)aroundNum++;
						if (myCell[n + width + (width - 1)].alive)aroundNum++;;
						if (myCell[n + width + 1].alive)aroundNum++;
						if (myCell[n - width].alive)aroundNum++;
						if (myCell[n - width + (width - 1)].alive)aroundNum++;
						if (myCell[n - width + 1].alive)aroundNum++;
					}
					else if (j == (width - 1)) {
						if (myCell[n - (width - 1)].alive)aroundNum++;
						if (myCell[n - 1].alive)aroundNum++;
						if (myCell[n + width].alive)aroundNum++;
						if (myCell[n + width - (width - 1)].alive)aroundNum++;;
						if (myCell[n + width - 1].alive)aroundNum++;
						if (myCell[n - width].alive)aroundNum++;
						if (myCell[n - width - (width - 1)].alive)aroundNum++;
						if (myCell[n - width - 1].alive)aroundNum++;
					}
					else {
						if (myCell[n - 1].alive)aroundNum++;
						if (myCell[n + 1].alive)aroundNum++;
						if (myCell[n + width].alive)aroundNum++;
						if (myCell[n + width - 1].alive)aroundNum++;;
						if (myCell[n + width + 1].alive)aroundNum++;
						if (myCell[n - width].alive)aroundNum++;
						if (myCell[n - width - 1].alive)aroundNum++;
						if (myCell[n - width + 1].alive)aroundNum++;
					}
				}
				if (myCell[n].alive) {
					if (aroundNum > 3 || aroundNum < 2) {
						myNewCell[n].alive = false;
					}
					else {
						myNewCell[n].alive = true;
					}
				}
				else {
					if (aroundNum == 3) {
						myNewCell[n].alive = true;
					}
				}
				n++;
			}
		}
		n = 0;
		for (; n < width * length; n++) {
			myCell[n] = myNewCell[n];
			myNewCell[n].alive = false;
		}

		turn++;
    }
	delete[] myCell;
	delete[] myNewCell;
    return 0;
}
/*#include <iostream>
#include <ctime>   // 用于time()
#include <chrono>
#include <thread>
#include <windows.h>
#include <cstdlib> // 用于rand()和srand()
using namespace std;
//细胞结构体
struct cell {
	int x=0;
	int y=0;
	bool alive=0;
};
//地图数据
struct mapData {
	cell *oldCell=new cell[400];
	cell *newCell=new cell[400];
};

int main()
{
	int n = 0;
	int  length = 50, width = 50;
	//初始化width * length个细胞
	cell* myCell = new cell[width * length];
	cell *myNewCell=new cell[width * length];
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			myCell[n].x = i;
			myCell[n].y = j;
			myCell[n].alive = false;
			myNewCell[n].x = i;
			myNewCell[n].y = j;
			myNewCell[n].alive = false;
			if (i == 5) {
				myCell[n].alive = true;
			}
			
			n++;
		}
	}
	

	int turn = 1;
	n = 0;
	while (turn < 100) {
		cout << "Turn Number is " << turn<<endl;
		n = 0;
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < width; j++) {
				if (myCell[n].alive) {
					cout << '#';
				}
				else {
					cout << ' ';
				}
				n++;
			}
			cout << endl;
		}
		cout << endl;
		n = 0;
		int aroundNum = 0;
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < width; j++) {
				aroundNum = 0;

				if (i == 0) {
					if (j == 0) {
						if (myCell[n + (width - 1)].alive)aroundNum++;
						if (myCell[n + 1].alive)aroundNum++;
						if (myCell[n + width].alive)aroundNum++;
						if (myCell[n + width + (width - 1)].alive)aroundNum++;;
						if (myCell[n + width + 1].alive)aroundNum++;
						if (myCell[n + width * (length - 1)].alive)aroundNum++;
						if (myCell[n + width * (length - 1) + (width - 1)].alive)aroundNum++;
						if (myCell[n + width * (length - 1) + 1].alive)aroundNum++;
					}
					else if (j == (width - 1)) {
						if (myCell[n - (width - 1)].alive)aroundNum++;
						if (myCell[n - 1].alive)aroundNum++;
						if (myCell[n + width].alive)aroundNum++;
						if (myCell[n + width - (width - 1)].alive)aroundNum++;;
						if (myCell[n + width - 1].alive)aroundNum++;
						if (myCell[n + width * (length - 1)].alive)aroundNum++;
						if (myCell[n + width * (length - 1) - (width - 1)].alive)aroundNum++;
						if (myCell[n + width * (length - 1) - 1].alive)aroundNum++;
					}
					else {
						if (myCell[n - 1].alive)aroundNum++;
						if (myCell[n + 1].alive)aroundNum++;
						if (myCell[n + width].alive)aroundNum++;
						if (myCell[n + width - 1].alive)aroundNum++;;
						if (myCell[n + width + 1].alive)aroundNum++;
						if (myCell[n + width * (length - 1)].alive)aroundNum++;
						if (myCell[n + width * (length - 1) - 1].alive)aroundNum++;
						if (myCell[n + width * (length - 1) + 1].alive)aroundNum++;
					}
				}
				else if (i == (length - 1)) {
					if (j == 0) {
						if (myCell[n + (width - 1)].alive)aroundNum++;
						if (myCell[n + 1].alive)aroundNum++;
						if (myCell[n - width].alive)aroundNum++;
						if (myCell[n - width + (width - 1)].alive)aroundNum++;;
						if (myCell[n - width + 1].alive)aroundNum++;
						if (myCell[n - width * (length - 1)].alive)aroundNum++;
						if (myCell[n - width * (length - 1) + (width - 1)].alive)aroundNum++;
						if (myCell[n - width * (length - 1) + 1].alive)aroundNum++;
					}
					else if (j == (width - 1)) {
						if (myCell[n - (width - 1)].alive)aroundNum++;
						if (myCell[n - 1].alive)aroundNum++;
						if (myCell[n - width].alive)aroundNum++;
						if (myCell[n - width - (width - 1)].alive)aroundNum++;;
						if (myCell[n - width - 1].alive)aroundNum++;
						if (myCell[n - width * (length - 1)].alive)aroundNum++;
						if (myCell[n - width * (length - 1) - (width - 1)].alive)aroundNum++;
						if (myCell[n - width * (length - 1) - 1].alive)aroundNum++;
					}
					else {
						if (myCell[n - 1].alive)aroundNum++;
						if (myCell[n + 1].alive)aroundNum++;
						if (myCell[n - width].alive)aroundNum++;
						if (myCell[n - width - 1].alive)aroundNum++;;
						if (myCell[n - width + 1].alive)aroundNum++;
						if (myCell[n - width * (length - 1)].alive)aroundNum++;
						if (myCell[n - width * (length - 1) - 1].alive)aroundNum++;
						if (myCell[n - width * (length - 1) + 1].alive)aroundNum++;
					}
				}
				else {
					if (j == 0) {
						if (myCell[n + (width - 1)].alive)aroundNum++;
						if (myCell[n + 1].alive)aroundNum++;
						if (myCell[n + width].alive)aroundNum++;
						if (myCell[n + width + (width - 1)].alive)aroundNum++;;
						if (myCell[n + width + 1].alive)aroundNum++;
						if (myCell[n - width].alive)aroundNum++;
						if (myCell[n - width + (width - 1)].alive)aroundNum++;
						if (myCell[n - width + 1].alive)aroundNum++;
					}
					else if (j == (width - 1)) {
						if (myCell[n - (width - 1)].alive)aroundNum++;
						if (myCell[n - 1].alive)aroundNum++;
						if (myCell[n + width].alive)aroundNum++;
						if (myCell[n + width - (width - 1)].alive)aroundNum++;;
						if (myCell[n + width - 1].alive)aroundNum++;
						if (myCell[n - width].alive)aroundNum++;
						if (myCell[n - width - (width - 1)].alive)aroundNum++;
						if (myCell[n - width - 1].alive)aroundNum++;
					}
					else {
						if (myCell[n - 1].alive)aroundNum++;
						if (myCell[n + 1].alive)aroundNum++;
						if (myCell[n + width].alive)aroundNum++;
						if (myCell[n + width - 1].alive)aroundNum++;;
						if (myCell[n + width + 1].alive)aroundNum++;
						if (myCell[n - width].alive)aroundNum++;
						if (myCell[n - width - 1].alive)aroundNum++;
						if (myCell[n - width + 1].alive)aroundNum++;
					}
				}
				if (myCell[n].alive) {
					if (aroundNum > 3 || aroundNum < 2) {
						myNewCell[n].alive = false;
					}
					else {
						myNewCell[n].alive = true;
					}
				}
				else {
					if (aroundNum == 3) {
						myNewCell[n].alive = true;
					}
				}
				n++;
			}
		}
		n = 0;
		for (; n < width * length; n++) {
			myCell[n] = myNewCell[n];
			myNewCell[n].alive = false;
		}

		turn++;
		this_thread::sleep_for(chrono::milliseconds(512));
		system("cls");
	}
	delete[] myCell;
	delete[] myNewCell;
}*/