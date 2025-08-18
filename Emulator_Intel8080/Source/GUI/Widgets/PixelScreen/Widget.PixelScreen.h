#ifndef I8080_UI_PIXEL_SCREEN_H
#define I8080_UI_PIXEL_SCREEN_H


#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Widget/I8080.Widget.h"
#include "Utils/OpenGL/PBO/PBO.h"
#include <string>



class Widget_PixelScreen : public I8080_Widget
{
public:
	Widget_PixelScreen(GLFWwindow* window, I8080* processor);
	~Widget_PixelScreen();
	void Draw() override;
	void Update() override;

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;
private:
	GLFWwindow* window;
	I8080* processor;
	PBO* pbo = nullptr;
	unsigned char* bufferPixelScreen = nullptr;

	int Ratio_Mode = 0;
	float ColorsLine[4] = { 0.f,0.f,0.f,0.2f };
	bool DrawLines = false;
	int ThiknessLines = 1;



	const char* info{
	u8"										        		*���������� �����*  \n"
	"\n"
	u8"����: 0x05  \n"
	u8"����������: 256�256  \n"
	u8"���������� ������: 256 (���������� �� ���������� ������ RGB[0bRRGGGBBB])   \n"
	"\n"
	u8"�������� ������ �����������:   \n"
	u8"		1. �������� � ���� 0x05 ����� ������ (0 - 255)\n"
	u8"		2. �������� � ���� 0x05 ����� ������� (0 - 255)\n"
	u8"		3. ������� ����� ������/������. ([0x00] - ������, [����� ������ ��������] - ������).\n"
	u8"		4. ��������/��������� �������� ����� ���������� ������� ������.\n"
	};
};




#endif // !I8080_UI_PIXEL_SCREEN_H

