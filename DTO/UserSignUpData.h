#pragma once
#include <string>

struct UserSignUpData {
    std::string name;
    std::string password;
    std::string email;
    bool allow_anonymous_questions;
};
