#include "WindowManager.h"

WindowManager::WindowManager() : ISettingObject(u8"�����������",u8"�����") {

}

WindowManager::~WindowManager(){
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "WindowManager::~WindowManager()\n";
#endif // !WITH_DEBUG_OUTPUT
}


void WindowManager::DrawSetting() {

	ISettingObject::DrawBegin();

	if (ImGui::RadioButton(u8"������� �����", IsWindowed))
		SetWindowed();

	ImGui::SameLine();

	if (ImGui::RadioButton(u8"������������� �����", !IsWindowed))
		SetFullscreen();

	ImGui::SameLine();
	HelpMarker(u8"����������� ����� ������� ����.");

	if (ImGui::RadioButton(u8"VSync", VSync_state))
		ToggleVSync();

	ImGui::SameLine();
	HelpMarker(u8"������������ �������������.");


	ImGuiContext& g = *GImGui;
	ImGuiIO& io = g.IO;

	ImGui::Text(u8"������� ���-�� ������ � ���. : %.1f", io.Framerate);

	static std::vector<std::string> items = { "30","45","60","75","90","120","144","165", u8"�������������" };

	std::string preview_value = std::to_string((int)OpenglWindow::Vars::FPS_target);
	if ((int)OpenglWindow::Vars::FPS_target == 32000){
		preview_value = u8"�������������";
	}


	if (ImGui::BeginCombo(u8"FPS", preview_value.c_str(), ImGuiComboFlags_WidthFitPreview)) {

		for (int i = 0; i < items.size(); i++)
		{
			bool selected = items[i] == preview_value;
			if (preview_value == "32000")
				selected = true;


			if (ImGui::Selectable(items[i].c_str(), &selected)) {
				if (items[i] == u8"�������������")
				{
					OpenglWindow::Vars::FPS_target = 32000;
				}
				else {
					OpenglWindow::Vars::FPS_target = stoi(items[i]);
				}
			}

			if (selected)
				ImGui::SetItemDefaultFocus();
		}

		ImGui::EndCombo();
	}
	ImGui::SameLine();
	HelpMarker(u8"���-�� ������ � �������\n����� �� ������ �� ������������������ ��������,\n�� ������ �� ������������ ������ � ������ �����������");
}


bool WindowManager::SetFullscreen() {
	if (IsWindowed) {
		IsWindowed = false;


		glfwGetWindowPos(OpenglWindow::Vars::window, &LastPos_x, &LastPos_y);
		glfwGetWindowSize(OpenglWindow::Vars::window, &LastSize_x, &LastSize_y);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwSetWindowMonitor(OpenglWindow::Vars::window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

		return true;
	}

	return false;
}
bool WindowManager::SetWindowed() {
	if (!IsWindowed) {
		IsWindowed = true;

		glfwSetWindowMonitor(OpenglWindow::Vars::window, NULL, LastPos_x, LastPos_y, LastSize_x, LastSize_y, 0);

		return true;
	}

	return false;
}
void WindowManager::ToggleFullscreen() {
	if (SetFullscreen())
		return;
	SetWindowed();
}
bool WindowManager::GetStateFullscreen() {
	return IsWindowed == false;
}


void WindowManager::SetMaximaze() {
	glfwMaximizeWindow(OpenglWindow::Vars::window);
}

void WindowManager::SetPosition(const int& posX,const int& posY) {
	glfwSetWindowPos(OpenglWindow::Vars::window, posX, posY);
}
void WindowManager::SetSize(const int& width, const int& height) {
	glfwSetWindowSize(OpenglWindow::Vars::window, width, height);
}


void WindowManager::DisableVSync() {
	VSync_state = false;
	glfwSwapInterval(0);
}
void WindowManager::EnableVSync() {
	VSync_state = true;
	glfwSwapInterval(1);
}
void WindowManager::ToggleVSync() {
	VSync_state = !VSync_state;
	if (VSync_state)
		EnableVSync();
	else
		DisableVSync();
}
void WindowManager::SetVSync(bool flag) {
	if (flag)
		EnableVSync();
	else
		DisableVSync();
}
bool WindowManager::GetStateVSync() {
	return VSync_state;
}




std::string WindowManager::SaveSetting() {
	int pos_x = 0, pos_y = 0;
	int size_x = 0, size_y = 0;
	glfwGetWindowPos(OpenglWindow::Vars::window, &pos_x, &pos_y);
	glfwGetWindowSize(OpenglWindow::Vars::window, &size_x, &size_y);

	std::string
		str_pos_x = std::to_string(pos_x),
		str_pos_y = std::to_string(pos_y),
		str_size_x = std::to_string(size_x),
		str_size_y = std::to_string(size_y),
		str_is_maximazed = std::to_string(glfwGetWindowAttrib(OpenglWindow::Vars::window, GLFW_MAXIMIZED)),
		str_is_fullscreen = std::to_string(IsWindowed == false),
		str_fps = std::to_string((int)OpenglWindow::Vars::FPS_target),
		str_vsync = std::to_string(VSync_state);


	std::string save_window = save_MakeBegin(8);
	save_window += save_MakeItem("Position X", str_pos_x);
	save_window += save_MakeItem("Position Y", str_pos_y);
	save_window += save_MakeItem("Size Width", str_size_x);
	save_window += save_MakeItem("Size Height", str_size_y);
	save_window += save_MakeItem("IsMaximazed", str_is_maximazed);
	save_window += save_MakeItem("IsFullscreen", str_is_fullscreen);
	save_window += save_MakeItem("FPS target", str_fps);
	save_window += save_MakeItem("VSync", str_vsync);


	return save_window;
}

void WindowManager::LoadSetting(const std::string& Data) {

	auto info = load_TokenizeData(Data);


	int Position_X = -1, Position_Y = -1, Size_Width = -1, Size_Height = -1;


	for (int i = 0; i < info.size(); i++) {

		if (info[i].NameVar == "Position X") {
			Position_X = stoi(info[i].ValueVar);
		}
		else if (info[i].NameVar == "Position Y") {
			Position_Y = stoi(info[i].ValueVar);
		}
		else if (info[i].NameVar == "Size Width") {
			Size_Width = stoi(info[i].ValueVar);
		}
		else if (info[i].NameVar == "Size Height") {
			Size_Height = stoi(info[i].ValueVar);
		}
		else if (info[i].NameVar == "IsMaximazed") {
			if (stoi(info[i].ValueVar))
				SetMaximaze();
		}
		else if (info[i].NameVar == "IsFullscreen") {
			if (stoi(info[i].ValueVar))
				SetFullscreen();
		}
		else if (info[i].NameVar == "FPS target") {
			OpenglWindow::Vars::FPS_target = stoi(info[i].ValueVar);
		}
		else if (info[i].NameVar == "VSync") {
			SetVSync(stoi(info[i].ValueVar));
		}
		else {
			std::cout << "Unknowed save element founded: [" << info[i].NameVar << "] [" << info[i].ValueVar << "]\n";
		}
	}

	CheckPosition(Position_X, Position_Y);
	CheckSize(Size_Width, Size_Height);

	if (Position_X != -1 && Position_Y != -1) {
		SetPosition(Position_X, Position_Y);
	}
	if (Size_Width != -1 && Size_Height != -1) {
		SetSize(Size_Width, Size_Height);
	}


}

void WindowManager::CheckPosition(int& Position_X, int& Position_Y) {
	if (Position_X < 0)
		Position_X = 100;

	if (Position_Y < 0)
		Position_Y = 100;
}

void WindowManager::CheckSize(int& Size_X, int& Size_Y) {
	if (Size_X < 1280)
		Size_X = 1280;

	if (Size_Y < 720)
		Size_Y = 720;
}

