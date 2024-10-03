#include "I8080.UI.Help.h"



Widget_Help::Widget_Help() :I8080_Widget(u8"Руководство") {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Reading file for widget help from <" << GetExePath() + "\\Help.data" << ">\n";
#endif
	ReadFromFile(GetExePath() + "\\Help.data");
}
Widget_Help::~Widget_Help() {

}
void Widget_Help::Draw() {
	if (GetFlagShow() == false)
		return;

	static float VirtualScaleFont = 1.f;
	ImGuiIO& io = ImGui::GetIO();

	ImU32 colorName = ImGui::GetColorU32(ImVec4(1.f, 0.5f, 0.5f, 1.f));

	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar)) {

		if (!isDataLoaded)
		{
			ImGui::Text(u8"Я не смог обнаружить файл Help.data рядом с исполняемым файлом :(\nТы куда его дел? Возвращай обратно.");
		}
		else {
			DrawRightMousePopup();
			for (int i = 0; i < categories.size(); i++) {

				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.95f, 0.75f, 1.f));

				if (ImGui::TreeNode(categories[i].name.c_str())) {
					ImGui::PopStyleColor();

					if (categories[i].categories.size() > 1) {
						for (int k = 0; k < categories[i].categories.size(); k++) {

							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.65f, 0.65f, 1.f, 1.f));
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

}

std::string Widget_Help::Save() {
	std::string output = "";
	output += MakeBegin(2);
	output += MakeSaveItem(string("Flag_Show"), std::to_string(GetFlagShow()));
	output += MakeSaveItem(string("EnableWrapedText"), std::to_string(EnableWrapedText));
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
		else if (name_arg == "EnableWrapedText")
			EnableWrapedText = stoi(value_arg);
		else
			std::cout << "Unknown name argument for widget: " << name_arg << std::endl;
	}
}



void Widget_Help::DrawRightMousePopup() {
	ImVec2 avail_size = ImGui::GetContentRegionAvail();
	ImVec2 pos = ImGui::GetCursorScreenPos();


	bool MouseInPopup = false;

	if (ImGui::IsMouseHoveringRect(pos, ImVec2(pos.x + avail_size.x, pos.y + avail_size.y))) {
		if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			ImGui::OpenPopup("PopupSettingHelp");
		}
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 8.0f));
	if (ImGui::BeginPopup("PopupSettingHelp"))
	{
		MouseInPopup = true;

		ImGui::Checkbox(u8"Переносить текст?", &EnableWrapedText);
		
		ImGui::EndPopup();
	}
	ImGui::PopStyleVar();
}


void Widget_Help::DrawTextWithAbbrivs(const std::vector < std::vector< std::any >>& Text) {
	for (int line = 0; line < Text.size(); line++){
		for (int element = 0; element < Text[line].size(); element++){

			if (Text[line][element].type() == typeid(std::string)) {
				std::string elem_text = std::any_cast<std::string>(Text[line][element]);

				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));

				if (EnableWrapedText){
					if (line == 0 && element == 0)
						RenderTextWrapped(elem_text.c_str(), true);
					else
						RenderTextWrapped(elem_text.c_str(), false);
				}
				else {
					ImGui::Text(elem_text.c_str());
				}

				ImGui::PopStyleColor();
			}
			else if (Text[line][element].type() == typeid(int)) {
				int elem_index = std::any_cast<int>(Text[line][element]);

				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 0.f, 1.f));

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

				ImGui::InputTextMultiline((u8"CodeBlock_"+elem_code.name).c_str(), elem_code.text.data(), elem_code.text.size(), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * (GetCountLines(elem_code.text) + 1)*1.1f), ImGuiInputTextFlags_ReadOnly);
			}


			if (element != Text[line].size() - 1)
				ImGui::SameLine(0,0);
		}
	}


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
				if (line.find_first_of("<") != std::string::npos) {

					while (line.find_first_of("<") != std::string::npos) {
						temp_line.push_back(line.substr(0, line.find_first_of("<")));
						begin = line.find_first_of("<") + 1;
						end = line.find_first_of(">");
						std::string abr_name = line.substr(begin, end - begin);
						temp_line.push_back(GetIndexAbbriv(abr_name));

						line = line.substr(end + 1);
					}

					temp_line.push_back(line);
				}
				else {
					temp_line.push_back(line);
				}


				temp_text.push_back(temp_line);
			}
		}
	}


	input.close();
}