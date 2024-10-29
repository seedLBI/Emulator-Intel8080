#include "UI/Widgets/I8080.UI.MemoryMonoPixelScreen.h"



Widget_MemoryPixelScreen::Widget_MemoryPixelScreen(I8080* processor):I8080_Widget(u8"Монохромный экран с общей памятью") {
	this->processor = processor;
}

Widget_MemoryPixelScreen::~Widget_MemoryPixelScreen() {

}
void Widget_MemoryPixelScreen::Draw() {

}
void Widget_MemoryPixelScreen::Update() {

}

std::string Widget_MemoryPixelScreen::Save() {

}
void Widget_MemoryPixelScreen::Load(const std::string& Data) {

}