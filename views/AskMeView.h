#pragma once
#include <string>
#include <vector>
#include "models/Question.h"
#include "models/User.h"
#include "DTO/UserSignUpData.h"
#include "DTO/UserLoginData.h"

class AskMeView {
    int get_int(const std::string& message, int min_value = INT_MIN, int max_value = INT_MAX);

    void print(const std::string& message, int depth = 0);

public:
    [[nodiscard]] int ShowAuthMenu() const;

    [[nodiscard]] UserSignUpData ShowSignUpFrom() const;

    [[nodiscard]] UserLoginData ShowLoginForm() const;

    [[nodiscard]] int ShowMainMenu() const;

    void ShowQuestionsToMe() const;

    void ShowQuestionsFromMe() const;

    [[nodiscard]] int ShowAnswerQuestion() const;

    [[nodiscard]] std::string ShowQuestionToAnswer(int question_id, int from_user_id) const;

    [[nodiscard]] int ShowDeleteQuestion() const;

    [[nodiscard]] int ShowRequestUserIdToAskQuestion() const;

    [[nodiscard]] int ShowRequestQuestionIdForThread() const;

    [[nodiscard]] std::string ShowRequestQuestionText() const;

    void ShowSystemUsers(const std::vector<User>& users) const;

    void ShowFeed(const std::vector<Question>& questions) const;

    [[nodiscard]] int ShowLogout() const;
};