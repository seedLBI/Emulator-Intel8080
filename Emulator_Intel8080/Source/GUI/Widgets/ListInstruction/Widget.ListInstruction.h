#ifndef UI_LIST_INSTRUCTION_H
#define UI_LIST_INSTRUCTION_H

#include "Core/Emulator/History/Caretaker.Momento.h"
#include "Core/Emulator/EmulationThread/EmulationThread.h"
#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Emulator/Processors/Intel8080/InfoInstruction/InfoInstruction.Data.h"
#include "Core/Widget/I8080.Widget.h"
#include "Utils/Values/Values.h"
#include <string>
#include <list>


class Widget_ListInstruction : public I8080_Widget
{
public:
	Widget_ListInstruction();
	~Widget_ListInstruction();
	void Draw() override;
	void Update() override;

	nlohmann::json	Save() override;
	void			Load(const nlohmann::json& Data) override;
private:
	std::vector<std::string> instruction;

	void GetAllInstruction();
};

#endif // !UI_LIST_INSTRUCTION_H
