#include "timer.h"

#ifndef COUNTDOWN_H
#define COUNTDOWN_H

class Countdown : public StopWatch
{
public:
	Countdown()
	{
		StopWatch();
		duration = 0;
		isCountingDown = false;
	}
	virtual ~Countdown()
	{
	}

	void StartCountdown(double a)
	{
		isCountingDown = true;
		duration = a;
		startTimer();
	}
	double GetTimeLeft() // true when times up
	{
		if (isCountingDown){
			duration -= getElapsedTime();
			if (duration <= 0){
				duration = 0;
				isCountingDown = false;
			}
		}

			return duration;
	}

	bool isCountingDown;
private:
	double duration;
	
};

#endif