#include "I8080.UI.HexViewer.h"



Widget_HexViewer::Widget_HexViewer(I8080* processor, TranslatorOutput* translator) :I8080_Widget(u8"Просмотр памяти") {
	this->processor = processor;
	this->translator = translator;

	mem_edit.ReadOnly = true;
	mem_edit.OptShowOptions = false;
	mem_edit.OptShowAscii = false;

}
Widget_HexViewer::~Widget_HexViewer() {

}
void Widget_HexViewer::Draw() {
	if (GetFlagShow() == false)
		return;

	if (processor == nullptr) {
		return;
	}

	mem_edit.DrawWindow(GetName_c_str(), GetPtrFlagShow(), processor, translator->Opcodes, Colors_TypesCommands);

}
void Widget_HexViewer::Update() {

}

std::string Widget_HexViewer::Save() {
	std::string output = "";
	output += MakeBegin(1);
	output += MakeSaveItem(string("Flag_Show"), std::to_string(GetFlagShow()));
	return output;
}

void Widget_HexViewer::Load(const std::string& Data) {
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