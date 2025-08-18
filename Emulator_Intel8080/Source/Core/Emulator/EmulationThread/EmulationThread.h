#ifndef EMULATION_THREAD_H
#define EMULATION_THREAD_H


#include "Config_Compilier.h"

#include "ThirdParty/IconFontCppHeaders/IconsFontAwesome6.h"
#include "ThirdParty/ImGui/imgui.h"
#include "ThirdParty/ImGui/imgui_internal.h"

#include "Core/Setting/interfaces/ISettingObject.h"
#include "Core/SaveSystem/SaveSystem.h"
#include "Core/Emulator/Processor/Processor.h"
#include "Core/Emulator/History/Caretaker.Momento.h"
#include "Core/Emulator/Processors/Intel8080/I8080.h"

#include "Utils/ImGui/Utils.ImGui.h"
#include "Utils/Values/Values.h"

#include <thread>
#include <GLFW/glfw3.h>


enum class SpeedMode{
	Infinity,
	Intel4004,
	Intel8008,
	Intel8080,
	Intel8085,
	Intel8086,
	Custom
};

namespace speed_name {
	const std::string infinity = u8"Infinity";
	const std::string intel4004 = u8"Intel 4004";
	const std::string intel8008 = u8"Intel 8008";
	const std::string intel8080 = u8"Intel 8080";
	const std::string intel8085 = u8"Intel 8085";
	const std::string intel8086 = u8"Intel 8086";
	const std::string custom = u8"Custom";
	const std::string unknown = u8"Unknown";
}



std::string toString(SpeedMode mode);
SpeedMode toSpeedMode(const std::string& mode);

enum class ControlMode {
	Stop,
	StepByStep,
	Continous
};

class EmulationThread : public ISettingObject {
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
	nlohmann::json SaveSetting() override;
	void LoadSetting(const nlohmann::json& Data) override;

private:
	Processor* processor;
	Caretaker_Momento* processor_CaretakerMomento = nullptr;

	uint64_t targetTicksPerSecond = 0;
	std::thread* threadObject = nullptr;
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

