#pragma once

#include "Cell.h"
#include <vector> // for storing the cells list
#include <iostream>
#include <stack> // for backtracking
#include <cstdlib> // for rand
#include <time.h> // initializing random seed
#include <SFML/Graphics.hpp> // for sfml


class Maze
{
private:
	std::vector<Cell*> cells;
	float cellHeight;
	float cellWidth;
	
	// ==================== cells color ======================
	const sf::Color notVisited = sf::Color(97, 204, 97, 255); // green
	const sf::Color inStack = sf::Color(233, 42, 42, 255); // red
	const sf::Color visited = sf::Color(0, 211, 250, 255); //blue
public:

	// constructor
	Maze(float cellHeight, float cellWidth);

	// destructor
	~Maze();

	/*
		CreateCells creats a maze grid of spicified cell width and height
		@param const float WINDOW_HEIGHT: height of the window
		@param const float WINDOW_WIDTH : width of the window
		@param const float CELL_HEIGHT  : height of the cell
		@param const float CELL_WIDTH   : width of the window
	*/
	void CreateCells(const float WINDOW_HEIGHT, const float WINDOW_WIDTH, const float CELL_HEIGHT, const float CELL_WIDTH);

	/*
		DrawMaze draws the maze to the screen
		@param sf::RenderWindow& window : reference to the the render window
	*/
	void DrawMaze(sf::RenderWindow& window);

	/*
		CreateMaze creats maze by using backtracking and stack
	*/
	void CreateMaze(sf::RenderWindow& window);

	//===================================== helperFunctions ======================================
	/*
		ValidCell helper function check if a passed cell is valid to move to or not 
		assums that the pointer ponts to a cell
		@param Cell* cellToCheck: pointer to cell which is to be check
		@return bool: true if the cell is not visited, false if the cell is in stack or is already visited
	*/
	bool ValidCell(Cell* cellToCheck);

	/*
		GetValidNeighborList helps to determine if the currcell has any valid neighbor or not
		@param Cell* currCell: pointer to cell whose neighbor is to be checked
		@return vector<int> : returns a vector list of all the valid cell and their position in the orginal list
	*/
	std::vector<int> GetValidNeighborList(Cell* currCell);

	/*
		WhichNeighbor helps to determine which direction is nextcellIndex relative to currCellIndex
		is a constant helperfunction
		@param const int currCellIndex: CellIndex of the currCell in the orginal list
		@param const int nextCellIndex: CellIndex of the nextCell in the orginal list
		@return int value -> 0,1,2,3 which respectively are east, west, north, and south
	*/
	const int WhichNeighbor(const int currCellIndex, const int nextCellIndex);

	/*
		Deletes Border of a cell according to the direction
		int value -> 0,1,2,3 which respectively are east, west, north, and south
		@param Cell* currCell: pointer to cell whose border is to be deleted
		@param const int direction: direction of border to delete
	*/
	void DeleteBorder(Cell*  currCell, const int direction);

	// ====================================== debugger ====================================
	/*
		prints neighbor
	*/
	void PrintNeighbor();

	/*
		prints all the valid neighbor
	*/
	void PrintAllValidNeighbor();

	/*
	prints all the valid neighbor
	*/
	void PrintValidNeighbor(Cell* currCell);
};

