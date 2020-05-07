/* Headers */
#include "Board.hpp"



/* Functions */
void Board::initialise(sf::RenderWindow *window)
{
	font.loadFromFile("ConcertOne-Regular.ttf");

	boardBackground.setFillColor(sf::Color::Black);
	boardBackground.setPosition(sf::Vector2f(0, 0));
	boardBackground.setSize(sf::Vector2f(boardSize * tileSize, boardSize * tileSize));

	snake.boardSize = boardSize;
	snake.tileSize = tileSize;

	food.initialise(window, tileSize);

	food.generate(&snake.body, boardSize, tileSize);

	snake.initialise(window);

	// Message box
	messageBox.setFillColor(sf::Color::Blue);
	messageBox.setSize(sf::Vector2f(boardBackground.getSize().x / 2, boardBackground.getSize().y / 4));
	messageBox.setPosition(sf::Vector2f(boardBackground.getSize().x / 2 - messageBox.getSize().x / 2, boardBackground.getSize().y / 2 - messageBox.getSize().y / 2));
	
	// Set fonts of texts
	gameOverText.setFont(font);
	gameWonText.setFont(font);
	snakeLengthText.setFont(font);
	pressEnterText.setFont(font);

	// Set strings of texts
	gameOverText.setString("GAME OVER!");
	gameWonText.setString("GAME WON!");
	pressEnterText.setString("[PRESS ENTER TO CONTINUE]");

	// Set character size of texts
	gameOverText.setCharacterSize(messageBox.getSize().y / 8);
	gameWonText.setCharacterSize(messageBox.getSize().y / 8);
	snakeLengthText.setCharacterSize(messageBox.getSize().y / 8);
	pressEnterText.setCharacterSize(messageBox.getSize().y / 8);

	// Set position of texts
	gameOverText.setOrigin(sf::Vector2f(gameOverText.getLocalBounds().left + gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().top + gameOverText.getLocalBounds().height / 2));
	gameOverText.setPosition(sf::Vector2f(messageBox.getPosition().x + messageBox.getSize().x / 2, messageBox.getPosition().y + messageBox.getSize().y / 2 - gameOverText.getCharacterSize() * 2));
	
	gameWonText.setOrigin(sf::Vector2f(gameWonText.getLocalBounds().left + gameWonText.getLocalBounds().width / 2, gameWonText.getLocalBounds().top + gameWonText.getLocalBounds().height / 2));
	gameWonText.setPosition(sf::Vector2f(messageBox.getPosition().x + messageBox.getSize().x / 2, messageBox.getPosition().y + messageBox.getSize().y / 2 - gameWonText.getCharacterSize() * 2));
	
	snakeLengthText.setPosition(sf::Vector2f(messageBox.getPosition().x + messageBox.getSize().x / 2, messageBox.getPosition().y + messageBox.getSize().y / 2));

	pressEnterText.setOrigin(sf::Vector2f(pressEnterText.getLocalBounds().left + pressEnterText.getLocalBounds().width / 2, pressEnterText.getLocalBounds().top + pressEnterText.getLocalBounds().height / 2));
	pressEnterText.setPosition(sf::Vector2f(messageBox.getPosition().x + messageBox.getSize().x / 2, messageBox.getPosition().y + messageBox.getSize().y / 2 + pressEnterText.getCharacterSize() * 2));
}

void Board::update(sf::RenderWindow *window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		snake.gameOver = false;

		// Get rid of the snake's body
		snake.body.clear();

		// Initialise the snake again
		snake.initialise(window);

		// Set the snake's direction to none
		snake.direction = snake.none;
	}

	if (snake.moreFoodNeeded)
	{
		food.generate(&snake.body, boardSize, tileSize);

		snake.moreFoodNeeded = false;
	}

	snake.foodPosition = food.food.getPosition();

	snake.update(window);
}

void Board::render(sf::RenderWindow *window)
{
	window->draw(boardBackground);

	food.render(window);

	snake.render(window);

	// Message box
	if (snake.gameOver || snake.gameWon)
	{
		window->draw(messageBox);
		
		snakeLengthText.setString("SNAKE LENGTH: " + std::to_string(snake.body.size()));
		snakeLengthText.setOrigin(sf::Vector2f(snakeLengthText.getLocalBounds().left + snakeLengthText.getLocalBounds().width / 2, snakeLengthText.getLocalBounds().top + snakeLengthText.getLocalBounds().height / 2));

		window->draw(snakeLengthText);
		
		window->draw(pressEnterText);

		if (snake.gameOver)
		{
			window->draw(gameOverText);
		}
		else if (snake.gameWon)
		{
			window->draw(gameWonText);
		}
	}
}