#include <SFML/Graphics.hpp>
using namespace sf;

const int height = 17;
const int width = 10;

int field[height][width] = { 0 };

int shape[7][4] =
{
    1,3,5,7,//I
    2,4,5,7,//Z
    3,5,4,6,//S
    3,5,4,7,//T
    2,3,5,7,//L
    3,5,7,6,//J
    2,3,4,5,//O

};

struct Point {
    int x, y;
}p[4],pre[4];

bool checkPositionRight() {
    for (int i = 0; i < 4; i++) {
        if (p[i].x<0 || p[i].x >= width || p[i].y >= height)return 0;
        else if (field[p[i].y][p[i].x])return 0;
    }
    return 1;
}

int main()
{
    srand(time(0));//随机数

    RenderWindow window(VideoMode(320*3, 420*3), "Tetris game");
    Texture text;
    text.loadFromFile("TetrisBlock.png");
    
    Sprite s(text);//指可移动图像
    s.setTextureRect(IntRect(0, 0, 64, 64));

    int dx = 0;
    bool rotate = false;
    int colorNum = 1;

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
            //按键
            if (gameEvent.type == Event::KeyPressed) {
                if (gameEvent.key.code == Keyboard::W)rotate = true;
                else if (gameEvent.key.code == Keyboard::A)dx = -1;
                else if (gameEvent.key.code == Keyboard::D)dx = 1;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            delay = 0.05;
        }
        //移动
        for (int i = 0; i < 4; i++) {
            pre[i] = p[i];
            p[i].x += dx;
        }
        if (!checkPositionRight()) {
            for (int i = 0; i < 4; i++) {
                p[i] = pre[i];
            }
        }
        //旋转
        if (rotate) {
            Point centerPoint = p[1];
            for (int i = 0; i < 4; i++)  {
                pre[i] = p[i];
                int tempx = p[i].y - centerPoint.y;
                int tempy = p[i].x - centerPoint.x;
                p[i].x = centerPoint.x - tempx;
                p[i].y = centerPoint.y + tempy;
            }
        }
        if (!checkPositionRight()) {
            for (int i = 0; i < 4; i++) {
                p[i] = pre[i];
            }
        }
        //下落间隔
        if (tickTime > delay) {
            for (int i = 0; i < 4; i++) {
                pre[i] = p[i];
                p[i].y += 1;
            }
            
            if (!checkPositionRight()) {
                for (int i = 0; i < 4; i++) {
                    field[pre[i].y][pre[i].x] = colorNum;
                }
                //新方块
                colorNum = rand() % 7;
                int shapeNum = rand() % 7;
                for (int i = 0; i < 4; i++) {
                    p[i].x = shape[shapeNum][i] % 2;
                    p[i].y = shape[shapeNum][i] / 2;

                }
            }
            tickTime = 0;

            int k = height - 1;
            for (int i = height - 1; i > 0; i--) {
                int count = 0;
                for (int j = 0; j < width; j++) {
                    if (field[i][j]) {
                        count++;
                    }
                    field[k][j] = field[i][j];
                }
                if (count < width) {
                    k--; 
                }
            }
        }


        dx = 0;rotate = false; delay = 0.3;

        //绘制
        window.clear(Color::White);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (field[i][j] == 0)continue;
                else {
                    s.setTextureRect(IntRect(field[i][j]*64, 0, 64, 64));//矩形范围
                    s.setPosition(j * 64, i * 64);
                    window.draw(s);
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            s.setTextureRect(IntRect(colorNum*64, 0, 64, 64));
            s.setPosition(p[i].x*64, p[i].y*64);
            window.draw(s);
        }
        window.display();
    }

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