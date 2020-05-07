/* Headers */
#include "Snake.hpp"



/* Functions */
void Snake::initialise(sf::RenderWindow *window)
{
	// Create the head
	sf::RectangleShape head;

	head.setPosition(sf::Vector2f((boardSize / 2) * tileSize, (boardSize / 2) * tileSize));
	head.setSize(sf::Vector2f(tileSize, tileSize));
	head.setFillColor(sf::Color::Yellow);

	// Add the head to the body
	body.push_back(head);
}

bool Snake::checkFoodEaten()
{
	bool foodEaten = false;

	// If the snake is moving to the left
	if (direction == left)
	{
		// If moving the head to the left will cause it to collide with some food
		if (foodPosition == sf::Vector2f(body[0].getPosition().x - tileSize, body[0].getPosition().y))
		{
			foodEaten = true;
		}
	}
	// If the snake is moving to the right
	else if (direction == right)
	{
		// If moving the head to the right will cause it to collide with some food
		if (foodPosition == sf::Vector2f(body[0].getPosition().x + tileSize, body[0].getPosition().y))
		{
			foodEaten = true;
		}
	}
	// If the snake is moving up
	else if (direction == up)
	{
		// If moving the head up will cause it to collide with some food
		if (foodPosition == sf::Vector2f(body[0].getPosition().x, body[0].getPosition().y - tileSize))
		{
			foodEaten = true;
		}
	}
	// If the snake is moving down
	else if (direction == down)
	{
		// If moving the head down will cause it to collide with some food
		if (foodPosition == sf::Vector2f(body[0].getPosition().x, body[0].getPosition().y + tileSize))
		{
			foodEaten = true;
		}
	}

	// If the snake will eat some food, add a "new head" where that food is
	if (foodEaten)
	{
		sf::RectangleShape newHead;

		newHead.setFillColor(sf::Color::Yellow);
		newHead.setPosition(foodPosition);
		newHead.setSize(sf::Vector2f(tileSize, tileSize));

		body.insert(body.begin(), newHead);

		body[1].setFillColor(sf::Color::Red);
	}

	// Return whether or not food was eaten
	return foodEaten;
}

void Snake::detectGameOver()
{
	// Check the snake won't move off the board
	if (direction == left && body[0].getPosition().x - tileSize < 0)
	{
		gameOver = true;
	}
	else if (direction == right && body[0].getPosition().x + tileSize > (boardSize - 1) * tileSize)
	{
		gameOver = true;
	}
	else if (direction == up && body[0].getPosition().y - tileSize < 0)
	{
		gameOver = true;
	}
	else if (direction == down && body[0].getPosition().y + tileSize > (boardSize - 1) * tileSize)
	{
		gameOver = true;
	}

	// Check the snake won't intercept its own body
	for (int bodyPart = 0; bodyPart < body.size(); bodyPart++)
	{
		if (direction == left && sf::Vector2f(body[0].getPosition().x - tileSize, body[0].getPosition().y) == body[bodyPart].getPosition())
		{
			gameOver = true;
		}
		else if (direction == right && sf::Vector2f(body[0].getPosition().x + tileSize, body[0].getPosition().y) == body[bodyPart].getPosition())
		{
			gameOver = true;
		}
		else if (direction == up && sf::Vector2f(body[0].getPosition().x, body[0].getPosition().y - tileSize) == body[bodyPart].getPosition())
		{
			gameOver = true;
		}
		else if (direction == down && sf::Vector2f(body[0].getPosition().x, body[0].getPosition().y + tileSize) == body[bodyPart].getPosition())
		{
			gameOver = true;
		}
	}
}

void Snake::move()
{
	// Detect game over
	detectGameOver();

	// Detect game won
	if (body.size() == boardSize * boardSize)
	{
		gameWon = true;
	}

	// Provided the game isn't won or lost
	if (!gameWon && !gameOver)
	{
		// If the snake hasn't eaten any food
		if (checkFoodEaten())
		{
			moreFoodNeeded = true;
		}
		else
		{
			// Check that the snake is moving in a direction
			if (direction != none)
			{
				// Go through the body parts (from the last one (the tail) to the second one (the one behind the head))
				for (int bodyPart = body.size() - 1; bodyPart != 0; bodyPart--)
				{
					body[bodyPart].setPosition(body[bodyPart - 1].getPosition());
				}

				// Move the head depending on the direction
				if (direction == left)
				{
					body[0].move(sf::Vector2f(-tileSize, 0));
				}
				else if (direction == right)
				{
					body[0].move(sf::Vector2f(tileSize, 0));
				}
				else if (direction == up)
				{
					body[0].move(sf::Vector2f(0, -tileSize));
				}
				else if (direction == down)
				{
					body[0].move(sf::Vector2f(0, tileSize));
				}
			}
		}
	}
}

void Snake::update(sf::RenderWindow *window)
{
	// Detect keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		bool movable = true;
		
		for (int bodyPart = 1; bodyPart < body.size(); bodyPart++)
		{
			if (body[bodyPart].getPosition() == sf::Vector2f(body[0].getPosition().x - tileSize, body[0].getPosition().y))
			{
				movable = false;
			}
		}

		if (movable)
		{
			direction = left;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		bool movable = true;

		for (int bodyPart = 1; bodyPart < body.size(); bodyPart++)
		{
			if (body[bodyPart].getPosition() == sf::Vector2f(body[0].getPosition().x + tileSize, body[0].getPosition().y))
			{
				movable = false;
			}
		}

		if (movable)
		{
			direction = right;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		bool movable = true;

		for (int bodyPart = 1; bodyPart < body.size(); bodyPart++)
		{
			if (body[bodyPart].getPosition() == sf::Vector2f(body[0].getPosition().x, body[0].getPosition().y - tileSize))
			{
				movable = false;
			}
		}

		if (movable)
		{
			direction = up;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		bool movable = true;

		for (int bodyPart = 1; bodyPart < body.size(); bodyPart++)
		{
			if (body[bodyPart].getPosition() == sf::Vector2f(body[0].getPosition().x, body[0].getPosition().y + tileSize))
			{
				movable = false;
			}
		}

		if (movable)
		{
			direction = down;
		}
	}

	// If 200 ms has passed
	if (gameClock.getElapsedTime().asMilliseconds() >= 200)
	{
		// Move the snake
		move();

		// Restart the game clock
		gameClock.restart();
	}
}

int GetNumberInCorrectRange(int Number)
{
	while (Number > 1530)
	{
		Number -= 1530;
	}

	return Number;
}

sf::Color GetColor(int Number)
{
	if (Number >= 0 && Number <= 255)
	{
		return sf::Color(255, Number, 0);
	}
	else if (Number >= 256 && Number <= 510)
	{
		Number -= 255;

		return sf::Color(255 - Number, 255, 0);
	}
	else if (Number >= 511 && Number <= 765)
	{
		Number -= 255 * 2;

		return sf::Color(0, 255, Number);
	}
	else if (Number >= 766 && Number <= 1020)
	{
		Number -= 255 * 3;

		return sf::Color(0, 255 - Number, 255);
	}
	else if (Number >= 1021 && Number <= 1275)
	{
		Number -= 255 * 4;

		return sf::Color(Number, 0, 255);
	}
	else if (Number >= 1276 && Number <= 1530)
	{
		Number -= 255 * 5;

		return sf::Color(255, 0, 255 - Number);
	}
}
#include<iostream>
void Snake::render(sf::RenderWindow *window)
{
	// Iterate through all of the body parts
	for (int bodyPart = 0; bodyPart < body.size(); bodyPart++)
	{
		// If not head
		int Number_in_Correct_Range = GetNumberInCorrectRange(bodyPart * 50);

		// Convert to color
		body[bodyPart].setFillColor(GetColor(Number_in_Correct_Range));

		// Draw the sf::RectangleShape
		window->draw(body[bodyPart]);
	}
}