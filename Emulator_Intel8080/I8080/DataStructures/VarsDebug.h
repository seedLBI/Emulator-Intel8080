#ifndef VARS_DEBUG_H
#define VARS_DEBUG_H

#include <string>

struct VarsDebug {
    std::string name_marker;
    int adress;
    bool isArray;
    int count_elements;

    VarsDebug(const std::string& name_marker,const int& address,const bool& isArray, const int& count_elements)
        : name_marker(name_marker), adress(adress), isArray(isArray), count_elements(count_elements) {}
};


#endif // !VARS_DEBUG_H
