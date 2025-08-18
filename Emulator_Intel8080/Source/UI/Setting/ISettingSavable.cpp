#include "UI/Setting/ISettingSavable.h"


ISettingSavable::ISettingSavable(const std::string& NameObject) {
	this->NameObject      = NameObject;
	this->NameObject_cstr = NameObject.c_str();
}
std::string ISettingSavable::SaveSetting() {
	return "";
}
void ISettingSavable::LoadSetting(const std::string& Data) {

}

std::string ISettingSavable::GetSaveObjectName() {
	return NameObject;
}
const char* ISettingSavable::GetSaveObjectName_cstr() {
	return NameObject_cstr;
}

std::string ISettingSavable::save_MakeBegin(const int& count_Lines) {
	return "[BEGIN] [" + NameObject + "] (" + std::to_string(count_Lines) + ")\n";
}
std::string ISettingSavable::save_MakeItem(const std::string& NameItem, const std::string& ValueItem) {
	return "[" + NameItem + "] [" + ValueItem + "]\n";
}

std::vector<std::string> ISettingSavable::SplitLine(const std::string& Line) {
	if (Line.size() == 0) {
		return std::vector<std::string>{Line};
	}
	if (Line[0] != '[') {
		return std::vector<std::string>{Line};
	}

	std::vector<std::string> result(2);

	auto begin = Line.find_first_of('[') + 1;
	auto end = Line.find_first_of(']');

	result[0] = Line.substr(begin, end - begin);

	begin = Line.find_last_of('[') + 1;
	end = Line.find_last_of(']');

	result[1] = Line.substr(begin, end - begin);

	return result;
}



std::vector<SettingLoadData> ISettingSavable::load_TokenizeData(const std::string& Data) {

	std::vector<SettingLoadData> result;

	auto Lines = split(Data, "\n");

	for (int i = 0; i < Lines.size(); i++)
	{
		auto t = SplitLine(Lines[i]);
		if (t.size() < 2){
			std::cout << "Puted data wrong check that line in debug...";
			exit(111);
		}

		result.emplace_back(t[0],t[1]);
	}


	return result;

}