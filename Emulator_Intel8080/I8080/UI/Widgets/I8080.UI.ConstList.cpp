#include "I8080.UI.ConstList.h"


Widget_ConstList::Widget_ConstList(TranslatorOutput* translator) :I8080_Widget(u8"Постоянные") {
	this->translator = translator;
}
Widget_ConstList::~Widget_ConstList() {

}
void Widget_ConstList::Draw() {
	if (GetFlagShow() == false)
		return;



	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 3));
	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow())) {


		static char* input = new char[120];

		static bool flag_first_init = false;

		if (flag_first_init == false) {
			flag_first_init = true;
			for (int i = 0; i < 120; i++)
				input[i] = 0;
		}

		ImGui::InputTextEx(u8"Поиск постоянных", u8"Поиск", input, 120, ImVec2(ImGui::GetWindowSize().x, 0), ImGuiInputTextFlags_NoLabel);

		int count_chars = 0;


		for (int i = 0; i < 120; i++) {
			if (input[i] == 0) {
				count_chars = i;
				break;
			}
		}

		static ImGuiTableFlags flags =
			ImGuiTableFlags_RowBg |
			ImGuiTableFlags_Borders | ImGuiTableFlags_Reorderable | ImGuiTableFlags_ScrollY;
		if (ImGui::BeginTable("table_consts", 2, flags))
		{
			ImGui::TableSetupColumn(u8"Названия", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn(u8"Значения", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible

			ImGui::TableHeadersRow();

			for (int i = 0; i < translator->Consts.size(); i++)
			{

				if (count_chars != 0)
				{
					bool flag_AllGood = true;
					if (translator->Consts[i].first.size() < count_chars)
						continue;

					for (int j = 0; j < count_chars; j++)
					{
						if (translator->Consts[i].first[j] != input[j]) {
							flag_AllGood = false;
							break;
						}
					}
					if (flag_AllGood == false)
						continue;
				}


				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);

				ImGui::Text(translator->Consts[i].first.c_str(), 0, i);


				ImGui::TableSetColumnIndex(1);

				ImGui::Text(to_string(translator->Consts[i].second).c_str(), 1, i);
			}




			ImGui::EndTable();
		}

		ImGui::End();
	}
	ImGui::PopStyleVar();

}
void Widget_ConstList::Update() {

}

std::string Widget_ConstList::Save() {
	std::string output = "";
	output += MakeBegin(1);
	output += MakeSaveItem(string("Flag_Show"), std::to_string(GetFlagShow()));
	return output;
}

void Widget_ConstList::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);

	std::vector<std::string> Lines = split(Data, "\n");
	for (int i = 0; i < Lines.size(); i++) {
		std::vector<std::string> info = SplitLine(Lines[i]);

		std::string name_arg = info[0];
		std::string value_arg = info[1];

		if (name_arg == "Flag_Show")
			SetFlagShow(stoi(value_arg));
		else
			std::cout << "Unknown name argument for widget: " << name_arg << std::endl;
	}
}