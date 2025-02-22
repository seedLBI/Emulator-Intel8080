#include "I8080.Widget.h"

I8080_Widget::I8080_Widget(const std::string& Name, const bool& flag) : SaveSystem(Name){
	this->Name = Name;
	Name_c_str = this->Name.c_str();
	Show = new bool;
	*Show = flag;
}

I8080_Widget::~I8080_Widget()
{
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "I8080_Widget::~I8080_Widget()\n";
#endif // !WITH_DEBUG_OUTPUT
}

void I8080_Widget::Draw() {

}

void I8080_Widget::Update() {

}
void I8080_Widget::UpdateActive() {
	if (IsSettedActive){
		IsSettedActive = false;
		MakeActiveCurrentWidget();
	}
}

void I8080_Widget::SetFocus() {
	TimerFocus = 1.f;
	flag_FocusSeted = true;
}

void I8080_Widget::SetActive() {

	IsSettedActive = true;
}

void I8080_Widget::MakeActiveCurrentWidget() {
	ImGui::SetWindowFocus(Name_c_str);
}

bool I8080_Widget::WindowIsVisiable() {

	ImGuiContext& g = *GImGui;

	// ���������� ��� ���� � ���������
	for (ImGuiWindow* window : g.Windows) {
		if (std::string(window->Name) == Name && window->Hidden == false) {
			return true;
		}
	}

	return false;
}

// ��� ��������� � Draw
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