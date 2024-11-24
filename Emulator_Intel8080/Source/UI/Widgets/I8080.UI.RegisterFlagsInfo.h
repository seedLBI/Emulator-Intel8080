#ifndef I8080_UI_REGISTER_FLAGS_INFO_H
#define I8080_UI_REGISTER_FLAGS_INFO_H

#include "Emulator\Processors\Intel8080\I8080.h"
#include "Emulator/Processors/Intel8080/Disassembler/I8080.Disassembler.h"
#include "UI\Widget\I8080.Widget.h"
#include "Utils\ImGui.Utils.h"
#include <string>


class Widget_RegisterFlagsInfo : public I8080_Widget
{
public:
	Widget_RegisterFlagsInfo(I8080* processor);
	~Widget_RegisterFlagsInfo();
	void Draw() override;
	void Update() override;
	void InitLastState();

	std::string Save() override;
	void Load(const std::string& Data) override;
private:
	I8080* processor;
	CurrentState		   current_state;
	CurrentStateNotPointer    prev_state;
};



#endif // !I8080_UI_REGISTER_FLAGS_INFO_H
