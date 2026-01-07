#pragma once
#include <map>
#include "models/User.h"
#include "repositories/UsersRepository.h"

class UserService {
    UsersRepository& repository;
public:
    explicit UserService(UsersRepository& repo);
    [[nodiscard]] const std::map<int, User>& GetAllUsers() const;
    bool SetAllowAnonymousQuestions(int user_id, bool allow) const;
};