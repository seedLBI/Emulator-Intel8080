#ifndef UI_LIST_INSTRUCTION_H
#define UI_LIST_INSTRUCTION_H

#include "Emulator/History/Caretaker.Momento.h"
#include "Emulator/EmulationThread/EmulationThread.h"
#include "Emulator\Processors\Intel8080\I8080.h"
#include "Emulator/Processors/Intel8080/InfoInstruction/InfoInstruction.Data.h"
#include "UI\Widget\I8080.Widget.h"
#include "Utils/Values/Values.Utils.h"
#include <string>
#include <list>


class Widget_ListInstruction : public I8080_Widget
{
public:
	Widget_ListInstruction();
	~Widget_ListInstruction();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void		Load(const std::string& Data) override;
private:
	std::vector<std::string> instruction;

	void GetAllInstruction();
};

#endif // !UI_LIST_INSTRUCTION_H
