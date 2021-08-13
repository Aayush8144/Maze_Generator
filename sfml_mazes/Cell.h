#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Cell
{
private:
	// ========================= Variable ===================
	float cellHeight;
	float cellWidth;
	sf::Color cellColor;

	// variable to store x and y position
	int xIndex; // stores factor for x-aixs (i in for loop) is used in x position 
	int yIndex; // stores factor for y-aixs (j in for loop) is used in y position

	// variable to store currCell index in the list
	int currCellIndex;

	// variable to store if the borders should be drawn or not
	// default to true
	bool northBorderDraw = true;
	bool eastBorderDraw = true;
	bool westBorderDraw = true;
	bool southBorderDraw = true;

	// vector to store the cells neighbor position in the list
	// Maze Class stores all the cell in a long 
	int eastNeighbor;
	int westNeighbor;
	int northNeighbor;
	int southNeighbor;


	// ========================== objects =====================
	// main cell object
	sf::RectangleShape cell;

	// boder objects
	sf::RectangleShape borderTop;
	sf::RectangleShape borderRight;
	sf::RectangleShape borderLeft;
	sf::RectangleShape borderBottom;

	// ====================== helper private function ===========
	/*
	* InitializeHelperFunction initialized all the object needed for the class
	* @param float windowHeight : height of the window
	* @param float windowWidth : width of the window
	*/
	void InitializeHelperFunciton(const float WINDOW_HEIGHT = 0, const float WINDOW_WIDTH = 0);

public:

	// default constructor
	Cell();

	/* constructor has default origin
	* @param float windowHeight: height of the window
	* @param float windowWidth: width of the window
	* @param float cellHeight: height of the cell
	* @param float cellWidth: width of the cell
	* @param sf::color cellCOlor: bg color of the cell, default to white
	* @param int xIndex: x-positon of the cell; default 0
	* @param int yIndex: y-positon of the cell; default 0
	*/
	Cell(float windowHeight, float windowWidth, float cellHeight, float cellWidth,
		sf::Color cellColor = sf::Color::White, int xIndex = 0, int yIndex = 0);

	// destructor
	~Cell();

	// copy constructor
	// @param const Cell& otherCell: memory address of Cell to be copied 
	Cell(const Cell& otherCell);

	// assignment constructor
	// @param const Cell& otherCell: memory address of Cell to be copied 
	// @returns ponter to self
	Cell& operator = (const Cell& otherCell);

	//==================== setters function ======================

	/* color setter funciton
	* @param sf::Color cellColor: color of the cell
	*/
	void SetColor(sf::Color cellColor);

	/* SetEastBorderDraw setter funciton
	* @param bool eastBorderPresent: contains the eastBorderDraw value
	*/
	void SetEastBorderDraw(bool eastBorderPresent) { eastBorderDraw = eastBorderPresent; }
	
	/* SetWestBorderDraw setter funciton
	* @param bool borderLeftPresent: contains the westBorderDraw value
	*/
	void SetWestBorderDraw(bool westBorderPresent) { westBorderDraw = westBorderPresent; }

	/* SetNorthBorderDraw setter funciton
	* @param bool northBorderPresent: contains the northBorderDraw value
	*/
	void SetNorthBorderDraw(bool northBorderPresent) { northBorderDraw = northBorderPresent; }

	/* SetSouthtBorderDraw setter funciton
	* @param bool southBorderPresent: contains the southBorderDraw value
	*/
	void SetSouthBorderDraw(bool southBorderPresent) { southBorderDraw = southBorderPresent; }

	//==================== getter function =======================

	/* cell height getter function
	* It is a constant function
	* @return cellHeight: returns height of the cell
	*/
	const float GetCellHeight() { return cellHeight; }

	/* cell width getter funciton
	* It is a constant function
	* @return cellWidth: returns width of the cell
	*/
	const float GetCellWidth() { return cellWidth; }

	/* xIndex getter function
	* It is a constant function
	* @return xIndex: returns yindex of the cell which affects the y position of the cell on the screen
	*/
	const int GetXIndex() { return xIndex; }

	/* yIndex getter function
	* It is a constant function
	* @return yIndex: returns yindex of the cell which is the x position of the cell on the screen
	*/
	const int GetYIndex() { return yIndex; }

	/* 
		helper Getter Function to get the index of the cell in the list
		It is a constant function
		@return currCellIndex: returns the index of the cell in the maze's cell list
	*/
	const int GetCellListIndex() { return currCellIndex; }

	/* color getter funciton
	* @return sf::Color cellColor: color of the cell
	*/
	sf::Color GetColor() { return cellColor; }

	// ============================= neighbor getter function ===========
	/* getter function to get cell north neighbor position in the list
	* It is a constant function
	* @return northNeighbor: returns north neighbor position in the list of the cell
	*/
	const int GetNorthNeighbor() { return northNeighbor; }

	/* getter function to get cell south neighbor position in the list
	* It is a constant function
	* @return southNeighbor: returns south neighbor position in the list of the cell
	*/
	const int GetSouthNeighbor() { return southNeighbor; }

	/* getter function to get cell west neighbor position in the list
	* It is a constant function
	* @return westNeighbor: returns west neighbor position in the list of the cell
	*/
	const int GetWestNeighbor() { return westNeighbor; }

	/* getter function to get cell east neighbor position in the list
	* It is a constant function
	* @return eastneighbor: returns east neighbor position in the list of the cell
	*/
	const int GetEastNeighbor() { return eastNeighbor; }


	// draws cell to the screen
	void Draw(sf::RenderWindow& window);
};

