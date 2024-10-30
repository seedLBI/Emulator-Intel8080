#ifndef I8080_UI_INPUT_0X08_H
#define I8080_UI_INPUT_0X08_H

#include "Emulator\I8080.h"
#include "UI\Widget\I8080.Widget.h"
#include "Utils/ImGui.Utils.h"
#include <string>




class Widget_Input0x08: public I8080_Widget
{
public:
	Widget_Input0x08(I8080* processor);
	~Widget_Input0x08();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;
private:
	I8080* processor = nullptr;
	const char* info{ 
		u8"Способ обращения к порту: \n"
		u8"- Написать IN 0x08 в коде.\n"
		u8"Протокол использования: \n"
		u8"1. Дождаться выполнения команды путём ввода пользовтелем значения\n"
		u8"2. Получить вводимое значение в регистре А" };



	bool Focus_ones = true;
	void SendValue_to_Port(const std::string& str_value);

	static int InputTextCallback(ImGuiInputTextCallbackData* data);

};







#endif // !I8080_UI_INPUT_0X08_H




