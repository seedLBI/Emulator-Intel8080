#ifndef I8080_UI_SYMBOL_PICKER_H
#define I8080_UI_SYMBOL_PICKER_H


#include "UI\Widget\I8080.Widget.h"
#include "Utils\ColorUtilities.h"
#include <cmath>
#include <string>
#include <Utils\TextUtils.h>
#include <IconFontCppHeaders/IconsFontAwesome6.h>
#include "TextEditor.h"


class Widget_SymbolPicker : public I8080_Widget
{
public:
	Widget_SymbolPicker(TextEditor* editor);
	~Widget_SymbolPicker();

	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;
private:
	TextEditor* editor;
};





#endif // !I8080_UI_SYMBOL_PICKER_H
