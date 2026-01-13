#include "QuestionService.h"

QuestionService::QuestionService(QuestionsRepository& repo): repository(repo) {}

std::map<int, Question> QuestionService::GetFeed() const {
    return repository.GetAllAnsweredQuestions();
}

std::map<int, Question> QuestionService::GetQuestionsToUser(int user_id) const {
    return repository.GetQuestionsToUser(user_id);
}

std::map<int, Question> QuestionService::GetQuestionsFromUser(int user_id) const {
    return repository.GetQuestionsFromUser(user_id);
}

std::optional<Question> QuestionService::FindQuestion(int question_id) const {
    return repository.FindById(question_id);
}

const Question& QuestionService::AskQuestion(int parent_id, std::string question_text, int to_user_id, int from_user_id,
                                             bool is_anonymous) const {
    return repository.AddQuestion(parent_id, std::move(question_text), to_user_id, from_user_id, is_anonymous);
}

std::optional<Question> QuestionService::AnswerQuestion(int question_id, std::string answer_text) const {
    return repository.AnswerQuestion(question_id, std::move(answer_text));
}

bool QuestionService::DeleteQuestion(int question_id) const {
    return repository.DeleteQuestion(question_id);
}