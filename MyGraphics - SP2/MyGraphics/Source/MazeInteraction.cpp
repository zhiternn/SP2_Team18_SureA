/******************************************************************************/
/*!
\file	MazeInteraction.cpp
\author Quek Cher Yi	
\par	email: 155124D@mymail.nyp.edu.sg
\brief
Class to define maze interactions
*/
/******************************************************************************/


#include "MazeInteraction.h"
#include "Application.h"
#include <ctime>
#include <iostream>

/******************************************************************************/
/*!
\brief	Maze constructor

\param	numberOfCols
	int for number of columns
\param	numberOfRows
	int for number of rows
\param	screenSizeX
	int for the x coords for screen
\param screenSizeY
	int for the y coords for screen
*/
/******************************************************************************/

Maze::Maze(int numberOfCols, int numberOfRows, int screenSizeX, int screenSizeY)
{
	gridSizeY = (float)(screenSizeY*1.f) / numberOfRows;   		//GridSize for each quad
	gridSizeX = (float)(screenSizeX*0.75f) / numberOfCols;		//GridSize for each quad
	startingPointX = (float)screenSizeX / 2.f;
	startingPointY = (float)screenSizeY / 2.f;
		
	rowNumber = numberOfRows;
	colNumber = numberOfCols;

	GenerateMap();
}

/******************************************************************************/
/*!
\brief	Generates the maze
*/
/******************************************************************************/

void Maze::GenerateMap()
{
	int iGeneratePathX = 1; // STARTING POINT
	int iGeneratePathY = 1; // STARTING POINT 
	int igCounter = 0;
	unsigned int irng = rand() % 4;
	bool overLap = false;
	int breakCounter = 0;

	//	clears the map
	for (size_t y = 0; y < colNumber; ++y){
		for (size_t x = 0; x < rowNumber; ++x){
			mapLayout[y][x] = MAP_BLOCK;
		}
	}

	//
	//	Randomly generates path
	//
	srand((unsigned int)time(NULL));
	do{
		irng = rand() % 4;
		//UP
		if (irng == 0){
			if (iGeneratePathY - 2 >= 1){
				if (mapLayout[iGeneratePathY - 2][iGeneratePathX] != MAP_PATH || overLap){
					igCounter += 2;
					mapLayout[iGeneratePathY - 1][iGeneratePathX] = MAP_PATH;
					mapLayout[iGeneratePathY - 2][iGeneratePathX] = MAP_PATH;
					iGeneratePathY -= 2;
					overLap = false;
					breakCounter = 0;
				}
			}
		}
		//DOWN
		else if (irng == 1){
			if (iGeneratePathY + 2 <= colNumber - 2){
				if (mapLayout[iGeneratePathY + 2][iGeneratePathX] != MAP_PATH || overLap){
					igCounter += 2;
					mapLayout[iGeneratePathY + 1][iGeneratePathX] = MAP_PATH;
					mapLayout[iGeneratePathY + 2][iGeneratePathX] = MAP_PATH;
					iGeneratePathY += 2;
					overLap = false;
					breakCounter = 0;
				}
			}
		}
		//LEFT
		else if (irng == 2){
			if (iGeneratePathX - 2 >= 1){
				if (mapLayout[iGeneratePathY][iGeneratePathX - 2] != MAP_PATH || overLap){
					igCounter += 2;
					mapLayout[iGeneratePathY][iGeneratePathX - 1] = MAP_PATH;
					mapLayout[iGeneratePathY][iGeneratePathX - 2] = MAP_PATH;
					iGeneratePathX -= 2;
					overLap = false;
					breakCounter = 0;
				}
			}
		}
		//RIGHT
		else if (irng == 3){
			if (iGeneratePathX + 2 <= rowNumber - 2){
				if (mapLayout[iGeneratePathY][iGeneratePathX + 2] != MAP_PATH || overLap){
					igCounter += 2;
					mapLayout[iGeneratePathY][iGeneratePathX + 1] = MAP_PATH;
					mapLayout[iGeneratePathY][iGeneratePathX + 2] = MAP_PATH;
					iGeneratePathX += 2;
					overLap = false;
					breakCounter = 0;
				}
			}
		}
		if (breakCounter >= 5){
			overLap = true;
		}
		breakCounter++;
	} while (mapLayout[colNumber - 3][rowNumber - 3] != MAP_PATH);// makes sure the map is filled up at least >= to the percentage inputed

	mapLayout[1][1] = MAP_START;							//Set starting position in array
	mapLayout[colNumber - 3][rowNumber - 3] = MAP_END;		//Set ending position in array

}			 

/******************************************************************************/
/*!
\brief 	Prints the map
	Nested loop to print map, prints according to whether its a map_block
*/
/******************************************************************************/
void Maze::PrintMap(){
	for (size_t y = 0; y<colNumber; ++y){
		for (size_t x = 0; x<rowNumber; ++x){
			if (mapLayout[y][x] == MAP_BLOCK){
				std::cout << (char)219;
			}
			else{
				std::cout << " ";
			}

		}
		std::cout << std::endl;
	}
}

/******************************************************************************/
/*!
\brief	Checks for collision && check if player completes the maze
		Uses perecentage of screensize to find where the mouse is compared to a single rendered quad


*/
/******************************************************************************/
void Maze::Collision(){
	double mouseX, mouseY;
	Application::GetMouseMovement(mouseX, mouseY);

	std::cout << startingPointX << "     Y        " << startingPointY << std::endl;

	int xGrid = abs(((((mouseX - startingPointX) - (gridSizeX * 0.5)) / gridSizeX) + 0.5));
	int yGrid = abs(((((mouseY - startingPointY) - (gridSizeY * 0.5)) / gridSizeY) + 0.5));

	if (mapLayout[yGrid][xGrid] == MAP_BLOCK){
		Application::SetMousePosition(gridSizeX + gridSizeX/2, gridSizeY + gridSizeY/2);
	}

	if (yGrid == colNumber - 3 && xGrid == rowNumber - 3){
		mazeSuccess = true;
	}
	
}

