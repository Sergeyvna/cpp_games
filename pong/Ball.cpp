#include "Ball.h"

Ball::Ball(float startX, float startY)
{
	m_pos.x = startX;
	m_pos.y = startY;

	m_shape.setSize(sf::Vector2f(10, 10));
	m_shape.setPosition(m_pos);
	m_shape.setFillColor(Color(0, 235, 96));
}

FloatRect Ball::getPos()
{
	return m_shape.getGlobalBounds();
}

RectangleShape Ball::getShape()
{
	return m_shape;
}

float Ball::getXVelocity()
{
	return m_directionX;
}

void Ball::reboundSides()
{
	m_directionX = -m_directionX;
}

void Ball::reboundBatOrTop()
{
	m_directionY = -m_directionY;
}

void Ball::reboundBottom()
{
	m_pos.y = 0;
	m_pos.x = 500;
	m_directionY = -m_directionY;
}

void Ball::update(Time dt) 
{
	m_pos.x += m_directionX * m_speed * dt.asSeconds();
	m_pos.y += m_directionY * m_speed * dt.asSeconds();

	m_shape.setPosition(m_pos);
}