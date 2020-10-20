#pragma once

#include <SFML/System/Vector2.hpp>

#ifdef _DEBUG
#define LOG(t, v) log_implementation(t, v)
#elif
#define LOG(t, v)
#endif

void log_implementation(std::string text, float value)
{
	std::cout << text << value << "\n";
}

void log_implementation(std::string text, sf::Vector2f vector)
{
	std::cout << text << "x: " << vector.x << " y: " << vector.y << "\n";
}

float length(sf::Vector2f vector)
{
	return static_cast<float>(sqrt(vector.x * vector.x + vector.y * vector.y));
}