#include <stdexcept>
#include <optional>
#include <sstream>
#include <vector>
#include "UsersRepository.h"
#include "core/util.h"

const std::string UsersRepository::DATA_FILENAME = "users.txt";

// TODO: should be the last user's id
int UsersRepository::LastId = 100;

int UsersRepository::GenerateId() {
    ++LastId;
    return LastId;
}

UsersRepository::UsersRepository() {
    LoadUsers();
}

void UsersRepository::LoadUsers() {
    auto allUsers = util::LoadFile(DATA_FILENAME);
    users.clear();
    for (const std::string& line : allUsers) {
        auto fields = util::SplitEscaped(line);
        if (fields.empty())
            continue;
        int id = stoi(fields[0]);
        std::string name = fields[1];
        std::string password = fields[2];
        std::string email = fields[3];
        bool anonymous_questions_allowed = stoi(fields[4]);
        User user(id, std::move(name), std::move(password), std::move(email), anonymous_questions_allowed);
        auto [it, inserted] = users.emplace(user.GetId(), std::move(user));
        if (!inserted) {
            throw std::runtime_error("User with same ID already exists");
        }
    }
    if (!users.empty())
        LastId = prev(users.end())->first;
}

void UsersRepository::SaveChanges() {
    auto allUsers = util::MapValues(users);
    util::WriteLinesToFile(DATA_FILENAME, PrepareToSave(util::MapValues(users)));
}

std::string UsersRepository::UserToLine(const User& user) {
    std::ostringstream os;
    os << user.GetId() << '|';
    os << user.GetName() << '|';
    os << user.GetPassword() << '|';
    os << user.GetEmail() << '|';
    os << user.IsAnonymousQuestionsAllowed() << '|';
    return os.str();
}

std::vector<std::string> UsersRepository::PrepareToSave(const std::vector<User>& users) {
    std::vector<std::string> lines;
    lines.reserve(users.size());

    for (const User& u : users) {
        lines.emplace_back(UserToLine(u));
    }
    return lines;
}

const std::map<int, User>& UsersRepository::GetAllUsers() const { return users; }

std::optional<User> UsersRepository::FindById(int id) const {
    auto it = users.find(id);
    if (it == users.end()) {
        return std::nullopt;
    }
    return it->second;
}

const User& UsersRepository::AddUser(std::string name, std::string password, std::string email,
                                     bool allow_anonymous_questions) {
    User user(GenerateId(), std::move(name), std::move(password), std::move(email), allow_anonymous_questions);
    auto [it, inserted] =
            users.emplace(user.GetId(), user);
    if (!inserted) {
        throw std::runtime_error("User with same ID already exists");
    }
    util::AddLineToFile(DATA_FILENAME, UserToLine(user));
    return it->second;
}

bool UsersRepository::SetAllowAnonymousQuestions(int user_id, bool allow) {
    auto it = users.find(user_id);
    if (it == users.end())
        return false;
    it->second.SetAllowAnonymousQuestions(allow);
    SaveChanges();
    return true;
}