#ifndef I8080_UI_COLOR_PICKER_H
#define I8080_UI_COLOR_PICKER_H


#include "Core/Widget/I8080.Widget.h"
#include "Utils/ColorUtilities.h"
#include "Utils/Text/Text.h"
#include "GUI/Widgets/CodeEditor/TextEditor.h"
#include "ThirdParty/IconFontCppHeaders/IconsFontAwesome6.h"

#include <cmath>
#include <string>

class Widget_ColorPicker : public I8080_Widget
{
public:
	Widget_ColorPicker(TextEditor* editor);
	~Widget_ColorPicker();

	void Draw() override;
	void Update() override;

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;
private:
	TextEditor* editor;
};




#endif // !I8080_UI_COLOR_PICKER_H
