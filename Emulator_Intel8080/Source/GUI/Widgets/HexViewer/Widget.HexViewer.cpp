#include "Widget.HexViewer.h"



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

nlohmann::json Widget_HexViewer::Save() {
	return SaveDefaultParameters();
}

void Widget_HexViewer::Load(const nlohmann::json& Data) {
	ReadDefaultParameters(Data);
}