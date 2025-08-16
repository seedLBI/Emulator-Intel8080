#ifndef UI_TABLE_INSTRUCTION_H
#define UI_TABLE_INSTRUCTION_H

#include "Core/Emulator/History/Caretaker.Momento.h"
#include "Core/Emulator/EmulationThread/EmulationThread.h"
#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Emulator/Processors/Intel8080/InfoInstruction/InfoInstruction.Data.h"
#include "Core/Emulator/Processors/Intel8080/InfoInstruction/InfoInstruction.Display.h"
#include "Core/Widget/I8080.Widget.h"

#include "GUI/HighlighterInstruction/I8080/I8080.HighlighterInstruction.h"

#include "Utils/Values/Values.h"
#include "Utils/ImGui/Utils.ImGui.h"

#include <string>
#include <list>

class Widget_TableInstruction : public I8080_Widget
{
public:
	Widget_TableInstruction();
	~Widget_TableInstruction();
	void Draw() override;
	void Update() override;

	nlohmann::json	Save() override;
	void			Load(const nlohmann::json& Data) override;
private:
	std::vector<std::pair<std::string,std::string>> instruction;

	void GetAllInstruction();
};


#endif // !UI_TABLE_INSTRUCTION_H
