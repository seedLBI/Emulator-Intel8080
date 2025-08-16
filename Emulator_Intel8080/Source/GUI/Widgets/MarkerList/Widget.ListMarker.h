#ifndef I8080_UI_MARKER_LIST_H
#define I8080_UI_MARKER_LIST_H

#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Widget/I8080.Widget.h"

#include "GUI/Notification/NotificationManager.h"
#include "GUI/Widgets/MnemoCodeViewer/Widget.MnemoCodeViewer.h"

#include <string>

class Widget_ListMarker : public I8080_Widget
{
public:
	Widget_ListMarker(I8080* processor, TranslatorOutput* translator, Widget_MnemocodeViewer* MnemocodeViewer, NotificationManager* notificationManager);
	~Widget_ListMarker();
	void Draw() override;
	void Update() override;

	nlohmann::json Save() override;
	void Load(const nlohmann::json& Data) override;
private:
	I8080* processor;
	TranslatorOutput* translator;
	Widget_MnemocodeViewer* MnemocodeViewer;
	NotificationManager* notificationManager;
};






#endif // !I8080_UI_MARKER_LIST_H
