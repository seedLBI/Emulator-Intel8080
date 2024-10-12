#include "Emulator/Compilier/Stable/Compiler.Stable.h"

CompilerStable::CompilerStable(){

}

CompilerStable::~CompilerStable(){

}

TranslatorOutput CompilerStable::Compile(const std::vector<std::string>& Code) {
	Clear();

	adressed_code.resize(Code.size(), 0);
	NeedCheckThatLineIndex.resize(Code.size(), 0);
	PosDotForNeedLine.resize(Code.size(), {});
	splited_code = Compiler::split_code(Code);

	Compiler::CompilerOutput.Line_and_Adress.resize(Code.size(), -1);

	if (Compiler::CompilerOutput.Error != TypeTranslatorError::NOTHING)
		return Compiler::CompilerOutput;



	if (Step1_MarkingAdresses()== false) {
		return Compiler::CompilerOutput;
	}
	if (Step2_ReplaceWithDirectValues() == false ) {
		return Compiler::CompilerOutput;
	}
	if (Step3_MakeByteArray() == false) {
		return Compiler::CompilerOutput;
	}

	for (auto& n : Markers)
		Compiler::CompilerOutput.Markers.emplace_back( n.first, n.second );

	Compiler::CompilerOutput.Consts = ConstsVector;

	Compiler::CompilerOutput.Vars = Vars;


	return Compiler::CompilerOutput;
}
void CompilerStable::Clear() {
	Compiler::CompilerOutput.Clear();
	splited_code.clear();
	splited_code_raw.clear();
	adressed_code.clear();
	Consts.clear();
	ConstsVector.clear();
	Markers.clear();
	Vars.clear();
	PosDotForNeedLine.clear();
	NeedCheckThatLineIndex.clear();
}


void CompilerStable::MakeError(const TypeTranslatorError& typeError, const int& Line) {
	Compiler::CompilerOutput.Error = typeError;
	Compiler::CompilerOutput.LineError = Line;
}


bool CompilerStable::Step1_MarkingAdresses() {
	int CurrentAdress = 0;
	int countCommandsAfterLastMarker = 0;

	CounterForNeedCheck = 0;



	std::string LastMarker_name;

	std::string LastGlobalMarker_name;

	for (int Line = 0; Line < splited_code.size(); ++Line) {

		if (splited_code[Line].size() == 0) continue;

		for (int i_element = 0; i_element < splited_code[Line].size(); ++i_element){

			std::string Element = splited_code[Line][i_element];

			if (Compiler::IsAllSpecialSymbols(Element)){
				MakeError(ERROR_WTF, Line);
				return false;
			}

			const size_t pos_dot = Element.find_first_of(".");
			const size_t pos_2dot = Element.find_first_of(":");
			const bool flag_have_dot = pos_dot != std::string::npos;
			const bool flag_have_2dot = pos_2dot != std::string::npos;
			PosDotForNeedLine[Line] = { pos_dot,pos_2dot,flag_have_dot,flag_have_2dot };


			const bool isDerektiv_or_localMarker = flag_have_dot && flag_have_2dot;


			if (isDerektiv_or_localMarker) {

				std::string command = Element.substr(pos_dot + 1, (pos_2dot - pos_dot) - 1);
				ToLowerAll(command);

				
				const bool haveNextElements = splited_code[Line].size() - 1 > i_element;

				if (command == "adr") {

					if (haveNextElements == false) {
						MakeError(ERROR_DEREKTIV_WITHOUT_ADRESS, Line);
						return false;
					}


					const auto value = Compiler::FromString2Int(splited_code[Line][i_element + 1]);


					if (value.second == Compiler::TypeValue::UNKNOWN) {
						MakeError(ERROR_UNKNOWN_VALUE_DEREKTIV, Line);
						return false;
					}

					if (value.first > MAX16BIT){
						MakeError(ERROR_OVERFLOW_VALUE_16BIT, Line);
						return false;
					}

					i_element++;
					CurrentAdress = value.first;
					adressed_code[Line] = value.first;


				}
				else if (command == "const") {

					if (haveNextElements == false) {
						MakeError(ERROR_DEREKTIV_CONST_WITHOUT_NAME, Line);
						return false;
					}

					const bool const_have_value = splited_code[Line].size() - i_element > 2;

					if (const_have_value == false) {
						MakeError(ERROR_DEREKTIV_WITHOUT_VALUE, Line);
						return false;
					}

					const std::string name_const = splited_code[Line][i_element + 1];

					if (Consts.contains(name_const)) {
						MakeError(ERROR_DUBLICAT_CONST, Line);
						return false;
					}

					if (Markers.contains(name_const)) {
						MakeError(ERROR_COLLISION_BETWEEN_NAMES_MARKER_AND_CONST, Line);
						return false;
					}

					const auto value_const = Compiler::FromString2Int(splited_code[Line][i_element + 2]);

					if (value_const.second == Compiler::TypeValue::UNKNOWN) {
						MakeError(ERROR_UNKNOWN_VALUE_DEREKTIV, Line);
						return false;
					}
					if (value_const.first > MAX16BIT) {
						MakeError(ERROR_OVERFLOW_VALUE_16BIT, Line);
						return false;
					}


					Consts[name_const] = value_const.first;
					ConstsVector.emplace_back(name_const, value_const.first);


				}
				else if (command == "set") {


					if (haveNextElements == false) {
						MakeError(ERROR_DEREKTIV_WITHOUT_VALUE, Line);
						return false;
					}

					adressed_code[Line] = CurrentAdress;

					if (countCommandsAfterLastMarker == 0 && Markers.empty() == false){

						const int count_vars = splited_code[Line].size() - (i_element + 1);
						const int LastMarker_adress = Markers[LastMarker_name];


						if (Vars.empty() == false && Vars.back().adress == LastMarker_adress) {
							Vars.back().count_elements += count_vars;
						}
						else {

							const bool isVarsMany = (count_vars > 1);
							
							Vars.emplace_back(
								LastMarker_name,
								LastMarker_adress,
								isVarsMany,
								count_vars);

						}

					}


					i_element++;


					while (splited_code[Line].size() > i_element) {


						const auto value_const = Compiler::FromString2Int(splited_code[Line][i_element]);

						if (value_const.second == Compiler::TypeValue::UNKNOWN) {

							if (NeedCheckThatLineIndex[CounterForNeedCheck - 1] != Line) {
								NeedCheckThatLineIndex[CounterForNeedCheck] = Line;
								CounterForNeedCheck++;
							}

						}
						else if (value_const.first > MAX8BIT) {
							MakeError(ERROR_OVERFLOW_VALUE_8BIT, Line);
							return false;
						}

						i_element++;
						CurrentAdress++;


						if (CurrentAdress > MAX16BIT) {
							MakeError(ERROR_OVERFLOW_ADRESS, Line);
							return false;
						}

					}

					continue;
				}
				else {

					bool is_creating_new_marker = Element[0] == '.';
					std::string marker = "";

					// ѕользователь вручную прописал им€ главного маркера

					if (is_creating_new_marker == false) {

						marker = Element.substr(0, pos_2dot);

						if (Compiler::CheckName(marker) == false) {
							MakeError(ERROR_WRONG_ADRESS_NAME, Line);
							return false;
						}

						if (Markers.contains(marker)) {
							MakeError(ERROR_DUBLICAT_MARKER, Line);
							return false;
						}
						else {
							// Ќужно проверить глобальный маркер.

							if (LastGlobalMarker_name.size() == 0) {
								MakeError(ERROR_CREATE_ANONIM_MARKER, Line);
								return false;
							}

							std::string globalCheck = Element.substr(0, pos_dot);

							if (globalCheck != LastGlobalMarker_name){
								MakeError(ERROR_WRONG_INIT_LOCAL_MARKER, Line);
								return false;
							}
						}

					}
					else {

						// ѕользователь создаЄт новый маркер использу€ локальный метки

						if (LastGlobalMarker_name.size() == 0) {
							MakeError(ERROR_CREATE_ANONIM_MARKER, Line);
							return false;
						}

						marker = LastGlobalMarker_name + "." + Element.substr(1, pos_2dot - 1);

						if (Compiler::CheckName(Element.substr(1, pos_2dot - 1)) == false) {
							MakeError(ERROR_WRONG_ADRESS_NAME, Line);
							return false;
						}

						if (Markers.contains(marker)) {
							MakeError(ERROR_DUBLICAT_MARKER, Line);
							return false;
						}

					}

					adressed_code[Line] = CurrentAdress;


					Markers[marker] = CurrentAdress;

					LastMarker_name = marker;



					NeedCheckThatLineIndex[CounterForNeedCheck] = Line;
					CounterForNeedCheck++;

					if (Consts.contains(marker)) {
						MakeError(ERROR_COLLISION_BETWEEN_NAMES_MARKER_AND_CONST, Line);
						return false;
					}

					countCommandsAfterLastMarker = 0;
					continue;
					

				}


			}
			else if (!flag_have_dot && flag_have_2dot) {
				const std::string marker = Element.substr(0, pos_2dot);

				if (Markers.contains(marker)){
					MakeError(ERROR_DUBLICAT_MARKER, Line);
					return false;
				}

				NeedCheckThatLineIndex[CounterForNeedCheck] = Line;
				CounterForNeedCheck++;

				adressed_code[Line] = CurrentAdress;
				Markers[marker] = CurrentAdress;

				if (Consts.contains(marker)){
					MakeError(ERROR_COLLISION_BETWEEN_NAMES_MARKER_AND_CONST, Line);
					return false;
				}
				LastMarker_name = marker;
				LastGlobalMarker_name = marker;
				countCommandsAfterLastMarker = 0;
				continue;
			}
			else if (flag_have_dot && !flag_have_2dot){
				MakeError(ERROR_UNKNOWN_COMMAND, Line);
				return false;
			}
			else {

				ToLowerAll(Element);

				int bytes = GetCountBytes(Element);
				int params = GetCountParams(Element);

				if (bytes == 0){
					MakeError(ERROR_UNKNOWN_COMMAND, Line);
					return false;
				}

				if (params != splited_code[Line].size() - 1) {
					MakeError(ERROR_INCORECT_PARAMS, Line);
					return false;
				}


				adressed_code[Line] = CurrentAdress;
				CurrentAdress += bytes;


				if (CurrentAdress > MAX16BIT)
				{
					MakeError(ERROR_OVERFLOW_ADRESS, Line);
					return false;
				}

				if (params > 0){
					NeedCheckThatLineIndex[CounterForNeedCheck] = Line;
					CounterForNeedCheck++;
				}


			}


			countCommandsAfterLastMarker++;

			break;

		}




	}

	return true;
}

bool CompilerStable::Step2_ReplaceWithDirectValues() {
	splited_code_raw = splited_code;

	int Size_NeedCheckThatLineIndex = CounterForNeedCheck;

	std::string LastMarker = "";


	for (int index = 0; index < Size_NeedCheckThatLineIndex; ++index) {
		int Line = NeedCheckThatLineIndex[index];
		const PosDotInfo pdi = PosDotForNeedLine[Line];
		for (int element = 0; element < splited_code[Line].size(); element++) {
			std::string Element = splited_code[Line][element];



			if (pdi.flag_have_dot && pdi.flag_have_2dot) {

				std::string command = Element.substr(pdi.pos_dot + 1, (pdi.pos_2dot - pdi.pos_dot) - 1);
				ToLowerAll(command);

				if (command == "set") {
					element++;

					while (splited_code[Line].size() > element) {
						auto value = FromString2Int(splited_code[Line][element]);


						if (value.second == TypeValue::UNKNOWN){

							auto Const_value = Consts.find(splited_code[Line][element]);

							if (Const_value == Consts.end()){
								MakeError(ERROR_WRONG_CONST, Line);
								return false;
							}
							if (Const_value->second > MAX8BIT){
								MakeError(ERROR_OVERFLOW_VALUE_8BIT, Line);
								return false;
							}

							splited_code[Line][element] = std::to_string(Const_value->second);
						}

						element++;

					}
					break;

				}
				else if (command == "adr") {
					break;
				}
				else if (command == "const") {
					break;
				}
				else {
					continue;
				}
				break;



			}
			else if (!pdi.flag_have_dot && pdi.flag_have_2dot) {
				std::string marker = Element.substr(0, pdi.pos_2dot);
				LastMarker = marker;
				continue;
			}
			else {
				ToLowerAll(Element);

				const static robin_hood::unordered_flat_set<std::string> instruction_imm8 = { "adi","sui","ani","ori","aci","sbi","xri","cpi","in","out","rst" };
				const static robin_hood::unordered_flat_set<std::string> instruction_imm16 = { "shld","sta","lhld","lda","call","cnz","cnc","cpo","cp","cz","cc","cpe","cm","jmp","jnz","jnc","jpo","jp","jz","jc","jpe","jm" };

				if (Element == "mvi")
				{
					auto value = FromString2Int(splited_code[Line][element + 2]);

					if (value.second == TypeValue::UNKNOWN)
					{

						auto ConstObject = Consts.find(splited_code[Line][element + 2]);

						if (ConstObject == Consts.end()) {
							MakeError(ERROR_WRONG_CONST, Line);
							return false;
						}
						if (ConstObject->second > MAX8BIT){
							MakeError(ERROR_OVERFLOW_VALUE_8BIT, Line);
							return false;
						}

						splited_code[Line][element + 2] = std::to_string(ConstObject->second);

					}

				}
				else if (instruction_imm8.contains(Element)){

					auto value = FromString2Int(splited_code[Line][element + 1]);

					if (value.second == TypeValue::UNKNOWN)
					{

						auto ConstObject = Consts.find(splited_code[Line][element + 1]);

						if (ConstObject == Consts.end()) {
							MakeError(ERROR_WRONG_CONST, Line);
							return false;
						}
						if (ConstObject->second > MAX8BIT) {
							MakeError(ERROR_OVERFLOW_VALUE_8BIT, Line);
							return false;
						}

						splited_code[Line][element + 1] = std::to_string(ConstObject->second);

					}

				}
				else if (instruction_imm16.contains(Element)) {
					auto value = FromString2Int(splited_code[Line][element + 1]);

					if (value.second == TypeValue::UNKNOWN)
					{
						if (splited_code[Line][element + 1][0] == '.') {
							splited_code[Line][element + 1] = LastMarker + splited_code[Line][element + 1];
						}


						auto ConstObject = Consts.find(splited_code[Line][element + 1]);
						auto MarkerObject = Markers.find(splited_code[Line][element + 1]);

						if (ConstObject == Consts.end() && MarkerObject == Markers.end()){
							MakeError(ERROR_WRONG_CONST_OR_MARKER, Line);
							return false;
						}

						if (ConstObject != Consts.end())
						{
							if (ConstObject->second > MAX16BIT){
								MakeError(ERROR_OVERFLOW_VALUE_16BIT, Line);
								return false;
							}

							splited_code[Line][element + 1] = std::to_string(ConstObject->second);
						}
						else {
							if (MarkerObject->second > MAX16BIT) {
								MakeError(ERROR_OVERFLOW_VALUE_16BIT, Line);
								return false;
							}

							splited_code[Line][element + 1] = std::to_string(MarkerObject->second);
						}


					}

				}
				else if (Element == "lxi") {
					auto value = FromString2Int(splited_code[Line][element + 2]);

					if (value.second == TypeValue::UNKNOWN){

						if (splited_code[Line][element + 2][0] == '.') {
							splited_code[Line][element + 2] = LastMarker + splited_code[Line][element + 2];
						}

						auto ConstObject = Consts.find(splited_code[Line][element + 2]);
						auto MarkerObject = Markers.find(splited_code[Line][element + 2]);

						if (ConstObject == Consts.end() && MarkerObject == Markers.end()) {
							MakeError(ERROR_WRONG_CONST_OR_MARKER, Line);
							return false;
						}

						if (ConstObject != Consts.end())
						{
							if (ConstObject->second > MAX16BIT) {
								MakeError(ERROR_OVERFLOW_VALUE_16BIT, Line);
								return false;
							}

							splited_code[Line][element + 2] = std::to_string(ConstObject->second);
						}
						else {
							if (MarkerObject->second > MAX16BIT) {
								MakeError(ERROR_OVERFLOW_VALUE_16BIT, Line);
								return false;
							}

							splited_code[Line][element + 2] = std::to_string(MarkerObject->second);
						}

					}

				}
			}
		}
	}

	return true;

}

bool CompilerStable::Step3_MakeByteArray() {

	auto FindIndexMarkerByAdress = [](const robin_hood::unordered_flat_map<std::string, uint16_t>& arr, const uint16_t& Adress) {
		for (auto& n : arr) {
			if (n.second == Adress)
				return n.first;
		}
		return std::string("");

	};



	for (int Line = 0; Line < splited_code.size(); ++Line) {

		if (splited_code[Line].size() == 0) continue;

		const PosDotInfo pdi = PosDotForNeedLine[Line];

		for (int i_element = 0; i_element < splited_code[Line].size(); ++i_element) {

			std::string Element = splited_code[Line][i_element];


			if (pdi.flag_have_dot && pdi.flag_have_2dot) {
				std::string command = Element.substr(pdi.pos_dot + 1, (pdi.pos_2dot - pdi.pos_dot) - 1);
				ToLowerAll(command);

				if (command == "adr") {
					break;
				}
				else if (command == "set") {
					i_element++;
					while (splited_code[Line].size() > i_element) {
						auto value = FromString2Int(splited_code[Line][i_element]);

						OpcodeAdressed ca;
						ca.adress_l = adressed_code[Line] % 256;
						ca.adress_h = adressed_code[Line] / 256;
						ca.opcode = value.first;

						Compiler::CompilerOutput.Line_and_Adress[Line] = adressed_code[Line] ;
						ca.command = ".set: " + splited_code_raw[Line][i_element];

						std::string MarkerName = FindIndexMarkerByAdress(Markers,adressed_code[Line]);
						if (MarkerName.empty() == false) {
							ca.marker = MarkerName;
							ca.adress_marker_l = ca.adress_l;
							ca.adress_marker_h = ca.adress_h;
						}


						CompilerOutput.Opcodes.emplace_back(ca);

						i_element++;
						adressed_code[Line]++;
					}
					continue;
				}
				else if (command == "const") {
					break;
				}
				else {
					continue;
				}
			}
			else if (!pdi.flag_have_dot && pdi.flag_have_2dot) {
				continue;
			}
			else {
				std::vector<uint8_t> opcodes = Compiler::TranslateInstruction(splited_code[Line]);

				if (CompilerOutput.Error != TypeTranslatorError::NOTHING) {
					CompilerOutput.LineError = Line;
					return false;
				}

				std::string command = "";

				for (int k = 0; k < splited_code[Line].size(); ++k) {
					command += splited_code_raw[Line][k] + " ";
				}

				for (int k = 0; k < opcodes.size(); ++k)
				{
					//cout << std::hex << int(opcodes[k])<< std::dec << endl;
					OpcodeAdressed ca;
					ca.adress_l = (adressed_code[Line] + k) % 256;
					ca.adress_h = (adressed_code[Line] + k) / 256;
					ca.opcode = opcodes[k];
					if (k == 0)
					{
						
						Compiler::CompilerOutput.Line_and_Adress[Line] = adressed_code[Line];
						ca.command = command;

						std::string MarkerName = FindIndexMarkerByAdress(Markers, adressed_code[Line]);
						if (MarkerName.empty() == false) {
							ca.marker = MarkerName;
							ca.adress_marker_l = ca.adress_l;
							ca.adress_marker_h = ca.adress_h;
						}
					}

					CompilerOutput.Opcodes.emplace_back(ca);

				}

			}


			break;
		}


	}


	return true;

}