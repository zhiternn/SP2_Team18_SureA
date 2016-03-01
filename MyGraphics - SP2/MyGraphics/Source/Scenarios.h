#ifndef SCENARIOS_H
#define SCENARIOS_H

#include "Countdown.h"

class ScenarioDefend
{
public:
	ScenarioDefend(int health, double duration, int increment);
	virtual ~ScenarioDefend();

	virtual void Update(double dt);
	int HP;

	bool stopScenario;
	bool winScenario;
private:
	int wave;
	int increment;
	int amountToSpawn;

	Countdown timer;

	void SpawnEnemies();
	void MoveEnemies();
};

//class ScenarioEvacuate : public Scenario
//{
//public:
//	ScenarioEvacuate(double duration);
//	virtual ~ScenarioEvacuate();
//
//	virtual void Update(double dt);
//
//private:
//};

//class ScenarioInfiltrate : public Scenario
//{
//public:
//	virtual void Update(double dt);
//private:
//};

#endif