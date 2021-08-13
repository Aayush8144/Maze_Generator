#include <iostream>
#include <SFML/Graphics.hpp>

#include "Maze.h"

const float WINDOW_HEIGHT = 900;
const float WINDOW_WIDTH = 900;
const float CELL_HEIGHT = 30;
const float CELL_WIDTH = 30;
const unsigned int FPS = 60;

int main()
{
	// window object
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "mazes");

	// setting FPS to 60
	window.setFramerateLimit(FPS);

	// events object
	sf::Event events;

	// maze objects
	Maze maze(CELL_HEIGHT,CELL_WIDTH);

	// creating the grid
	maze.CreateCells(WINDOW_HEIGHT, WINDOW_WIDTH, CELL_HEIGHT, CELL_WIDTH);

	// variables 
	bool play = true;
	bool mazeCreateOn = true;
	
	// main while loop (game loop)
	while (play)
	{
		// events
		while (window.pollEvent(events))
		{
			// event for closing the window
			if (events.type == sf::Event::Closed) play = false;
		}
		// logics

		if (mazeCreateOn)
		{
			maze.CreateMaze(window);
			mazeCreateOn = false;
		}

		// render
		window.clear(); // clearing the screen

		// drawing the maze to the screen
		maze.DrawMaze(window);

		window.display(); // displaying the screen
	}

	// cleaning
	window.close();

	return 0;
}