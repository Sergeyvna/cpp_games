#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bat
{
private:
	Vector2f m_pos;
	RectangleShape m_shape;
	float m_speed = 1000.f;
	bool m_movingRight = false;
	bool m_movingLeft = false;

public:

	Bat(float startX, float startY);

	FloatRect getPos();
	RectangleShape getShape();

	void moveLeft();
	void moveRight();
	void stopLeft();
	void stopRight();

	void update(Time dt);
};
