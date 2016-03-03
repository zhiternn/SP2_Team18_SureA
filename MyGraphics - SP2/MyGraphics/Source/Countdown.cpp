/******************************************************************************/
/*!
\file	Countdown.cpp
\author Quek Cher Yi
\par	email: 155124D@mymail.nyp.edu.sg
\brief
Class to count time
*/
/******************************************************************************/


#include "Countdown.h"

Countdown::Countdown(){
	StopWatch();
	duration = 0;
	isCountingDown = false;
}

Countdown::~Countdown(){

}

/******************************************************************************/
/*!
\param	double a

\brief	starts countdown timer
		duration of the total time
*/
/******************************************************************************/

void Countdown::StartCountdown(double a)
{
	isCountingDown = true;
	duration = a;
	startTimer();
}

/******************************************************************************/
/*!
\brief	Gets how much time has past since countdown timer started
*/
/******************************************************************************/

double Countdown::GetTimeLeft() // true when times up
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