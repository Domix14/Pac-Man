#pragma once

#include <iostream>
#include <SFML/System/Vector2.hpp>

#ifdef _DEBUG
#define LOG(t, v) log_implementation(t, v)
#define LOGS(t) log_implementation(t)
#elif
#define LOG(t, v)
#endif

static int randRange(int start, int end)
{
	static bool first = true;
	if(first)
	{
		std::srand(static_cast<unsigned>(time(NULL)));
		first = false;
	}
	if (start == end) return start;
	return (std::rand() % ((end + 1) - start)) + start;
}

static void log_implementation(std::string text, float value)
{
	std::cout << text << value << "\n";
}

static void log_implementation(std::string text, sf::Vector2f vector)
{
	std::cout << text << "x: " << vector.x << " y: " << vector.y << "\n";
}

static void log_implementation(std::string text)
{
	std::cout << text << "\n";
}

static void log_implementation(std::string text, sf::Vector2i vector)
{
	std::cout << text << "x: " << vector.x << " y: " << vector.y << "\n";
}

static float length(sf::Vector2f vector)
{
	return static_cast<float>(sqrt(vector.x * vector.x + vector.y * vector.y));
}

static sf::Vector2i abs(sf::Vector2i vector)
{
	vector.x = abs(vector.x);
	vector.y = abs(vector.y);
	return vector;
}