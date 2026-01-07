#include "QuestionService.h"

std::vector<Question> QuestionService::VectorizeMap(const std::map<int, Question>& map) const {
    const std::map<int, Question>& questions_map = map;
    std::vector<Question> questions;
    questions.reserve(questions_map.size());
    for (auto& [id, question] : questions_map) {
        questions.emplace_back(question);
    }
    return questions;
}

QuestionService::QuestionService(QuestionsRepository& repo): repository(repo) {}

std::vector<Question> QuestionService::GetFeed() const {
    return VectorizeMap(repository.GetAllAnsweredQuestions());
}

std::vector<Question> QuestionService::GetQuestionsToUser(int user_id) const {
    return VectorizeMap(repository.GetQuestionsToUser(user_id));
}

std::vector<Question> QuestionService::GetQuestionsFromUser(int user_id) const {
    return VectorizeMap(repository.GetQuestionsFromUser(user_id));
}

const Question& QuestionService::AskQuestion(int parent_id, std::string question_text, int to_user_id, int from_user_id,
                                      bool is_anonymous) const {
    return repository.AddQuestion(parent_id, std::move(question_text), to_user_id, from_user_id, is_anonymous);
}

const Question& QuestionService::AnswerQuestion(int question_id, std::string answer_text) const {
    return repository.AnswerQuestion(question_id, std::move(answer_text));
}

bool QuestionService::DeleteQuestion(int question_id) const {
    return repository.DeleteQuestion(question_id);
}