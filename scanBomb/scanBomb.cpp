#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

struct block
{
	int x = 0;
	int y = 0;
	int num = 0;

	block(int xx = 0, int yy = 0, int n = 0) {
		x = xx;
		y = yy;
		num = n;
	}
};



int main()
{
	vector<vector<block>>myblock(20, vector<block>(20));
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			myblock[i][j].x = j;
			myblock[i][j].y = i;
		}
	}

	sf::RenderWindow window(sf::VideoMode(640, 640), "bomb game");
	sf::Texture text;
	text.loadFromFile("block.png");

	sf::Sprite/*指可移动图像*/s(text);
	s.setTextureRect(sf::IntRect(0, 0, 32, 32));


	while (window.isOpen())
	{

		sf::Event gameEvent;
		while (window.pollEvent(gameEvent))
		{
			if (gameEvent.type == sf::Event::Closed) {
				window.close();
			}
			if (gameEvent.type== sf::Event::EventType::MouseButtonPressed) {
				int x = sf::Mouse::getPosition(window).x / 32;
				int y = sf::Mouse::getPosition(window).y / 32;
				myblock[y][x].num++;
				if (myblock[y][x].num == 13) {
					myblock[y][x].num = 0;
				}
			}

		}

		

		window.clear(sf::Color::White);
		for(int i=0;i<20;i++){
			for (int j = 0; j < 20; j++) {

				s.setTextureRect(sf::IntRect(myblock[i][j].num * 32, 0, 32, 32));//矩形范围

				s.setPosition(j * 32, i * 32);


				window.draw(s);

			}
		}
		window.display();
	}

}
