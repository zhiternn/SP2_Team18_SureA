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

	Maze(int limitX = 31, int limitY = 30)
	{
		sizeX = limitX;
		sizeY = limitY;
	}

	~Maze(){}
	
	void PrintMap();
	void GenerateMap();
	
	int sizeX;
	int sizeY;

	int mapLayout[30][31];
private:

	int generatePathX;
	int generatePathY;
	int overallSize;
	unsigned int MapRNG = rand() % 4;
	bool overlap = false;
	int overlapCounter;
};



#endif