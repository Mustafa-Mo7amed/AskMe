#include <regex>
#include <algorithm>
#include <bits/ranges_algo.h>
#include "Validator.h"

bool Validator::IsEmptyOrBlank(const std::string& str) {
    return str.empty() || std::ranges::all_of(str.begin(), str.end(), [](const char c) {
        return std::isspace(c);
    });
}

bool Validator::IsValidEmail(const std::string& email) {
    static const std::regex pattern(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return std::regex_match(email, pattern);
}