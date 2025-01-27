#include "EmulationThread.h"



std::string toString(SpeedMode mode) {
	switch (mode){
	case SpeedMode::Infinity:
		return u8"Infinity";
		break;
	case SpeedMode::Intel4004:
		return u8"Intel4004";
		break;
	case SpeedMode::Intel8008:
		return u8"Intel8008";
		break;
	case SpeedMode::Intel8080:
		return u8"Intel8080";
		break;
	case SpeedMode::Intel8085:
		return u8"Intel8085";
		break;
	case SpeedMode::Intel8086:
		return u8"Intel8086";
		break;
	case SpeedMode::Custom:
		return u8"Custom";
		break;
	default:
		return u8"Unknown";
		break;
	}
}

void EmulationThread::SetControlMode(const ControlMode& mode) {

	if (mode == Control)
		return;

	while (isThreadWorking() == true)
		processor->ActiveFlagStop();

	Control = mode;
}

void EmulationThread::SetSpeedMode(const SpeedMode& mode) {

#ifdef WITH_DEBUG_OUTPUT
	cout << "SetSpeedMode: " << (int)mode << std::endl;
#endif


	if (!UserSpeeds.empty() && mode == Speed){
		if (IndexChoosedCustomSpeedModeLast == IndexChoosedCustomSpeedMode)
			return;
	}
	else if (mode == Speed)
		return;

	ControlMode lastControlMode = Control;


	while (isThreadWorking() == true)
		processor->ActiveFlagStop();

	Control = ControlMode::Stop;



	Speed = mode;


	switch (Speed)
	{
	case SpeedMode::Infinity:
		break;
	case SpeedMode::Intel4004:
		targetTicksPerSecond = 740'000;
		break;
	case SpeedMode::Intel8008:
		targetTicksPerSecond = 800'000;
		break;
	case SpeedMode::Intel8080:
		targetTicksPerSecond = 3'000'000;
		break;
	case SpeedMode::Intel8085:
		targetTicksPerSecond = 6'000'000;
		break;
	case SpeedMode::Intel8086:
		targetTicksPerSecond = 16'000'000;
		break;
	case SpeedMode::Custom:
		targetTicksPerSecond = UserSpeeds[IndexChoosedCustomSpeedMode].targetTicksPerSecond;
		break;
	default:
		break;
	}


	if (flag_ReturnStateAfterChangeSpeed) {

		if (lastControlMode == ControlMode::Continous)
			processor->ResetFlagStop();

		Control = lastControlMode;
	}

	IndexChoosedCustomSpeedModeLast = IndexChoosedCustomSpeedMode;

}


void EmulationThread::WaitThread() {
	while (isThreadWorking()) {}
}

bool EmulationThread::isThreadWorking() {
	return flag_ThreadWorking;
}

EmulationThread::EmulationThread(Processor* processor, Caretaker_Momento* processor_CaretakerMomento) : ISettingObject(u8"��������",u8"��������") {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Creating second thread for processor\n";
#endif

	this->processor = processor;
	this->processor_CaretakerMomento = processor_CaretakerMomento;
	threadObject = new thread(&EmulationThread::ThreadLoop, this);
}

EmulationThread::~EmulationThread() {

}

SpeedMode EmulationThread::GetSpeedMode() {
	return Speed;
}
ControlMode EmulationThread::GetControlMode() {
	return Control;
}

void EmulationThread::ThreadLoop() {

	while (true) {

		if (Control == ControlMode::Continous) {
			flag_ThreadWorking = true;


			if (Speed == SpeedMode::Infinity){

				if (processor->isHistoryModeEnabled()) {
					while (1) {

						processor_CaretakerMomento->Backup();
						processor->NextStepWithHistorySaving();

						if (processor->OnBreakPoint() || *processor->IsStop()) {
							Control = ControlMode::Stop;
							break;
						}
					}
				}
				else {
					while (1) {

						processor->NextStep();

						if (processor->OnBreakPoint() || *processor->IsStop()) {
							Control = ControlMode::Stop;
							break;
						}
					}
				}

			}
			if (Speed != SpeedMode::Infinity){
				auto		startTime		  = std::chrono::high_resolution_clock::now();
				uint64_t	startTicks		  = processor->GetCountTicks();
				long double TimeTickPerSecond = 1.0 / (long double)targetTicksPerSecond;

				if (processor->isHistoryModeEnabled()) {
					while (1) {
						uint64_t						   CurrentTicks = processor->GetCountTicks() - startTicks;
						std::chrono::duration<long double> CurrentTime = std::chrono::high_resolution_clock::now() - startTime;
						uint64_t						   CountTicksNeed = CurrentTime.count() / TimeTickPerSecond;


						if (CurrentTicks <= CountTicksNeed) {
							processor_CaretakerMomento->Backup();
							processor->NextStepWithHistorySaving();
						}

						if (processor->OnBreakPoint() || *processor->IsStop()) {
							Control = ControlMode::Stop;
							break;
						}

					}
				}
				else {
					while (1) {
						uint64_t						   CurrentTicks = processor->GetCountTicks() - startTicks;
						std::chrono::duration<long double> CurrentTime = std::chrono::high_resolution_clock::now() - startTime;
						uint64_t						   CountTicksNeed = CurrentTime.count() / TimeTickPerSecond;


						if (CurrentTicks <= CountTicksNeed) {
							processor->NextStep();

						}

						if (processor->OnBreakPoint() || *processor->IsStop()) {
							Control = ControlMode::Stop;
							break;
						}

					}
				}
			}
			
			flag_ThreadWorking = false;
		}


		this_thread::sleep_for(chrono::milliseconds(100));
	}
}


void EmulationThread::LoadNextSpeed() {
	if (Speed == SpeedMode::Infinity)
		SetSpeedMode(SpeedMode::Intel4004);
	else if (Speed == SpeedMode::Intel4004)
		SetSpeedMode(SpeedMode::Intel8008);
	else if (Speed == SpeedMode::Intel8008)
		SetSpeedMode(SpeedMode::Intel8080);
	else if (Speed == SpeedMode::Intel8080)
		SetSpeedMode(SpeedMode::Intel8085);
	else if (Speed == SpeedMode::Intel8085)
		SetSpeedMode(SpeedMode::Intel8086);
	else if (Speed == SpeedMode::Intel8086) {
		if (UserSpeeds.empty())
			SetSpeedMode(SpeedMode::Infinity);
		else {
			IndexChoosedCustomSpeedMode = 0;
			SetSpeedMode(SpeedMode::Custom);
		}
	}
	else if (Speed == SpeedMode::Custom) {
		if (IndexChoosedCustomSpeedMode + 1 <= UserSpeeds.size() - 1){
			IndexChoosedCustomSpeedMode++;
			SetSpeedMode(SpeedMode::Custom);
		}
		else 
			SetSpeedMode(SpeedMode::Infinity);
	}
}

void EmulationThread::LoadPreviousSpeed() {
	if (Speed == SpeedMode::Intel8086)
		SetSpeedMode(SpeedMode::Intel8085);
	else if (Speed == SpeedMode::Intel8085)
		SetSpeedMode(SpeedMode::Intel8080);
	else if (Speed == SpeedMode::Intel8080)
		SetSpeedMode(SpeedMode::Intel8008);
	else if (Speed == SpeedMode::Intel8008)
		SetSpeedMode(SpeedMode::Intel4004);
	else if (Speed == SpeedMode::Intel4004)
		SetSpeedMode(SpeedMode::Infinity);
	else if (Speed == SpeedMode::Infinity) {
		if (UserSpeeds.empty())
			SetSpeedMode(SpeedMode::Intel8085);
		else {
			IndexChoosedCustomSpeedMode = UserSpeeds.size() - 1;
			SetSpeedMode(SpeedMode::Custom);
		}
	}
	else if (Speed == SpeedMode::Custom){
		if (IndexChoosedCustomSpeedMode - 1 >= 0) {
			IndexChoosedCustomSpeedMode--;
			SetSpeedMode(SpeedMode::Custom);
		}
		else
			SetSpeedMode(SpeedMode::Intel8086);
	}
}


int EmulationThread::InputTextCallback(ImGuiInputTextCallbackData* data) {
	if (data->EventFlag == ImGuiInputTextFlags_CallbackCharFilter) {
		if (data->EventChar < '0' || data->EventChar > '9') {
			return 1;
		}
	}

	if (data->EventFlag == ImGuiInputTextFlags_CallbackEdit) {
		if (data->BufTextLen > 0) {
			uint64_t value = std::stoull(data->Buf);

			if (value > 100'000'000'000) {
				if (data->BufTextLen > 0) {
					data->Buf[data->BufTextLen - 1] = '\0';
					data->BufDirty = true;
					data->BufTextLen--;
				}
			}

			if (data->BufTextLen > 1 && data->Buf[0] == '0') {
				for (int i = 0; i < data->BufTextLen; ++i) {
					data->Buf[i] = data->Buf[i + 1];
				}
				data->Buf[data->BufTextLen - 1] = '\0';
				data->BufTextLen--;
				data->BufDirty = true;
			}

		}
	}

	return 0;  // ���������� 0, ���� ��� ��
}


void EmulationThread::DrawMainMenu() {
	if (Speed == SpeedMode::Infinity)
		ImGui::Text(("  " + std::string(ICON_FA_INFINITY) + u8" ��").c_str());
	else
		ImGui::Text(("  " + TicksToString(targetTicksPerSecond)).c_str());

	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(u8"������������� ����������� �� ���-�� ������, ������� ����� ��������� ��������� �� ������� �������.\n��� ����������� ����� ������ ��� �������� � ����������.");
}

void EmulationThread::DrawSetting() {
	//ISettingObject::DrawBegin();


	//flag_EnableHistory
	ImGui::SeparatorText(u8"������� ����������");

	if (ImGui::RadioButton(u8"�������� ���������� ������� ����������� ����������", processor->isHistoryModeEnabled())) {
		while (isThreadWorking() == true)
			processor->ActiveFlagStop();

		processor->ToggleHistoryMode();
		processor_CaretakerMomento->ClearHistory();
	}
	ImGui::SameLine();
	HelpMarker(u8"��������� ������ ��� ����� ��� �������.\n�� ����������� ������� ������������������ ��������.");


	static int CountMaxHistory = processor_CaretakerMomento->GetMaxCount();

	
	ImGui::Text(u8"������������ ���-�� ������� �������:");
	if (ImGui::SliderInt(u8"SliderMaxCountHistory", &CountMaxHistory, 2, 1'000, "%i", ImGuiSliderFlags_NoLabel)) {
		if (CountMaxHistory < 2)
			CountMaxHistory = 2;

		if (CountMaxHistory > 1000)
			CountMaxHistory = 1000;

		while (isThreadWorking() == true)
			processor->ActiveFlagStop();
		processor_CaretakerMomento->SetMaxCount(CountMaxHistory);
	}

	ImGui::Text("");

	ImGui::SeparatorText(u8"�������� ����������");

	string Selected = "";


	const std::string str_Infinity  = u8"��������������";
	const std::string str_Intel4004 = u8"(740 ���) Intel4004";
	const std::string str_Intel8008 = u8"(800 ���) Intel8008";
	const std::string str_Intel8080 = u8"(3 ���) Intel8080";
	const std::string str_Intel8085 = u8"(6 ���) Intel8085";
	const std::string str_Intel8086 = u8"(16 ���) Intel8086";

	if (Speed      == SpeedMode::Infinity)
		Selected = str_Infinity;
	else if (Speed == SpeedMode::Intel4004)
		Selected = str_Intel4004;
	else if (Speed == SpeedMode::Intel8008)
		Selected = str_Intel8008;
	else if (Speed == SpeedMode::Intel8080)
		Selected = str_Intel8080;
	else if (Speed == SpeedMode::Intel8085)
		Selected = str_Intel8085;
	else if (Speed == SpeedMode::Intel8086)
		Selected = str_Intel8086;
	else if (Speed == SpeedMode::Custom)
		Selected = "(" + TicksToString(UserSpeeds[IndexChoosedCustomSpeedMode].targetTicksPerSecond) + ") " + UserSpeeds[IndexChoosedCustomSpeedMode].name;


	if (ImGui::BeginCombo(u8"��������", Selected.c_str(), ImGuiComboFlags_WidthFitPreview)) {


		if (ImGui::Selectable(str_Infinity.c_str(), Selected == str_Infinity))
			SetSpeedMode(SpeedMode::Infinity);
		if (Selected == str_Infinity)
			ImGui::SetItemDefaultFocus();

		if (ImGui::Selectable(str_Intel4004.c_str(), Selected == str_Intel4004))
			SetSpeedMode(SpeedMode::Intel4004);
		if (Selected == str_Intel4004)
			ImGui::SetItemDefaultFocus();

		if (ImGui::Selectable(str_Intel8008.c_str(), Selected == str_Intel8008))
			SetSpeedMode(SpeedMode::Intel8008);
		if (Selected == str_Intel8008)
			ImGui::SetItemDefaultFocus();

		if (ImGui::Selectable(str_Intel8080.c_str(), Selected == str_Intel8080))
			SetSpeedMode(SpeedMode::Intel8080);
		if (Selected == str_Intel8080)
			ImGui::SetItemDefaultFocus();

		if (ImGui::Selectable(str_Intel8085.c_str(), Selected == str_Intel8085))
			SetSpeedMode(SpeedMode::Intel8085);
		if (Selected == str_Intel8085)
			ImGui::SetItemDefaultFocus();

		if (ImGui::Selectable(str_Intel8086.c_str(), Selected == str_Intel8086))
			SetSpeedMode(SpeedMode::Intel8086);
		if (Selected == str_Intel8086)
			ImGui::SetItemDefaultFocus();

		
		ImGuiWindow* imgui_window = ImGui::GetCurrentWindow();
		ImDrawList* draw_list = ImGui::GetForegroundDrawList();

		for (int i = 0; i < UserSpeeds.size(); i++){
			std::string Title = "(" + TicksToString(UserSpeeds[i].targetTicksPerSecond) + ") " + UserSpeeds[i].name;

			if (ButtonDelete(imgui_window, draw_list, ("userSpeeds" + std::to_string(i)).c_str(), ImColor(ImVec4(1.f, 1.f, 1.f, 1.f)))) {
				UserSpeeds.erase(UserSpeeds.begin() + i);
				i--;
				continue;
			}

			//ImGui::SameLine();
			if (ImGui::Selectable(Title.c_str(), i == IndexChoosedCustomSpeedMode && Speed == SpeedMode::Custom)) {
				IndexChoosedCustomSpeedMode = i;
				SetSpeedMode(SpeedMode::Custom);
			}
		
			if (i == IndexChoosedCustomSpeedMode && Speed == SpeedMode::Custom)
				ImGui::SetItemDefaultFocus();
		}


		if (ButtonCenteredOnLine(u8"�������� �����������", 0.5f))
			PopupCreation_opened = true;

		ImGui::EndCombo();
	}
	
	if (ImGui::RadioButton(u8"��������� ���������� ��������� ���������� ���������� ����� ��������� ��������", flag_ReturnStateAfterChangeSpeed))
		flag_ReturnStateAfterChangeSpeed = !flag_ReturnStateAfterChangeSpeed;

	DrawPopup();
}

void EmulationThread::DrawPopup() {
	if (PopupCreation_opened == false)
		return;

	ImGui::OpenPopup(u8"�������� ����������������� �����������");

	const ImGuiWindowFlags flagsWindow = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();

	ImVec2 size = ImGui::GetMainViewport()->WorkSize;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));


	ImGui::SetNextWindowSize(ImVec2(ImGui::CalcTextSize(u8"�������� ����������������� �����������              ").x, ImGui::GetFontSize() * 12.5f));


	static char buf_name[120];
	static char buf_value[120];
	static bool FirstLoad = false;
	if (FirstLoad == false){
		FirstLoad = true;
		for (int i = 0; i < 120; i++) {
			buf_name[i] = 0;
			buf_value[i] = 0;
		}
	}

	if (ImGui::BeginPopupModal(u8"�������� ����������������� �����������", &PopupCreation_opened, flagsWindow)){
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetFontSize() * 0.5f);
		center.x -= ImGui::GetCurrentWindow()->Size.x / 2;
		center.y -= ImGui::GetCurrentWindow()->Size.y / 2;
		ImGui::GetCurrentWindow()->Pos = center;

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5, 0.5, 0.5, 1.0));
		TextCenteredOnLine(u8"(�������������)", 0, 0);
		ImGui::PopStyleColor();

		TextCenteredOnLine(u8"�������� �����������", 0, 0);
		



		ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));

		float input_width = ImGui::CalcItemWidth();
		ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x - input_width) / 2.f);
		ImGui::InputText("1102", buf_name, 120, ImGuiInputTextFlags_NoLabel);

		ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));


		TextCenteredOnLine(u8"������� ����� ���-�� ������", 0, 0);
		ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));

		input_width = ImGui::CalcItemWidth();
		ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x - input_width) / 2.f);
		ImGui::SetNextItemWidth(input_width - ImGui::CalcTextSize(u8"�������").x);
		ImGui::InputText("1104", buf_value, 120, ImGuiInputTextFlags_NoLabel| ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CallbackCharFilter | ImGuiInputTextFlags_CallbackEdit, InputTextCallback);

		ImGui::SameLine();
		if (!std::string(buf_value).empty())
			ImGui::Text(std::string(" " + TicksToString(std::stoull(std::string(buf_value)))).c_str());
		else
			ImGui::Text(std::string(" " + TicksToString(0)).c_str());

		//InputTextCallback
		ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));



		bool pressed = ButtonCenteredOnLine(u8"�������", 0.5f);

		if (ImGui::IsKeyPressed(ImGuiKey_Enter))
			pressed = true;

		if (pressed){

			if (!std::string(buf_value).empty()){
				PopupCreation_opened = false;

				CustomSpeed tempSpeed;
				tempSpeed.name = buf_name;

				tempSpeed.targetTicksPerSecond = std::stoull(std::string(buf_value));

				UserSpeeds.emplace_back(tempSpeed);

				IndexChoosedCustomSpeedMode = UserSpeeds.size() - 1;
				SetSpeedMode(SpeedMode::Custom);
			}
			else
				pressed = false;
		}

		ImGui::EndPopup();
	}

	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

std::string EmulationThread::TicksToString(const uint64_t& ticks) {

	std::string Output = "";

	uint64_t Kilo = ticks / 1'000;
	uint64_t Mega = ticks / 1'000'000;
	uint64_t Giga = ticks / 1'000'000'000;
	uint64_t Tera = ticks / 1'000'000'000'000;

	if (Tera != 0){
		Output += to_string(Tera);

		uint64_t ost = ticks - Tera * 1'000'000'000'000;

		if (ost > 0)
			Output += "." + to_string(ost).substr(0,2);

		Output += u8" ���";
	}
	else if (Giga != 0){
		Output += to_string(Giga);

		uint64_t ost = ticks - Giga* 1'000'000'000;

		if (ost > 0)
			Output += "." + to_string(ost).substr(0, 2);

		Output += u8" ���";
	}
	else if (Mega != 0) {
		Output += to_string(Mega);

		uint64_t ost = ticks - Mega* 1'000'000;

		if (ost > 0)
			Output += "." + to_string(ost).substr(0, 2);

		Output += u8" ���";
	}
	else if (Kilo != 0) {
		Output += to_string(Kilo);

		uint64_t ost = ticks - Kilo* 1'000;

		if (ost > 0)
			Output += "." + to_string(ost).substr(0, 2);

		Output += u8" ���";
	}
	else {
		Output += to_string(ticks);
		Output += u8" ��";
	}

	return Output;
}

std::string EmulationThread::SaveSetting() {
	std::string result = save_MakeBegin(5 + UserSpeeds.size()*2);


	for (int i = 0; i < UserSpeeds.size(); i++) {
		result += save_MakeItem("NameCustomSpeed", UserSpeeds[i].name);
		result += save_MakeItem("ValueCustomSpeed", std::to_string(UserSpeeds[i].targetTicksPerSecond));
	}
	result += save_MakeItem("IndexChoosedCustomSpeedMode", std::to_string(IndexChoosedCustomSpeedMode));
	result += save_MakeItem("flag_ReturnStateAfterChangeSpeed", std::to_string(flag_ReturnStateAfterChangeSpeed));
	result += save_MakeItem("SpeedMode", toString(Speed));

	result += save_MakeItem("Flag_HistoryModeEnabled", std::to_string(processor->isHistoryModeEnabled()));
	result += save_MakeItem("MaxCountHistoryElements", std::to_string(processor_CaretakerMomento->GetMaxCount()));


	return result;
}

void EmulationThread::LoadSetting(const std::string& Data) {
	auto info = load_TokenizeData(Data);

	std::string path_temp;

	CustomSpeed tempSpeed;

	for (SettingLoadData data : info) {
		if (data.NameVar == "SpeedMode") {
			if (data.ValueVar == "Infinity")
				SetSpeedMode(SpeedMode::Infinity);
			else if (data.ValueVar == "Intel4004")
				SetSpeedMode(SpeedMode::Intel4004);
			else if (data.ValueVar == "Intel8008")
				SetSpeedMode(SpeedMode::Intel8080);
			else if (data.ValueVar == "Intel8080")
				SetSpeedMode(SpeedMode::Intel8080);
			else if (data.ValueVar == "Intel8085")
				SetSpeedMode(SpeedMode::Intel8085);
			else if (data.ValueVar == "Intel8086")
				SetSpeedMode(SpeedMode::Intel8086);
			else if (data.ValueVar == "Custom")
				SetSpeedMode(SpeedMode::Custom);
			else
				std::cout << "Unknown speedmode argument: " << data.ValueVar << std::endl;
		}
		else if (data.NameVar == "NameCustomSpeed") {
			tempSpeed.name = data.ValueVar;
		}
		else if (data.NameVar == "ValueCustomSpeed") {
			tempSpeed.targetTicksPerSecond = std::stoull(data.ValueVar);
			UserSpeeds.emplace_back(tempSpeed);
		}
		else if (data.NameVar == "IndexChoosedCustomSpeedMode")
			IndexChoosedCustomSpeedMode = stoi(data.ValueVar);
		else if (data.NameVar == "flag_ReturnStateAfterChangeSpeed")
			flag_ReturnStateAfterChangeSpeed = stoi(data.ValueVar);
		else if (data.NameVar == "Flag_HistoryModeEnabled")
			processor->Set_HistoryMode(stoi(data.ValueVar));
		else if (data.NameVar == "MaxCountHistoryElements")
			processor_CaretakerMomento->SetMaxCount(stoi(data.ValueVar));
		else
			std::cout << "EmulationThread::LoadSetting -> Unknown name argument: " << data.NameVar << std::endl;
	}
}