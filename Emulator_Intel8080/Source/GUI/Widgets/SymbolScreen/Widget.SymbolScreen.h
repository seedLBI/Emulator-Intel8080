#ifndef I8080_UI_SYMBOL_SCREEN_H
#define I8080_UI_SYMBOL_SCREEN_H


#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Widget/I8080.Widget.h"
#include <string>

class Widget_SymbolScreen : public I8080_Widget
{
public:
	Widget_SymbolScreen(I8080* processor);
	~Widget_SymbolScreen();
	void Draw() override;
	void Update() override;

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;
private:
	I8080* processor;

	float ColorsLine[4] = { 1.f,1.f,1.f,0.3 };
	bool DrawLines = true;
	int ThiknessLines = 1;
	int Ratio_Mode = 0;
};


#endif // !I8080_UI_SYMBOL_SCREEN_H

