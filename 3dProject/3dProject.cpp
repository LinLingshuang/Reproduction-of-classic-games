#include <iostream>
#include <cmath>
#include <iomanip>
#include <SFML/Graphics.hpp>

using namespace std;

const float Pi = 3.1415926;

//三维向量
class Vector3 {
public:
	Vector3(){
		x = 0;
		y = 0;
		z = 0;
	}
	Vector3(float xx,float yy, float zz) {
		x = xx;
		y = yy;
		z = zz;
	}
	Vector3(const Vector3 & otherVector3) {
		x = otherVector3.x;
		y = otherVector3.y;
		z = otherVector3.z;
	}
	~Vector3() {};

	Vector3 operator+(const Vector3 &otherVector3)const {
		return Vector3(x + otherVector3.getX(), y + otherVector3.getY(), z + otherVector3.getZ());
	}
	Vector3 operator-(const Vector3 &otherVector3)const{
		return Vector3(x - otherVector3.getX(), y - otherVector3.getY(), z - otherVector3.getZ());
	}
	Vector3 operator*(const float num)const {
		return Vector3(x * num, y * num, z * num);
	}
	Vector3 operator/(const float num)const {
		return Vector3(x / num, y / num, z / num);
	}
	bool operator==(const Vector3 &otherVector3)const {
		if (x == otherVector3.getX() && y == otherVector3.getY() && z == otherVector3.getZ()) {
			return true;
		}
		return false;
	}
	float operator*(const Vector3 &otherVector3)const{
		return (x * otherVector3.getX() + y * otherVector3.getY() + z * otherVector3.getZ());
	}

	float length()const {
		return sqrtf(x * x + y * y + z * z);
	}
	float cosAngel(const Vector3 &otherVector3)const {
		return ((*this) * otherVector3) / ((*this).length() * otherVector3.length());
	}

	float getX()const { return x; }
	float getY()const { return y; }
	float getZ()const { return z; }

private:
	float x;
	float y;
	float z;

};

class Matrix33 {
public:
	Matrix33() {
		xVector3 = Vector3(1, 0, 0);
		yVector3 = Vector3(0, 1, 0);
		zVector3 = Vector3(0, 0, 1);
	}
	Matrix33(const Vector3 xxVector3,const Vector3 yyVector3,const Vector3 zzVector3) {
		xVector3 = xxVector3;
		yVector3 = yyVector3;
		zVector3 = zzVector3;
	}
	Matrix33(const Matrix33 & otherMatrix33) {
		xVector3 = otherMatrix33.xVector3;
		yVector3 = otherMatrix33.yVector3;
		zVector3 = otherMatrix33.zVector3;
	}
	~Matrix33(){}
	Matrix33 operator+(const Matrix33 &otherMatrix33)const {
		return Matrix33(xVector3 + otherMatrix33.getXvector3(),
						yVector3 + otherMatrix33.getYvector3(),
						zVector3 + otherMatrix33.getZvector3());
	}
	Matrix33 operator-(const Matrix33 &otherMatrix33)const {
		return Matrix33(xVector3 - otherMatrix33.getXvector3(),
						yVector3 - otherMatrix33.getYvector3(),
						zVector3 - otherMatrix33.getZvector3());
	}
	bool operator==(const Matrix33 &otherMatrix33)const {
		if (xVector3 == otherMatrix33.getXvector3() &&
			yVector3 == otherMatrix33.getYvector3() &&
			zVector3 == otherMatrix33.getZvector3()) {
			return true;
		}
		return false;
	}
	void transposition() {
		Vector3 tempxVector3 = xVector3;
		Vector3 tempyVector3 = yVector3;
		Vector3 tempzVector3 = zVector3;
		xVector3 = Vector3(tempxVector3.getX(), tempyVector3.getX(), tempzVector3.getX());
		yVector3 = Vector3(tempxVector3.getY(), tempyVector3.getY(), tempzVector3.getY());
		zVector3 = Vector3(tempxVector3.getZ(), tempyVector3.getZ(), tempzVector3.getZ());
	}

	Matrix33 friend findExcessMatrix(Matrix33 A, Matrix33 B);

	Vector3 getXvector3()const { return xVector3; }
	Vector3 getYvector3()const { return yVector3; }
	Vector3 getZvector3()const { return zVector3; }

private:
	Vector3 xVector3;
	Vector3 yVector3;
	Vector3 zVector3;
};

struct camera {
	Vector3 xWorldBase = Vector3(1, 0, 0);
	Vector3 yWorldBase = Vector3(0, 1, 0);
	Vector3 zWorldBase = Vector3(0, 0, 1);

	Vector3 xbase = Vector3(1, 0, 0);
	Vector3 ybase = Vector3(0, 1, 0);
	Vector3 zbase = Vector3(0, 0, 1);


	Vector3 position = Vector3();
	void setPosition(float x, float y, float z) {
		position = Vector3(x, y, z);
	}
	void setBase(Vector3 xxbase, Vector3 yybase, Vector3 zzbase) {
		xbase = xxbase;
		ybase = yybase;
		zbase = zzbase;
	}

	void move(char key) {
		switch (key)
		{
		case 'W':
			position = position + xbase;
			break;
		case 'A':
			position = position + ybase;
			break;
		case 'E':
			position = position + zbase;
			break;
		case 'S':
			position = position - xbase;
			break;
		case 'D':
			position = position - ybase;
			break;
		case 'Q':
			position = position - zbase;
			break;
		default:
			position = position;
			break;
		}
	}

	void rotate(char key) {
		switch (key)
		{
		case 'Z':
			setBase(xbase * cosf(Pi/180) + ybase * sinf(Pi / 180),
					xbase * cosf(Pi / 180 + Pi / 2) + ybase * sinf(Pi / 180 + Pi / 2),
					zbase);
			break;
		case 'X':
			setBase(xbase * cosf(-Pi / 180) + ybase * sinf(-Pi / 180),
				xbase * cosf(-Pi / 180 + Pi / 2) + ybase * sinf(-Pi / 180 + Pi / 2),
				zbase);
			break;
		case 'C':
			setBase(xbase * cosf(Pi / 180) + zbase * sinf(Pi / 180),
				ybase,
				xbase * cosf(Pi / 180 + Pi / 2) + zbase * sinf(Pi / 180 + Pi / 2)
				); 
			break;
		case 'V':
			setBase(xbase * cosf(-Pi / 180) + zbase * sinf(-Pi / 180),
				ybase,
				xbase * cosf(-Pi / 180 + Pi / 2) + zbase * sinf(-Pi / 180 + Pi / 2)
			);
			break;
		case 'R':
			setBase(xbase,
				ybase * cosf(Pi / 180) + zbase * sinf(Pi / 180),
				ybase * cosf(Pi / 180 + Pi / 2) + zbase * sinf(Pi / 180 + Pi / 2));
			break;
		case 'T':
			setBase(xbase,
				ybase * cosf(-Pi / 180) + zbase * sinf(-Pi / 180),
				ybase * cosf(-Pi / 180 + Pi / 2) + zbase * sinf(-Pi / 180 + Pi / 2));
			break;
		default:
			break;
		}
		
	}
};

struct block {
	Vector3 xbase = Vector3(1, 0, 0);
	Vector3 ybase = Vector3(0, 1, 0);
	Vector3 zbase = Vector3(0, 0, 1);

	Vector3 position = Vector3();
	Vector3 viewPosition = Vector3();
	void setPosition(float x, float y,float z) {
		position = Vector3(x, y, z);
	}
	void setBase(Vector3 xxbase, Vector3 yybase, Vector3 zzbase) {
		xbase = xxbase;
		ybase = yybase;
		zbase = zzbase;
	}
	void findTransformationPosition(camera c) {
		Vector3 positionVector = position - c.position;
		Matrix33 A(xbase, ybase, zbase);
		Matrix33 B(c.xbase, c.ybase, c.zbase);
		B.transposition();
		Matrix33 C = findExcessMatrix(A, B);

		//std::cout << "Excess Matrix is：" << endl
		//	<< "[" << setw(6) << C.getXvector3().getX() << "," << setw(6) << C.getXvector3().getY() << "," << setw(6) << C.getXvector3().getZ() << "]" << endl
		//	<< "[" << setw(6) << C.getYvector3().getX() << "," << setw(6) << C.getYvector3().getY() << "," << setw(6) << C.getYvector3().getZ() << "]" << endl
		//	<< "[" << setw(6) << C.getZvector3().getX() << "," << setw(6) << C.getZvector3().getY() << "," << setw(6) << C.getZvector3().getZ() << "]" << endl;

		Matrix33 X(Vector3(positionVector.getX(), 0, 0), Vector3(positionVector.getY(), 0, 0), Vector3(positionVector.getZ(), 0, 0));
		Matrix33 Y = findExcessMatrix(C, X);
		viewPosition = Vector3(Y.getXvector3().getX(), Y.getYvector3().getX(), Y.getZvector3().getX());
	}
};

void initialize(int length, Vector3 point, block myBlocks[]) {
	int x = point.getX();
	int y = point.getY();
	int z = point.getZ();
	for (int i = 0; i < length; i++) {
		myBlocks[i].setPosition(1 + i + x, 0 + y, 0 + z);
		myBlocks[i + length * 1].setPosition(1 + i + x, length + 1 + y, 0 + z);
		myBlocks[i + length * 2].setPosition(1 + i + x, 0 + y, length + 1 + z);
		myBlocks[i + length * 3].setPosition(1 + i + x, length + 1 + y, length + 1 + z);
		myBlocks[i + length * 4].setPosition(0 + x, 1 + i + y, 0 + z);
		myBlocks[i + length * 5].setPosition(length + 1 + x, 1 + i + y, 0 + z);
		myBlocks[i + length * 6].setPosition(0 + x, 1 + i + y, length + 1 + z);
		myBlocks[i + length * 7].setPosition(length + 1 + x, 1 + i + y, length + 1 + z);
		myBlocks[i + length * 8].setPosition(0 + x, 0 + y, 1 + i + z);
		myBlocks[i + length * 9].setPosition(length + 1 + x, 0 + y, 1 + i + z);
		myBlocks[i + length * 10].setPosition(0 + x, length + 1 + y, 1 + i + z);
		myBlocks[i + length * 11].setPosition(length + 1 + x, length + 1 + y, 1 + i + z);
	}
	myBlocks[length * 12].setPosition(0 + x, 0 + y, 0 + z);
	myBlocks[length * 12 + 1].setPosition(length + 1 + x, 0 + y, 0 + z);
	myBlocks[length * 12 + 2].setPosition(0 + x, length + 1 + y, 0 + z);
	myBlocks[length * 12 + 3].setPosition(length + 1 + x, length + 1 + y, 0 + z);
	myBlocks[length * 12 + 4].setPosition(0 + x, 0 + y, length + 1 + z);
	myBlocks[length * 12 + 5].setPosition(length + 1 + x, 0 + y, length + 1 + z);
	myBlocks[length * 12 + 6].setPosition(0 + x, length + 1 + y, length + 1 + z);
	myBlocks[length * 12 + 7].setPosition(length + 1 + x, length + 1 + y, length + 1 + z);

}


Matrix33 findExcessMatrix(Matrix33 A, Matrix33 B) {
	Matrix33 AA=A;
	Matrix33 BB=B;
	//while (!(AA == Matrix33())) {
		//
		while (AA.getXvector3().getX() == 0.0) {
			Vector3 tempXvector3 = AA.getXvector3();
			Vector3 tempYvector3 = AA.getYvector3();
			Vector3 tempZvector3 = AA.getZvector3();
			AA.xVector3= tempYvector3;
			AA.yVector3= tempZvector3;
			AA.zVector3= tempXvector3;
			Vector3 tempBXvector3 = BB.getXvector3();
			Vector3 tempBYvector3 = BB.getYvector3();
			Vector3 tempBZvector3 = BB.getZvector3();
			BB.xVector3 = tempBYvector3;
			BB.yVector3 = tempBZvector3;
			BB.zVector3 = tempBXvector3;
		}
		if (AA.getXvector3().getX() != 1.0) {
			Vector3 tempXvector3 = AA.getXvector3();
			Vector3 tempYvector3 = AA.getYvector3();
			Vector3 tempZvector3 = AA.getZvector3();
			AA.xVector3 = Vector3(AA.getXvector3().getX() / AA.getXvector3().getX(),
									  AA.getXvector3().getY() / AA.getXvector3().getX(),
									  AA.getXvector3().getZ() / AA.getXvector3().getX());
			BB.xVector3 = Vector3(BB.getXvector3().getX() / tempXvector3.getX(),
									  BB.getXvector3().getY() / tempXvector3.getX(),
									  BB.getXvector3().getZ() / tempXvector3.getX());
		}
		if (AA.getYvector3().getX() != 0.0) {
			Vector3 tempXvector3 = AA.getXvector3();
			Vector3 tempYvector3 = AA.getYvector3();
			Vector3 tempZvector3 = AA.getZvector3();
			AA.yVector3 = Vector3(AA.getYvector3().getX() - AA.getXvector3().getX() * AA.getYvector3().getX(),
									  AA.getYvector3().getY() - AA.getXvector3().getY() * AA.getYvector3().getX(),
									  AA.getYvector3().getZ() - AA.getXvector3().getZ() * AA.getYvector3().getX());
			BB.yVector3 = Vector3(BB.getYvector3().getX() - BB.getXvector3().getX() * tempYvector3.getX(),
									  BB.getYvector3().getY() - BB.getXvector3().getY() * tempYvector3.getX(),
									  BB.getYvector3().getZ() - BB.getXvector3().getZ() * tempYvector3.getX());
		}
		if (AA.getZvector3().getX() != 0.0) {
			Vector3 tempXvector3 = AA.getXvector3();
			Vector3 tempYvector3 = AA.getYvector3();
			Vector3 tempZvector3 = AA.getZvector3();
			AA.zVector3 = Vector3(AA.getZvector3().getX() - AA.getXvector3().getX() * AA.getZvector3().getX(),
									  AA.getZvector3().getY() - AA.getXvector3().getY() * AA.getZvector3().getX(),
									  AA.getZvector3().getZ() - AA.getXvector3().getZ() * AA.getZvector3().getX());
			BB.zVector3 = Vector3(BB.getZvector3().getX() - BB.getXvector3().getX() * tempZvector3.getX(),
									  BB.getZvector3().getY() - BB.getXvector3().getY() * tempZvector3.getX(),
									  BB.getZvector3().getZ() - BB.getXvector3().getZ() * tempZvector3.getX());
		}
		//
		while (AA.getYvector3().getY() == 0.0) {
			Vector3 tempYvector3 = AA.getYvector3();
			Vector3 tempZvector3 = AA.getZvector3();
			AA.yVector3 = tempZvector3;
			AA.zVector3 = tempYvector3;
			Vector3 tempBYvector3 = BB.getYvector3();
			Vector3 tempBZvector3 = BB.getZvector3();
			BB.yVector3 = tempBZvector3;
			BB.zVector3 = tempBYvector3;
		}
		if (AA.getYvector3().getY() != 1.0) {
			Vector3 tempXvector3 = AA.getXvector3();
			Vector3 tempYvector3 = AA.getYvector3();
			Vector3 tempZvector3 = AA.getZvector3();
			AA.yVector3 = Vector3(AA.getYvector3().getX() / AA.getYvector3().getY(),
								      AA.getYvector3().getY() / AA.getYvector3().getY(),
									  AA.getYvector3().getZ() / AA.getYvector3().getY());
			BB.yVector3 = Vector3(BB.getYvector3().getX() / tempYvector3.getY(),
									  BB.getYvector3().getY() / tempYvector3.getY(),
									  BB.getYvector3().getZ() / tempYvector3.getY());
		}
		if (AA.getZvector3().getY() != 0.0) {
			Vector3 tempXvector3 = AA.getXvector3();
			Vector3 tempYvector3 = AA.getYvector3();
			Vector3 tempZvector3 = AA.getZvector3();
			AA.zVector3 = Vector3(AA.getZvector3().getX() - AA.getYvector3().getX() * AA.getZvector3().getY(),
									  AA.getZvector3().getY() - AA.getYvector3().getY() * AA.getZvector3().getY(),
									  AA.getZvector3().getZ() - AA.getYvector3().getZ() * AA.getZvector3().getY());
			BB.zVector3 = Vector3(BB.getZvector3().getX() - BB.getYvector3().getX() * tempZvector3.getY(),
									  BB.getZvector3().getY() - BB.getYvector3().getY() * tempZvector3.getY(),
									  BB.getZvector3().getZ() - BB.getYvector3().getZ() * tempZvector3.getY());
		}
		//
		if (AA.getZvector3().getZ() != 1.0) {
			Vector3 tempXvector3 = AA.getXvector3();
			Vector3 tempYvector3 = AA.getYvector3();
			Vector3 tempZvector3 = AA.getZvector3();
			AA.zVector3 = Vector3(AA.getZvector3().getX() / AA.getZvector3().getZ(),
									  AA.getZvector3().getY() / AA.getZvector3().getZ(),
									  AA.getZvector3().getZ() / AA.getZvector3().getZ());
			BB.zVector3 = Vector3(BB.getZvector3().getX() / tempZvector3.getZ(),
									  BB.getZvector3().getY() / tempZvector3.getZ(),
									  BB.getZvector3().getZ() / tempZvector3.getZ());
		}
		//
		if (AA.getXvector3().getZ() != 0.0) {
			Vector3 tempXvector3 = AA.getXvector3();
			Vector3 tempYvector3 = AA.getYvector3();
			Vector3 tempZvector3 = AA.getZvector3();
			AA.xVector3 = Vector3(AA.getXvector3().getX() - AA.getZvector3().getX() * AA.getXvector3().getZ(),
								   	  AA.getXvector3().getY() - AA.getZvector3().getY() * AA.getXvector3().getZ(),
									  AA.getXvector3().getZ() - AA.getZvector3().getZ() * AA.getXvector3().getZ());
			BB.xVector3 = Vector3(BB.getXvector3().getX() - BB.getZvector3().getX() * tempXvector3.getZ(),
									  BB.getXvector3().getY() - BB.getZvector3().getY() * tempXvector3.getZ(),
									  BB.getXvector3().getZ() - BB.getZvector3().getZ() * tempXvector3.getZ());
		}
		if (AA.getYvector3().getZ() != 0.0) {
			Vector3 tempXvector3 = AA.getXvector3();
			Vector3 tempYvector3 = AA.getYvector3();
			Vector3 tempZvector3 = AA.getZvector3();
			AA.yVector3 = Vector3(AA.getYvector3().getX() - AA.getZvector3().getX() * AA.getYvector3().getZ(),
									  AA.getYvector3().getY() - AA.getZvector3().getY() * AA.getYvector3().getZ(),
									  AA.getYvector3().getZ() - AA.getZvector3().getZ() * AA.getYvector3().getZ());
			BB.yVector3 = Vector3(BB.getYvector3().getX() - BB.getZvector3().getX() * tempYvector3.getZ(),
									  BB.getYvector3().getY() - BB.getZvector3().getY() * tempYvector3.getZ(),
									  BB.getYvector3().getZ() - BB.getZvector3().getZ() * tempYvector3.getZ());
		}
		//
		if (AA.getXvector3().getY() != 0.0) {
			Vector3 tempXvector3 = AA.getXvector3();
			Vector3 tempYvector3 = AA.getYvector3();
			Vector3 tempZvector3 = AA.getZvector3();
			AA.xVector3 = Vector3(AA.getXvector3().getX() - AA.getYvector3().getX() * AA.getXvector3().getY(),
									  AA.getXvector3().getY() - AA.getYvector3().getY() * AA.getXvector3().getY(),
									  AA.getXvector3().getZ() - AA.getYvector3().getZ() * AA.getXvector3().getY());
			BB.xVector3 = Vector3(BB.getXvector3().getX() - BB.getYvector3().getX() * tempXvector3.getY(),
									  BB.getXvector3().getY() - BB.getYvector3().getY() * tempXvector3.getY(),
									  BB.getXvector3().getZ() - BB.getYvector3().getZ() * tempXvector3.getY());
		}
		//
	//}
	Matrix33 C = BB;
	return C;
}
bool Screen[500][1000] = { false };


void shootOnScreen(block b,camera c) {
	float screenXposition = 400;
	float screenYposition = 0;
	float screenZposition = 0;
	b.findTransformationPosition(c);
	if (b.viewPosition.getX() > 0) {

		float shootX = screenXposition* b.viewPosition.getY() / b.viewPosition.getX();
		float shootY = screenXposition* b.viewPosition.getZ() / b.viewPosition.getX();

		if (shootX < 500 && shootX >= -500 && shootY < 250 && shootY >= -250) {
			int x = shootX;
			int y = shootY;
			if (x == 500) {
				x--;
			}
			if (y == 250) {
				y--;
			}
			Screen[249-y][499-x] = true;
		}

	}
}


int main() {
	int length1 = 20, length2 = 40, length3 = 50, length4 = 100;
	Vector3 point1(0,0,0), point2(25,25,-50), point3(-70,-60,10), point4(-10,-140,-50);
	block* myBlocks1 = new block[length1 * 12 + 8];
	block* myBlocks2 = new block[length2 * 12 + 8];
	block* myBlocks3 = new block[length3 * 12 + 8];
	block* myBlocks4 = new block[length4 * 12 + 8];

	initialize(length1, point1, myBlocks1);
	initialize(length2, point2, myBlocks2);
	initialize(length3, point3, myBlocks3);
	initialize(length4, point4, myBlocks4);

	camera myCamera;
	myCamera.setPosition(20, 100, 10);
	
	myCamera.setBase(Vector3(cosf(-Pi / 4), sinf(-Pi / 4), 0), Vector3(cosf(-Pi / 4 + Pi / 2), sinf(-Pi / 4 + Pi / 2), 0), Vector3(0, 0, 1));


	for (int i = 0; i < 500; i++) {
		for (int j = 0; j < 1000; j++) {
			Screen[i][j] = false;
		}
	}

	sf::RenderWindow window(sf::VideoMode(1000, 500), "3D game");
	sf::Texture text;
	text.loadFromFile("block.png");

	sf::Sprite/*指可移动图像*/s(text);
	s.setTextureRect(sf::IntRect(0, 0, 1, 1));


	float tickTime = 0, delay = 0.3;

	sf::Clock clock;

	

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		tickTime += time;

		sf::Event gameEvent;
		while (window.pollEvent(gameEvent))
		{
			if (gameEvent.type == sf::Event::Closed) {
				window.close();
			}
			if (gameEvent.type == sf::Event::KeyPressed) {
				if (gameEvent.key.code == sf::Keyboard::W)	myCamera.move('W');
				else if (gameEvent.key.code == sf::Keyboard::A)myCamera.move('A');
				else if (gameEvent.key.code == sf::Keyboard::S)myCamera.move('S');
				else if (gameEvent.key.code == sf::Keyboard::D)myCamera.move('D');
				else if (gameEvent.key.code == sf::Keyboard::Q)myCamera.move('Q');
				else if (gameEvent.key.code == sf::Keyboard::E)myCamera.move('E');

				else if (gameEvent.key.code == sf::Keyboard::Z)myCamera.rotate('Z');
				else if (gameEvent.key.code == sf::Keyboard::X)myCamera.rotate('X');
				else if (gameEvent.key.code == sf::Keyboard::C)myCamera.rotate('C');
				else if (gameEvent.key.code == sf::Keyboard::V)myCamera.rotate('V');
				else if (gameEvent.key.code == sf::Keyboard::R)myCamera.rotate('R');
				else if (gameEvent.key.code == sf::Keyboard::T)myCamera.rotate('T');

				for (int i = 0; i < 500; i++) {
					for (int j = 0; j < 1000; j++) {
						Screen[i][j] = false;
					}
				}
			}

		}
		//下落间隔
		if (tickTime > delay) {
			tickTime = 0;
		}
		delay = 0.3;

		for (int i = 0; i < length1*12+8; i++) {
			shootOnScreen(myBlocks1[i], myCamera);
		}
		for (int i = 0; i < length2 * 12 + 8; i++) {
			shootOnScreen(myBlocks2[i], myCamera);
		}
		for (int i = 0; i < length3 * 12 + 8; i++) {
			shootOnScreen(myBlocks3[i], myCamera);
		}
		for (int i = 0; i < length4 * 12 + 8; i++) {
			shootOnScreen(myBlocks4[i], myCamera);
		}
		
			window.clear(sf::Color::White);
		

		for (int i = 0; i < 500; i++) {
			for (int j = 0; j < 1000; j++) {
				if (Screen[i][j]) {
					s.setTextureRect(sf::IntRect(0, 0, 1, 1));//矩形范围

					s.setPosition(j , i );
					window.draw(s);
					/*
					s.setPosition(j + 500, i + 1 + 250);
					window.draw(s);
					s.setPosition(j + 500, i - 1 + 250);
					window.draw(s);
					s.setPosition(j + 1 + 500, i + 250);
					window.draw(s);
					s.setPosition(j - 1 + 500, i + 250);
					window.draw(s);
					s.setPosition(j + 1 + 500, i + 1 + 250);
					window.draw(s);
					s.setPosition(j + 1 + 500, i - 1 + 250);
					window.draw(s);
					s.setPosition(j - 1 + 500, i + 1 + 250);
					window.draw(s);
					s.setPosition(j - 1 + 500, i - 1 + 250);
					window.draw(s);  
					*/
				}
				else {
					
				}
			}
			
		}
		/*
		for (int i = 0; i < 500; i++) {
			for (int j = 0; j < 1000; j++) {
				if (Screen[i][j]) {
					cout << '#';
				}
				else {
					cout << ' ';
				}
			}
			cout << endl;
		}
		system("cls");
		*/
		window.display();



	}



}


	
	/*
	while (1) {
		for (int i = 0; i < 248; i++) {
			shootOnScreen(myBlocks[i], myCamera);
		}

		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 100; j++) {
				if (Screen[i][j]) {
					cout << '#';
				}
				else {
					cout << ' ';
				}
			}
			cout << endl;
		}
		char a;
		cin >> a;

		if (a == 'w') {
			myCamera.setPosition(myCamera.position.getX(), myCamera.position.getY()-1, myCamera.position.getZ());
		}
		if (a == 'a') {
			myCamera.setPosition(myCamera.position.getX()+1, myCamera.position.getY(), myCamera.position.getZ());
		}
		if (a == 's') {
			myCamera.setPosition(myCamera.position.getX(), myCamera.position.getY()+1, myCamera.position.getZ());
		}
		if (a == 'd') {
			myCamera.setPosition(myCamera.position.getX()-1, myCamera.position.getY(), myCamera.position.getZ());
		}

	}
	*/
	//myBlock.setPosition(1, 1, 0);

	//std::cout << "Vector x is：" << endl <<
	//	"[" << setw(6) << myBlock.position.getX() << "," << setw(6) << myBlock.position.getY() << "," << setw(6) << myBlock.position.getZ() << "]" << endl << endl;
	
	//myBlock.setBase(Vector3(-5.23, 0.235, 1.356), Vector3(1.235, 2.567, -1.635), Vector3(1.23, 2.78, -3.56));
	//std::cout << "Base e1 are：" << endl
	//	<< "[" << setw(6) << myBlock.xbase.getX() << "," << setw(6) << myBlock.ybase.getX() << "," << setw(6) << myBlock.zbase.getX() << "]" << endl
	//	<< "[" << setw(6) << myBlock.xbase.getY() << "," << setw(6) << myBlock.ybase.getY() << "," << setw(6) << myBlock.zbase.getY() << "]" << endl
	//	<< "[" << setw(6) << myBlock.xbase.getZ() << "," << setw(6) << myBlock.ybase.getZ() << "," << setw(6) << myBlock.zbase.getZ() << "]" << endl << endl;
	
	//camera myCamera;
	//myCamera.setPosition(0, 50, 0);

	//std::cout << "Vector c is：" << endl <<
	//	"[" << setw(6) << myCamera.position.getX() << "," << setw(6) << myCamera.position.getY() << "," << setw(6) << myCamera.position.getZ() << "]" << endl << endl;
	
	//myCamera.setBase(Vector3((1 / sqrtf(2)), (1 / sqrtf(2)), 0), Vector3(-(1 / sqrtf(2)), 1 / sqrtf(2), 0), Vector3(0, 0, 1));
	
	//std::cout << "Base e2 are：" << endl
	//	<< "[" << setw(6) << myCamera.xbase.getX() << "," << setw(6) << myCamera.ybase.getX() << "," << setw(6) << myCamera.zbase.getX() << "]" << endl
	//	<< "[" << setw(6) << myCamera.xbase.getY() << "," << setw(6) << myCamera.ybase.getY() << "," << setw(6) << myCamera.zbase.getY() << "]" << endl
	//	<< "[" << setw(6) << myCamera.xbase.getZ() << "," << setw(6) << myCamera.ybase.getZ() << "," << setw(6) << myCamera.zbase.getZ() << "]" << endl << endl;
	
	//myBlock.findTransformationPosition(myCamera);
	
	//std::cout << "Vector y is：" << endl <<
	//	"[" << setw(6) << myBlock.viewPosition.getX() << "," << setw(6) << myBlock.viewPosition.getY() << "," << setw(6) << myBlock.viewPosition.getZ() << "]" << endl << endl;
