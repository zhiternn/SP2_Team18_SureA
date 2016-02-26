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
		MAP_PATH,
		MAP_START,
		MAP_END
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
	float startingPointX;
	float startingPointY;
	bool mazeSuccess;

	int mapLayout[16][16];
private:

	int generatePathX;
	int generatePathY;
	int overallSize;
	unsigned int MapRNG = rand() % 4;
	bool overlap = false;
	int overlapCounter;
};



#endif