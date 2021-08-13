#include "Maze.h"

Maze::Maze(float cellHeight, float cellWidth)
{
	this->cellHeight = cellHeight;
	this->cellWidth = cellWidth;
}

Maze::~Maze()
{
}

void Maze::CreateCells(const float WINDOW_HEIGHT, const float WINDOW_WIDTH, const float CELL_HEIGHT, const float CELL_WIDTH)
{
	Cell* tempCell = NULL;

	for (int yIndex = 0; yIndex < WINDOW_HEIGHT / CELL_HEIGHT; ++yIndex)
	{
		for (int xIndex = 0; xIndex < WINDOW_WIDTH / CELL_WIDTH; ++xIndex)
		{
			tempCell = new Cell(WINDOW_HEIGHT, WINDOW_WIDTH, CELL_HEIGHT, CELL_WIDTH, notVisited, xIndex, yIndex);

			// adding the tempCell to the vector list
			cells.push_back(tempCell);
		}
	}
}

void Maze::DrawMaze(sf::RenderWindow& window)
{
	// drawing the cells to the screen
	for (int i = 0; i < cells.size(); i++)
	{
		cells.at(i)->Draw(window);
	}
}

void Maze::CreateMaze(sf::RenderWindow& window)
{
	// initializing random seed
	srand(time(0));
	
	// ========================= Variables =========================
	Cell* currCell = cells.at(0);// curr cell pointer, starts at the 0,0 coordinate
	int visitedCellNum = 0;  // to count the total number of visited cell
	std::stack<int> cellBackrackStack; // stack to backtrack

	// loop to create the maze
	// runs until all the cells are visited
	while (visitedCellNum < cells.size())
	{
		// incereasing the visited cell count 
		++visitedCellNum;

		// adding currCell to stack for backtrack
		cellBackrackStack.push(currCell->GetCellListIndex());
		
		// setting the color of the visited cell
		currCell->SetColor(inStack);

		// find next cell
		// runs until break or stack is empty
		while (!cellBackrackStack.empty())
		{
			// getting all the valid neighbour list
			std::vector<int> validNeighborList = GetValidNeighborList(currCell);

			if (validNeighborList.size() != 0)
			{
				// chosing a neighbor of the currCell
				// choosing a random index from the validNeighborList
				const int nextCellIndex = rand() % validNeighborList.size();

				int currCellActualIndex = currCell->GetCellListIndex();
				int nextCellActualIndex = validNeighborList.at(nextCellIndex);
				
				// ============================= for currCell ============================
				// detecting the border to delete for currcell
				int currToNextCellDirection = WhichNeighbor(currCellActualIndex, nextCellActualIndex);

				// deleting the border for currCell
				DeleteBorder(currCell, currToNextCellDirection);
				
				// ============================= for currCell ============================

				// detecting the border to delete for nextCell
				int nextToCurrCellDirection = WhichNeighbor(nextCellActualIndex, currCellActualIndex);

				// deleting the border for currCell
				DeleteBorder(cells.at(nextCellActualIndex), nextToCurrCellDirection);

				// updating currCell
				currCell = cells.at(nextCellActualIndex);
				
				break; // getting out of the loop
			}
			else 
			{
				// need to backtrack as there are no valid neighbour
				currCell->SetColor(visited); // updating the cell color
				cellBackrackStack.pop();	// removing the cell from the stack
				if (!cellBackrackStack.empty())
				{
					currCell = cells.at(cellBackrackStack.top()); // updating curr cell to top of the stack
				}
			}
		}
		// render
		window.clear(); // clearing the screen
		
		// drawing the maze to the screen
		DrawMaze(window);

		window.display(); // displaying the screen
	}

}

bool Maze::ValidCell(Cell* cellToCheck)
{
	// checking if cellToCheck is valid or not 
	// that is if it is green color
	if (cellToCheck->GetColor() == notVisited)
		return true;
	return false;
}

std::vector<int> Maze::GetValidNeighborList(Cell* currCell)
{
	// ================================ concept ========================================
	/* 
		concept for checking if the neighbor is valid or not 
		checking if the neighbor saved position in the orginal cell list is -1, it is invalid
		and 
		then checking if the neighbor's cell color is gray ,i.e. not visited
		then adding to the allValidNeighbor list
	*/
	
	// =============================== variables ======================================
	std::vector<int> allValidNeighbor; // vector to store all the valid neighbor

	// ================= checking neighbor in each direction=========================
	// checking north neighbor
	if (currCell->GetNorthNeighbor() != -1)
	{
		// neighbor is in the orginal cell list
		//Now checking if the north neighbor
		if (ValidCell(cells.at(currCell->GetNorthNeighbor())))
			allValidNeighbor.push_back(currCell->GetNorthNeighbor());
	}

	// checking south neighbor
	if (currCell->GetSouthNeighbor() != -1)
	{
		// neighbor is in the orginal cell list
		if (ValidCell(cells.at(currCell->GetSouthNeighbor())))
			allValidNeighbor.push_back(currCell->GetSouthNeighbor());
	}

	// checking East neighbor
	if (currCell->GetEastNeighbor() != -1)
	{
		// neighbor is in the orginal cell list
		if (ValidCell(cells.at(currCell->GetEastNeighbor())))
			allValidNeighbor.push_back(currCell->GetEastNeighbor());
	}

	// checking West neighbor
	if (currCell->GetWestNeighbor() != -1)
	{
		// neighbor is in the orginal cell list
		if (ValidCell(cells.at(currCell->GetWestNeighbor())))
			allValidNeighbor.push_back(currCell->GetWestNeighbor());
	}

	return allValidNeighbor;
}

const int Maze::WhichNeighbor(const int currCellIndex, const int nextCellIndex)
{
	// ================================ concept ==========================
	/*
		 when nextCellIndex - currCellIndex
		east neighbor index is right after currCell in the list -> so difference is 1
		west neighbor index is right before currCell in the list -> so difference is -1 
		north neighbor index is way before currCell in the list -> so difference is less than -1 i.e -5
		south neighbor index is way before currCell in the list -> so difference is more than 1

		return int value -> 0,1,2,3 which respectively are east, west, north, and south
	*/
	const int nextCellDirection = nextCellIndex - currCellIndex;

	if (nextCellDirection == 1)
	{
		return 0; // east
	}
	else if (nextCellDirection == -1)
	{
		return 1; // west
	}
	else if (nextCellDirection < -1)
	{
		return 2; // north
	}
	else if (nextCellDirection > 1)
	{
		return 3; // south
	}
	else
	{
		std::cout << "ERROR! in " << currCellIndex <<" while detecting which border" << std::endl;
		return -1; // error
	}
}

void Maze::DeleteBorder(Cell* currCell, const int direction)
{
	// direction value 0, 1, 2, 3  respectively represent are east, west, north, and south
	switch (direction)
	{
	case 0:
		currCell->SetEastBorderDraw(false);
		break;
	case 1:
		currCell->SetWestBorderDraw(false);
		break;
	case 2:
		currCell->SetNorthBorderDraw(false);
		break;
	case 3:
		currCell->SetSouthBorderDraw(false);
		break;
	default:
		std::cout << "ERROR! while deleteing border of cell at index " << currCell->GetCellListIndex() << " towards "
			<< direction << " direction" << std::endl;
		break;
	}
}

void Maze::PrintNeighbor()
{
	// printing
	for (int i = 0; i < cells.size(); i++)
	{
		// printing the coordinate of current cell
		std::cout << cells.at(i)->GetXIndex() << "," << cells.at(i)->GetYIndex() <<
			"-------> whose actual index in the list is : " << cells.at(i)->GetCellListIndex()
			<< std::endl;

		// printing the index in the list of  each neighbor
		std::cout << "east: " << cells.at(i)->GetEastNeighbor() << std::endl;
		std::cout << "west: " << cells.at(i)->GetWestNeighbor() << std::endl;
		std::cout << "north: " << cells.at(i)->GetNorthNeighbor() << std::endl;
		std::cout << "south: " << cells.at(i)->GetSouthNeighbor() << std::endl << std::endl;
	}
}

void Maze::PrintAllValidNeighbor()
{
	// printing all valid neighbor
	for (int i = 0; i < cells.size(); i++)
	{
		// printing all valid neighbor for element at i
		PrintValidNeighbor(cells.at(i));
	}
}

void Maze::PrintValidNeighbor(Cell* currCell)
{
	// variable to save all valid neighbor
	std::vector<int> allValidNeighbor;

	// getting the valid neighbor 
	allValidNeighbor = GetValidNeighborList(currCell);

	// printing all the valid neighbour
	// printing the coordinate of current cell
	std::cout << currCell->GetXIndex() << "," << currCell->GetYIndex() << std::endl;

	// printing the index in the list of  each valid neighbor
	// doesnot account for which index represent which direction
	std::cout << "valid neighbor list: ";
	for (int j = 0; j < allValidNeighbor.size(); j++)
	{
		std::cout << allValidNeighbor.at(j) << " ";
	}
	std::cout << std::endl;
}
