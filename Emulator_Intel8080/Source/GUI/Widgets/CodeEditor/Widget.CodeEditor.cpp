#include "Widget.CodeEditor.h"


Widget_CodeEditor::Widget_CodeEditor(FPS_Timer* fps_timer) : I8080_Widget(u8"Редактор кода") {
	this->fps_timer = fps_timer;
	editor = new TextEditor(fps_timer);
}
Widget_CodeEditor::~Widget_CodeEditor() {

}
void Widget_CodeEditor::Draw() {
	if (GetFlagShow() == false)
		return;




	if (editor->IsTextChanged())
		flags_CodeEditor = ImGuiWindowFlags_UnsavedDocument;
	//cout << flags << endl;


	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), flags_CodeEditor)) {
		editor->Render(GetName_c_str());
		ImGui::End();
	}
	ImGui::PopStyleVar();



}
void Widget_CodeEditor::Update() {
	UpdateActive();
}


void Widget_CodeEditor::SetFlagWindow(int flag_value) {
	flags_CodeEditor = flag_value;
}


bool Widget_CodeEditor::GetFlagWindow() {
	return flags_CodeEditor == ImGuiWindowFlags_UnsavedDocument;
}

nlohmann::json Widget_CodeEditor::Save() {
	return SaveDefaultParameters();
}

void Widget_CodeEditor::Load(const nlohmann::json& Data) {
	ReadDefaultParameters(Data);
}

TextEditor* Widget_CodeEditor::GetPtrTextEditor() {
	return editor;
}