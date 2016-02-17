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
		timeStarted = false;
	}
	virtual ~Countdown()
	{
	}

	void StartCountdown(double a)
	{
		timeStarted = true;
		duration = a;
		startTimer();
	}
	bool TimesUp() // true when times up
	{
		if (timeStarted){
			duration -= getElapsedTime();

			//std::cout << duration << std::endl;

			if (duration <= 0){
				duration = 0;
				timeStarted = false;

				return true;
			}
		}

		return false;
	}

private:
	double duration;
	bool timeStarted;
};

#endif