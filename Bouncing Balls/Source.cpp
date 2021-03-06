#include <iostream>
#include <sstream>
#include <algorithm>

#include <SFML/Graphics.hpp>
#include "Timer.h"
#include "FrameTime.h"
#include "Particles.h"
#include "Constants.h"

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Particle Simulator", sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	sf::Font font;
	if (!font.loadFromFile("Monaco Regular.ttf"))
		return EXIT_FAILURE;

	float frameTime = 0;

	std::stringstream textFrameTime;

	sf::Text sf_frameTime(textFrameTime.str(), font, 20);
	sf_frameTime.setPosition(sf::Vector2f(10, 10));

	sf::Text sf_legends("Keyboard Input\n1. Press SPACE to pause.\n2. Press R to reset.\n3.Press M to change mode.", font, 20);
	sf_legends.setPosition(SCREEN_WIDTH - 10 - sf_legends.getGlobalBounds().width, 10);

	Particles particles(sf::Color::Green, QUANTITY);
	Particles particles_low(sf::Color::Red, QUANTITY_LOW);

	bool paused = false;
	bool reset = false;
	bool mode = false;

	while (window.isOpen())
	{
		FrameTime frame_time(frameTime);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					paused = !paused;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
					reset = true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
					mode = !mode;
			}
		}

		textFrameTime.str(std::string());
		textFrameTime << "frame time: " << frameTime << "ms (" << 1000 / frameTime << "fps)";
		sf_frameTime.setString(textFrameTime.str());

		if (!paused)
		{
			if (mode)
				particles.update(frameTime);
			else
				particles_low.update(frameTime);
		}
		if (reset)
		{
			particles.reset();
			particles_low.reset();
			reset = false;
		}

		window.clear();
		if (mode)
			particles.draw(window);
		else
			particles_low.draw(window);
		window.draw(sf_frameTime);
		window.draw(sf_legends);
		window.display();
	}

	return EXIT_SUCCESS;
}