#include "I8080.UI.HexViewer.h"



Widget_HexViewer::Widget_HexViewer(I8080* processor, TranslatorOutput* translator, Widget_MnemocodeViewer* widget_MnemocodeViewer) :I8080_Widget(u8"Просмотр памяти") {
	this->processor = processor;
	this->translator = translator;
	this->widget_MnemocodeViewer = widget_MnemocodeViewer;


	mem_edit.ReadOnly = true;
	mem_edit.OptShowOptions = false;
	mem_edit.OptShowAscii = false;

}
Widget_HexViewer::~Widget_HexViewer() {

}

MemoryEditor* Widget_HexViewer::GetPtrMemoryEditor() {
	return &mem_edit;
}

void Widget_HexViewer::Draw() {
	if (GetFlagShow() == false)
		return;


	if (processor == nullptr) {
		return;
	}

	mem_edit.DrawWindow(GetName_c_str(), GetPtrFlagShow(), processor, widget_MnemocodeViewer, translator->Opcodes, Colors_TypesCommands);

}
void Widget_HexViewer::Update() {
	UpdateActive();
}

std::string Widget_HexViewer::Save() {
	std::string output = "";
	output += MakeBegin(2);
	output += MakeSaveItem(std::string("Flag_Show"), std::to_string(GetFlagShow()));
	output += MakeSaveItem(std::string("Flag_Active"), std::to_string(WindowIsVisiable()));
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
		else if (name_arg == "Flag_Active") {
			if (stoi(value_arg) == 1)
				SetActive();
		}
		else
			std::cout << "Unknown name argument for widget: " << name_arg << std::endl;
	}
}