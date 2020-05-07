#ifndef FOOD_HPP
#define FOOD_HPP

#include "SFML/Graphics.hpp"

#include <random>

class Food
{
	public:
		void initialise(sf::RenderWindow *window, int tileSize);
		void generate(std::vector<sf::RectangleShape> *body, int boardSize, int tileSize);
		void render(sf::RenderWindow *window);

		sf::RectangleShape food;

		bool gameWon = false;
};

#endif