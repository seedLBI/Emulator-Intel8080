#include "Emulator/Compilier/Stable/Compiler.Stable.h"

CompilerStable::CompilerStable(){

}

CompilerStable::~CompilerStable(){

}

TranslatorOutput CompilerStable::Compile(const std::vector<std::string>& Code) {
	ClearAllArrays();

	adressed_code.resize(Code.size(), 0);

	splited_code = Compiler::split_code(Code);

	if (Compiler::CompilerOutput.Error != TypeTranslatorError::NOTHING)
		return Compiler::CompilerOutput;



	if (!Step1_MarkingAdresses()) {
		return Compiler::CompilerOutput;
	}

	return Compiler::CompilerOutput;
}

void CompilerStable::MakeError(const TypeTranslatorError& typeError, const int& Line) {
	Compiler::CompilerOutput.Error = typeError;
	Compiler::CompilerOutput.LineError = Line;
}

void CompilerStable::ClearAllArrays() {
	Compiler::CompilerOutput.Clear();
	adressed_code.clear();
	Consts.clear();
	Markers.clear();
	Vars.clear();
}

bool CompilerStable::Step1_MarkingAdresses() {

	int CurrentAdress = 0;
	int countCommandsAfterLastMarker = 0;

	std::string LastMarker_name;

	std::string LastGlobalMarker_name;
	std::string  LastLocalMarker_name;


	for (int Line = 0; Line < splited_code.size(); ++Line) {

		if (splited_code[Line].size() == 0) continue;

		for (int i_element = 0; i_element < splited_code[Line].size(); ++i_element){

			const std::string Element = splited_code[Line][i_element];

			if (Compiler::IsAllSpecialSymbols(Element)){
				MakeError(ERROR_WTF, Line);
				return false;
			}

			const size_t pos_dot = Element.find_first_of(".");
			const size_t pos_2dot = Element.find_first_of(":");
			const bool flag_have_dot = pos_dot != string::npos;
			const bool flag_have_2dot = pos_2dot != string::npos;

			const bool isDerektiv_or_localMarker = flag_have_dot && flag_have_2dot;


			if (isDerektiv_or_localMarker) {

				string command = Element.substr(pos_dot + 1, (pos_2dot - pos_dot) - 1);
				ToLowerAll(command);

				const bool haveNextElements = splited_code[Line].size() > i_element;

				if (command == "adr") {

					if (!haveNextElements) {
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



						const auto value_const = Compiler::FromString2Int(splited_code[Line][i_element + 2]);

						if (value_const.second == Compiler::TypeValue::UNKNOWN) {
							MakeError(ERROR_UNKNOWN_VALUE_DEREKTIV, Line);
							return false;
						}
						if (value_const.first > MAX8BIT) {
							MakeError(ERROR_OVERFLOW_VALUE_16BIT, Line);
							return false;
						}

					}

				}
				else {

				}


			}


			countCommandsAfterLastMarker++;

			break;

		}




	}

	return true;
}