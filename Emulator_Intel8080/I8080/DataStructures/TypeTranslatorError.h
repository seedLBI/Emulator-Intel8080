#ifndef TYPE_TRANSLATOR_ERROR_H
#define TYPE_TRANSLATOR_ERROR_H


#include <string>

enum TypeTranslatorError {
    NOTHING,
    ERROR_UNKNOWN_COMMAND = 1,
    ERROR_WTF,                                      // USED
    ERROR_INCORECT_PARAMS,                          // USED
    ERROR_INCORECT_VALUE,                           // USED
    ERROR_INCORECT_REGISTER,                        // USED
    ERROR_UNKNOWN_VALUE_DEREKTIV,                   // USED
    ERROR_DEREKTIV_CONST_WITHOUT_NAME,              // USED
    ERROR_DEREKTIV_WITHOUT_VALUE,                   // USED
    ERROR_DEREKTIV_WITHOUT_ADRESS,                  // USED
    ERROR_CREATE_ANONIM_MARKER,                     // USED
    ERROR_WRONG_ADRESS_NAME,                        // USED
    ERROR_WRONG_DEREKTIV_CONST_NAME,                // USED
    ERROR_WRONG_CONST,                              // USED
    ERROR_WRONG_CONST_OR_MARKER,                    // USED
    ERROR_WRONG_LOCAL_MARKER,                       // USED
    ERROR_WRONG_REGISTER_COMMAND,
    ERROR_WRONG_VALUE_REGISTER_COMMAND,
    ERROR_WRONG_ADRESSED_COMMAND,
    ERROR_WRONG_VALUE_ADRESSED_COMMAND,
    ERROR_WRONG_MARKER_ADRESS_COMMAND,
    ERROR_DUBLICAT_MARKER,                          // USED
    ERROR_DUBLICAT_CONST,                           // USED
    ERROR_COLLISION_BETWEEN_NAMES_MARKER_AND_CONST, // USED
    ERROR_OVERFLOW_ADRESS,                          // USED
    ERROR_OVERFLOW_VALUE_8BIT,                      // USED
    ERROR_OVERFLOW_VALUE_16BIT,                     // USED
    ERROR_WHERE_SECOND_DOUBLE_QUOTE,                // USED
    ERROR_UNSUPPORTED_SYMBOL,
};


std::string GetErrorInfo(const int& type);


#endif // !TYPE_TRANSLATOR_ERROR_H
