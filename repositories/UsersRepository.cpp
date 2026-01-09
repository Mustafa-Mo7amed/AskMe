#include <stdexcept>
#include <optional>
#include "UsersRepository.h"

// TODO: should be the last user's id
int UsersRepository::LastId = 100;

int UsersRepository::GenerateId() {
    ++LastId;
    return LastId;
}

void UsersRepository::LoadUsers() {}

void UsersRepository::SaveChanges() {}

const std::map<int, User>& UsersRepository::GetAllUsers() const { return users; }

std::optional<User> UsersRepository::FindById(int id) const {
    auto it = users.find(id);
    if (it == users.end()) {
        return std::nullopt;
    }
    return it->second;
}

const User& UsersRepository::AddUser(std::string name, std::string password, std::string email, bool allow_anonymous_questions) {
    User user(GenerateId(), std::move(name), std::move(password), std::move(email), allow_anonymous_questions);
    auto [it, inserted] =
            users.emplace(user.GetId(), std::move(user));
    if (!inserted) {
        throw std::runtime_error("User with same ID already exists");
    }
    return it->second;
}

bool UsersRepository::SetAllowAnonymousQuestions(int user_id, bool allow) {
    auto it = users.find(user_id);
    if (it == users.end())
        return false;
    it->second.SetAllowAnonymousQuestions(allow);
    return true;
}