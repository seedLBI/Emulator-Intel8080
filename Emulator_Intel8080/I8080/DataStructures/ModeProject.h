#ifndef MODE_PROJECT_H
#define MODE_PROJECT_H


#include <string>



enum class ModeProject {
    USER,
    BIN,
    COM
};

std::string ModeProject_To_Str(const ModeProject& mode);




#endif
