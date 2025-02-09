#include "I8080.UI.Help.h"



Widget_Help::Widget_Help() :I8080_Widget(u8"�����������"), IThemeLoadable(u8"�����������") {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Reading file for widget help from <" << GetExePath() + "\\Help.data" << ">\n";
#endif
	ReadFromFile(GetExePath() + "\\Help.data");

	IThemeLoadable::InitListWord({
		u8"��������� ���������",
		u8"��������� ������������",
		u8"��������� ���������� (�����)",
		u8"������������ (�����)"
		});


}
Widget_Help::~Widget_Help() {

}
void Widget_Help::Draw() {
	if (GetFlagShow() == false)
		return;


	static float VirtualScaleFont = 1.f;
	ImGuiIO& io = ImGui::GetIO();


	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(),  ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar)) {

		if (!isDataLoaded)
		{
			ImGui::Text(u8"� �� ���� ���������� ���� Help.data ����� � ����������� ������ :(\n�� ���� ��� ���? ��������� �������.");
		}
		else {
			
			DrawRightMousePopup();

			for (int i = 0; i < categories.size(); i++) {

				ImGui::PushStyleColor(ImGuiCol_Text, color_Category);

				if (ImGui::TreeNode(categories[i].name.c_str())) {
					ImGui::PopStyleColor();

					if (categories[i].categories.size() > 1) {
						for (int k = 0; k < categories[i].categories.size(); k++) {

							ImGui::PushStyleColor(ImGuiCol_Text, color_SubCategory);
							if (ImGui::TreeNode(categories[i].categories[k].name.c_str())) {
								ImGui::PopStyleColor();
								DrawTextWithAbbrivs(categories[i].categories[k].text_with_index);

								ImGui::TreePop();
							}
							else {
								ImGui::PopStyleColor();
							}

						}
					}
					else {
						DrawTextWithAbbrivs(categories[i].categories[0].text_with_index);
					}

					ImGui::TreePop();
				}
				else {
					ImGui::PopStyleColor();
				}

			}



		}

		ImGui::End();
	}

}
void Widget_Help::Update() {

	UpdateActive();
}

std::string Widget_Help::Save() {
	std::string output = "";
	output += MakeBegin(3);
	output += MakeSaveItem(std::string("Flag_Show"), std::to_string(GetFlagShow()));
	output += MakeSaveItem(std::string("Flag_Active"), std::to_string(WindowIsVisiable()));
	output += MakeSaveItem(std::string("EnableWrapedText"), std::to_string(EnableWrapedText));
	return output;
}
void Widget_Help::Load(const std::string& Data) {
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
		else if (name_arg == "EnableWrapedText")
			EnableWrapedText = stoi(value_arg);
		else
			std::cout << "Unknown name argument for widget: " << name_arg << std::endl;
	}
}


void Widget_Help::LoadColors() {

	for (int i = 0; i < object_colors.colors.size(); i++) {
		if (object_colors.colors[i].nameColor == u8"��������� ���������")
			color_Category = object_colors.colors[i].color;
		else if (object_colors.colors[i].nameColor == u8"��������� ������������")
			color_SubCategory = object_colors.colors[i].color;
		else if (object_colors.colors[i].nameColor == u8"��������� ���������� (�����)")
			color_Tooltip = object_colors.colors[i].color;
		else if (object_colors.colors[i].nameColor == u8"������������ (�����)")
			color_Attention = object_colors.colors[i].color;
	}
}
std::vector<NamedColor> Widget_Help::GetDefaultLightColors() {
	return {
		{u8"��������� ���������",			ImColor(106,48,0,255)},
		{u8"��������� ������������",		ImColor(214,76,0,255)},
		{u8"��������� ���������� (�����)",	ImColor(84,0,211,255)},
		{u8"������������ (�����)",			ImColor(160,0,0,255)}
	};

}
std::vector<NamedColor> Widget_Help::GetDefaultDarkColors() {
	return {
		{u8"��������� ���������",ImVec4(1.f, 0.95f, 0.75f, 1.f)},
		{u8"��������� ������������",ImVec4(0.65f, 0.65f, 1.f, 1.f)},
		{u8"��������� ���������� (�����)", ImVec4(1.f, 1.f, 0.f, 1.f)},
		{u8"������������ (�����)",ImVec4(1.f, 0.4f, 0.4f, 1.f)}
	};
}



void Widget_Help::DrawRightMousePopup() {

	ImVec2 window_pos = ImGui::GetWindowPos();
	ImVec2 window_size = ImGui::GetWindowSize();
	

	bool MouseInPopup = false;

	if (ImGui::IsMouseHoveringRect(window_pos, ImVec2(window_pos.x + window_size.x, window_pos.y + window_size.y))) {
		if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			ImGui::OpenPopup("PopupSettingHelp");
		}
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 8.0f));
	if (ImGui::BeginPopup("PopupSettingHelp"))
	{
		MouseInPopup = true;

		ImGui::Checkbox(u8"���������� �����?", &EnableWrapedText);
		
		ImGui::EndPopup();
	}
	ImGui::PopStyleVar();
}


void Widget_Help::DrawTextWithAbbrivs(const std::vector < std::vector< std::any >>& Text) {
	for (int line = 0; line < Text.size(); line++){

		if (Text[line].empty()) {
			ImGui::Text("");
		}

		for (int element = 0; element < Text[line].size(); element++){

			if (Text[line][element].type() == typeid(std::string)) {
				std::string elem_text = std::any_cast<std::string>(Text[line][element]);

				//ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));

				if (EnableWrapedText){
					if (line == 0 && element == 0)
						RenderTextWrapped(elem_text.c_str(), true);
					else
						RenderTextWrapped(elem_text.c_str(), false);
				}
				else {
					ImGui::Text(elem_text.c_str());
				}

				//ImGui::PopStyleColor();
			}
			else if (Text[line][element].type() == typeid(int)) {
				int elem_index = std::any_cast<int>(Text[line][element]);

				ImGui::PushStyleColor(ImGuiCol_Text, color_Tooltip);

				if (EnableWrapedText) {
					if (line == 0 && element == 0)
						RenderTextWrapped(abrivs[elem_index].name.c_str(), true);
					else
						RenderTextWrapped(abrivs[elem_index].name.c_str(), false);
				}
				else {
					ImGui::Text(abrivs[elem_index].name.c_str());
				}

				ImGui::PopStyleColor();

				if(ImGui::BeginItemTooltip()) {
					ImGui::Text(abrivs[elem_index].mean.c_str());
					ImGui::End();
				}
			}
			else if (Text[line][element].type() == typeid(CodeBlock)) {

				CodeBlock elem_code = std::any_cast<CodeBlock>(Text[line][element]);

				ImGui::SeparatorText(elem_code.name.c_str());

				ImGui::InputTextMultiline((u8"CodeBlock_"+elem_code.name).c_str(), elem_code.text.data(), elem_code.text.size(), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * (GetCountLines(elem_code.text) + 1)*1.1f), ImGuiInputTextFlags_ReadOnly| ImGuiInputTextFlags_NoLabel);
			}
			else if (Text[line][element].type() == typeid(ColoredText)) {

				ColoredText elem_code = std::any_cast<ColoredText>(Text[line][element]);

				ImGui::TextColored(color_Attention, elem_code.text.c_str());
				if (ImGui::IsItemHovered())
					Singletone_InfoInstruction::Instance().Display(elem_code.text, "");

			}
			else if (Text[line][element].type() == typeid(HyperTextForWidget)) {

				HyperTextForWidget elem_code = std::any_cast<HyperTextForWidget>(Text[line][element]);

				if (ImGui::ButtonEx(elem_code.text.c_str()))
					Button_pressed = elem_code.text;
			}

			//HyperTextForWidget

			if (element != Text[line].size() - 1)
				ImGui::SameLine(0,0);
		}
	}


}

std::string Widget_Help::GetCommand() {
	std::string temp = Button_pressed;
	Button_pressed.clear();
	return temp;
}


std::any Widget_Help::GetIndexAbbriv(const std::string& name) {
	for (int i = 0; i < abrivs.size(); i++){
		if (name == abrivs[i].name)
			return i;
	}
	std::cout << "Don't have abriv with name: [" << name << "]\n";
	return name;
}
void Widget_Help::ReadFromFile(const std::string& Path2File) {



	std::ifstream input;
	input.open(stringUTF8_to_wstring(Path2File));


	if (!isFileExist(input)) {
		std::cout << "File for help not exist. Path seted: [" << Path2File << "]\n";
		return;
	}
	isDataLoaded = true;


	std::string line;

	std::string Current_Category = "";
	std::string Current_SubCategory = "";


	Category temp_Category;
	SubCategory temp_subCategory;

	std::vector<std::vector<std::any>> temp_text;

	CodeBlock temp_CodeBlock;

	while (getline(input, line)) {
		auto begin = line.find_first_of("[") + 1;
		auto end = line.find_first_of("]");

		std::string stage = "";

		if (line[0] == '[' && begin != std::string::npos && end != std::string::npos) {
			stage = line.substr(begin, end - begin);
		}
		
		if (stage == "ABBRIV_MEAN"){
			line = line.substr(end + 1);

			begin = line.find_first_of("[") + 1;
			end = line.find_first_of("]");

			std::string abbriv_name = line.substr(begin, end - begin);

			line = line.substr(end + 1);

			begin = line.find_first_of("[") + 1;
			end = line.find_first_of("]");

			std::string abbriv_mean = line.substr(begin, end - begin);

			abrivs.push_back({ abbriv_name,abbriv_mean });

		}
		else if (stage == "BEGIN_CATEGORY")
		{
			line = line.substr(end + 1);

			begin = line.find_first_of("[") + 1;
			end = line.find_first_of("]");

			Current_Category = line.substr(begin, end - begin);

			temp_Category.name = Current_Category;
			temp_text.clear();

		}
		else if (stage == "BEGIN") {
			line = line.substr(end + 1);

			begin = line.find_first_of("[") + 1;
			end = line.find_first_of("]");

			Current_SubCategory = line.substr(begin, end - begin);

			temp_subCategory.name = Current_SubCategory;

			temp_subCategory.text_with_index.clear();
			temp_text.clear();
		}
		else if (stage == "BEGIN_CODE") {
			line = line.substr(end + 1);

			begin = line.find_first_of("[") + 1;
			end = line.find_first_of("]");

			temp_CodeBlock.name = line.substr(begin, end - begin);

		}
		else if (stage == "END_CODE") {

			temp_text.back().push_back(temp_CodeBlock);

			temp_CodeBlock.name = "";
			temp_CodeBlock.text = "";

		}
		else if (stage == "END") {

			if (Current_SubCategory.empty() == false){
				temp_subCategory.text_with_index = temp_text;
				Current_SubCategory = "";

				temp_Category.categories.push_back(temp_subCategory);
				temp_text.clear();
			}
			else if (Current_Category.empty() == false) {
				

				if (temp_Category.categories.empty())
				{
					SubCategory temp ={ "",temp_text };
					categories.push_back(Category{ Current_Category,std::vector<SubCategory>{temp} });

					temp_text.clear();
				}
				else {
					categories.push_back(temp_Category);
					temp_Category.categories.clear();
				}

				Current_Category = "";

			}

		}
		else if (stage.empty()){
			std::vector<std::any> temp_line;


			if (temp_CodeBlock.name.empty() == false) {
				temp_CodeBlock.text += line + "\n";
			}
			else {

				bool Begin_Hashteg = false;
				bool Begin_Figure = false;
				bool Begin_Abriv = false;

				std::string temp = "";

				int index = 0;
				while (true) {

					if (index > line.size() - 1 || line.empty())
						break;

					if (line[index] == '<'){
						if (temp.empty() == false) {
							temp_line.push_back(temp);
							temp.clear();
						}
						Begin_Abriv = true;
					}
					else if (line[index] == '>') {
						Begin_Abriv = false;
						temp_line.push_back(GetIndexAbbriv(temp));
						temp.clear();
					}
					else if (line[index] == '{') {

						if (temp.empty() == false) {
							temp_line.push_back(temp);
							temp.clear();
						}

						Begin_Figure = true;
					}
					else if (line[index] == '}') {
						Begin_Figure = false;
						temp_line.push_back(HyperTextForWidget{ temp });
						temp.clear();
					}
					else if (line[index] == '#') {

						if (Begin_Hashteg){
							Begin_Hashteg = false;
							temp_line.push_back(ColoredText{ temp });
							temp.clear();
						}
						else {
							if (temp.empty() == false) {
								temp_line.push_back(temp);
								temp.clear();
							}
							Begin_Hashteg = true;
						}
					}
					else {
						temp += line[index];
					}


					index++;
				}

				if (temp.empty() == false)
					temp_line.push_back(temp);

				temp_text.push_back(temp_line);
			}
		}
	}


	input.close();
}