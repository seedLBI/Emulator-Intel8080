#ifndef INFO_INSTRUCTION_STRUCTURES_H
#define INFO_INSTRUCTION_STRUCTURES_H

#include <vector>
#include <string>
#include <any>


enum class ENUM_Arguments {
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
enum class ENUM_Bytes {
	Opcode,
	Value,
	Value_low,
	Value_high,
	Adress_low,
	Adress_high,
	MAX
};
enum class ENUM_FlagsState {
	Unaffected,
	Affected,
	Reset,
	Set
};
enum class ENUM_TicksMean {
	Condition,
	M_Used,
	Always
};
enum class ENUM_Category {
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

enum class ENUM_Branching {
	IF,
	ELSE
};


struct FlagsList {
	ENUM_FlagsState Sign;
	ENUM_FlagsState Zero;
	ENUM_FlagsState ACarry;
	ENUM_FlagsState Parity;
	ENUM_FlagsState Carry;

	FlagsList(const ENUM_FlagsState& Sign,
		const ENUM_FlagsState& Zero,
		const ENUM_FlagsState& ACarry,
		const ENUM_FlagsState& Parity,
		const ENUM_FlagsState& Carry) {

		this->Sign = Sign;
		this->Zero = Zero;
		this->ACarry = ACarry;
		this->Parity = Parity;
		this->Carry = Carry;
	}
};
struct InstructionInfo {
	std::vector<ENUM_Arguments>			_Arguments;
	std::vector<ENUM_Bytes>				_Bytes;
	std::string							_Declaration;
	std::vector<std::vector<std::any>>	_PseudoCode;
	std::vector<int>					_Ticks;
	ENUM_TicksMean						_TicksMean;
	FlagsList							_Flags_status;
	std::vector<ENUM_Category>			_Categories;
};
struct CommandArguments {
	std::string type_argument;
	std::vector<std::string> available_values;
};


CommandArguments ENUM_Arguments_to_CommandArguments(const ENUM_Arguments& object);
std::string ENUM_Bytes_to_str(const ENUM_Bytes& object);
std::string ENUM_FlagsState_to_str(const ENUM_FlagsState& object);
std::string Get_info_ticks_mean(std::vector<int> ticks, ENUM_TicksMean mean);

std::string ENUM_Branching_to_str(const ENUM_Branching& object);
#endif // !1
