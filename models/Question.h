#pragma once
#include <string>

class Question {
    int Id;
    int ParentId;
    std::string QuestionText;
    std::string AnswerText;
    int ToUserId;
    int FromUserId;
    const bool IS_ANONYMOUS;

public:
    Question(int id, std::string question_text, int to_user_id, int from_user_id, int parent_id,
             bool is_anonymous);

    Question(int id, std::string question_text, std::string answer_text, int to_user_id, int from_user_id, int parent_id,
             bool is_anonymous);

    [[nodiscard]] int GetId() const;

    [[nodiscard]] const std::string& GetQuestionText() const;

    [[nodiscard]] const std::string& GetAnswerText() const;

    void SetAnswerText(std::string answer_text);

    [[nodiscard]] int GetToUserId() const;

    [[nodiscard]] int GetFromUserId() const;

    [[nodiscard]] bool IsAnonymous() const;

    [[nodiscard]] bool IsAnswered() const;
};