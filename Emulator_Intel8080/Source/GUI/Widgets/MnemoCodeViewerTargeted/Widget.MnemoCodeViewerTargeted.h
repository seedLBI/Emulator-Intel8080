#ifndef I8080_UI_MNEMOCODEVIEWERTARGETED
#define I8080_UI_MNEMOCODEVIEWERTARGETED

#include <string>


#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Widget/I8080.Widget.h"
#include "Core/Theme/interface/IThemeLoadable.h"
#include "Core/Setting/interfaces/ISettingObject.h"

#include "Utils/ImGui/Utils.ImGui.h"

#include "DataStructures/TypesCommand.h"

#include "GUI/HighlighterInstruction/I8080/I8080.HighlighterInstruction.h"



class Widget_MnemocodeViewerTargeted : public I8080_Widget, public IThemeLoadable
{
public:
	Widget_MnemocodeViewerTargeted(I8080* processor, TranslatorOutput* translator);
	~Widget_MnemocodeViewerTargeted();
	void Draw() override;
	void Update() override;

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;

	std::vector<NamedColor> GetDefaultLightColors() override;
	std::vector<NamedColor> GetDefaultDarkColors() override;
	void LoadColors() override;

private:

	enum TargetType {
		PC,
		SP,
		HL,
		DE,
		BC
	};

	std::string TargetType_to_str(const TargetType& _target);
	TargetType  str_to_TargetType(const std::string& str_target);

	TargetType target = TargetType::PC;

	I8080* processor;
	TranslatorOutput* translator;
	ImColor color_target = ImVec4(1.0f, 0.3f, 0.3f, 0.45f);
};



#endif // !I8080_UI_MNEMOCODEVIEWERTARGETED
