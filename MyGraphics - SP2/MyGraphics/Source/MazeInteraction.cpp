#include "MazeInteraction.h"
#include "Application.h"
#include <ctime>
#include <iostream>

//void MazeInteraction::GenerateMap(){
//	unsigned int MapRNG = rand() % 4;
//
//	srand((unsigned int)time(NULL));
//	
//
//	do{
//		MapRNG = rand() % 4;
//		//Move up
//		if (MapRNG == 0){
//			if (generatePathY-2>=1){
//				if (){
//					overallSize += 2;
//					//map stuff
//
//					generatePathY -= 2;
//					overlap = false;
//					overlapCounter = 0;
//				}
//			}
//		}
//		//Move Down
//		else if (MapRNG == 1){
//			if (generatePathY + 2 <= ){
//				if (){
//					overallSize += 2;
//					//map stuff
//
//					generatePathY += 2;
//					overlap = false;
//					overlapCounter = 0;
//				}
//			}
//		}
//
//
//		//Move Left
//		else if (MapRNG == 2){
//			if (generatePathX - 2 >= 1){
//				if (){
//					overallSize += 2;
//
//					generatePathX -= 2;
//					overlap = false;
//					overlapCounter = 0;
//				}
//			}
//		}
//		//Move Right
//		else if (MapRNG == 3){
//			if (generatePathX + 2 <= ){
//				if (){
//					overallSize += 2;
//					generatePathX += 2;
//					overlap = false;
//					overlapCounter = 0;
//				}
//			}
//		}
//
//		if (overlapCounter >= 5){
//			overlap = true;
//		}
//		overlapCounter++;
//	}
//	while (overallSize<mapSize)
//}

Maze::Maze(int numberOfCols, int numberOfRows, int screenSizeX, int screenSizeY)
{
		gridSizeY = (float)(screenSizeY*0.75) / numberOfRows;
		gridSizeX = (float)(screenSizeX*0.8) / numberOfCols;
		startingPointX = 1;
		startingPointY = 1;
		rowNumber = numberOfRows;
		colNumber = numberOfCols;


		GenerateMap();
		
}

void Maze::GenerateMap(void)
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
	//	RANDOMLY GENERATE PATHS STARTING FROM CENTER
	//
	srand((unsigned int)time(NULL));
	mapLayout[1][1] = MAP_PATH;
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
}			 

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

void Maze::Collision(){
	double mouseX, mouseY;
	Application::GetMouseMovement(mouseX, mouseY);
	int xGrid = abs(((((mouseX - startingPointX) - (gridSizeX * 0.5)) / gridSizeX) + 0.5)) / 10 + 1;
	int yGrid = abs(((((mouseY - startingPointY) - (gridSizeY * 0.5)) / gridSizeY) + 0.5)) / 10;

	std::cout << xGrid << ", " << yGrid << std::endl;

	if (mapLayout[yGrid][xGrid] != MAP_PATH){
		std::cout << " LANGAED " << std::endl;
	}
	
}