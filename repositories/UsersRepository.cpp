#include "UsersRepository.h"
#include <stdexcept>

int UsersRepository::LastId = 100;

int UsersRepository::GenerateId() {
    ++LastId;
    return LastId;
}

void UsersRepository::LoadUsers() {}

void UsersRepository::SaveChanges() {}

const std::map<int, User>& UsersRepository::GetAllUsers() const { return users; }

const User& UsersRepository::FindById(int id) const {
    auto it = users.find(id);
    if (it == users.end()) {
        throw std::runtime_error("User not found");
    }
    return it->second;
}

User UsersRepository::AddUser(std::string name, std::string password, std::string email, bool allow_anonymous_questions) {
    User user(GenerateId(), std::move(name), std::move(password), std::move(email), allow_anonymous_questions);
    auto [it, inserted] =
            users.emplace(user.GetId(), std::move(user));
    if (!inserted) {
        throw std::runtime_error("User with same ID already exists");
    }
    return it->second;
}