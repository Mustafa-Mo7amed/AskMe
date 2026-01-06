#include "Validator.h"

#include <bits/ranges_algo.h>

bool Validator::IsEmptyOrBlank(const std::string& str) {
    return str.empty() || std::ranges::all_of(str.begin(), str.end(), [](const char c) {
        return std::isspace(c);
    });
}