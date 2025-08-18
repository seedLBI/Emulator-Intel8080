#ifndef UI_TABLE_INSTRUCTION_H
#define UI_TABLE_INSTRUCTION_H

#include "Emulator/History/Caretaker.Momento.h"
#include "Emulator/EmulationThread/EmulationThread.h"
#include "Emulator\Processors\Intel8080\I8080.h"
#include "Emulator/Processors/Intel8080/InfoInstruction/InfoInstruction.Data.h"
#include "Emulator/Processors/Intel8080/InfoInstruction/InfoInstruction.Display.h"
#include "UI\Widget\I8080.Widget.h"
#include "UI/HighlighterInstruction/I8080/I8080.HighlighterInstruction.h"
#include "Utils/Values/Values.Utils.h"
#include "Utils/ImGui.Utils.h"
#include <string>
#include <list>

class Widget_TableInstruction : public I8080_Widget
{
public:
	Widget_TableInstruction();
	~Widget_TableInstruction();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void		Load(const std::string& Data) override;
private:
	std::vector<std::pair<std::string,std::string>> instruction;


	void GetAllInstruction();
};


#endif // !UI_TABLE_INSTRUCTION_H
