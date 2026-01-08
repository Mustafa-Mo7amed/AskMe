#pragma once
#include <string>
#include <vector>
#include <map>
#include "models/Question.h"
#include "models/User.h"
#include "DTO/UserSignUpData.h"
#include "DTO/UserLoginData.h"

class AskMeView {
    int get_int(const std::string& message = "", int min_value = INT_MIN, int max_value = INT_MAX) const;

    [[nodiscard]] std::string get_string(const std::string& message = "", int max_size = INT_MAX) const;

    void print(const std::string& message, int depth = 0, bool newline = false) const;

    void printQuestionThread(int node, int parent, const std::map<int, Question>& questions,
                       const std::map<int, std::vector<int>>& adj, int depth) const;

    void printQuestionsList(const std::map<int, Question>& questions) const;

    [[nodiscard]] std::string format_question(const Question& question, bool include_answer) const;

public:
    [[nodiscard]] int ShowAuthMenu() const;

    [[nodiscard]] UserSignUpData ShowSignUpFrom() const;

    void ShowUserIdAfterSignUp(int id) const;

    [[nodiscard]] UserLoginData ShowLoginForm() const;

    [[nodiscard]] int ShowMainMenu() const;

    void ShowQuestionsToMe(const std::map<int, Question>& questions) const;

    void ShowQuestionsFromMe(const std::map<int, Question>& questions) const;

    [[nodiscard]] int ShowAnswerQuestion() const;

    [[nodiscard]] std::string ShowQuestionToAnswer(const Question& question) const;

    [[nodiscard]] int ShowDeleteQuestion() const;

    [[nodiscard]] int ShowRequestUserIdToAskQuestion() const;

    [[nodiscard]] int ShowRequestQuestionIdForThread(const User& user) const;

    [[nodiscard]] std::string ShowRequestQuestionText() const;

    void ShowSystemUsers(const std::vector<User>& users) const;

    void ShowFeed(const std::vector<Question>& questions) const;
};