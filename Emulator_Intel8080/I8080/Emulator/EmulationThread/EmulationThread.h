#ifndef EMULATION_THREAD_H
#define EMULATION_THREAD_H

#include "Config_Compilier.h"
#include "OpenglWindow/OpenglWindow.h"
#include "UI/Setting/ISettingObject.h"
#include "IconFontCppHeaders/IconsFontAwesome6.h"
#include "SaveSystem/SaveSystem.h"
#include "Emulator/I8080.h"
#include "Utils/ImGui.Utils.h"
#include <thread>


enum class SpeedMode{
	Infinity,
	Intel8080,
	Intel8085,
	Custom
};

std::string toString(SpeedMode mode);

enum class ControlMode {
	Stop,
	StepByStep,
	Continous
};

class EmulationThread : public ISettingObject
{
public:
	EmulationThread(I8080* processor);
	~EmulationThread();

	void SetControlMode(const ControlMode& mode);
	ControlMode GetControlMode();

	void SetSpeedMode(const SpeedMode& mode);
	SpeedMode GetSpeedMode();

	bool isThreadWorking();
	void WaitThread();


	void DrawMainMenu();


	void LoadNextSpeed();
	void LoadPreviousSpeed();

	void DrawSetting() override;
	std::string SaveSetting() override;
	void LoadSetting(const std::string& Data) override;

private:
	I8080* processor;
	uint64_t targetTicksPerSecond = 0;
	uint64_t targetTicksPerFrame = 0;
	thread* threadObject = nullptr;
	void ThreadLoop();


	struct CustomSpeed {
		std::string name;
		uint64_t targetTicksPerSecond = 0;
		uint64_t targetTicksPerFrame = 0;
	};
	std::vector<CustomSpeed> UserSpeeds;

	int IndexChoosedCustomSpeedMode = -1;
	bool flag_ReturnStateAfterChangeSpeed = false;
	bool flag_ThreadWorking = false;
	bool PopupCreation_opened = false;


	SpeedMode Speed = SpeedMode::Infinity;
	ControlMode Control = ControlMode::Stop;


	void DrawPopup();

	std::string TicksToString(const uint64_t& ticks);
	static int InputTextCallback(ImGuiInputTextCallbackData* data);

};




#endif

