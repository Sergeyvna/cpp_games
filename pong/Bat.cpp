#include "Bat.h"

Bat::Bat(float startX, float startY)
{
	m_pos.x = startX;
	m_pos.y = startY;

	m_shape.setSize(sf::Vector2f(50, 5));
	m_shape.setPosition(m_pos);
	m_shape.setFillColor(Color(0, 235, 96));
}

FloatRect Bat::getPos()
{
	return m_shape.getGlobalBounds();
}

RectangleShape Bat::getShape()
{
	return m_shape;
}

void Bat::moveLeft()
{
	m_movingLeft = true;
}

void Bat::moveRight()
{
	m_movingRight = true;
}

void Bat::stopLeft()
{
	m_movingLeft = false;
}

void Bat::stopRight()
{
	m_movingRight = false;
}

void Bat::update(Time dt)
{
	if (m_movingLeft)
	{
		m_pos.x -= m_speed * dt.asSeconds();
	}
	
	if (m_movingRight)
	{
		m_pos.x += m_speed * dt.asSeconds();
	}

	m_shape.setPosition(m_pos);
}