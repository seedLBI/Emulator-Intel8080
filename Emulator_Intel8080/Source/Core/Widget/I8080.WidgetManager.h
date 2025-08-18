#ifndef I8080_WIDGET_MANAGER_H
#define I8080_WIDGET_MANAGER_H

#include "I8080.Widget.h"
#include "Core/SaveSystem/SaveSystem.h"
#include "Utils/Timer/Timer.Framerate.h"
#include "Utils/File/File.h"
#include "Utils/Text/Text.h"
#include <vector>


class I8080_WidgetManager : public SaveSystem
{
public:
	I8080_WidgetManager(FPS_Timer* fps_timer);
	~I8080_WidgetManager();

	void Draw();
	void Update();

	void AddWidgetPtr(I8080_Widget* ptr_widget);
	I8080_Widget* GetWidgetPtr(const std::string& NameObject);

	void Load(const nlohmann::json& Data) override;
	nlohmann::json Save() override;

	void LoadVisibilitySettings(std::vector<std::pair<std::string, bool>>);
	std::vector<std::pair<std::string, bool>> GetVisibilitySettings();


	bool GetFlag_AllOpened();

	void CloseAll();
	void OpenAll();

	int GetIndexSaveObject(const std::string& NameObject);



private:
	FPS_Timer* fps_timer = nullptr;
	std::vector<I8080_Widget*> ptr_widgets;

	int indexHelp = -1;


	int FindIndex(std::string nameWidget);
};

#endif // !I8080_WIDGET_MANAGER_H
