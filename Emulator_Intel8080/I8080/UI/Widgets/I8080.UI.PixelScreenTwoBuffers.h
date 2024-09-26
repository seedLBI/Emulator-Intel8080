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
		u8"Порт: 0x06  \n"
		u8"Разрешение: 256х256  \n"
		u8"Количество цветов: 256 (кодируются по упрощённой модели RGB[0bRRGGGBBB])   \n"
		"\n"
		u8"Протокол обмена информацией:   \n"
		u8"		1. Записать в порт 0x06 режим (0 - 3) 0 - Установить пиксель, 1 - Прочитать пиксель, 2 - Поменять буферы, 3 - отчистить буферы \n"
		u8"		Если выбран режим (2) или (3) то начинать сначала\n"
		u8"		2. Записать в порт 0x06 номер строки  (0 - 255)\n"
		u8"		3. Записать в порт 0x06 номер столбца (0 - 255)\n"
		u8"		Если выбран режим (1) то вызываем out 0x06 и получаем значение пикселя\n"
		u8"		4. Записать в порт 0x06 цвет в формате 0bRRGGGBBB\n"
	};
};


#endif // !I8080_UI_PIXEL_SCREEN_TWO_BUFFERS_H
