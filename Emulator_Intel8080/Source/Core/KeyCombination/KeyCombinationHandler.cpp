#include "KeyCombinationHandler.h"


KeyCombinationHandler::KeyCombinationHandler(FPS_Timer* fps_timer, GLFWwindow* window, NotificationManager* notificationManager) : ISettingObject(u8"KeyCombination",u8"Управление") {
	this->fps_timer = fps_timer;
	this->window = window;
	this->notificationManager = notificationManager;
}

KeyCombinationHandler::~KeyCombinationHandler() {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "KeyCombinationHandler::~KeyCombinationHandler()\n";
#endif // !WITH_DEBUG_OUTPUT
}



bool KeyCombinationHandler::GetCollision(const KeyCombination& comb) {
	if (GetIndexCollision(comb) != -1)
		return true;
	return false;
}

bool KeyCombinationHandler::AddCombination(const std::string& Name, const KeyCombination& comb) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Trying AddCombination\n";
#endif

	if (GetCollision(comb) == true) {
#ifdef WITH_DEBUG_OUTPUT
		std::cout << "Combination not added\n";
#endif
		return false;
	}
	combinations.push_back({ Name,comb });

	KeysToCheck = GetUniqueKeys();
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Combination added\n";

	std::cout << "Unique_Keys: ";
	for (int i = 0; i < KeysToCheck.size(); i++)
	{
		std::cout <<"[" << KeyToStr(KeysToCheck[i].number) << "] ";
	}
	std::cout << "\n";


	std::cout << "Combinations: ";

	std::cout << "|||||||||||||||||||||||||||||||||||||||||\n";
	for (int i = 0; i < combinations.size(); i++){
		std::cout << "------------------------------------\n";
		std::cout << "Name: [" << combinations[i].first << "]\n";
		std::cout << "Keys: ";

		for (int j = 0; j < combinations[i].second.keys.size(); j++)
		{
			std::cout << "<" << KeyToStr(combinations[i].second.keys[j]) << "> ";
		}
		std::cout << "\n";

	}
#endif

	return true;

}

void KeyCombinationHandler::Update() {
	if (flag_StopProcess == false && PopupSetKeyIsOpen == false) {
		ProcessAllUniqueKeys();
		ProcessAllFunctions();
	}
}

int KeyCombinationHandler::GetIndexKeyByNumber(const int& number) {
	for (int i = 0; i < KeysToCheck.size(); i++) {
		if (KeysToCheck[i].number == number)
			return i;
	}
	return -1;
}

void KeyCombinationHandler::ProcessAllFunctions() {
	int Value_maxequal = -1;
	int Index_maxequal = -1;

	for (int i = 0; i < combinations.size(); i++) {

		int val = -1;


		bool OnePressed = false;

		for (int j = 0; j < combinations[i].second.keys.size(); j++) {

			int index = GetIndexKeyByNumber(combinations[i].second.keys[j]);

			if (index == -1)
				break;

			if (KeysToCheck[index].isPressed == true) {
				OnePressed = true;
				val++;
			}
			else if (KeysToCheck[index].isDown == true)
				val++;
		}

		if (val + 1 != combinations[i].second.keys.size())
			continue;
		if (OnePressed == false)
			continue;

		if (val > Value_maxequal) {
			Value_maxequal = val;
			Index_maxequal = i;
		}

	}


	for (int i = 0; i < KeysToCheck.size(); i++)
		KeysToCheck[i].isPressed = false;

	if (Index_maxequal == -1)
		return;


#ifdef WITH_DEBUG_OUTPUT
	std::string DebugOutput;
	for (int i = 0; i < combinations[Index_maxequal].second.keys.size(); i++){
		int k = combinations[Index_maxequal].second.keys[i];
		if (i == combinations[Index_maxequal].second.keys.size() - 1)
			DebugOutput += KeyToStr(k);
		else
			DebugOutput += KeyToStr(k) + " + ";
	}

	std::cout << "Function: [" << combinations[Index_maxequal].first << "] <" << DebugOutput << ">\n";
#endif


	combinations[Index_maxequal].second.v_function();




}

void KeyCombinationHandler::ProcessAllUniqueKeys() {

	for (int i = 0; i < KeysToCheck.size(); i++)
	{
		KeysToCheck[i].isDownLastState = KeysToCheck[i].isDown;

		if (glfwGetKey(window, KeysToCheck[i].number) == GLFW_PRESS)
			KeysToCheck[i].isDown = true;
		else
			KeysToCheck[i].isDown = false;

		if (KeysToCheck[i].isDown != KeysToCheck[i].isDownLastState && KeysToCheck[i].isDownLastState == false)
			KeysToCheck[i].isPressed = true;
	}
}

std::vector<Key> KeyCombinationHandler::GetUniqueKeys() {

	std::vector<Key> result;

	auto contains = [&result](int newValue) {
		if (result.empty())
			return false;
		for (int i = 0; i < result.size(); i++) {
			if (newValue == result[i].number)
				return true;
		}
		return false;
		};


	for (int i = 0; i < combinations.size(); i++) {
		for (int j = 0; j < combinations[i].second.keys.size(); j++) {
			const int newKey = combinations[i].second.keys[j];
			if (contains(combinations[i].second.keys[j]) == false)
				result.emplace_back(newKey, false, false);
		}
	}

	std::sort(result.begin(), result.end(), [](Key& a, Key& b) {return a.number > b.number; });

	return result;
}


void KeyCombinationHandler::DrawPopupSetKey() {

	static const ImGuiWindowFlags flagsWindow =
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoScrollbar;

	static std::vector<int> LastPressedKeys;
	static float TimePressed = 0.f;



	if (PopupSetKeyIsOpen){
		ImGui::OpenPopup(u8"Установка новой комбинации");


		ImVec2 center = ImGui::GetMainViewport()->GetCenter();

		ImVec2 size = ImGui::GetMainViewport()->WorkSize;

		float HeightWindow = ImGui::GetTextLineHeight() * 10.5f;
		if (combinations[SelectedCombination_For_setting].second.keys.empty() == false)
			HeightWindow = ImGui::GetTextLineHeight() * 12.5f;

		ImGui::SetNextWindowSize(ImVec2(ImGui::CalcTextSize(u8"        Удерживай нужную комбинацию клавиш        ").x, HeightWindow));


		if (ImGui::BeginPopupModal(u8"Установка новой комбинации", &PopupSetKeyIsOpen, flagsWindow)) {


			if (combinations[SelectedCombination_For_setting].second.keys.empty() == false){
				ImGui::Dummy(ImVec2(0, 10));
				if (ButtonCenteredOnLine(u8"Стереть текущую комбинацию", 0.5f)) {
					PopupSetKeyIsOpen = false;
					TimePressed = 0.f;
					LastPressedKeys.clear();

					combinations[SelectedCombination_For_setting].second.ChangeKeys({});

					KeysToCheck = GetUniqueKeys();

				}
			}


			ImDrawList* draw_list = ImGui::GetWindowDrawList();

			center.x -= ImGui::GetCurrentWindow()->Size.x / 2;
			center.y -= ImGui::GetCurrentWindow()->Size.y / 2;
			ImGui::GetCurrentWindow()->Pos = center;

			ImGui::Dummy(ImVec2(0, 10));

			TextCenteredOnLine(u8"Удерживай нужную комбинацию клавиш", 0, 0);
			TextCenteredOnLine(u8"в течение одной секунды.", 0, 0);





			std::vector<int> kkk = GetNumberPressedKeys(window);
			std::sort(kkk.begin(), kkk.end(), std::greater<int>());

			ErrorCombination error = GetErrorOfThisCombination(kkk);



			bool flag_error_orange = error != ErrorCombination::NOTHING && error != ErrorCombination::ERROR_COLLISION && error != ErrorCombination::ERROR_IDENTICAL;


			if (kkk != LastPressedKeys || kkk.empty() == true || (flag_error_orange)) {
				TimePressed = 0.f;
			}
			else {
				TimePressed += (float)fps_timer->GetDeltaTime();
			}
			LastPressedKeys = kkk;


			std::string Keys;
			for (int j = 0; j < kkk.size(); j++) {
				if (j != kkk.size() - 1)
					Keys += KeyToHumanReadbleStr(kkk[j]) + " + ";
				else
					Keys += KeyToHumanReadbleStr(kkk[j]);
			}

			TextCenteredOnLine(Keys.c_str(), 0, 0, 0.5f, true);


			ImGui::Dummy(ImVec2(0,5));

			ImVec2 p = ImGui::GetCursorScreenPos();
			ImVec2 window_size = ImGui::GetWindowSize();

			p.x += 10;

			window_size.x -= 20;

			float width = window_size.x;
			float height = 20.f;

			draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), IM_COL32(50, 50, 50, 255));

			if (flag_error_orange){
				draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), IM_COL32(100, 50, 50, 255));
			}
			else if(error == ErrorCombination::ERROR_COLLISION || error == ErrorCombination::ERROR_IDENTICAL) {
				float progress_width = width * TimePressed;
				draw_list->AddRectFilled(p, ImVec2(p.x + progress_width, p.y + height), ImColor{ 1.f,0.5f,0.2f,1.f });
			}
			else {
				float progress_width = width * TimePressed;
				draw_list->AddRectFilled(p, ImVec2(p.x + progress_width, p.y + height), ImColor{ 0.5f,1.f,0.5f,1.f });
			}

			ImGui::Dummy(ImVec2(0, 10));

			if (error == ErrorCombination::ERROR_COLLISION || error == ErrorCombination::ERROR_IDENTICAL)
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.5f, 0.2f, 1.f));
			else
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.2f, 0.2f, 1.f));
			TextCenteredOnLine(ErrorCombination_To_string(error).c_str(), 0, 0, 0.5f, true);
			ImGui::PopStyleColor();



			if (TimePressed > 1.f)
			{
				if (error == ErrorCombination::ERROR_COLLISION)
				{
					int index = GetIndexCollision(kkk);
					combinations[index].second.ChangeKeys({});
					

					static const ImVec4 color_Orange{ 0.45f,0.35f,0.1f,1.0f };
					static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

					std::string Text = u8"Возникло совпадение комбинаций.\nДля разрешения проблемы у следующей команды\nкомбинация будет стёрта:";

					std::string Text2 = "[" + combinations[index].first + "]";

					notificationManager->AddNottification(Notification(color_Orange, 8.f, std::vector<N_Element*>{
						new N_Message(color_WHITE, Text),
						new N_Message(color_WHITE, Text2)
					},
						nullptr));

				}
				else if (error == ErrorCombination::ERROR_IDENTICAL)
				{

					static const ImVec4 color_Orange{ 0.45f,0.35f,0.1f,1.0f };
					static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };


					static uint8_t type_message = 0;

					const static std::vector<std::string> variants{
	 u8"Ну и ладно....",
	 u8"Ок...",
	 u8"Странно...",
	 u8"А зачем?",
	 u8"Для чего ты это делаешь?",
	 u8"может ХВАТИТ?!!?!?!?!",
	 u8"ты хочешь проверить все фразы?",
	 u8"упорный",
	 u8"ну давай давай.",
	 u8"что не кончаются?",
	 u8"но ты близок",
	 u8"вот вот",
	 u8"скоро",
	 u8"я устал их делать...",
	 u8"...",u8"......",u8".........",u8"..................",
	 u8"ты чемпион."
					};
					
					std::string Text = variants[type_message];





					notificationManager->AddNottification(Notification(color_Orange, 3.f, std::vector<N_Element*>{
						new N_Message(color_WHITE, Text)
					},
						nullptr));

					type_message++;
					if (type_message > 19)
						type_message = 0;

				}




				PopupSetKeyIsOpen = false;
				TimePressed = 0.f;
				LastPressedKeys.clear();

				combinations[SelectedCombination_For_setting].second.ChangeKeys(kkk);

				KeysToCheck = GetUniqueKeys();


				for (int i = 0; i < KeysToCheck.size(); i++)
				{
					KeysToCheck[i].isDown = true;
					KeysToCheck[i].isDownLastState = true;
				}


			}

		}


	}
	else {
		if (LastPressedKeys.empty() == false)
			LastPressedKeys.clear();

		TimePressed = 0.f;
	}
}

bool KeyCombinationHandler::PopupIsOpen() {
	return PopupSetKeyIsOpen;
}

std::string KeyCombinationHandler::GetStrCombinationByName(const std::string& name) {
	for (int i = 0; i < combinations.size(); i++){
		if (combinations[i].first == name)
			return combinations[i].second.GetKeysStr();
	}
	return "";
}

int KeyCombinationHandler::GetIndexCollision(const std::vector<int>& comb) {

	if (comb.empty())
		return -1;

	for (int i = 0; i < combinations.size(); i++) {

		if (comb.size() != combinations[i].second.keys.size())
			continue;

		bool AllEqual = true;
		for (int j = 0; j < combinations[i].second.keys.size(); j++) {
			if (combinations[i].second.keys[j] != comb[j]) {
				AllEqual = false;
				break;
			}
		}
		if (AllEqual)
			return i;

	}


	return -1;
}

int KeyCombinationHandler::GetIndexCollision(const KeyCombination& comb) {


	if (comb.keys.empty())
		return -1;

	for (int i = 0; i < combinations.size(); i++) {

		if (comb.keys.size() != combinations[i].second.keys.size())
			continue;

		bool AllEqual = true;
		for (int j = 0; j < combinations[i].second.keys.size(); j++) {
			if (combinations[i].second.keys[j] != comb.keys[j]) {
				AllEqual = false;
				break;
			}
		}
		if (AllEqual)
			return i;

	}


	return -1;
}

int KeyCombinationHandler::GetIndexCombinationByName(const std::string& name) {
	for (int i = 0; i < combinations.size(); i++) {
		if (combinations[i].first == name)
			return i;
	}
	return -1;
}

KeyCombinationHandler::ErrorCombination KeyCombinationHandler::GetErrorOfThisCombination(const std::vector<int>& Keys) {
	if (Keys.empty())
		return ErrorCombination::NOTHING;

	if (Keys.size() > 4)
		return ErrorCombination::ERROR_TOO_MUCH_COUNT;

	bool AllNumbersAndSymbols = true;

	for (int i = 0; i < Keys.size(); i++){
		if (Keys[i] < 39 || Keys[i] > 96)
		{
			AllNumbersAndSymbols = false;
			break;
		}
	}

	if (AllNumbersAndSymbols)
		return ErrorCombination::ERROR_ONLY_SYMBOLS_AND_NUMBERS;


	int indexCollision = GetIndexCollision(Keys);


	if (indexCollision == SelectedCombination_For_setting)
		return ErrorCombination::ERROR_IDENTICAL;

	if (indexCollision != -1)
		return ErrorCombination::ERROR_COLLISION;



	return ErrorCombination::NOTHING;

}

std::string KeyCombinationHandler::ErrorCombination_To_string(const ErrorCombination& error) {
	switch (error)
	{
	case ErrorCombination::NOTHING:
		return "";
		break;
	case ErrorCombination::ERROR_COLLISION:
		return u8"Такая комбинация существует.";
		break;
	case ErrorCombination::ERROR_ONLY_SYMBOLS_AND_NUMBERS:
		return u8"Нельзя использовать только символы.";
		break;
	case ErrorCombination::ERROR_TOO_MUCH_COUNT:
		return u8"Клавиш слишком много.";
		break;
	case ErrorCombination::ERROR_IDENTICAL:
		return u8"Зачем устанавливать ту же самую комбинацию?";
		break;
	default:
		return u8"Неизвестная ошибка.";
		break;
	}
}

void KeyCombinationHandler::DrawSetting() {


	if (ImGui::BeginTable(u8"CombinationsTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_HighlightHoveredColumn | ImGuiTableFlags_ScrollY, ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y - 10.f) )) {

		ImGui::TableSetupColumn(u8"Название команды", ImGuiTableColumnFlags_WidthStretch);
		ImGui::TableSetupColumn(u8"Комбинация клавиш", ImGuiTableColumnFlags_WidthStretch);


		ImGui::TableSetupScrollFreeze(1, 1);


		ImGui::TableHeadersRow();


		static int selected = -1;

		for (int i = 0; i < combinations.size(); i++) {
			ImGui::TableNextRow(0, 2.f * ImGui::GetTextLineHeight());
			ImGui::TableNextColumn();

			TextCenteredOnLine(combinations[i].first.c_str(), 0, i, 0.5f, true);

			ImGui::TableNextColumn();

			bool s = selected == i;


			std::string key_name = combinations[i].second.GetKeysHumanStr();

			if (key_name.empty()) {
				for (int j = 0; j < i; j++)
					key_name += " ";
			}

			if (ImGui::Selectable(key_name.c_str(), &s, ImGuiSelectableFlags_Centered, ImVec2(0, 2.f * ImGui::GetTextLineHeight()))) {
				selected = i;
				SelectedCombination_For_setting = i;
				PopupSetKeyIsOpen = true;

			}


			if (PopupSetKeyIsOpen == false) {
				selected = -1;
				SelectedCombination_For_setting = -1;
			}


		}

		ImGui::EndTable();
	}

	DrawPopupSetKey();
}

nlohmann::json KeyCombinationHandler::SaveSetting() {

	nlohmann::json result;

	for (int i = 0; i < combinations.size(); i++){
		std::string Keys;
		for (int j = 0; j < combinations[i].second.keys.size(); j++) {
			if (j != combinations[i].second.keys.size() - 1)
				Keys += KeyToStr(combinations[i].second.keys[j]) + " + ";
			else
				Keys += KeyToStr(combinations[i].second.keys[j]);
		}

		result[combinations[i].first] = Keys;
	}

	return result;

}

void KeyCombinationHandler::LoadSetting(const nlohmann::json& Data) {


	for (auto& [Name, Combination] : Data.items()) {
		int indexNameCombination = GetIndexCombinationByName(Name);
		if (indexNameCombination != -1)
			combinations[indexNameCombination].second.SetKeysByStr(Combination.get<std::string>());
	}
	KeysToCheck = GetUniqueKeys();

}