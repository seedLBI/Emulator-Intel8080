#ifndef MUTEX_H
#define MUTEX_H

#include <Windows.h>
#include <iostream>
#include <string>

class Mutex
{
public:
	Mutex();
	Mutex(const char* Name);
	~Mutex();

	void Enter();
	void Leave();

private:
	HANDLE ID = 0;
	SECURITY_ATTRIBUTES sa;
};



#endif 