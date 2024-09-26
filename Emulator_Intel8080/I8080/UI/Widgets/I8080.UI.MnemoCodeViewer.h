#ifndef I8080_UI_MNEMOCODE_VIEWER_H
#define I8080_UI_MNEMOCODE_VIEWER_H


#include "Emulator\I8080.h"
#include "UI\Widget\I8080.Widget.h"
#include <string>
#include "DataStructures\TypesCommand.h"


class Widget_MnemocodeViewer : public I8080_Widget
{
public:
	Widget_MnemocodeViewer(I8080* processor, TranslatorOutput* translator);
	~Widget_MnemocodeViewer();
	void Draw() override;
	void Update() override;

	void FollowCursorPC();
	void FollowCursor(int position);

	std::string Save() override;
	void Load(const std::string& Data) override;
private:
	I8080* processor;
	TranslatorOutput* translator;

	int pos_follow = 0;
}; 


#endif // !I8080_UI_MNEMOCODE_VIEWER_H
