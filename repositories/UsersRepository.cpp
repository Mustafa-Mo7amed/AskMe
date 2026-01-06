#include "UsersRepository.h"
#include <stdexcept>

void UsersRepository::LoadUsers() {}

void UsersRepository::SaveChanges() {}

[[nodiscard]] const std::map<int, User>& UsersRepository::GetAllUsers() const { return users; }

[[nodiscard]] const User& UsersRepository::FindById(int id) const {
    auto it = users.find(id);
    if (it == users.end()) {
        throw std::runtime_error("User not found");
    }
    return it->second;
}

void UsersRepository::AddUser(User user) {
    auto [it, inserted] =
            users.emplace(user.GetId(), std::move(user));
    if (!inserted) {
        throw std::runtime_error("User with same ID already exists");
    }
}