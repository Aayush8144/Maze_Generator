#include "Cell.h"


void Cell::InitializeHelperFunciton(const float WINDOW_HEIGHT, const float WINDOW_WIDTH)
{
	// initializing the cell
	this->cell.setSize(sf::Vector2f(cellWidth, cellHeight)); // setting the size of the cell
	this->cell.setFillColor(cellColor); // setting color
	this->cell.setPosition(xIndex * cellHeight, yIndex * cellWidth); // setting positon

	//=============== initializing the borders ====================

	// setting the size of the border which is 50th of the cell
	float borderThickness = 50;

	// border top
	this->borderTop.setSize(sf::Vector2f(cellWidth, cellHeight / borderThickness)); // setting the size of the border
	this->borderTop.setFillColor(sf::Color(90, 97, 102)); // setting color to grey
	this->borderTop.setPosition(xIndex * cellHeight, yIndex * cellWidth); // setting positon

	// border left
	this->borderLeft.setSize(sf::Vector2f(cellWidth / borderThickness, cellHeight)); // setting the size of the border
	this->borderLeft.setFillColor(sf::Color(90, 97, 102)); // setting color to grey
	this->borderLeft.setPosition(xIndex * cellHeight, yIndex * cellWidth); // setting positon

	// border right
	this->borderRight.setSize(sf::Vector2f(cellWidth / borderThickness, cellHeight)); // setting the size of the border
	this->borderRight.setFillColor(sf::Color(90, 97, 102)); // setting color to grey
	this->borderRight.setPosition(((xIndex + 1) * cellWidth) - borderRight.getSize().x, yIndex * cellHeight); // setting positon

																											  // border right
	this->borderBottom.setSize(sf::Vector2f(cellWidth, cellHeight / borderThickness)); // setting the size of the border
	this->borderBottom.setFillColor(sf::Color(90, 97, 102)); // setting color to grey
	this->borderBottom.setPosition(xIndex * cellHeight, ((yIndex + 1) * cellWidth) - borderTop.getSize().y); // setting positon

	// ============================= neighbors ================================
	// varialbe containing the total number of cells
	int xTotalIndex = WINDOW_WIDTH / cellWidth;
	int yTotalIndex = WINDOW_HEIGHT / cellHeight;

	// variable to store currCell index in the list
	this->currCellIndex = (yIndex * xTotalIndex) + xIndex;

	// east neighbor 
	// east neighbor is to the right of the currCell 
	// currCell position + 1
	if (xIndex != xTotalIndex - 1)
		eastNeighbor = currCellIndex + 1; 
	else
		eastNeighbor = -1; // does not exist

	// west neighbor
	// west neighbor is to the left of the currCell 
	// currCell position + 1
	if (xIndex != 0)
		westNeighbor = currCellIndex - 1;

	else
		westNeighbor = -1; // does not exist

	// north neighbor
	// north neighbor is above of the currCell 
	// currCell position  - xTotalIndex
	if (yIndex != 0)
		northNeighbor = currCellIndex - xTotalIndex;

	else
		northNeighbor = -1; // does not exist

	// south neighbor
	// south neighbor is below of the currCell 
	// currCell position  + xTotalIndex
	if (yIndex != yTotalIndex - 1)
		southNeighbor = currCellIndex + xTotalIndex;

	else
		southNeighbor = -1; // does not exist

}

Cell::Cell()
{
	// initializing the private data variable
	this->cellHeight = 0;
	this->cellWidth = 0;
	this->cellColor = sf::Color::White;
	this->xIndex = 0;
	this->yIndex = 0;
	
	// curcurrCellIndex is inialized by the initialize helper function
	// initiaizing the class
	InitializeHelperFunciton();
	
}

Cell::Cell(float windowHeight, float windowWidth, float cellHeight, float cellWidth, sf::Color cellColor, int xIndex, int yIndex)
{

	// initializing the private data variable
	this->cellHeight = cellHeight;
	this->cellWidth = cellWidth;
	this->cellColor = cellColor; // initially set to notVisited (from maze class)
	this->xIndex = xIndex;
	this->yIndex = yIndex;

	// initiaizing the clss
	InitializeHelperFunciton(windowHeight, windowWidth);
}

Cell::~Cell()
{
}

Cell::Cell(const Cell& otherCell)
{

	// coping the private data variable
	this->cellHeight = otherCell.cellHeight;
	this->cellWidth = otherCell.cellWidth;
	this->cellColor = otherCell.cellColor;
	this->xIndex = otherCell.xIndex;
	this->yIndex = otherCell.yIndex;

	// curcurrCellIndex is inialized by the initialize helper function
	// initiaizing the clss
	InitializeHelperFunciton();
}

Cell& Cell::operator=(const Cell& otherCell)
{
	// copying the private data variable
	this->cellHeight = otherCell.cellHeight;
	this->cellWidth = otherCell.cellWidth;
	this->cellColor = otherCell.cellColor;
	this->xIndex = otherCell.xIndex;
	this->yIndex = otherCell.yIndex;

	// curcurrCellIndex is inialized by the initialize helper function
	// initiaizing the class
	InitializeHelperFunciton();

	return *this;
}

void Cell::SetColor(sf::Color cellColor)
{ 
	this->cellColor = cellColor;
	cell.setFillColor(cellColor);
}

void Cell::Draw(sf::RenderWindow& window)
{
	window.draw(cell);

	//===================== rendering borders ==================

	// checking if border are present or not
	if (northBorderDraw)
	{
	window.draw(borderTop);
	}
	if (westBorderDraw)
	{
		window.draw(borderLeft);
	}
	if (eastBorderDraw)
	{
		window.draw(borderRight);
	}
	if (southBorderDraw)
	{
		window.draw(borderBottom);
	}
}
