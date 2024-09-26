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