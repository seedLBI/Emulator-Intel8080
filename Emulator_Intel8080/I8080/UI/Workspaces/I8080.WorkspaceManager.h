#ifndef I8080_WORKSPACE_MANAGER_H
#define I8080_WORKSPACE_MANAGER_H

#include "Config_Compilier.h"
#include "UI\Workspaces\I8080.Workspace.h"
#include "Utils\ImGui.Utils.h"
#include "IconFontCppHeaders/IconsFontAwesome6.h"
#include "UI\Widget\I8080.WidgetManager.h"
#include "SaveSystem\SaveSystem.h"
#include <string>
#include <vector>

class I8080_WorkspaceManager : SaveSystem {
public:
	I8080_WorkspaceManager(I8080_WidgetManager* widget_manager);
	~I8080_WorkspaceManager();

	void		AddWorkspace(const std::string& Name, const bool& LoadStyle);

	std::string GetNameCurrentWorkspace();
	int			GetCount();
	int			GetIndexChoosed();

	void		SetNeedLoad();
	void		SetIndexChoosed(int indexToChoose);

	void		LoadChoosed();
	void		LoadNext();


	std::string Save() override;
	void		Load(const std::string& Data) override;

	void		Draw();
	void		Update();

private:
	I8080_WidgetManager* widget_manager = nullptr;

	std::vector<I8080_Workspace> workspaces;

	ImU32 ColorForeground = ImColor(ImVec4(1.f, 1.f, 1.f, 1.f));

	int IndexChoosed = 0;

	int IndexDrag = 0;
	bool Draging = false;

	bool NeedLoadIni = false;

	bool OpenedPopupCreation = false;
	bool OpenedPopupSetting  = false;
	int IndexSetting = 0;

	bool DrawPopupCreation(char* name, int name_size);
	bool DrawPopupSetting(int index, char* name, int name_size);

	bool DrawEdit(ImGuiWindow* imgui_window, ImDrawList* draw_list,const int& index);
	bool DrawDelete(ImGuiWindow* imgui_window, ImDrawList* draw_list, const int& index);
	bool DrawText(const int& index);

	bool DrawAddNewWorkspace(ImDrawList* draw_list);
};


#endif // !I8080_WORKSPACE_MANAGER_H

