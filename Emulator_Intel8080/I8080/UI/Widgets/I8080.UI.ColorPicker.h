#ifndef I8080_UI_COLOR_PICKER_H
#define I8080_UI_COLOR_PICKER_H

#include <cmath>
#include <string>
#include "UI\Widget\I8080.Widget.h"
#include "Utils\ColorUtilities.h"
#include <Utils\TextUtils.h>
#include <IconFontCppHeaders/IconsFontAwesome6.h>
#include "TextEditor.h"


class Widget_ColorPicker : public I8080_Widget
{
public:
	Widget_ColorPicker(TextEditor* editor);
	~Widget_ColorPicker();

	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;
private:
	TextEditor* editor;
};




#endif // !I8080_UI_COLOR_PICKER_H
