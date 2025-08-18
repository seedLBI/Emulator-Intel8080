#include "WindowManager.h"

WindowManager::WindowManager(GLFWwindow* window, FPS_Timer* fps_timer) : ISettingObject(u8"�����������",u8"�����") {
	this->window = window;
	this->fps_timer = fps_timer;
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
	MyHelpMarker(u8"����������� ����� ������� ����.");

	if (ImGui::RadioButton(u8"VSync", VSync_state))
		ToggleVSync();

	ImGui::SameLine();
	MyHelpMarker(u8"������������ �������������.");


	ImGuiContext& g = *GImGui;
	ImGuiIO& io = g.IO;

	ImGui::Text(u8"������� ���-�� ������ � ���. : %.1f", io.Framerate);

	static std::vector<std::string> items = { "30","45","60","75","90","120","144","165", u8"�������������" };

	

	std::string preview_value = std::to_string((int)fps_timer->GetTargetFPS());

	if ((int)fps_timer->GetTargetFPS() == 0){
		preview_value = u8"�������������";
	}


	if (ImGui::BeginCombo(u8"FPS", preview_value.c_str(), ImGuiComboFlags_WidthFitPreview)) {

		for (int i = 0; i < items.size(); i++)
		{
			bool selected = items[i] == preview_value;
			if (preview_value == "0")
				selected = true;


			if (ImGui::Selectable(items[i].c_str(), &selected)) {
				if (items[i] == u8"�������������")
				{
					fps_timer->SetTargetFPS(0);
				}
				else {
					fps_timer->SetTargetFPS(stoi(items[i]));
				}
			}

			if (selected)
				ImGui::SetItemDefaultFocus();
		}

		ImGui::EndCombo();
	}
	ImGui::SameLine();
	MyHelpMarker(u8"���-�� ������ � �������\n����� �� ������ �� ������������������ ��������,\n�� ������ �� ������������ ������ � ������ �����������");
}


bool WindowManager::SetFullscreen() {

	if (glfwGetWindowMonitor(window))
		return true;

	glfwGetWindowPos(window, &LastPos_x, &LastPos_y);
	glfwGetWindowSize(window, &LastSize_x, &LastSize_y);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	if (!monitor) return false;

	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwSetWindowMonitor(
		window,
		monitor,
		0, 0,                     // ������� ���� �� ��������
		mode->width, mode->height, // ������ �� ���� �����
		mode->refreshRate          // ������� ����������
	);

	IsWindowed = false;

	return true;
}
bool WindowManager::SetWindowed() {


	// ���� ��� � ������� ������ � ������ �� ������
	if (!glfwGetWindowMonitor(window))
		return true;

	// ����������� ���������� �������/�������
	glfwSetWindowMonitor(
		window,
		nullptr,                 // = ������� �����
		LastPos_x, LastPos_y,  // ������ �������
		LastSize_x, LastSize_y, // ������ ������
		0                        // ������������ � ������� ������
	);

	IsWindowed = true;

	return true;
}

void WindowManager::ToggleFullscreen() {
	if (glfwGetWindowMonitor(window)) {
		SetWindowed();
	}
	else {
		SetFullscreen();
	}
}
bool WindowManager::GetStateFullscreen() {
	return glfwGetWindowMonitor(window) != nullptr;
}


void WindowManager::SetMaximaze() {
	glfwMaximizeWindow(window);
}

void WindowManager::SetPosition(const int& posX,const int& posY) {
	glfwSetWindowPos(window, posX, posY);
}
void WindowManager::SetSize(const int& width, const int& height) {
	glfwSetWindowSize(window, width, height);
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




nlohmann::json WindowManager::SaveSetting() {


	nlohmann::json result;

	int pos_x = 0, pos_y = 0;
	int size_x = 0, size_y = 0;
	glfwGetWindowPos(window, &pos_x, &pos_y);
	glfwGetWindowSize(window, &size_x, &size_y);

	result["position.x"] = pos_x;
	result["position.y"] = pos_y;
	result["size.x"] = size_x;
	result["size.y"] = size_y;
	result["is_maximazed"] = glfwGetWindowAttrib(window, GLFW_MAXIMIZED);
	result["is_fullscreen"] = IsWindowed == false;
	result["fps"] = (int)fps_timer->GetTargetFPS();
	result["vsync"] = VSync_state;


	return result;

}

void WindowManager::LoadSetting(const nlohmann::json& Data) {
	int Position_X = -1, Position_Y = -1, Size_Width = -1, Size_Height = -1;

	if (Data.contains("position.x"))
		Position_X = Data["position.x"].get<int>();

	if (Data.contains("position.y"))
		Position_Y = Data["position.y"].get<int>();

	if (Data.contains("size.x"))
		Size_Width = Data["size.x"].get<int>();

	if (Data.contains("size.y"))
		Size_Height = Data["size.y"].get<int>();

	if (Data.contains("is_maximazed")) {
		if (Data["is_maximazed"].get<int>())
			SetMaximaze();
	}

	if (Data.contains("is_fullscreen")) {
		if (Data["is_fullscreen"].get<int>())
			SetFullscreen();
	}

	if (Data.contains("fps"))
		fps_timer->SetTargetFPS(Data["fps"].get<int>());

	if (Data.contains("vsync"))
		SetVSync(Data["vsync"].get<bool>());


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

