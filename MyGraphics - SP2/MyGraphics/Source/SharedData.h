#include <vector>

using std::vector;

#ifndef SHAREDDATA_H
#define SHAREDDATA_H

class SharedData
{
public:
	enum GAME_STATE
	{
		G_MENU,
		G_GAME,
		G_EXIT,

		G_TOTAL
	};
	GAME_STATE gameState;
	bool stateChange;

	double m_X;
	double m_Y;
	double m_newX;
	double m_newY;

	static SharedData* GetInstance()
	{
		static SharedData data;
		return &data;
	}

private:
	SharedData() {

		gameState = G_MENU;
		stateChange = false;

		m_X = 400;
		m_Y = 300;
		m_newX = 400;
		m_newY = 300;
	}
	~SharedData() {

	}

};
#endif