#ifndef PROCESSSCHEDULER__H
#define PROCESSSCHEDULER__H

#include "ProcessesManager.h"
#include "Process.h"
#include <iostream>
#include <list>

class ProcessScheduler {
private:
	std::list<PCB*>::iterator iteratorToMinElement;
	//zmienne pomocnicze potrzebne do wyliczenia nowego burstTime, kiedy zajdzie potrzeba:
	short differenceCounter , startCounter, endCounter{ 0 };
	//procedura odpowiadająca za planowanie przydziału procesora
	void SRTSchedulingAlgorithm();
public:
	//procedura sluzaca do uruchomienia procesu i wywołania planisty
	void RunProcess();
};
#endif PROCESSSCHEDULER__H