#pragma once
#include <map>
#include "models/User.h"

class UsersRepository {
    static int LastId;
    std::map<int, User> users;

    void LoadUsers();

    void SaveChanges();

    [[nodiscard]] static int GenerateId();

public:
    [[nodiscard]] const std::map<int, User>& GetAllUsers() const;

    [[nodiscard]] std::optional<User> FindById(int id) const;

    const User& AddUser(std::string name, std::string password, std::string email, bool allow_anonymous_questions);

    bool SetAllowAnonymousQuestions(int user_id, bool allow);
};