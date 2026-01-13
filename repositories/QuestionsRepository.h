#pragma once
#include <map>
#include <vector>
#include <optional>
#include "models/Question.h"

class QuestionsRepository {
    static const std::string DATA_FILENAME;

    static int LastId;
    std::map<int, Question> questions;

    void LoadQuestions();

    void SaveChanges();

    [[nodiscard]] static int GenerateId();

    std::string QuestionToLine(const Question& question);

    std::vector<std::string> PrepareToSave(const std::vector<Question>& questions);

public:
    QuestionsRepository();
    [[nodiscard]] const std::map<int, Question>& GetAllQuestions() const;

    [[nodiscard]] std::map<int, Question> GetAllAnsweredQuestions() const;

    [[nodiscard]] std::map<int, Question> GetQuestionsFromUser(int user_id) const;

    [[nodiscard]] std::map<int, Question> GetQuestionsToUser(int user_id) const;

    [[nodiscard]] std::optional<Question> FindById(int id) const;

    bool DeleteQuestion(int id);

    const Question& AddQuestion(Question question);

    const Question& AddQuestion(int parent_id,
                    std::string question_text,
                    int to_user_id,
                    int from_user_id,
                    bool is_anonymous);

    std::optional<Question> AnswerQuestion(int question_id, std::string answer_text);
};