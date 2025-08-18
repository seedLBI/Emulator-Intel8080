#ifndef I8080_UI_HEX_VIEWER_H
#define I8080_UI_HEX_VIEWER_H

#include <string>
#include <vector>

#include "ThirdParty/ImGui/imgui_memory_editor.h"
#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Widget/I8080.Widget.h"
#include "GUI/Widgets/MnemoCodeViewer/Widget.MnemoCodeViewer.h"
#include "DataStructures/TypesCommand.h"




class Widget_HexViewer : public I8080_Widget
{
public:
	Widget_HexViewer(I8080* processor, TranslatorOutput* translator, Widget_MnemocodeViewer* widget_MnemocodeViewer);
	~Widget_HexViewer();
	void Draw() override;
	void Update() override;


	MemoryEditor* GetPtrMemoryEditor();

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;
private:
	MemoryEditor mem_edit;
	I8080* processor;
	Widget_MnemocodeViewer* widget_MnemocodeViewer;
	TranslatorOutput* translator;
	
};






#endif // !I8080_UI_HEX_VIEWER_H
