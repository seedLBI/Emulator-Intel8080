#ifndef EMULATION_THREAD_H
#define EMULATION_THREAD_H

#include "Config_Compilier.h"
#include "OpenglWindow/OpenglWindow.h"
#include "UI/Setting/ISettingObject.h"
#include "IconFontCppHeaders/IconsFontAwesome6.h"
#include "SaveSystem/SaveSystem.h"
#include "Emulator/Processors/Processor.h"
#include "Emulator/History/Caretaker.Momento.h"
#include "Emulator\Processors\Intel8080\I8080.h"
#include "Utils/ImGui.Utils.h"
#include <thread>


enum class SpeedMode{
	Infinity,
	Intel4004,
	Intel8008,
	Intel8080,
	Intel8085,
	Intel8086,
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
	EmulationThread(Processor* processor, Caretaker_Momento* processor_CaretakerMomento);
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
	Processor* processor;
	Caretaker_Momento* processor_CaretakerMomento = nullptr;

	uint64_t targetTicksPerSecond = 0;
	thread* threadObject = nullptr;
	void ThreadLoop();


	struct CustomSpeed {
		std::string name;
		uint64_t targetTicksPerSecond = 0;
	};
	std::vector<CustomSpeed> UserSpeeds;

	int IndexChoosedCustomSpeedMode = -1;
	int IndexChoosedCustomSpeedModeLast = -1;


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

