#ifndef I8080_UI_MNEMOCODEVIEWERTARGETED
#define I8080_UI_MNEMOCODEVIEWERTARGETED


#include "Emulator\Processors\Intel8080\I8080.h"
#include "UI\Widget\I8080.Widget.h"
#include "Utils/ImGui.Utils.h"
#include <string>
#include "DataStructures\TypesCommand.h"
#include "UI/Setting/ISettingObject.h"
#include "UI/HighlighterInstruction/I8080/I8080.HighlighterInstruction.h"
#include "UI/Theme/interface/IThemeLoadable.h"


class Widget_MnemocodeViewerTargeted : public I8080_Widget, public IThemeLoadable
{
public:
	Widget_MnemocodeViewerTargeted(I8080* processor, TranslatorOutput* translator);
	~Widget_MnemocodeViewerTargeted();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;

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
