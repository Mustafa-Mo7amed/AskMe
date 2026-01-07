#pragma once
#include <string>

class User {
    int Id;
    std::string Name;
    std::string Password;
    std::string Email;
    bool AllowAnonymousQuestions;

public:
    User(int id, std::string name, std::string password, std::string email,
         bool allow_anonymous_questions);

    [[nodiscard]] int GetId() const;

    [[nodiscard]] const std::string& GetName() const;

    [[nodiscard]] const std::string& GetPassword() const;

    [[nodiscard]] const std::string& GetEmail() const;

    [[nodiscard]] bool IsAnonymousQuestionsAllowed() const;

    bool SetAllowAnonymousQuestions(bool allowed);
};