#ifndef I8080_CARETAKER_MOMENTO_H
#define I8080_CARETAKER_MOMENTO_H

#include "Core/Emulator/Processors/Intel8080/Disassembler/I8080.Disassembler.h"
#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Emulator/History/Caretaker.Momento.h"
#include "Core/Emulator/History/Momento.h"
#include "Core/Emulator/Processors/Intel8080/History/Momento/I8080.Momento.h"

#include "Utils/Text/Text.h"
#include <vector>
#include <string>

class I8080_Caretaker_Momento : public Caretaker_Momento
{
public:
	I8080_Caretaker_Momento(I8080* processor);
	~I8080_Caretaker_Momento();

	std::vector<std::pair<std::string, std::string>> GetHistory() override;
};





#endif // !I8080_CARETAKER_MOMENTO_H
