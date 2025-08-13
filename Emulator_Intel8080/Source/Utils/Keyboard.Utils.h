#ifndef KEYBOARD_UTILS_H
#define KEYBOARD_UTILS_H

#include "ThirdParty/OpenGL/include/glfw3.h"
#include "robin_hood.h"
#include <string>
#include <vector>


std::string KeyToStr(const int& key);

std::string KeyToHumanReadbleStr(const int& key);

int StrToKey(const std::string& str);

std::vector<int> GetNumberPressedKeys(GLFWwindow* window);



#endif // !KEYBOARD_UTILS_H
