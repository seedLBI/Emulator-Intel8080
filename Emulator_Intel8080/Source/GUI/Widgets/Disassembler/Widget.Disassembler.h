#ifndef I8080_UI_DISASSEMBLER_H
#define I8080_UI_DISASSEMBLER_H


#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Emulator/Processors/Intel8080/Disassembler/I8080.Disassembler.h"
#include "Core/Widget/I8080.Widget.h"
#include "Utils/ImGui/Utils.ImGui.h"
#include "Utils/Text/Text.h"
#include <string>


class Widget_Disassembler : public I8080_Widget
{
public:
	Widget_Disassembler(I8080* processor);
	~Widget_Disassembler();
	void Draw() override;
	void Update() override;

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;
private:
	I8080* processor;
};


#endif // !I8080_UI_DISASSEMBLER_H
