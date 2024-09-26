#include "SaveSystem.h"


SaveSystem::SaveSystem(const std::string& NameObject) {
	this->NameObject = NameObject;
}



SaveSystem::~SaveSystem() {

}

std::string SaveSystem::GetName() {
	return NameObject;
}

std::string SaveSystem::Save() {
	return "";
}

void SaveSystem::Load(const std::string& Data) {

}

std::string SaveSystem::MakeSaveItem(const std::string& NameItem,const std::string& ValueItem) {
	return "[" + NameItem + "] [" + ValueItem + "]\n";
}
std::string SaveSystem::MakeBegin(const std::string& NameBegin, const int& count_Lines) {
	return "[BEGIN] [" + NameBegin + "] (" + std::to_string(count_Lines) + ")\n";
}
std::string SaveSystem::MakeBegin(const int& count_Lines) {
	return "[BEGIN] [" + NameObject + "] (" + std::to_string(count_Lines) + ")\n";
}

std::vector<std::string> SaveSystem::SplitLine(const std::string& Line) {
	if (Line.size() == 0){
		return std::vector<std::string>{Line};
	}
	if (Line[0] != '['){
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


std::vector < std::pair < std::string, std::string >> SaveSystem::SplitData(const std::string& Data) {
	std::vector < std::pair < std::string, std::string >> result;

	auto Lines = split(Data,"\n");

	for (int i = 0; i < Lines.size(); i++)
	{
		auto t = SplitLine(Lines[i]);
		if (t.size() < 2)
		{
			std::cout << "Puted data wrong check that line in debug...";
			exit(111);
		}

		result.push_back({t[0],t[1]});
	}


	return result;
}

void SaveSystem::PrintDebugInfoAboutData(const std::string& Data) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "-----------------------------------------------------------------------\n";
	std::cout << "Loading Data for [" << GetName() << "]:\n";
	std::cout << Data << std::endl;
#endif
}