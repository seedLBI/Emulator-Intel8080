#include "Caretaker.Momento.h"

I8080_Caretaker_Momento::I8080_Caretaker_Momento(I8080* processor) : Caretaker_Momento(processor) {

}

I8080_Caretaker_Momento::~I8080_Caretaker_Momento(){

}

std::vector<std::pair<std::string, std::string>> I8080_Caretaker_Momento::GetHistory() {
	static std::vector<std::pair<std::string, std::string>> output;

	if (Caretaker_Momento::changed)
	{
		output.clear();
		output.resize(momentos.size());

		Caretaker_Momento::changed = false;


		for (int i = 0; i < momentos.size(); i++) {

			auto I8080moment = dynamic_cast<I8080_Momento*>(momentos[i].get());

			auto data = Instructuion_to_String(I8080moment->Get_opcode(), I8080moment->Get_data_first_byte(), I8080moment->Get_data_second_byte());


			std::string First = int2string_0x_Hex(I8080moment->Get_opcode());

			std::string Second = "";

			for (int j = 0; j < data.first.size(); j++) {
				Second += data.first[j];
			}

			if (output.size() - 1 >= i) {
				output[i] = { First, Second };
			}
			else
				break;

		}
	}
	else {
		return output;
	}




	return output;
}