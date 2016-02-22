#ifndef MAZEINTERACTION_H
#define MAZEINTERACTION_H


#include <stdlib.h>

#include <vector>

using std::vector;

class Maze{


public:
	enum MAP_STUFF
	{
		MAP_BLOCK,
		MAP_PATH
	};
	Maze(){}
	Maze(int numberOfCols, int numberOfRows, int screenSizeX, int screenSizeY);
	~Maze(){}
	
	void PrintMap();
	void GenerateMap();
	void Collision();
	
	float gridSizeX;
	float gridSizeY;
	int rowNumber;
	int colNumber;
	int startingPointX;
	int startingPointY;

	int mapLayout[10][10];
private:

	int generatePathX;
	int generatePathY;
	int overallSize;
	unsigned int MapRNG = rand() % 4;
	bool overlap = false;
	int overlapCounter;
};



#endif