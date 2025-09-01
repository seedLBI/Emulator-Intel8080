#include "EmulationControls.h"

#include "Config_Compilier.h"

#include "GUI/Widgets/RegisterFlagsInfo/Widget.RegisterFlagsInfo.h"
#include "GUI/Widgets/MnemoCodeViewer/Widget.MnemoCodeViewer.h"
#include "GUI/Widgets/CodeEditor/Widget.CodeEditor.h"

#include "Core/ProjectManager/ProjectManager.h"
#include "Core/Emulator/EmulationThread/EmulationThread.h"
#include "Core/Emulator/History/Caretaker.Momento.h"
#include "Core/Emulator/Processor/Processor.h"


EmulationControls::EmulationControls(
	Processor* processor,
	Caretaker_Momento* processor_CaretakerMomento,
	EmulationThread* emulationThread,
	ProjectManager* projectManager,
	Widget_RegisterFlagsInfo* widget_RegisterFlagsInfo,
	Widget_MnemocodeViewer* widget_MnemocodeViewer,
	Widget_CodeEditor* widget_CodeEditor)
{
	this->processor = processor;
	this->processor_CaretakerMomento = processor_CaretakerMomento;
	this->emulationThread = emulationThread;
	this->projectManager = projectManager;
	this->widget_RegisterFlagsInfo = widget_RegisterFlagsInfo;
	this->widget_MnemocodeViewer = widget_MnemocodeViewer;
	this->widget_CodeEditor = widget_CodeEditor;
}
EmulationControls::~EmulationControls() {

}



void EmulationControls::Play() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Pressed Emulator_Play()\n";
#endif

	processor->ResetFlagStop();
	emulationThread->SetControlMode(ControlMode::Continous);


}
void EmulationControls::Pause() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Pressed Emulator_Pause()\n";
#endif

	emulationThread->SetControlMode(ControlMode::Stop);
	emulationThread->WaitThread();

	widget_RegisterFlagsInfo->InitLastState();
	widget_MnemocodeViewer->FollowCursorPC();
}
void EmulationControls::Stop() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Pressed Emulator_Stop()\n";
#endif

	emulationThread->SetControlMode(ControlMode::Stop);
	emulationThread->WaitThread();

	processor->ActiveFlagStop();
	processor->Reset();

	//processor->RemoveAllBreakPoints();
	processor_CaretakerMomento->ClearHistory();

	widget_RegisterFlagsInfo->InitLastState();
	widget_MnemocodeViewer->FollowCursorPC();
}
void EmulationControls::Undo_step() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Pressed Emulator_Undo_step() \n";
#endif

	if (processor->isHistoryModeEnabled() == false)
		return;

	emulationThread->SetControlMode(ControlMode::StepByStep);
	emulationThread->WaitThread();

	
	//processor->ResetFlagStop();
	widget_RegisterFlagsInfo->InitLastState();
	processor_CaretakerMomento->Undo();
	widget_MnemocodeViewer->FollowCursorPC();
}
void EmulationControls::Next_step() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Pressed Emulator_Next_step() \n";
#endif
	emulationThread->SetControlMode(ControlMode::StepByStep);
	emulationThread->WaitThread();

	//processor->ResetFlagStop();
	widget_RegisterFlagsInfo->InitLastState();

	if (processor->isHistoryModeEnabled()) {
		processor_CaretakerMomento->Backup();
		processor->NextStepWithHistorySaving();
	}
	else
		processor->NextStep();




	widget_MnemocodeViewer->FollowCursorPC();



	auto data = processor_CaretakerMomento->GetHistory();

}
void EmulationControls::FullReset() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Pressed Emulator_FullReset()\n";
#endif
	emulationThread->SetControlMode(ControlMode::Stop);
	emulationThread->WaitThread();

	processor->ActiveFlagStop();
	processor->EraseMemory();
	processor->RemoveAllBreakPoints();
	processor->Reset();
	processor->Reset();

	processor_CaretakerMomento->ClearHistory();

	widget_CodeEditor->GetPtrTextEditor()->DeleteAllBreakpoints();

	projectManager->GetPtrTranslatorOutput()->Opcodes.clear();

	widget_RegisterFlagsInfo->InitLastState();
	widget_MnemocodeViewer->FollowCursorPC();

}
