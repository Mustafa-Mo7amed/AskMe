#include <optional>
#include "UserService.h"

UserService::UserService(UsersRepository& repo): repository(repo) {}

const std::map<int, User>& UserService::GetAllUsers() const { return repository.GetAllUsers(); }

std::optional<User> UserService::FindUser(int id) const {
    return repository.FindById(id);
}

const User& UserService::AddUser(std::string name, std::string password, std::string email,
                                 bool allow_anonymous_questions) const {
    return repository.AddUser(std::move(name), std::move(password), std::move(email), allow_anonymous_questions);
}

bool UserService::SetAllowAnonymousQuestions(int user_id, bool allow) const {
    return repository.SetAllowAnonymousQuestions(user_id, allow);
}