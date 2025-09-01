#ifndef EMULATION_CONTROLS_H
#define EMULATION_CONTROLS_H

class Processor;
class Caretaker_Momento;
class EmulationThread;
class ProjectManager;
class Widget_RegisterFlagsInfo;
class Widget_MnemocodeViewer;
class Widget_CodeEditor;


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

