#ifndef I8080_UI_KEYBOARD_H
#define I8080_UI_KEYBOARD_H

#include "Emulator\Processors\Intel8080\I8080.h"
#include "UI\Widget\I8080.Widget.h"
#include "TextEditor.h"
#include <string>

class Widget_Keyboard : public I8080_Widget
{
public:
	Widget_Keyboard(TextEditor* editor);
	~Widget_Keyboard();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;
private:
	TextEditor* editor = nullptr;
	const vector<vector<string>> layers_names_array = {
			{"Esc","1","2","3","4","5","6","7","8","9","0","-","=","BackSp"},
			{"Tab","q","w","e","r","t","y","u","i","o","p","[","]","|\\"},
			{"CapsLk","a","s","d","f","g","h","j","k","l",";","'","Enter"},
			{"ShiftL","z","x","c","v","b","n","m",",",".","/","ShiftR"},
			{"CtrlL","AltL","Space","AltR","CtrlR"}
	};
	const vector<vector<string>> layers_values_array = {
			{"0x0a","0x01","0x02","0x03","0x04","0x05","0x06","0x07","0x08","0x09","0x00","0x0b","0x0c","0x0d"},
			{"0x0e","0x0f","0x10","0x11","0x12","0x13","0x14","0x15","0x16","0x17","0x18","0x19","0x1a","0x1b"},
			{"0x1c","0x1d","0x1e","0x1f","0x20","0x21","0x22","0x23","0x24","0x25","0x26","0x27","0x28"},
			{"0x29","0x2a","0x2b","0x2c","0x2d","0x2e","0x2f","0x30","0x31","0x32","0x33","0x34"},
			{"0x35","0x36","0x37","0x38","0x39"}
	};
	const vector<vector<float>> layers_sizes_array = {
			{1.3f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.15f},
			{1.8f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,2.7f},
			{1.f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.4f},
			{1.2f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,1.32f},
			{1.1f,1.3f,2.7f,1.3f,1.1f}
	};
	const vector<vector<ImGuiKey>> layers_keys_array = {
			{ImGuiKey_Escape,ImGuiKey_1,ImGuiKey_2,ImGuiKey_3,ImGuiKey_4,ImGuiKey_5,ImGuiKey_6,ImGuiKey_7,ImGuiKey_8,ImGuiKey_9,ImGuiKey_0,ImGuiKey_Minus,ImGuiKey_Equal,ImGuiKey_Backspace},
			{ImGuiKey_Tab,ImGuiKey_Q,ImGuiKey_W,ImGuiKey_E,ImGuiKey_R,ImGuiKey_T,ImGuiKey_Y,ImGuiKey_U,ImGuiKey_I,ImGuiKey_O,ImGuiKey_P,ImGuiKey_LeftBracket,ImGuiKey_RightBracket,ImGuiKey_Backslash},
			{ImGuiKey_CapsLock,ImGuiKey_A,ImGuiKey_S,ImGuiKey_D,ImGuiKey_F,ImGuiKey_G,ImGuiKey_H,ImGuiKey_J,ImGuiKey_K,ImGuiKey_L,ImGuiKey_Semicolon,ImGuiKey_Apostrophe,ImGuiKey_Enter},
			{ImGuiKey_LeftShift,ImGuiKey_Z,ImGuiKey_X,ImGuiKey_C,ImGuiKey_V,ImGuiKey_B,ImGuiKey_N,ImGuiKey_M,ImGuiKey_Comma,ImGuiKey_Period,ImGuiKey_Slash,ImGuiKey_RightShift},
			{ImGuiKey_LeftCtrl,ImGuiKey_LeftAlt,ImGuiKey_Space,ImGuiKey_RightAlt,ImGuiKey_RightCtrl}
	};
};


#endif // ! I8080_UI_KEYBOARD_H
