#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


std::string toString(double digit){
	int slice = round(digit*100);
	std::string beforeDot = std::to_string(abs(slice)/100);
	std::string afterDot = std::to_string(abs(slice)%100);
	return (digit < 0)? "-" +beforeDot + "."+afterDot:beforeDot + "."+afterDot; 
}



using namespace sf;

const int W = 600;
const int H = 600;


int main() {
	std::vector<double> xInput = {  -3,      -2,      -1,       0,      1,      2       };
    std::vector<double> yInput = {   0.04979, 0.13534, 0.36788, 1,      2.7183, 7.3891  };
	RenderWindow window(VideoMode(W, H), "plotting");

	int x0 = W/2;
	int y0 = H / 2;
	int sc = 100;

	RectangleShape OX(Vector2f(W, 1));
	OX.setFillColor(Color::Black);
	OX.setPosition(0, y0);

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

	const int serifNum = 24;
	Font font;
    font.loadFromFile("./calibri.ttf");
	Text X("X", font);
	Text Y("Y", font);
	X.setFillColor(Color::Black);
	Y.setFillColor(Color::Black);
	X.setCharacterSize(16);
	Y.setCharacterSize(16);
	Y.setPosition(x0 + 10, 1);
	X.setPosition(W - 15, y0 + 5);
	Text VerticalMark[serifNum];
	RectangleShape VerticalSerif[serifNum];
	for (int i = 0; i < serifNum; i++) {
		VerticalSerif[i].setSize(Vector2f(1, 6));
		VerticalSerif[i].setFillColor(Color::Black);
        VerticalSerif[i].setPosition(x0 + (i-serifNum/2)*sc/4, y0 - 3);

		VerticalMark[i].setFont(font);
		VerticalMark[i].setFillColor(Color::Black);
		VerticalMark[i].setCharacterSize(10);
		VerticalMark[i].setString(toString((i-serifNum/2)/4.0));
		VerticalMark[i].setPosition(x0 + (i-serifNum/2)*sc/4 - 7, y0 + 3);
	}
	VerticalMark[0].setString("0");
	VerticalMark[0].setPosition(x0 + 5, y0 + 3);

	Text HorizontaMark[serifNum];
    RectangleShape HorizontalSerif[serifNum];
	for (int i = 0; i < serifNum; i++) {
		HorizontalSerif[i].setSize(Vector2f(1, 6));
		HorizontalSerif[i].setFillColor(Color::Black);
        HorizontalSerif[i].setPosition(x0 + 3, y0 + (serifNum/2-i)*sc/4);
        HorizontalSerif[i].setRotation(90);

		HorizontaMark[i].setFont(font);
		HorizontaMark[i].setFillColor(Color::Black);
		HorizontaMark[i].setCharacterSize(10);
		HorizontaMark[i].setString(toString((i-serifNum/2)/4.0));
		HorizontaMark[i].setPosition(x0 + 5, y0 + (serifNum/2-i)*sc/4);
	}

	CircleShape point(0.5);
	point.setFillColor(Color::Blue);
	int o1 = -7;
	int o2 = 7;
	float c = 6000;
	int mass = (o2-o1) * c + 1;

	CircleShape pointInput(3);
	pointInput.setFillColor(Color::Red);

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
			float y = 2.58737 + 1.28793*x;
			float x1 = x0 + x * sc;
			float y1 = y0 - y * sc;

			point.setPosition(x1, y1);
			window.draw(point);
		}

		for (int i = 0; i < mass; i++) {
			float x = o1 + i / c;
			float y = 1.21264 + 1.80345*x + 0.515523*x*x;
			float x1 = x0 + x * sc;
			float y1 = y0 - y * sc;

			point.setPosition(x1, y1);
			window.draw(point);
		}

		for(int i = 0; i < xInput.size(); i++) {
			float x1 = x0 + xInput[i] * sc;
			float y1 = y0 - yInput[i] * sc;
			pointInput.setPosition(x1, y1);
			window.draw(pointInput);
		}


		for (int i = 0; i < serifNum-1; i++) {
			if(i == serifNum/2) continue;
			window.draw(VerticalSerif[i]);
			window.draw(VerticalMark[i]);
			window.draw(HorizontalSerif[i]);
			window.draw(HorizontaMark[i]);
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