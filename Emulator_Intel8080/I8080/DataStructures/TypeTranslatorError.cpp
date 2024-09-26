#include "TypeTranslatorError.h"

std::string GetErrorInfo(const int& type) {
    switch (type)
    {
    case ERROR_UNKNOWN_COMMAND:
        return u8"Неизвестная или неверно записанная команда.";
        break;
    case ERROR_WTF:
        return u8"Я не могу определить ошибку, ты что написал?";
        break;
    case ERROR_INCORECT_PARAMS:
        return u8"Неправильно заданы параметры.";
        break;
    case ERROR_INCORECT_REGISTER:
        return u8"Такого регистра не существует.";
        break;
    case ERROR_INCORECT_VALUE:
        return u8"Неправильно задано число.";
        break;
    case ERROR_DEREKTIV_CONST_WITHOUT_NAME:
        return u8"Назови константу как-нибудь.";
        break;
    case ERROR_DEREKTIV_WITHOUT_VALUE:
        return u8"В дерективе отсутствует число, добавь его.";
        break;
    case ERROR_DEREKTIV_WITHOUT_ADRESS:
        return u8"В дерективе отсутствует адрес, добавь его.";
        break;
    case ERROR_UNKNOWN_VALUE_DEREKTIV:
        return u8"Неправильно задано число в дерективе.";
        break;
    case ERROR_WRONG_ADRESS_NAME:
        return u8"Имя адреса не должно начинаться с цифр и знаков.";
        break;
    case ERROR_WRONG_DEREKTIV_CONST_NAME:
        return u8"Константа не должна начинаться с цифр и знаков.";
        break;
    case ERROR_WRONG_CONST:
        return u8"Такой константы не существует.";
        break;
    case ERROR_WRONG_CONST_OR_MARKER:
        return u8"Такой константы или маркера не существует.";
        break;
    case ERROR_CREATE_ANONIM_MARKER:
        return u8"Прежде чем использовать анонимный маркер нужно поставить глобальный маркер";
        break;
    case ERROR_WRONG_LOCAL_MARKER:
        return u8"Такого маркера не существует";
        break;
    case ERROR_WRONG_REGISTER_COMMAND:
        return u8"Неправильно задана команда.";
        break;
    case ERROR_WRONG_VALUE_REGISTER_COMMAND:
        return u8"Неправильно задано значение в команде.";
        break;
    case ERROR_WRONG_ADRESSED_COMMAND:
        return u8"Неправильно задана команда.";
        break;
    case ERROR_WRONG_VALUE_ADRESSED_COMMAND:
        return u8"Неправильно задано значение адреса в команде.";
        break;
    case ERROR_WRONG_MARKER_ADRESS_COMMAND:
        return u8"Неправильно задан маркер в команде, такого маркера нету.";
        break;
    case ERROR_OVERFLOW_ADRESS:
        return u8"При размешении опкодов адрес ушёл за границы памяти (64 Кбайт), оптимизируй код.";
        break;
    case ERROR_OVERFLOW_VALUE_8BIT:
        return u8"Ты зашёл за границы 8 битного числа, пиши меньше. (0 - 255) (0x0 - 0xff)";
        break;
    case ERROR_OVERFLOW_VALUE_16BIT:
        return u8"Ты зашёл за границы 16 битного числа, пиши меньше. (0 - 65535) (0x0 - 0xffff)";
        break;
    case ERROR_DUBLICAT_MARKER:
        return u8"Такое имя для маркера уже существует, придумай другое.";
        break;
    case ERROR_DUBLICAT_CONST:
        return u8"Такое имя для константы уже существует, придумай другое.";
        break;
    case ERROR_COLLISION_BETWEEN_NAMES_MARKER_AND_CONST:
        return u8"У тебя имя константы с именем маркера совпало, не допускай этого.";
        break;
    case ERROR_WHERE_SECOND_SINGLE_QUOTE:
        return u8"Нужно всегда закрывать одинарные ковычки!";
        break;
    case ERROR_WHERE_SECOND_DOUBLE_QUOTE:
        return u8"Нужно всегда закрывать двойные ковычки!";
        break;
    default:
        return u8"Неизвестная ошибка\n";
        break;
    }
}

