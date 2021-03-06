#include "Scenarios.h"
#include "Enemy.h"
#include "Friendly.h"

//============================================================================================
//SCENARIO DEFEND
//============================================================================================

ScenarioDefend::ScenarioDefend(int health, double duration, int increment, bool multiplay)
{

	this->increment = increment;
	amountToSpawn = increment;
	HP = health;
	wave = 1;
	winScenario = false;
	timer.StartCountdown(duration);
	this->multiplay = multiplay;

	SpawnEnemies();
	MoveEnemies();
}

ScenarioDefend::~ScenarioDefend()
{
	for (vector<Enemy*>::iterator it = Enemy::enemyList.begin(); it != Enemy::enemyList.end();){
		delete *it;
		it = Enemy::enemyList.erase(it);
	}
}

void ScenarioDefend::Update(double dt, bool multiplay)
{
	this->multiplay = multiplay;
	if (timer.GetTimeLeft() > 0){
		if (Enemy::enemyList.size() <= 0){//check for wave completion
			wave++;
			amountToSpawn += increment;

			SpawnEnemies();
			MoveEnemies();
		}
	}
	if (Enemy::enemyList.size() > 0){
		for (vector<Enemy*>::iterator it = Enemy::enemyList.begin(); it != Enemy::enemyList.end();){//check if enemies reached destination
			if ((*it)->reachedDestination){
				HP -= 1;
				if (HP <= 0){// LOSE
					stopScenario = true;
				}

				delete *it;
				it = Enemy::enemyList.erase(it);
			}
			else{
				it++;
			}
		}
	}
	if (timer.GetTimeLeft() <= 0 && Enemy::enemyList.size() <= 0){// WIN
		winScenario = true;
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
			Vector3(0, 0, 1), // direction
			(float)(rand() % 40 + 20) / 10.f // speed
		);
	}
}

void ScenarioDefend::MoveEnemies()
{
	for (vector<Enemy*>::iterator it = Enemy::enemyList.begin(); it != Enemy::enemyList.end(); ++it){
		if (multiplay){
			if (rand() % 2){
				(*it)->GoTo(Vector3(-22.3, 2.8, 40.75));
			}
			else{
				(*it)->GoTo(Vector3(22.3, 2.8, 40.75));
			}
		}
		else{
			(*it)->GoTo(Vector3(-22.3, 2.8, 40.75));
		}
	}
}