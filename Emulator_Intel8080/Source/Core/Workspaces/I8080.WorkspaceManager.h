#ifndef I8080_WORKSPACE_MANAGER_H
#define I8080_WORKSPACE_MANAGER_H

#include "Config_Compilier.h"

#include "ThirdParty/IconFontCppHeaders/IconsFontAwesome6.h"

#include "Core/Workspaces/I8080.Workspace.h"
#include "Core/Widget/I8080.WidgetManager.h"
#include "Core/Setting/interfaces/ISettingObject.h"
#include "Core/SaveSystem/SaveSystem.h"

#include "Utils/ImGui/Utils.ImGui.h"

#include <string>
#include <vector>

class I8080_WorkspaceManager : public SaveSystem, public ISettingObject {
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
	void		LoadPrevious();
	

	nlohmann::json	Save() override;
	void			Load(const nlohmann::json& Data) override;

	nlohmann::json	SaveSetting() override;
	void			LoadSetting(const nlohmann::json& Data) override;
	void			DrawSetting() override;

	void			Draw();
	void			Update();

private:
	I8080_WidgetManager* widget_manager = nullptr;

	std::vector<I8080_Workspace> workspaces;

	ImU32 ColorForeground = ImColor(ImVec4(1.f, 1.f, 1.f, 1.f));

	int IndexChoosed = 0;

	int IndexDrag = 0;
	bool Draging = false;

	bool NeedLoadIni = false;
	int countLoad = 1;

	bool OpenedPopupCreation = false;
	bool OpenedPopupSetting  = false;
	int IndexSetting = 0;

	bool SaveCurrentWorkspaceBeforeClosingApp = true;

	bool DrawPopupCreation(char* name, int name_size);
	bool DrawPopupSetting(int index, char* name, int name_size);

	bool DrawEdit(ImGuiWindow* imgui_window, ImDrawList* draw_list,const int& index);
	bool DrawDelete(ImGuiWindow* imgui_window, ImDrawList* draw_list, const int& index);
	bool DrawText(const int& index);

	bool DrawAddNewWorkspace(ImDrawList* draw_list);
};


#endif // !I8080_WORKSPACE_MANAGER_H

