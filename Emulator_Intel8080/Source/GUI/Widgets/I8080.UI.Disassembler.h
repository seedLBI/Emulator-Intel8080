#ifndef I8080_UI_DISASSEMBLER_H
#define I8080_UI_DISASSEMBLER_H


#include "Emulator\Processors\Intel8080\I8080.h"
#include "Emulator/Processors/Intel8080/Disassembler/I8080.Disassembler.h"
#include "UI\Widget\I8080.Widget.h"
#include "Utils\ImGui.Utils.h"
#include <string>


class Widget_Disassembler : public I8080_Widget
{
public:
	Widget_Disassembler(I8080* processor);
	~Widget_Disassembler();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;
private:
	I8080* processor;
};


#endif // !I8080_UI_DISASSEMBLER_H
