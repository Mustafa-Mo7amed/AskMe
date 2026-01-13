#pragma once
#include <vector>
#include "repositories/QuestionsRepository.h"

class QuestionService {
    QuestionsRepository& repository;

public:
    explicit QuestionService(QuestionsRepository& repo);

    [[nodiscard]] std::map<int, Question> GetFeed() const;

    [[nodiscard]] std::map<int, Question> GetQuestionsToUser(int user_id) const;

    [[nodiscard]] std::map<int, Question> GetQuestionsFromUser(int user_id) const;

    [[nodiscard]] std::optional<Question> FindQuestion(int question_id) const;

    const Question& AskQuestion(int ParentId,
                                std::string QuestionText,
                                int ToUserId,
                                int FromUserId,
                                bool IS_ANONYMOUS) const;

    [[nodiscard]] std::optional<Question> AnswerQuestion(int question_id, std::string answer_text) const;

    bool DeleteQuestion(int question_id) const;
};