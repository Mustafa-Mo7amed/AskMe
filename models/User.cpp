#include "User.h";

User::User(const int id, std::string name, std::string password, std::string email,
           const bool allow_anonymous_questions)
    : Id(id), Name(std::move(name)), Password(std::move(password)), Email(std::move(email)),
      AllowAnonymousQuestions(allow_anonymous_questions) {}

int User::GetId() const { return Id; }

const std::string& User::GetName() const { return Name; }

const std::string& User::GetPassword() const { return Password; }

const std::string& User::GetEmail() const { return Email; }

bool User::IsAnonymousQuestionsAllowed() const {
    return AllowAnonymousQuestions;
}

bool User::SetAllowAnonymousQuestions(bool allowed) {
    return AllowAnonymousQuestions = allowed;
}