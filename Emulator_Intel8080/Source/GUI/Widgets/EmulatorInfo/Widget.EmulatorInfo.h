#ifndef I8080_UI_EMULATOR_INFO_H
#define I8080_UI_EMULATOR_INFO_H

#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Widget/I8080.Widget.h"
#include "Utils/ImGui/Utils.ImGui.h"
#include <string>
#include <GLFW/glfw3.h>

class Widget_EmulatorInfo : public I8080_Widget
{
public:
	Widget_EmulatorInfo(I8080* processor);
	~Widget_EmulatorInfo();
	void Draw() override;
	void Update() override;

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;
private:
	I8080* processor;
	CurrentState current_state;
	std::string ConvertToSI(const uint64_t& value, const char* unit);
};



#endif // !I8080_UI_EMULATOR_INFO_H
