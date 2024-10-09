#include "I8080.UI.CodeEditor.h"


Widget_CodeEditor::Widget_CodeEditor() : I8080_Widget(u8"Редактор кода") {
	editor = new TextEditor();
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

}


void Widget_CodeEditor::SetFlagWindow(int flag_value) {
	flags_CodeEditor = flag_value;
}


bool Widget_CodeEditor::GetFlagWindow() {
	return flags_CodeEditor == ImGuiWindowFlags_UnsavedDocument;
}

std::string Widget_CodeEditor::Save() {
	std::string output = "";
	output += MakeBegin(1);
	output += MakeSaveItem(string("Flag_Show"), std::to_string(GetFlagShow()));
	return output;
}

void Widget_CodeEditor::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);

	std::vector<std::string> Lines = split(Data, "\n");
	for (int i = 0; i < Lines.size(); i++) {
		std::vector<std::string> info = SplitLine(Lines[i]);

		std::string name_arg = info[0];
		std::string value_arg = info[1];

		if (name_arg == "Flag_Show")
			SetFlagShow(stoi(value_arg));
		else
			std::cout << "Unknown name argument for widget: " << name_arg << std::endl;
	}
}

TextEditor* Widget_CodeEditor::GetPtrTextEditor() {
	return editor;
}