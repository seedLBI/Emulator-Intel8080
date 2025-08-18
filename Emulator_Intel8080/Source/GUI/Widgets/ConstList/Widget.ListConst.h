#ifndef I8080_UI_CONST_LIST_H
#define I8080_UI_CONST_LIST_H


#define _NO_COM

#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Widget/I8080.Widget.h"

#include <string>



class Widget_ListConst : public I8080_Widget {
public:
	Widget_ListConst(TranslatorOutput* translator);
	~Widget_ListConst();
	void Draw() override;
	void Update() override;

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;
private:
	TranslatorOutput* translator;
};






#endif // !I8080_UI_CONST_LIST_H
