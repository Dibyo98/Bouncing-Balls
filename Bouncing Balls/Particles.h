#pragma once
#include <SFML/Graphics.hpp>

class Particles
{
public:
	Particles(const sf::Color& colour, const int& quantity);
	~Particles();
	void reset();
	void update(const float& frameTime);
	void draw(sf::RenderWindow& window);

private:
	void boundsCheck();
	void frictionCheck(const float& frameTime);
	void collisionCheck(const float& frameTime);

private:
	sf::CircleShape* m_particles;
	sf::Vector2f* m_velocities;
	sf::Vector2f* m_positions;
	int m_quantity;
};