#ifndef I8080_WIDGET_MANAGER_H
#define I8080_WIDGET_MANAGER_H

#include "UI\Widget\I8080.Widget.h"
#include "SaveSystem\SaveSystem.h"
#include "Utils\TextUtils.h"
#include <vector>


class I8080_WidgetManager : public SaveSystem
{
public:
	I8080_WidgetManager();
	~I8080_WidgetManager();

	void Draw();
	void Update();

	void AddWidgetPtr(I8080_Widget* ptr_widget);

	void Load(const std::string& Data) override;
	std::string Save() override;

	void LoadVisibilitySettings(std::vector<std::pair<std::string, bool>>);
	std::vector<std::pair<std::string, bool>> GetVisibilitySettings();


	bool GetFlag_AllOpened();

	void CloseAll();
	void OpenAll();

	int GetIndexSaveObject(const std::string& NameObject);



private:
	std::vector<I8080_Widget*> ptr_widgets;

	int FindIndex(std::string nameWidget);
};

#endif // !I8080_WIDGET_MANAGER_H
