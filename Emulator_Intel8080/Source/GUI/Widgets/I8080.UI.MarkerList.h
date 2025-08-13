#ifndef I8080_UI_MARKER_LIST_H
#define I8080_UI_MARKER_LIST_H

#include "Notification/NotificationManager.h"
#include "Emulator/Processors/Intel8080/I8080.h"
#include "UI/Widget/I8080.Widget.h"
#include <string>
#include "UI/Widgets/I8080.UI.MnemoCodeViewer.h"



class Widget_MarkerList : public I8080_Widget
{
public:
	Widget_MarkerList(I8080* processor, TranslatorOutput* translator, Widget_MnemocodeViewer* MnemocodeViewer, NotificationManager* notificationManager);
	~Widget_MarkerList();
	void Draw() override;
	void Update() override;

	std::string Save() override;
	void Load(const std::string& Data) override;
private:
	I8080* processor;
	TranslatorOutput* translator;
	Widget_MnemocodeViewer* MnemocodeViewer;
	NotificationManager* notificationManager;
};






#endif // !I8080_UI_MARKER_LIST_H
