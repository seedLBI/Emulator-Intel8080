#ifndef I8080_UI_VAR_LIST_H
#define I8080_UI_VAR_LIST_H

#include "Emulator\I8080.h"
#include "UI\Widget\I8080.Widget.h"
#include <string>


class Widget_VarList : public I8080_Widget
{
public:
	Widget_VarList(I8080* processor, TranslatorOutput* translator);
	~Widget_VarList();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;
private:
	I8080* processor;
	TranslatorOutput* translator;
};




#endif // !I8080_UI_VAR_LIST_H
