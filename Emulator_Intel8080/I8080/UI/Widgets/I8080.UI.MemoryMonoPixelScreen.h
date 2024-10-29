#ifndef MEMORYMONOPIXELSCREEN_H
#define MEMORYMONOPIXELSCREEN_H


#include "PBO.h"
#include "Emulator\I8080.h"
#include "Emulator/Disassembler/Disassembler.h"
#include "UI\Widget\I8080.Widget.h"
#include "Utils\ImGui.Utils.h"
#include <string>


// TODO: Доделать
class Widget_MemoryPixelScreen : public I8080_Widget
{
public:
	Widget_MemoryPixelScreen(I8080* processor);
	~Widget_MemoryPixelScreen();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;
private:
	I8080* processor;
	PBO* pbo = nullptr;
	uint8_t* bufferPixelScreen = nullptr;
};




#endif // !MEMORYMONOPIXELSCREEN_H

