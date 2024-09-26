#include "TypeTranslatorError.h"

std::string GetErrorInfo(const int& type) {
    switch (type)
    {
    case ERROR_UNKNOWN_COMMAND:
        return u8"����������� ��� ������� ���������� �������.";
        break;
    case ERROR_WTF:
        return u8"� �� ���� ���������� ������, �� ��� �������?";
        break;
    case ERROR_INCORECT_PARAMS:
        return u8"����������� ������ ���������.";
        break;
    case ERROR_INCORECT_REGISTER:
        return u8"������ �������� �� ����������.";
        break;
    case ERROR_INCORECT_VALUE:
        return u8"����������� ������ �����.";
        break;
    case ERROR_DEREKTIV_CONST_WITHOUT_NAME:
        return u8"������ ��������� ���-������.";
        break;
    case ERROR_DEREKTIV_WITHOUT_VALUE:
        return u8"� ��������� ����������� �����, ������ ���.";
        break;
    case ERROR_DEREKTIV_WITHOUT_ADRESS:
        return u8"� ��������� ����������� �����, ������ ���.";
        break;
    case ERROR_UNKNOWN_VALUE_DEREKTIV:
        return u8"����������� ������ ����� � ���������.";
        break;
    case ERROR_WRONG_ADRESS_NAME:
        return u8"��� ������ �� ������ ���������� � ���� � ������.";
        break;
    case ERROR_WRONG_DEREKTIV_CONST_NAME:
        return u8"��������� �� ������ ���������� � ���� � ������.";
        break;
    case ERROR_WRONG_CONST:
        return u8"����� ��������� �� ����������.";
        break;
    case ERROR_WRONG_CONST_OR_MARKER:
        return u8"����� ��������� ��� ������� �� ����������.";
        break;
    case ERROR_CREATE_ANONIM_MARKER:
        return u8"������ ��� ������������ ��������� ������ ����� ��������� ���������� ������";
        break;
    case ERROR_WRONG_LOCAL_MARKER:
        return u8"������ ������� �� ����������";
        break;
    case ERROR_WRONG_REGISTER_COMMAND:
        return u8"����������� ������ �������.";
        break;
    case ERROR_WRONG_VALUE_REGISTER_COMMAND:
        return u8"����������� ������ �������� � �������.";
        break;
    case ERROR_WRONG_ADRESSED_COMMAND:
        return u8"����������� ������ �������.";
        break;
    case ERROR_WRONG_VALUE_ADRESSED_COMMAND:
        return u8"����������� ������ �������� ������ � �������.";
        break;
    case ERROR_WRONG_MARKER_ADRESS_COMMAND:
        return u8"����������� ����� ������ � �������, ������ ������� ����.";
        break;
    case ERROR_OVERFLOW_ADRESS:
        return u8"��� ���������� ������� ����� ���� �� ������� ������ (64 �����), ����������� ���.";
        break;
    case ERROR_OVERFLOW_VALUE_8BIT:
        return u8"�� ����� �� ������� 8 ������� �����, ���� ������. (0 - 255) (0x0 - 0xff)";
        break;
    case ERROR_OVERFLOW_VALUE_16BIT:
        return u8"�� ����� �� ������� 16 ������� �����, ���� ������. (0 - 65535) (0x0 - 0xffff)";
        break;
    case ERROR_DUBLICAT_MARKER:
        return u8"����� ��� ��� ������� ��� ����������, �������� ������.";
        break;
    case ERROR_DUBLICAT_CONST:
        return u8"����� ��� ��� ��������� ��� ����������, �������� ������.";
        break;
    case ERROR_COLLISION_BETWEEN_NAMES_MARKER_AND_CONST:
        return u8"� ���� ��� ��������� � ������ ������� �������, �� �������� �����.";
        break;
    case ERROR_WHERE_SECOND_SINGLE_QUOTE:
        return u8"����� ������ ��������� ��������� �������!";
        break;
    case ERROR_WHERE_SECOND_DOUBLE_QUOTE:
        return u8"����� ������ ��������� ������� �������!";
        break;
    default:
        return u8"����������� ������\n";
        break;
    }
}

