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
	bool winScenario;
protected:
	Countdown timer;
};

class ScenarioDefend : public Scenario
{
public:
	ScenarioDefend(int health, double duration, int increment);
	virtual ~ScenarioDefend();

	virtual void Update(double dt);

private:
	int wave;
	int increment;
	int amountToSpawn;
	int HP;

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