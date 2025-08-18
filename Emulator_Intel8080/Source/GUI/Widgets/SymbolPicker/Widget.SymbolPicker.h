#ifndef I8080_UI_SYMBOL_PICKER_H
#define I8080_UI_SYMBOL_PICKER_H


#include <cmath>
#include <string>

#include "Core/Widget/I8080.Widget.h"

#include "Utils/ColorUtilities.h"
#include "Utils/Text/Text.h"

#include "GUI/Widgets/CodeEditor/TextEditor.h"

#include "ThirdParty/IconFontCppHeaders/IconsFontAwesome6.h"



class Widget_SymbolPicker : public I8080_Widget
{
public:
	Widget_SymbolPicker(TextEditor* editor);
	~Widget_SymbolPicker();

	void Draw() override;
	void Update() override;

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;
private:
	TextEditor* editor;
};





#endif // !I8080_UI_SYMBOL_PICKER_H
