#pragma once
#include <string>

struct UserLoginData {
    int id;
    std::string password;

    UserLoginData(int id, std::string password): id(id), password(std::move(password)) {}
};