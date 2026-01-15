#pragma once
#include <map>
#include <vector>
#include <optional>
#include "models/User.h"
#include "repositories/UsersRepository.h"

class UserService {
    UsersRepository& repository;

public:
    explicit UserService(UsersRepository& repo);

    [[nodiscard]] const std::map<int, User>& GetAllUsers() const;

    [[nodiscard]] std::optional<User> FindUser(int id) const;

    [[nodiscard]] std::optional<User> FindUser(std::string email) const;

    [[nodiscard]] const User& AddUser(std::string name, std::string password, std::string email,
                                      bool allow_anonymous_questions) const;

    bool SetAllowAnonymousQuestions(int user_id, bool allow) const;
};