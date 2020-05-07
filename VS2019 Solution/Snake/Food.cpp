/* Headers */
#include "Food.hpp"

/* Functions */
void Food::initialise(sf::RenderWindow *window, int tileSize)
{
	food.setSize(sf::Vector2f(tileSize, tileSize));
	food.setFillColor(sf::Color::White);
}

void Food::generate(std::vector<sf::RectangleShape> *body, int boardSize, int tileSize)
{
	// If there are available spaces
	if (body->size() != boardSize * boardSize)
	{
		// Generate a random location for the food
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(0, boardSize - 1);

		food.setPosition(sf::Vector2f(tileSize * dist(mt), tileSize * dist(mt)));

		// Check the food isn't now inside the snake
		for (int bodyPart = 0; bodyPart < body->size(); bodyPart++)
		{
			// If the food is inside a body part
			if (body->at(bodyPart).getPosition() == food.getPosition())
			{
				// Generate the food in a new random location
				generate(body, boardSize, tileSize);
			}
		}
	}
}

void Food::render(sf::RenderWindow *window)
{
	// Draw the food
	window->draw(food);
}