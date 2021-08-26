#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Particles.h"
#include "Constants.h"

bool fEquals(const float& a, const float& b)
{
	return fabs(a - b) < EPSILON;
}

void moveAlongVector(sf::Vector2f& p, sf::Vector2f t, const float& d)
{
	float ep = d / sqrt(t.x * t.x + t.y * t.y);
	p += ep * t;
}

float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return a.x * b.x + a.y * b.y;
}

Particles::Particles(const sf::Color& colour)
{
	m_particles = new sf::CircleShape[QUANTITY];
	m_positions = new sf::Vector2f[QUANTITY];
	m_velocities = new sf::Vector2f[QUANTITY];

	for (int i = 0; i < QUANTITY; i++)
	{
		m_particles[i].setRadius(RADIUS);
		m_particles[i].setOrigin(sf::Vector2f(RADIUS, RADIUS));
		m_particles[i].setFillColor(colour);

		m_positions[i].x = (float(rand()) / RAND_MAX) * SCREEN_WIDTH;
		m_positions[i].y = (float(rand()) / RAND_MAX) * SCREEN_HEIGHT;
		m_particles[i].setPosition(sf::Vector2f(m_positions[i]));

		m_velocities[i].x = ((float(rand()) / RAND_MAX) * 2 - 1) * MAX_VELOCITY / 2.0f;
		m_velocities[i].y = 0;
	}
}

void Particles::reset()
{
	for (int i = 0; i < QUANTITY; i++)
	{
		m_positions[i].x = (float(rand()) / RAND_MAX) * SCREEN_WIDTH;
		m_positions[i].y = (float(rand()) / RAND_MAX) * SCREEN_HEIGHT;
		m_particles[i].setPosition(sf::Vector2f(m_positions[i]));

		m_velocities[i].x = ((float(rand()) / RAND_MAX) * 2 - 1) * MAX_VELOCITY / 2.0f;
		m_velocities[i].y = 0;
	}
}

Particles::~Particles()
{
	delete[] m_particles;
	delete[] m_positions;
	delete[] m_velocities;
}

void Particles::update(const float& frameTime)
{
	for (int i = 0; i < QUANTITY; i++)
	{
		m_velocities[i].y += G * frameTime * 0.01f;

		m_positions[i].x += m_velocities[i].x * frameTime * 0.01f;
		m_positions[i].y += m_velocities[i].y * frameTime * 0.01f;
	}
	boundsCheck();
	frictionCheck(frameTime);
	collisionCheck(frameTime);

	for (int i = 0; i < QUANTITY; i++)
	{
		m_particles[i].setPosition(m_positions[i]);
	}
}

void Particles::boundsCheck()
{
	for (int i = 0; i < QUANTITY; i++)
	{
		if (m_positions[i].x < RADIUS || m_positions[i].x > SCREEN_WIDTH - RADIUS)
		{
			m_positions[i].x = std::min(SCREEN_WIDTH - RADIUS, std::max(RADIUS, m_positions[i].x));
			m_velocities[i].x = -E * m_velocities[i].x;
		}
		if (m_positions[i].y < RADIUS || m_positions[i].y > SCREEN_HEIGHT - RADIUS)
		{
			m_positions[i].y = std::min(SCREEN_HEIGHT - RADIUS, std::max(RADIUS, m_positions[i].y));
			m_velocities[i].y = -E * m_velocities[i].y;
		}
	}
}

void Particles::frictionCheck(const float& frameTime)
{
	for (int i = 0; i < QUANTITY; i++)
	{
		float ratio = 1.0f / (1.0f + (frameTime * FK));
		if (fEquals(m_velocities[i].x * frameTime * 0.01f, 0.0f) && (fEquals(m_positions[i].x, RADIUS) || fEquals(m_positions[i].x, SCREEN_WIDTH - RADIUS)))
		{
			m_velocities[i].y = ratio * m_velocities[i].y;
		}
		if (fEquals(m_velocities[i].y * frameTime * 0.01f, 0.0f) && (fEquals(m_positions[i].y, RADIUS) || fEquals(m_positions[i].y, SCREEN_HEIGHT - RADIUS)))
		{
			m_velocities[i].x = ratio * m_velocities[i].x;
		}
	}
}

void Particles::collisionCheck(const float& frameTime)
{
	for (int i = 0; i < QUANTITY; i++)
	{
		for (int j = 0; j < QUANTITY && j != i; j++)
		{
			float x1 = m_positions[i].x;
			float y1 = m_positions[i].y;
			float x2 = m_positions[j].x;
			float y2 = m_positions[j].y;

			float dist = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
			if (dist <= 2 * RADIUS)
			{
				moveAlongVector(m_positions[i], m_positions[j] - m_positions[i], -(2 * RADIUS - dist) / 2);
				moveAlongVector(m_positions[j], m_positions[j] - m_positions[i], (2 * RADIUS - dist) / 2);

				sf::Vector2f normal = (m_positions[i] - m_positions[j]) / (2 * RADIUS);
				sf::Vector2f tangent;
				tangent.x = -normal.y;
				tangent.y = normal.x;

				float dpTan1 = dotProduct(m_velocities[i], tangent);
				float dpTan2 = dotProduct(m_velocities[j], tangent);

				float dpNorm1 = dotProduct(m_velocities[i], normal);
				float dpNorm2 = dotProduct(m_velocities[j], normal);

				m_velocities[i] = (tangent * dpTan1) + (normal * dpNorm2);
				m_velocities[j] = (tangent * dpTan2) + (normal * dpNorm1);
				m_velocities[i] *= 1.0f / (1.0f + (E * frameTime * 0.005f));
				m_velocities[j] *= 1.0f / (1.0f + (E * frameTime * 0.005f));
			}
		}
	}
}

void Particles::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < QUANTITY; i++)
	{
		window.draw(m_particles[i]);
	}
}