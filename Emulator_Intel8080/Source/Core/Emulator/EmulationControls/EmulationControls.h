#ifndef EMULATION_CONTROLS_H
#define EMULATION_CONTROLS_H

#define _HAS_STD_BYTE 0
#include "Config_Compilier.h"

#include "GUI/Widgets/RegisterFlagsInfo/Widget.RegisterFlagsInfo.h"
#include "GUI/Widgets/MnemoCodeViewer/Widget.MnemoCodeViewer.h"
#include "GUI/Widgets/CodeEditor/Widget.CodeEditor.h"

#include "Core/ProjectManager/ProjectManager.h"
#include "Core/Emulator/EmulationThread/EmulationThread.h"
#include "Core/Emulator/History/Caretaker.Momento.h"
#include "Core/Emulator/Processor/Processor.h"


class EmulationControls
{
public:
	EmulationControls(
		Processor* processor,
		Caretaker_Momento* processor_CaretakerMomento,
		EmulationThread* emulationThread,
		ProjectManager * projectManager,
		Widget_RegisterFlagsInfo* widget_RegisterFlagsInfo,
		Widget_MnemocodeViewer* widget_MnemocodeViewer,
		Widget_CodeEditor* widget_CodeEditor);
	~EmulationControls();

	void Play();
	void Pause();
	void Stop();
	void Undo_step();
	void Next_step();
	void FullReset();


private:
	Processor* processor = nullptr;
	Caretaker_Momento* processor_CaretakerMomento = nullptr;
	EmulationThread* emulationThread = nullptr;
	ProjectManager* projectManager = nullptr;
	Widget_RegisterFlagsInfo* widget_RegisterFlagsInfo = nullptr;
	Widget_MnemocodeViewer* widget_MnemocodeViewer = nullptr;
	Widget_CodeEditor* widget_CodeEditor = nullptr;

};




#endif // !EMULATION_CONTROLS_H

