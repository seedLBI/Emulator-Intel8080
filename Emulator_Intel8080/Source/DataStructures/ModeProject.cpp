#include "ModeProject.h"

std::string ModeProject_To_Str(const ModeProject& mode) {
    switch (mode) {
    case ModeProject::USER:
        return u8"USER";
        break;
    case ModeProject::BIN:
        return u8"BIN";
        break;
    case ModeProject::COM:
        return u8"COM";
        break;
    default:
        break;
    }
}