#include "UI/AuthorPopup/AuthorPopup.h"


AuthorPopup::AuthorPopup() {
	Backend.ReadFromMemoryWithAlpha(Author_Backend);
	Close.ReadFromMemoryWithAlpha(Author_Close);
	EyeTransparent.ReadFromMemoryWithAlpha(Author_EyeTransparent);
	Front.ReadFromMemoryWithAlpha(Author_Front);
	LeftEye.ReadFromMemoryWithAlpha(Author_LeftEye);
	RightEye.ReadFromMemoryWithAlpha(Author_RightEye);
}

AuthorPopup::~AuthorPopup()
{
}

void AuthorPopup::Open() {
	isOpen = true;
}

void AuthorPopup::Draw() {
	if (!isOpen)
		return;

	ImGui::OpenPopup(u8"О программе");

	static const ImGuiWindowFlags flagsWindow =
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoScrollbar;

	ImVec2 center = ImGui::GetMainViewport()->GetCenter();

	ImVec2 size = ImGui::GetMainViewport()->WorkSize;

	float width_window = ImGui::CalcTextSize(u8"Чё то какая-то инфа в одну строчку должна вмешаться в это окно?!?!?!?!?!?!??!?!?!?!!&!.").x;
	float height_window = ImGui::GetTextLineHeight() * 18.f;
	ImGui::SetNextWindowSize(ImVec2(width_window, height_window));


	float asp = (height_window-70) / SizePicture.y;

	ImVec2 SizeImage_asp = ImVec2(SizePicture.x * asp, SizePicture.y * asp);


	ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	if (ImGui::BeginPopupModal(u8"О программе", &isOpen, flagsWindow)) {


		center.x -= ImGui::GetCurrentWindow()->Size.x / 2;
		center.y -= ImGui::GetCurrentWindow()->Size.y / 2;
		ImGui::GetCurrentWindow()->Pos = center;

		ImGui::BeginChild("left Author", ImVec2(SizeImage_asp.x + 20, 0));

		ImVec2 aa = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ aa.x + 20, aa.y + 20 });
		aa = ImGui::GetCursorPos();

		ImGui::Image((ImTextureID)(intptr_t)Backend.GetTextureID(), SizeImage_asp);
		ImGui::SetCursorPos(aa);
		ImGui::Image((ImTextureID)(intptr_t)EyeTransparent.GetTextureID(), SizeImage_asp);


		DrawEyes(aa, SizeImage_asp,asp);


		ImGui::SetCursorPos(aa);
		ImGui::Image((ImTextureID)(intptr_t)Front.GetTextureID(), SizeImage_asp);

		if (glfwGetMouseButton(OpenglWindow::Vars::window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			ImGui::SetCursorPos(aa);
			ImGui::Image((ImTextureID)(intptr_t)Close.GetTextureID(), SizeImage_asp);
		}

		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("Right Author", ImVec2(0, 0));

		aa = ImGui::GetCursorPos();
		aa.x += 17;
		aa.y += 20;
		ImGui::SetCursorPos(aa);

		ImGui::TextWrapped(u8"Программа была написанна под впечетлением от эмулятора М.В.Рожкова. Приятного использования)");
		ImGui::Text("");

		TextCenteredOnLine(u8"Над программой работали:",0,0);
		ImGui::Text("");
		aa = ImGui::GetCursorPos();
		aa.x += 17;
		ImGui::SetCursorPos(aa);
		ImGui::Text(u8"Автор:        Коржунов А.С.");
		aa = ImGui::GetCursorPos();
		aa.x += 17;
		ImGui::SetCursorPos(aa);
		ImGui::Text(u8"Тестировщик:  Эберле В.С.");
		aa = ImGui::GetCursorPos();
		aa.x += 17;
		ImGui::SetCursorPos(aa);
		ImGui::Text(u8"Науч. рук. :  Чередниченко О.М.");
		ImGui::Text("");

		TextCenteredOnLine(u8"Мои контакты:", 0, 0);

		aa = ImGui::GetCursorPos();
		aa.x += 17;
		ImGui::SetCursorPos(aa);
		ImGui::Text("Github: ");
		ImGui::SameLine();
		if (ImGui::Button("github.com/seedLBI/Emulator-Intel8080")) {
			ShellExecute(0, 0, L"https://github.com/seedLBI/Emulator-Intel8080", 0, 0, SW_SHOW);
		}
		aa = ImGui::GetCursorPos();
		aa.x += 17;
		ImGui::SetCursorPos(aa);
		ImGui::Text(u8"Вк:     ");
		ImGui::SameLine();
		if (ImGui::Button("vk.com/seedlbi")) {
			ShellExecute(0, 0, L"https://vk.com/seedlbi", 0, 0, SW_SHOW);
		}


		ImGui::EndChild();



		

		

		


	}

	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}


void AuthorPopup::DrawEyes(ImVec2 PosDraw, const ImVec2& SizeImage, const float& aspect) {

	ImVec2 Mouse = { - PosDraw.x - SizeImage.x - 143 * aspect + ImGui::GetMousePos().x, -PosDraw.y - SizeImage.y - 20* aspect + ImGui::GetMousePos().y };

	ImVec2 LeftEyeOffset{ 263* aspect,(71)* aspect };
	ImVec2 RightEyeOffset{ 343* aspect,(86)* aspect };

	ImVec2 LeftEyeCenter{ 273 * aspect,(70) * aspect };
	ImVec2 RightEyeCenter{ 352 * aspect,(86) * aspect };


	ImVec2 LeftDeltaCenter{ LeftEyeCenter.x - Mouse.x,LeftEyeCenter.y - Mouse.y };
	ImVec2 RightDeltaCenter{ RightEyeCenter.x - Mouse.x,RightEyeCenter.y - Mouse.y };

	float distanceLeft = sqrtf(LeftDeltaCenter.x * LeftDeltaCenter.x + LeftDeltaCenter.y * LeftDeltaCenter.y);
	float distanceRight = sqrtf(RightDeltaCenter.x * RightDeltaCenter.x + RightDeltaCenter.y * RightDeltaCenter.y);

	ImVec2 LeftDeltaCenterNormal{ LeftDeltaCenter.x/ distanceLeft,LeftDeltaCenter.y/ distanceLeft };
	ImVec2 RightDeltaCenterNormal{ RightDeltaCenter.x/ distanceRight,RightDeltaCenter.y/ distanceRight };

	ImVec2 NewLeft = { LeftEyeCenter.x - 1.6f*LeftDeltaCenterNormal.x * (16 - 10) - LeftEyeOffset.x,LeftEyeCenter.y - LeftDeltaCenterNormal.y * (16 - 10) - LeftEyeOffset.y };
	ImVec2 NewRight = { RightEyeCenter.x - 1.6f * RightDeltaCenterNormal.x * (15 - 10) - RightEyeOffset.x,RightEyeCenter.y - RightDeltaCenterNormal.y * (15 - 10) - RightEyeOffset.y };



	ImGui::SetCursorPos({ PosDraw.x + NewLeft.x, PosDraw.y + NewLeft.y });
	ImGui::Image((ImTextureID)(intptr_t)LeftEye.GetTextureID(), SizeImage);

	ImGui::SetCursorPos({ PosDraw.x + NewRight.x, PosDraw.y + NewRight.y });
	ImGui::Image((ImTextureID)(intptr_t)RightEye.GetTextureID(), SizeImage);
}