#include "I8080.Widget.h"

I8080_Widget::I8080_Widget(const std::string& Name, const bool& flag) : SaveSystem(Name){
	this->Name = Name;
	Name_c_str = this->Name.c_str();
	Show = new bool;
	*Show = flag;
}

I8080_Widget::~I8080_Widget()
{
}

void I8080_Widget::Draw() {

}

void I8080_Widget::Update() {

}

void I8080_Widget::SetFocus() {
	TimerFocus = 1.f;
	flag_FocusSeted = true;
}


// Это добавлять в Draw
void I8080_Widget::UpdateFocus() {
	if (flag_FocusSeted){
		ImGui::SetWindowFocus(Name_c_str);
		flag_FocusSeted = false;
	}
	TimerFocus -= OpenglWindow::GetDeltaTime();
	if (TimerFocus < 0.f)
		TimerFocus = 0.f;
}

float I8080_Widget::GetTimerFocus() {
	return TimerFocus;
}

std::string I8080_Widget::GetCommand() {
	return "";
}

bool I8080_Widget::GetFlagShow() {
	return *Show;
}

bool* I8080_Widget::GetPtrFlagShow() {
	return Show;
}

void I8080_Widget::SetFlagShow(const bool& value) {
	*Show = value;
}

std::string I8080_Widget::GetName() {
	return Name;
}

const char* I8080_Widget::GetName_c_str() {
	return Name_c_str;
}


void I8080_Widget::Load(const std::string& Data) {

}
std::string I8080_Widget::Save() {
	return "";
}