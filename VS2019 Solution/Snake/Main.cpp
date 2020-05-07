/* Headers */
#include "Board.hpp"

#include "SFML/Graphics.hpp"

/* Global Variables */
Board board;

/* Functions */

// Center the view and implement the letterbox view
void adjustView(sf::RenderWindow *window)
{
	// Get the view of the window
	sf::View adjustedView = window->getView();

	// Set the center of the view at the center of the board
	adjustedView.setCenter(sf::Vector2f(board.boardBackground.getSize().x / 2, board.boardBackground.getSize().y / 2));

	// Set the size of the view to the size of the board
	adjustedView.setSize(sf::Vector2f(board.boardBackground.getSize().x, board.boardBackground.getSize().y));

	// Calculate the aspect ratio of the window and the view 
	float windowAspectRatio = (float) window->getSize().x / window->getSize().y;
	float viewAspectRatio = (float) adjustedView.getSize().x / adjustedView.getSize().y;

	// If the letterboxing is horizontal
	if (windowAspectRatio > viewAspectRatio)
	{
		// Calculate the ratio of the aspect ratio of the view to the aspect ratio of the window
		float masterRatio = viewAspectRatio / windowAspectRatio;

		// Adjust the viewport position and size to account for the difference in the aspect ratio of the view and window
		adjustedView.setViewport(sf::FloatRect((1 - masterRatio) / 2, 0, masterRatio, 1));
	}
	// If the letterboxing is vertical (or there is none at all)
	else
	{
		// Calculate the ratio of the aspect ratio of the window to the aspect ratio of the view
		float masterRatio = windowAspectRatio / viewAspectRatio; // If there is no letterboxing this will equal 1

		// Adjust the viewport position and size to account for the difference in the aspect ratio of the view and window
		adjustedView.setViewport(sf::FloatRect(0, (1 - masterRatio) / 2, 1, masterRatio));
	}

	// Set our new adjusted view as the window's view
	window->setView(adjustedView);
}

// Set object default properties
void initialise(sf::RenderWindow *window)
{
	board.initialise(window);

	adjustView(window);
}

// Respond to window events
void handleEvents(sf::RenderWindow *window)
{
	sf::Event event;

	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
		else if (event.type == sf::Event::Resized)
		{
			adjustView(window);
		}
	}
}

// Update objects every iteration of the game loop
void update(sf::RenderWindow *window)
{
	board.update(window);
}

// Clear the screen, draw objects, and display the screen
void render(sf::RenderWindow *window)
{
	window->clear(sf::Color(60, 60, 60));

	board.render(window);

	window->display();
}

// Program entry point
int main()
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");

	// Initialise all objects
	initialise(&window);

	// Game loop
	while (window.isOpen())
	{
		// Respond to window events
		handleEvents(&window);

		// Update all objects
		update(&window);

		// Draw all objects on screen
		render(&window);
	}

	return 0;
}