#include <stdexcept>
#include <optional>
#include "QuestionsRepository.h"
#include "core/util.h"

// TODO: should be the last question's id
int QuestionsRepository::LastId = 100;

int QuestionsRepository::GenerateId() {
    ++LastId;
    return LastId;
}

void QuestionsRepository::LoadUsers() {}

void QuestionsRepository::SaveChanges() {}

const std::map<int, Question>& QuestionsRepository::GetAllQuestions() const {
    return questions;
}

std::map<int, Question> QuestionsRepository::GetAllAnsweredQuestions() const {
    std::map<int, Question> answered_questions;
    for (auto& [id, question] : questions) {
        if (question.IsAnswered()) {
            answered_questions.emplace(id, question);
        }
    }
    return answered_questions;
}

std::map<int, Question> QuestionsRepository::GetQuestionsFromUser(int user_id) const {
    std::map<int, Question> user_questions;
    for (auto& [id, question] : questions) {
        if (question.GetFromUserId() == user_id) {
            user_questions.emplace(id, question);
        }
    }
    return user_questions;
}

std::map<int, Question> QuestionsRepository::GetQuestionsToUser(int user_id) const {
    std::map<int, Question> user_questions;
    for (auto& [id, question] : questions) {
        if (question.GetToUserId() == user_id) {
            user_questions.emplace(id, question);
        }
    }
    return user_questions;
}

std::optional<Question> QuestionsRepository::FindById(int id) const {
    auto it = questions.find(id);
    if (it == questions.end())
        return std::nullopt;
    return it->second;
}

bool QuestionsRepository::DeleteQuestion(int id) {
    auto it = questions.find(id);
    if (it == questions.end())
        return false;
    questions.erase(it);
    return true;
}

const Question& QuestionsRepository::AddQuestion(Question question) {
    auto [it, inserted] = questions.emplace(question.GetId(), question);
    return it->second;
}

const Question& QuestionsRepository::AddQuestion(int parent_id,
                                                 std::string question_text,
                                                 int to_user_id,
                                                 int from_user_id,
                                                 bool is_anonymous) {
    Question question(GenerateId(), std::move(question_text), to_user_id,
                      from_user_id, parent_id, is_anonymous);
    auto [it, inserted] = questions.emplace(question.GetId(), question);
    return it->second;
}

std::optional<Question> QuestionsRepository::AnswerQuestion(int question_id, std::string answer_text) {
    if (util::IsEmptyOrBlank(answer_text)) {
        throw std::invalid_argument("answer text cannot be empty");
    }
    auto it = questions.find(question_id);
    if (it == questions.end()) {
        return std::nullopt;
    }
    it->second.SetAnswerText(std::move(answer_text));
    return it->second;
}