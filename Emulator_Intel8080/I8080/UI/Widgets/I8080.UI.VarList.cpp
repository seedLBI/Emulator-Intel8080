#include "I8080.UI.VarList.h"



Widget_VarList::Widget_VarList(I8080* processor, TranslatorOutput* translator) :I8080_Widget(u8"Переменные") {
	this->processor = processor;
	this->translator = translator;
}

Widget_VarList::~Widget_VarList() {

}

void Widget_VarList::Draw() {
	if (GetFlagShow() == false)
		return;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 3));
	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow())) {

		static ImGuiTableFlags flags =
			ImGuiTableFlags_RowBg |
			ImGuiTableFlags_Borders | ImGuiTableFlags_Reorderable | ImGuiTableFlags_ScrollY;
		if (ImGui::BeginTable("table_vars", 2, flags))
		{
			ImGui::TableSetupColumn(u8"Названия", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn(u8"Значения", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible

			ImGui::TableHeadersRow();

			for (int i = 0; i < translator->Vars.size(); i++)
			{

				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);

				ImGui::Text(translator->Vars[i].name_marker.c_str(), 0, i);


				ImGui::TableSetColumnIndex(1);

				string text = "";

				for (int j = 0; j < translator->Vars[i].count_elements; j++)
				{
					text += to_string(processor->GetMemory()[translator->Vars[i].adress + j]);
					if (j != translator->Vars[i].count_elements - 1)
					{
						text += ", ";
					}
				}

				ImGui::Text(text.c_str(), 1, i);
			}




			ImGui::EndTable();
		}

		ImGui::End();
	}
	ImGui::PopStyleVar();
}

void Widget_VarList::Update() {

}


std::string Widget_VarList::Save() {
	std::string output = "";
	output += MakeBegin(1);
	output += MakeSaveItem(string("Flag_Show"), std::to_string(GetFlagShow()));
	return output;
}

void Widget_VarList::Load(const std::string& Data) {
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

