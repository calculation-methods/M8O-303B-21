#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


std::string toString(double digit){
	int temp = round(digit*10);
	return std::to_string(temp/10)+"."+std::to_string(temp%10);
}



using namespace sf;

const int W = 600;
const int H = 600;


int main() {
	RenderWindow window(VideoMode(W, H), "drawing graph");

	int x0 = 10;
	int y0 = H / 2;
	int sc = 50;

	RectangleShape OX(Vector2f(W, 1));
	OX.setFillColor(Color::Black);
	OX.setPosition(x0, y0);

	RectangleShape OY(Vector2f(1, H));
	OY.setFillColor(Color::Black);
	OY.setPosition(x0, 0);

	RectangleShape arrow[4];
	for (int i = 0; i < 4; i++) {
		arrow[i].setSize(Vector2f(1, 10));
		arrow[i].setFillColor(Color::Black);
		if (i < 2)
			arrow[i].setPosition(x0, 0);
		else
			arrow[i].setPosition(W, y0);
	}
	arrow[0].setRotation(25);
	arrow[1].setRotation(-25);
	arrow[2].setRotation(60);
	arrow[3].setRotation(-250);

	const int serifNum = 23;
	Font font;
    font.loadFromFile("./calibri.ttf");
	Text X("X", font);
	Text Y("Y", font);
	X.setFillColor(Color::Black);
	Y.setFillColor(Color::Black);
	X.setCharacterSize(16);
	Y.setCharacterSize(16);
	X.setPosition(19, 1);
	Y.setPosition(W - 15, y0 + 5);
	Text VerticalMark[serifNum];
	RectangleShape VerticalSerif[serifNum];
	for (int i = 0; i < serifNum; i++) {
		VerticalSerif[i].setSize(Vector2f(1, 6));
		VerticalSerif[i].setFillColor(Color::Black);
        VerticalSerif[i].setPosition(x0 + i*sc/2, y0 - 3);

		VerticalMark[i].setFont(font);
		VerticalMark[i].setFillColor(Color::Black);
		VerticalMark[i].setCharacterSize(10);
		VerticalMark[i].setString(toString(i/2.0));
		VerticalMark[i].setPosition(x0 + i*sc/2, y0 + 3);
	}
	VerticalMark[0].setString("0");
	VerticalMark[0].setPosition(x0 + 5, y0 + 3);

    RectangleShape HorizontalSerif[serifNum];
	for (int i = 0; i < serifNum; i++) {
		HorizontalSerif[i].setSize(Vector2f(1, 6));
		HorizontalSerif[i].setFillColor(Color::Black);
        HorizontalSerif[i].setPosition(x0 + 3, y0 + (i - 11)*sc/2);
        HorizontalSerif[i].setRotation(90);
	}

	CircleShape point(0.5);
	point.setFillColor(Color::Blue);
	int o1 = 0;
	int o2 = 5;
	float c = 250;
	int mass = (o2-o1) * c + 1;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
            }
		}

		window.clear(Color::White);

		for (int i = 0; i < mass; i++) {
			float x = o1 + i / c;
			float y = exp(x) - 2*x - 2;
			float x1 = x0 + x * sc;
			float y1 = y0 - y * sc;

			point.setPosition(x1, y1);
			window.draw(point);
		}

		for (int i = 0; i < serifNum; i++){
			window.draw(VerticalSerif[i]);
			window.draw(VerticalMark[i]);
			window.draw(HorizontalSerif[i]);
        }
		window.draw(OX);
		window.draw(OY);
		window.draw(X);
		window.draw(Y);
		for (int i = 0; i < 4; i++){
			window.draw(arrow[i]);
        }

		window.display();
	}

	return 0;
}