#pragma once
#include <map>
#include <vector>
#include "models/User.h"

class UsersRepository {
    static const std::string DATA_FILENAME;

    static int LastId;

    std::map<int, User> users;

    void LoadUsers();

    void SaveChanges();

    static std::string UserToLine(const User& user);

    static std::vector<std::string> PrepareToSave(const std::vector<User>& users);

    static int GenerateId();

public:
    UsersRepository();
    [[nodiscard]] const std::map<int, User>& GetAllUsers() const;

    [[nodiscard]] std::optional<User> FindById(int id) const;

    const User& AddUser(std::string name, std::string password, std::string email, bool allow_anonymous_questions);

    bool SetAllowAnonymousQuestions(int user_id, bool allow);
};