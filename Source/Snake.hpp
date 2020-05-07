#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "SFML/Graphics.hpp"

class Snake
{
	public:
		void initialise(sf::RenderWindow *window);
		bool checkFoodEaten();
		void detectGameOver();
		void move();
		void update(sf::RenderWindow *window);
		void render(sf::RenderWindow *window);

		std::vector<sf::RectangleShape> body;

		int boardSize;
		int tileSize;

		enum Direction { left, right, up, down, none };

		int direction = none;

		sf::Clock gameClock;

		sf::Vector2f foodPosition;

		bool moreFoodNeeded = false;

		bool gameOver = false;
		bool gameWon = false;
};

#endif