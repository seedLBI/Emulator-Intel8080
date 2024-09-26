#ifndef I8080_UI_CONST_LIST_H
#define I8080_UI_CONST_LIST_H

#include "Emulator\I8080.h"
#include "UI\Widget\I8080.Widget.h"
#include <string>

class Widget_ConstList : public I8080_Widget
{
public:
	Widget_ConstList(TranslatorOutput* translator);
	~Widget_ConstList();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;
private:
	TranslatorOutput* translator;
};






#endif // !I8080_UI_CONST_LIST_H
