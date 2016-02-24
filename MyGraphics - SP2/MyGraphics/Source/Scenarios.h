#ifndef SCENARIOS_H
#define SCENARIOS_H

#include "Countdown.h"

class Scenario
{
public:
	Scenario(double duration);
	virtual ~Scenario();

	virtual void Update(double dt) = 0;

	bool stopScenario;
protected:
	Countdown timer;
};

class ScenarioDefend : public Scenario
{
public:
	ScenarioDefend(int increment, double duration);
	virtual ~ScenarioDefend();

	virtual void Update(double dt);

private:
	int wave;
	int increment;
	int amountToSpawn;

	void SpawnEnemies();
	void MoveEnemies();
};

//class ScenarioEvacuate : public Scenario
//{
//public:
//	virtual void Update(double dt);
//private:
//};
//
//class ScenarioInfiltrate : public Scenario
//{
//public:
//	virtual void Update(double dt);
//private:
//};

#endif