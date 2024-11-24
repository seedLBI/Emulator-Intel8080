#ifndef VARS_DEBUG_H
#define VARS_DEBUG_H

#include <string>

struct VarsDebug {

    std::string name_marker = "";
    int adress = 0;
    bool isArray = false;
    int count_elements = 0;

    VarsDebug(const std::string& name_marker,const int& adress,const bool& isArray, const int& count_elements){
        this->name_marker = name_marker;
        this->adress = adress;
        this->isArray = isArray;
        this->count_elements = count_elements;
    }
};


#endif // !VARS_DEBUG_H
