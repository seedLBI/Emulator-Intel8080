#ifndef I8080_UI_VAR_LIST_H
#define I8080_UI_VAR_LIST_H

#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Widget/I8080.Widget.h"
#include <string>


class Widget_ListVar : public I8080_Widget
{
public:
	Widget_ListVar(I8080* processor, TranslatorOutput* translator);
	~Widget_ListVar();
	void Draw() override;
	void Update() override;

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;
private:
	I8080* processor;
	TranslatorOutput* translator;
};




#endif // !I8080_UI_VAR_LIST_H
