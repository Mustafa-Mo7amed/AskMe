#pragma once
#include <string>
#include <vector>
#include <map>
#include "models/Question.h"
#include "models/User.h"
#include "DTO/UserSignUpData.h"
#include "DTO/UserLoginData.h"

class AskMeView {
    [[nodiscard]] static int get_int(const std::string& message = "", int min_value = INT_MIN,
                                     int max_value = INT_MAX);

    [[nodiscard]] static std::string get_string(const std::string& message = "", int max_size = INT_MAX);

    static void print(const std::string& message, int depth = 0, bool newline = false);

    static void printQuestionThread(int node, const std::map<int, Question>& questions,
                                    const std::map<int, User>& users,
                                    const std::map<int, std::vector<int>>& adj, int depth, bool only_answered = false);

    static void printQuestionsList(const std::map<int, Question>& questions, const std::map<int, User>& users,
                                   bool only_answered = false);

    [[nodiscard]] static std::string format_question(const Question& question, const std::map<int, User>& users,
                                                     bool include_answer, int depth = 0);

    [[nodiscard]] static bool checkAnswerYesNo(std::string answer);

public:
    [[nodiscard]] int ShowAuthMenu() const;

    [[nodiscard]] UserSignUpData ShowSignUpFrom() const;

    void ShowUserIdAfterSignUp(int id) const;

    [[nodiscard]] UserLoginData ShowLoginForm() const;

    void ShowWrongIdOrPassword() const;

    [[nodiscard]] int ShowMainMenu() const;

    void ShowQuestionsToMe(const std::map<int, Question>& questions, const std::map<int, User>& users) const;

    void ShowQuestionsFromMe(const std::map<int, Question>& questions, const std::map<int, User>& users) const;

    [[nodiscard]] int ShowRequestQuestionIdToAnswer() const;

    [[nodiscard]] std::string ShowQuestionToAnswer(const Question& question, const std::map<int, User>& users) const;

    [[nodiscard]] int ShowDeleteQuestion() const;

    void ShowDeleteQuestionSuccess() const;

    [[nodiscard]] int ShowRequestUserIdToAskQuestion() const;

    [[nodiscard]] bool ShowRequestAnonymousQuestion(const User& user) const;

    [[nodiscard]] int ShowRequestQuestionIdForThread() const;

    [[nodiscard]] std::string ShowRequestQuestionText() const;

    void ShowSystemUsers(const std::vector<User>& users) const;

    void ShowFeed(const std::map<int, Question>& questions, const std::map<int, User>& users) const;

    [[nodiscard]] bool AnonymousQuestionsConfiguration() const;

    void ShowAnonymousQuestionsConfigurationSuccess() const;

    void ShowWrongMainMenuInput() const;

    void ShowQuestionNotFound() const;

    void ShowUserNotFound() const;

    void ShowAnswerQuestionNotAllowed() const;

    void ShowDeleteQuestionNotAllowed() const;

    void ShowSelfQuestionNotAllowed() const;

    void ShowUserAlreadyExists() const;
};