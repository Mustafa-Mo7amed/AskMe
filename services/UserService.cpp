#include "UserService.h"

UserService::UserService(UsersRepository& repo): repository(repo) {}

const std::map<int, User>& UserService::GetAllUsers() const { return repository.GetAllUsers(); }

bool UserService::SetAllowAnonymousQuestions(int user_id, bool allow) const {
    return repository.SetAllowAnonymousQuestions(user_id, allow);
}