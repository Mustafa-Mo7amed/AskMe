#pragma once
#include <vector>

#include "repositories/QuestionsRepository.h"

class QuestionService {
    QuestionsRepository& repository;
    [[nodiscard]] std::vector<Question> VectorizeMap(const std::map<int, Question>& map) const;
public:
    explicit QuestionService(QuestionsRepository& repo);

    [[nodiscard]] std::vector<Question> GetFeed() const;

    [[nodiscard]] std::vector<Question> GetQuestionsToUser(int user_id) const;

    [[nodiscard]] std::vector<Question> GetQuestionsFromUser(int user_id) const;

    const Question& AskQuestion(int ParentId,
                         std::string QuestionText,
                         int ToUserId,
                         int FromUserId,
                         bool IS_ANONYMOUS) const;

    const Question& AnswerQuestion(int question_id, std::string answer_text) const;

    bool DeleteQuestion(int question_id) const;
};