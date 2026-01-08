#pragma once
#include <vector>

#include "repositories/QuestionsRepository.h"

class QuestionService {
    QuestionsRepository& repository;

public:
    explicit QuestionService(QuestionsRepository& repo);

    [[nodiscard]] std::vector<Question> QuestionMapValues(const std::map<int, Question>& map) const;

    [[nodiscard]] std::map<int, Question> GetFeed() const;

    [[nodiscard]] std::map<int, Question> GetQuestionsToUser(int user_id) const;

    [[nodiscard]] std::map<int, Question> GetQuestionsFromUser(int user_id) const;

    const Question& AskQuestion(int ParentId,
                                std::string QuestionText,
                                int ToUserId,
                                int FromUserId,
                                bool IS_ANONYMOUS) const;

    const Question& AnswerQuestion(int question_id, std::string answer_text) const;

    bool DeleteQuestion(int question_id) const;
};