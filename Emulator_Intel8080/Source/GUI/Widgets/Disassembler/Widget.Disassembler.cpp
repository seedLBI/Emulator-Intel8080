#include "Widget.Disassembler.h"


Widget_Disassembler::Widget_Disassembler(I8080* processor) : I8080_Widget(u8"Дизассемблер") {
	this->processor = processor;
}

Widget_Disassembler::~Widget_Disassembler() {

}

void Widget_Disassembler::Draw() {
	if (GetFlagShow() == false)
		return;
	
	int count = 0;

	static int CountLoop = 10;

	static std::vector<std::pair<uint16_t, std::string>> Markers;


	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow())) {

		
		ImGui::SliderInt(u8"Кол-во инструкций", &CountLoop, 1, 25, "%d");


		ImGui::BeginChild("LeftBlock_Disassembler", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 0));
		{
			ImGui::BeginTable("TableOfInstruction", 1, ImGuiTableFlags_RowBg);

			for (int i = 0; i < CountLoop; i++)
			{

				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);

				uint8_t first__Byte = 0;
				uint8_t second_Byte = 0;
				uint8_t third__Byte = 0;

				if (processor->GetProgrammCounter() + count <= SIZE_MEMORY - 1)
					first__Byte = processor->GetMemory()[processor->GetProgrammCounter() + count];
				else
					break;
				if (processor->GetProgrammCounter() + 1 + count <= SIZE_MEMORY - 1)
					second_Byte = processor->GetMemory()[processor->GetProgrammCounter() + count + 1];
				if (processor->GetProgrammCounter() + 2 + count <= SIZE_MEMORY - 1)
					third__Byte = processor->GetMemory()[processor->GetProgrammCounter() + count + 2];

				auto info = Instructuion_to_String(first__Byte, second_Byte, third__Byte);

				count += info.second;

				std::string BytesInfo = "";

				for (int j = 0; j < info.second; j++) {

					if (j == 0)
					{
						std::string data = to_hex_string(first__Byte);
						ToUpperALL(data);
						BytesInfo += data;
					}
					else if (j == 1) {
						std::string data = to_hex_string(second_Byte);
						ToUpperALL(data);
						BytesInfo += " " + data;
					}
					else if (j == 2) {
						std::string data = to_hex_string(third__Byte);
						ToUpperALL(data);
						BytesInfo += " " + data;
					}
				}
				BytesInfo.append(8, ' ');

				std::string IntructionInfo = info.first[0];

				if (info.first.size() == 2){
					uint16_t value2Find = (uint16_t)string_formatted_to_value(info.first[1]);


					bool Finded = false;
					for (int i = 0; i < Markers.size(); i++){

						if (Markers[i].first == value2Find){
							IntructionInfo += Markers[i].second;
							Finded = true;
							break;
						}
					}
					if (Finded == false)
						IntructionInfo += info.first[1];

				}


				ImGui::Text((BytesInfo + "   " + IntructionInfo).c_str(), 0, 14);
			}

			ImGui::EndTable();
		}
		ImGui::EndChild();

		ImGui::SameLine();
		

		ImGui::BeginChild("RightBlock_Disassemblerr");
		{
			

			static bool FirstClean = true;
			static char* input_adress = new char[5];
			static char* input_Marker = new char[256];

			if (FirstClean){
				FirstClean = false;
				for (int i = 0; i < 4; i++)
					input_adress[i] = 0;
				for (int i = 0; i < 256; i++)
					input_Marker[i] = 0;
			}


			ImGui::BeginTable("TableOfAddingMarker", 3, ImGuiTableFlags_Borders);

			ImGui::TableSetupColumn(u8"Адрес", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupColumn(u8"Имя", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupColumn(u8"", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableHeadersRow();

			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::PushItemWidth(-FLT_MIN);
			ImGui::InputText("Adress", input_adress, 5, ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_NoLabel);

			ImGui::TableSetColumnIndex(1);
			ImGui::PushItemWidth(-FLT_MIN);
			ImGui::InputText("Name", input_Marker, 256, ImGuiInputTextFlags_NoLabel);

			ImGui::TableSetColumnIndex(2);

			if (ImGui::Button("Accept")) {

				std::string temp_adress;
				std::string temp_name;

				for (int i = 0; i < 4; i++) {
					if (input_adress[i] == 0)
						break;
					temp_adress += input_adress[i];

					input_adress[i] = 0;
				}
				
				for (int i = 0; i < 256; i++) {
					if (input_Marker[i] == 0)
						break;
					temp_name += input_Marker[i];

					input_adress[i] = 0;
				}


				for (int i = 0; i < 4; i++)
					input_adress[i] = 0;
				for (int i = 0; i < 256; i++)
					input_Marker[i] = 0;


				if (temp_adress.empty() == false && temp_name.empty() == false) {

					uint16_t Adress_value = (uint16_t)string_formatted_to_value("0x" + temp_adress);

					bool FindSameAdressOrName = false;

					for (int i = 0; i < Markers.size(); i++){
						if (Adress_value == Markers[i].first || temp_name == Markers[i].second){
							FindSameAdressOrName = true;
							break;
						}
					}

					if (FindSameAdressOrName == false)
						Markers.emplace_back(Adress_value, temp_name);


				}


			}

			ImGui::EndTable();

			ImGui::BeginTable("TableListMarker", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg);

			ImGui::TableSetupColumn(u8"Адрес", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupColumn(u8"Имя", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableHeadersRow();

			for (int i = 0; i < Markers.size(); i++)
			{

				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);

				ImGui::Text(to_hex_string(Markers[i].first).c_str());
				ImGui::TableSetColumnIndex(1);
				ImGui::Text(Markers[i].second.c_str());

			}



			ImGui::EndTable();

				//ImGui::SameLine();

				//ImGui::SameLine();

				
				
		}
		ImGui::EndChild();






		ImGui::End();
	}
}

void Widget_Disassembler::Update() {
	UpdateActive();
}

nlohmann::json Widget_Disassembler::Save() {
	return SaveDefaultParameters();
}

void Widget_Disassembler::Load(const nlohmann::json& Data) {
	ReadDefaultParameters(Data);
}