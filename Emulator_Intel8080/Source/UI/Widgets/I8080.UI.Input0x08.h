#ifndef I8080_UI_INPUT_0X08_H
#define I8080_UI_INPUT_0X08_H

#include "Emulator\Processors\Intel8080\I8080.h"
#include "UI\Widget\I8080.Widget.h"
#include "UI/Theme/interface/IThemeLoadable.h"
#include "Utils/ImGui.Utils.h"
#include <string>




class Widget_Input0x08: public I8080_Widget, public IThemeLoadable
{
public:
	Widget_Input0x08(I8080* processor);
	~Widget_Input0x08();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;

	void LoadColors() override;
	std::vector<NamedColor> GetDefaultLightColors() override;
	std::vector<NamedColor> GetDefaultDarkColors() override;

private:
	I8080* processor = nullptr;
	const char* info{ 
		u8"������ ��������� � �����: \n"
		u8"- �������� IN 0x08 � ����.\n"
		u8"�������� �������������: \n"
		u8"1. ��������� ���������� ������� ���� ����� ������������ ��������\n"
		u8"2. �������� �������� �������� � �������� �" };


	ImColor color_Active;

	bool Focus_ones = true;
	void SendValue_to_Port(const std::string& str_value);

	static int InputTextCallback(ImGuiInputTextCallbackData* data);

};







#endif // !I8080_UI_INPUT_0X08_H




