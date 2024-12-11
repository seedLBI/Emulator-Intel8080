#ifndef INFO_INSTRUCTION_STRUCTURES_H
#define INFO_INSTRUCTION_STRUCTURES_H

#include <vector>
#include <string>
#include <any>


enum class InstructionArguments {
	Register8,
	Register16_WithSP,
	Register16_WithSP_low,
	Register16_WithSP_high,
	Register16_WithPSW,
	Register16_WithPSW_low,
	Register16_WithPSW_high,
	Register16_OnlyBD,
	Value8,
	Value16,
	Value16_low,
	Value16_high,
	ValueSpecial,
	ArgumentsCount
};
enum class InstructionBytes {
	Opcode,
	Value,
	Value_low,
	Value_high,
	Adress_low,
	Adress_high,
	MAX
};
enum class InstructionFlagsState {
	Unaffected,
	Affected,
	Reset,
	Set
};
enum class InstructionTicksMean {
	Condition,
	M_Used,
	Always
};
enum class InstructionCategory {
	MOVE_LOAD_STORE,
	STACK_OPS,
	JUMP,
	CALL,
	RETURN,
	RESTART,
	INPUT_OUTPUT,
	INCREMENT,
	DECREMENT,
	ADD,
	SUBTRACT,
	LOGICAL,
	ROTATE,
	SPECIALS,
	CONTROL
};

enum class InstructionBranching {
	IF,
	ELSE
};


struct FlagsList {
	InstructionFlagsState Sign;
	InstructionFlagsState Zero;
	InstructionFlagsState ACarry;
	InstructionFlagsState Parity;
	InstructionFlagsState Carry;

	FlagsList(const InstructionFlagsState& Sign,
		const InstructionFlagsState& Zero,
		const InstructionFlagsState& ACarry,
		const InstructionFlagsState& Parity,
		const InstructionFlagsState& Carry) {

		this->Sign = Sign;
		this->Zero = Zero;
		this->ACarry = ACarry;
		this->Parity = Parity;
		this->Carry = Carry;
	}
};
struct InstructionInfo {
	std::vector<InstructionArguments>			_Arguments;
	std::vector<InstructionBytes>				_Bytes;
	std::string							_Declaration;
	std::vector<std::vector<std::any>>	_PseudoCode;
	std::vector<int>					_Ticks;
	InstructionTicksMean						_TicksMean;
	FlagsList							_Flags_status;
	std::vector<InstructionCategory>			_Categories;
	std::vector<uint8_t>				_Opcodes;
};
struct CommandArguments {
	std::string type_argument;
	std::vector<std::string> available_values;
};


CommandArguments ENUM_Arguments_to_CommandArguments(const InstructionArguments& object);
std::string ENUM_Bytes_to_str(const InstructionBytes& object);
std::string ENUM_FlagsState_to_str(const InstructionFlagsState& object);
std::string Get_info_ticks_mean(std::vector<int> ticks, InstructionTicksMean mean);

std::string ENUM_Branching_to_str(const InstructionBranching& object);
#endif // !1
