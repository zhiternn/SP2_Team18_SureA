#include "Scenarios.h"
#include "Enemy.h"

Scenario::Scenario(double duration)
{
	timer.StartCountdown(duration);
	stopScenario = false;
}

Scenario::~Scenario()
{
}

//============================================================================================
//SCENARIO DEFEND
//============================================================================================

ScenarioDefend::ScenarioDefend(int increment, double duration) :
Scenario(duration)
{
	this->increment = increment;
	amountToSpawn = increment;
	wave = 1;

	SpawnEnemies();
	MoveEnemies();
}

ScenarioDefend::~ScenarioDefend()
{
	for (vector<Enemy*>::iterator it = Enemy::enemyList.begin(); it != Enemy::enemyList.end();){
		it = Enemy::enemyList.erase(it);
	}
}

void ScenarioDefend::Update(double dt)
{
	if (timer.GetTimeLeft() > 0){
		if (Enemy::enemyList.size() <= 0){
			wave++;
			amountToSpawn += increment;

			SpawnEnemies();
			MoveEnemies();
		}
	}
	else{
		stopScenario = true;
	}
}

void ScenarioDefend::SpawnEnemies()
{
	for (size_t i = 0; i < amountToSpawn; ++i){
		//enemies to spawn between
		//X: -45 - 45
		//Y: 20 - 20
		//Z: -25 - -45
		//random speed between 1.f - 4.f
		new Enemy(
			Vector3( // position
			rand() % 91 - 45, // x pos
			20,				// y pos
			rand() % 21 - 45	// z pos
			),
			Vector3( // direction
			0, 0, 1
			),
			(float)(rand() % 40 + 10) / 10.f // speed
			);
	}
}


void ScenarioDefend::MoveEnemies()
{
	for (vector<Enemy*>::iterator it = Enemy::enemyList.begin(); it != Enemy::enemyList.end(); ++it){
		(*it)->GoTo(Vector3(0, 0, 0));
	}
}