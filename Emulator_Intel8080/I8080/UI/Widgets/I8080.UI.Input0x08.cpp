#include "I8080.UI.Input0x08.h"


Widget_Input0x08::Widget_Input0x08(I8080* processor) : I8080_Widget(u8"���� �����") {
	this->processor = processor;
}
Widget_Input0x08::~Widget_Input0x08() {

}


void Widget_Input0x08::SendValue_to_Port(const std::string& str_value) {
	if (str_value.size() != 0) {
		unsigned int value = std::stoi(str_value);
		if (value < 256)
			processor->InputAnswer2Port(value);
	}
	Focus_ones = true;
}



int Widget_Input0x08::InputTextCallback(ImGuiInputTextCallbackData* data) {
	// ���������, ��� �������� ������ - ��� ����� ��� backspace
	if (data->EventFlag == ImGuiInputTextFlags_CallbackCharFilter) {
		// ���� ������ �� ����� � �� backspace, ���������� ����
		if (data->EventChar < '0' || data->EventChar > '9') {
			return 1;  // ������������ ������, �������� ����
		}
	}

	// ��������� ������� �������� � ������
	if (data->EventFlag == ImGuiInputTextFlags_CallbackEdit) {
		if (data->BufTextLen > 0) {
			// ����������� ������ � �����
			int value = atoi(data->Buf);

			// ���� ����� ������ 255, ������� ��������� ������
			if (value > 255) {
				if (data->BufTextLen > 0) {
					data->Buf[data->BufTextLen - 1] = '\0';  // ������� ��������� ������
					data->BufDirty = true;  // ��������, ��� ����� ��� �������
					data->BufTextLen--;  // ������������ ����� ������
				}
			}

			// ��������� �� ������� ������� �����
			if (data->BufTextLen > 1 && data->Buf[0] == '0') {
				// ������� ������ ������, ���� ��� �� ������������ ������ "0"
				for (int i = 0; i < data->BufTextLen; ++i) {
					data->Buf[i] = data->Buf[i + 1]; // �������� �����
				}
				data->Buf[data->BufTextLen - 1] = '\0';  // ������� ��������� ������
				data->BufTextLen--;  // ������������ ����� ������
				data->BufDirty = true;  // ��������, ��� ����� ��� �������
			}

		}
	}

	return 0;  // ���������� 0, ���� ��� ��
}




void Widget_Input0x08::Draw() {



	ImVec4 ColorBG = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
	float t = 0.f;

	float Lerp = pow(0.01, OpenglWindow::GetDeltaTime());

	if (processor->IsWaitingPortInput()) {
		float t = abs( sin(glfwGetTime() * 8.f) * 0.2f + 0.2f);
		ColorBG.x = 0.f;
		ColorBG.y = t;
		ColorBG.z = 0.f;
	}
	else {
		Focus_ones = true;
	}

	if (processor->IsWaitingPortInput() && Focus_ones) {
		if (GetFlagShow() == false)
			SetFlagShow(true);

		MakeActiveCurrentWidget();
	}

	if (GetFlagShow() == false)
		return;


	ImVec4 NewColorBG = ImVec4((ColorBG.x) , (ColorBG.y), ColorBG.z, 1.0f);

 	ImGui::PushStyleColor(ImGuiCol_WindowBg, NewColorBG);

	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_AlwaysAutoResize)) {

		if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort)) {
			ImGui::BeginTooltip();
			ImGui::Text(info);
			ImGui::EndTooltip();
		}

		ImGui::Text(u8"���� �������� � ���� 0x08");
		ImGui::Separator();

		static char buf2[4] = "";

		if (Focus_ones && processor->IsWaitingPortInput()){
			Focus_ones = false;
			ImGui::SetKeyboardFocusHere(0);
		}

		std::string str_value(buf2);


		if (ImGui::InputText(
			u8"�������� �� 0 �� 255",
			buf2,
			4,
			ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_NoLabel | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCharFilter | ImGuiInputTextFlags_CallbackEdit,
			InputTextCallback)
			) 
		{

			SendValue_to_Port(str_value);
			for (int i = 0; i < 4; i++)
				buf2[i] = 0;
		}

		
		ImGui::SameLine();

		if (ImGui::Button(u8"����")) {
			if (processor->IsWaitingPortInput()){
				SendValue_to_Port(str_value);
			}

			for (int i = 0; i < 4; i++)
				buf2[i] = 0;
		}

		ImGui::SameLine();

		HelpMarker(u8"������� �������� �� 0 �� 255, � ����� ������ � ���� �� ������ �������� ������.");



		ImGui::End();
	}

	ImGui::PopStyleColor();

}
void Widget_Input0x08::Update() {
	UpdateActive();
}

std::string Widget_Input0x08::Save() {
	std::string output = "";
	output += MakeBegin(2);
	output += MakeSaveItem(std::string("Flag_Show"), std::to_string(GetFlagShow()));
	output += MakeSaveItem(std::string("Flag_Active"), std::to_string(WindowIsVisiable()));
	return output;
}

void Widget_Input0x08::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);

	std::vector<std::string> Lines = split(Data, "\n");
	for (int i = 0; i < Lines.size(); i++) {
		std::vector<std::string> info = SplitLine(Lines[i]);

		std::string name_arg = info[0];
		std::string value_arg = info[1];

		if (name_arg == "Flag_Show")
			SetFlagShow(stoi(value_arg));
		else if (name_arg == "Flag_Active") {
			if (stoi(value_arg) == 1)
				SetActive();
		}
		else
			std::cout << "Unknown name argument for widget: " << name_arg << std::endl;
	}
}
