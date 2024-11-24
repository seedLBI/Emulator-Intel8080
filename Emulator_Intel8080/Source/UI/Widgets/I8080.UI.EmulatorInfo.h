#ifndef I8080_UI_EMULATOR_INFO_H
#define I8080_UI_EMULATOR_INFO_H

#include "Emulator\Processors\Intel8080\I8080.h"
#include "UI\Widget\I8080.Widget.h"
#include "Utils\ImGui.Utils.h"
#include <string>


class Widget_EmulatorInfo : public I8080_Widget
{
public:
	Widget_EmulatorInfo(I8080* processor);
	~Widget_EmulatorInfo();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;
private:
	I8080* processor;
	CurrentState current_state;
	std::string ConvertToSI(uint64_t value);
};



#endif // !I8080_UI_EMULATOR_INFO_H
