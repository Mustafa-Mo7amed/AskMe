#pragma once
#include <string>

struct UserSignUpData {
    std::string name;
    std::string email;
    std::string password;
    bool allow_anonymous_questions;

    UserSignUpData(std::string name,  std::string email, std::string password,
                   bool allow_anonymous_questions)
        : name(std::move(name)),
          email(std::move(email)),
          password(std::move(password)),
          allow_anonymous_questions(allow_anonymous_questions) {}
};