#include "TypesCommand.h"

TypesCommands GetTypeCommand(std::string command) {
    auto FindInArray = [](const std::vector<std::string>array, std::string to_find) {
        return std::find(array.begin(), array.end(), to_find) != array.end();
        };


    // Prepare line to checking
    EraseSideSpaces(command);
    if (command.find(" ") != std::string::npos)
        command.erase(command.begin() + command.find(" "), command.end());
    ToLowerAll(command);





    const std::vector<std::string>  MovingData_Command = { "mov","mvi","lxi","lda","lhld","sta","shld","ldax","stax","xchg" };
    const std::vector<std::string>  Adding_Command = { "add","adi","adc","aci","inr","inx","dad" };
    const std::vector<std::string>  Subtracting_Command = { "sub","sui","sbb","sbi","dcr","dcx" };
    const std::vector<std::string>  Logic_Command = { "ana","ani","ora","ori","xra","xri","rlc","rrc","ral","rar","cma","stc","cmc" };
    const std::vector<std::string>  Compare_Command = { "cmp","cpi" };
    const std::vector<std::string>  Calls_Command = { "call","cnz","cz","cnc","cc","cpo","cpe","cp","cm","rst" };
    const std::vector<std::string>  Returns_Command = { "ret","rnz","rz","rnc","rc","rpo","rpe","rp","rm" };
    const std::vector<std::string>  Jumps_Command = { "jmp","jz","jnz","jc","jnc","jp","jm","jpo","jpe" };
    const std::vector<std::string>  Input_output_Command = { "in","out" };
    const std::vector<std::string>  Stack_Command = { "sphl","push","pop","xthl" };
    const std::vector<std::string>  Other_Command = { "pchl","nop","hlt" };
    const std::vector<std::string>  derektiv_Command = { ".set:" };

    const std::vector<std::vector<std::string>> arrays = {
        MovingData_Command,
        Adding_Command,
        Subtracting_Command,
        Logic_Command,
        Compare_Command,
        Calls_Command,
        Returns_Command,
        Jumps_Command,
        Input_output_Command,
        Stack_Command,
        Other_Command,
        derektiv_Command };

    for (int i = 0; i < arrays.size(); ++i) {
        if (FindInArray(arrays[i], command))
            return TypesCommands(i);
    }
    return TypesCommands::Wrong_command;

}


std::vector<ImVec4> Colors_TypesCommands ={
        ImVec4(0.28f, 1.f, 0.89f, 1.f),
        ImVec4(1.f, 0.f, 0.4f, 1.f),
        ImVec4(0.65f, 0.f, 1.f, 1.f),
        ImVec4(0.51f, 0.74f, 0.f, 1.f),
        ImVec4(0.73f, 0.74f, 0.f, 1.f),
        ImVec4(1.f, 0.2f, 0.f, 1.f),
        ImVec4(1.f, 0.42f, 0.f, 1.f),
        ImVec4(0.f, 0.43f, 1.f, 1.f),
        ImVec4(1.f, 0.84f, 0.f, 1.f),
        ImVec4(1.f, 1.f, 1.f, 1.f),
        ImVec4(0.82f, 0.79f, 0.75f, 1.f),
        ImVec4(0.7f, 0.2f, 0.2f, 1.f), };


