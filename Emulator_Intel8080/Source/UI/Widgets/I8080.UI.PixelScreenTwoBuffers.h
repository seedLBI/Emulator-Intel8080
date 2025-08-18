#ifndef I8080_UI_PIXEL_SCREEN_TWO_BUFFERS_H
#define I8080_UI_PIXEL_SCREEN_TWO_BUFFERS_H

#include "Emulator\Processors\Intel8080\I8080.h"
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


	int DrawFrontBuffer = true;

	float ColorsLine[4] = { 0.f,0.f,0.f,0.2f };
	bool DrawLines = false;
	int ThiknessLines = 1;
	int Ratio_Mode = 0;

};


#endif // !I8080_UI_PIXEL_SCREEN_TWO_BUFFERS_H
