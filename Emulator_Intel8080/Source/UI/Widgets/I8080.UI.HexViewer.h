#ifndef I8080_UI_HEX_VIEWER_H
#define I8080_UI_HEX_VIEWER_H

#include "imgui_memory_editor.h"
#include "Emulator\Processors\Intel8080\I8080.h"
#include "UI\Widget\I8080.Widget.h"
#include <string>
#include <vector>
#include "DataStructures\TypesCommand.h"


class Widget_HexViewer : public I8080_Widget
{
public:
	Widget_HexViewer(I8080* processor, TranslatorOutput* translator);
	~Widget_HexViewer();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;
private:
	MemoryEditor mem_edit;
	I8080* processor;
	TranslatorOutput* translator;
	
};






#endif // !I8080_UI_HEX_VIEWER_H