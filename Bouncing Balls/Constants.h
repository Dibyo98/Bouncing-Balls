#pragma once
#include <SFML/Graphics.hpp>

const unsigned int SCREEN_HEIGHT = unsigned int(0.75f * sf::VideoMode::getDesktopMode().height);
const unsigned int SCREEN_WIDTH = unsigned int(0.75f * sf::VideoMode::getDesktopMode().width);
constexpr float MAX_VELOCITY = 50;
constexpr float G = 9.8f;
constexpr float E = 0.85f;
constexpr float FK = 0.0005f;
constexpr int QUANTITY = 200;
constexpr int QUANTITY_LOW = 4;
constexpr float RADIUS = 10;
constexpr float EPSILON = 0.9f;