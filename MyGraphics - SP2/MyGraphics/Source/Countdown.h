/******************************************************************************/
/*!
\file	Timer.h
\author Quek Cher Yi
\par	email: 155124D@mymail.nyp.edu.sg
\brief
Class to define Countdown and its methods
*/
/******************************************************************************/



#include "timer.h"

#ifndef COUNTDOWN_H
#define COUNTDOWN_H

class Countdown : public StopWatch
{
public:
	Countdown();
	~Countdown();

	void StartCountdown(double a);
	double GetTimeLeft();
	bool isCountingDown;
private:
	double duration;
	
};

#endif