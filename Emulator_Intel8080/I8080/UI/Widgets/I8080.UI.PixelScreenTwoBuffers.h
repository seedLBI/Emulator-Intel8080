#ifndef I8080_UI_PIXEL_SCREEN_TWO_BUFFERS_H
#define I8080_UI_PIXEL_SCREEN_TWO_BUFFERS_H

#include "Emulator\I8080.h"
#include "UI\Widget\I8080.Widget.h"
#include "PBO.h"
#include <string>



class Widget_PixelScreenTwoBuffers : public I8080_Widget
{
public:
	Widget_PixelScreenTwoBuffers(I8080* processor);
	~Widget_PixelScreenTwoBuffers();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;
private:
	I8080* processor;
	PBO* pbo = nullptr;
	unsigned char* bufferPixelScreen = nullptr;

	float ColorsLine[4] = { 0.f,0.f,0.f,0.2f };
	bool DrawLines = false;
	int ThiknessLines = 1;
	int Ratio_Mode = 0;

	const char* info{
		u8"����: 0x06  \n"
		u8"����������: 256�256  \n"
		u8"���������� ������: 256 (���������� �� ���������� ������ RGB[0bRRGGGBBB])   \n"
		"\n"
		u8"�������� ������ �����������:   \n"
		u8"		1. �������� � ���� 0x06 ����� (0 - 3) 0 - ���������� �������, 1 - ��������� �������, 2 - �������� ������, 3 - ��������� ������ \n"
		u8"		���� ������ ����� (2) ��� (3) �� �������� �������\n"
		u8"		2. �������� � ���� 0x06 ����� ������  (0 - 255)\n"
		u8"		3. �������� � ���� 0x06 ����� ������� (0 - 255)\n"
		u8"		���� ������ ����� (1) �� �������� out 0x06 � �������� �������� �������\n"
		u8"		4. �������� � ���� 0x06 ���� � ������� 0bRRGGGBBB\n"
	};
};


#endif // !I8080_UI_PIXEL_SCREEN_TWO_BUFFERS_H
