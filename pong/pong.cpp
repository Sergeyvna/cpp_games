#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
	VideoMode vm(1024, 640);
	RenderWindow window(vm, "Pong", Style::None);

	int score = 0;
	int lives = 3;

	Bat bat(1024 / 2, 640 - 20);
	Ball ball(1024 / 2, 0);

	Text hud;
	Font font;
	font.loadFromFile("fonts/8bit.ttf");

	hud.setFont(font);
	hud.setCharacterSize(25);
	hud.setFillColor(Color(0, 235, 96));
	hud.setPosition(30, 30);

	Clock clock;

	while (window.isOpen())
	{
		//input
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left) && bat.getPos().left > 0)
			bat.moveLeft();
		else
			bat.stopLeft();

		if (Keyboard::isKeyPressed(Keyboard::Right) && bat.getPos().left + bat.getPos().width < window.getSize().x)
			bat.moveRight();
		else
			bat.stopRight();


		//update
		Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);

		//ui
		std::stringstream ss;
		ss << "Score: " << score << " Lives: " << lives;
		hud.setString(ss.str());

		//restricting ball movement
		if (ball.getPos().top > window.getSize().y)
		{
			ball.reboundBottom();
			lives--;

			if (lives < 1)
			{
				score = 0;
				lives = 3;
			}
		}

		if (ball.getPos().top < 0)
		{
			ball.reboundBatOrTop();
			score++;
		}

		if (ball.getPos().left < 0 || ball.getPos().left + ball.getPos().width > window.getSize().x)
		{
			ball.reboundSides();
			score++;
		}
			

		if(ball.getPos().intersects(bat.getPos()))
			ball.reboundBatOrTop();



		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
	}

	return 0;
}
