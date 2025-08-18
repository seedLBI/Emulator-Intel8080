#ifndef UI_HISTORY_INSTRUCTION
#define UI_HISTORY_INSTRUCTION


#include "Core/Emulator/History/Caretaker.Momento.h"
#include "Core/Emulator/EmulationThread/EmulationThread.h"
#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Widget/I8080.Widget.h"
#include <string>


class Widget_HistoryInstruction : public I8080_Widget
{
public:
	Widget_HistoryInstruction(I8080* processor,EmulationThread* emulationThread, Caretaker_Momento* processor_CaretakerMomento);
	~Widget_HistoryInstruction();
	void Draw() override;
	void Update() override;

	nlohmann::json	Save() override;
	void			Load(const nlohmann::json& Data) override;
private:
	I8080* processor = nullptr;
	EmulationThread* emulationThread = nullptr;
	Caretaker_Momento* processor_CaretakerMomento = nullptr;
};




#endif // !UI_HISTORY_INSTRUCTION
