#ifndef BOARD_HPP
#define BOARD_HPP

#include "Food.hpp"
#include "Snake.hpp"

#include "SFML/Graphics.hpp"

class Board
{
	public:
		void initialise(sf::RenderWindow *window);
		void update(sf::RenderWindow *window);
		void render(sf::RenderWindow *window);

		sf::RectangleShape boardBackground;

		int boardSize = 20;
		int tileSize = 32;

		Food food;
		Snake snake;

		sf::Font font;

		sf::RectangleShape messageBox;

		sf::Text gameOverText;
		sf::Text gameWonText;
		sf::Text snakeLengthText;
		sf::Text pressEnterText;
};

#endif