#ifndef TYPES_COMMAND_H
#define TYPES_COMMAND_H

#include <string>
#include <vector>
#include "Utils/TextUtils.h"
#include "imgui.h"

enum TypesCommands {
    MovingData,
    Adding,
    Subtracting,
    Logic,
    Compare,
    Calls,
    Returns,
    Jumps,
    Input_output,
    Stack,
    Other,
    Derektiv,
    Wrong_command
};
TypesCommands GetTypeCommand(std::string command);


extern std::vector<ImVec4> Colors_TypesCommands;

#endif // !TYPES_COMMAND_H
