#ifndef EMULATION_THREAD_H
#define EMULATION_THREAD_H

#include "Config_Compilier.h"
#include "OpenglWindow/OpenglWindow.h"
#include "SaveSystem/SaveSystem.h"
#include "Emulator/I8080.h"
#include <thread>


enum class SpeedMode{
	Infinity,
	Intel8080,
	Intel8085
};

std::string toString(SpeedMode mode);

enum class ControlMode {
	Stop,
	StepByStep,
	Continous
};

class EmulationThread : public SaveSystem
{
public:
	EmulationThread(I8080* processor);
	~EmulationThread();

	void SetControlMode(const ControlMode& mode);
	ControlMode GetControlMode();

	void SetSpeedMode(const SpeedMode& mode);
	SpeedMode GetSpeedMode();


	bool isThreadWorking();


	std::string Save() override;
	void Load(const std::string& Data) override;

private:
	I8080* processor;

	SpeedMode Speed = SpeedMode::Infinity;
	ControlMode Control = ControlMode::Stop;

	bool flag_ThreadWorking = false;
	thread* threadObject = nullptr;

	void ThreadLoop();


};




#endif

