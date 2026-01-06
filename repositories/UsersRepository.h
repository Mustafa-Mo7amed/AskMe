#pragma once
#include <map>
#include <models/User.h>

class UsersRepository {
    std::map<int, User> users;
    void LoadUsers();
    void SaveChanges();
public:
    [[nodiscard]] const std::map<int, User>& GetAllUsers() const;

    [[nodiscard]] const User& FindById(int id) const;

    void AddUser(User user);
};