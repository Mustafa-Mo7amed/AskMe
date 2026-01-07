#pragma once

#include <string>

class Validator {
public:
    static bool IsEmptyOrBlank(const std::string& str);

    static bool IsValidEmail(const std::string& email);
};