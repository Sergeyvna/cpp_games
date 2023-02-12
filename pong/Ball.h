#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
	Vector2f m_pos;
	RectangleShape m_shape;

	float m_speed = 700.f;
	float m_directionX = 0.2f;
	float m_directionY = 0.2f;

public:

	Ball(float startX, float startY);

	FloatRect getPos();
	RectangleShape getShape();

	float getXVelocity();
	void reboundSides();
	void reboundBatOrTop();
	void reboundBottom();
	void update(Time dt);

};
