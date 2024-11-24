#include "I8080.Caretaker.Momento.h"

I8080_Caretaker_Momento::I8080_Caretaker_Momento(I8080* processor) : Caretaker_Momento(processor) {

}

I8080_Caretaker_Momento::~I8080_Caretaker_Momento(){

}

std::vector<std::string> I8080_Caretaker_Momento::GetHistory() {
	std::vector<std::string> output(momentos.size());

	for (int i = 0; i < momentos.size(); i++){

		auto I8080moment = dynamic_cast<I8080_Momento*>(momentos[i].get());

		auto data = Instructuion_to_String(I8080moment->Get_opcode(), I8080moment->Get_data_first_byte(), I8080moment->Get_data_second_byte());
		std::string instruction = std::to_string(I8080moment->Get_opcode()) + " [";
		for (int j = 0; j < data.first.size(); j++){
			instruction += data.first[j];
		}
		instruction += "]";

		if (output.size() - 1 >= i)
			output[i] = instruction;
		else
			break;

	}

	return output;
}