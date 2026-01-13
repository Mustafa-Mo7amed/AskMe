#include <stdexcept>
#include <optional>
#include <vector>
#include <sstream>
#include "QuestionsRepository.h"
#include "core/util.h"

const std::string QuestionsRepository::DATA_FILENAME = "questions.txt";

int QuestionsRepository::LastId = 100;

int QuestionsRepository::GenerateId() {
    ++LastId;
    return LastId;
}

void QuestionsRepository::LoadQuestions() {
    auto allQuestions = util::LoadFile(DATA_FILENAME);
    questions.clear();
    for (const std::string& line : allQuestions) {
        auto fields = util::SplitEscaped(line);
        if (fields.empty())
            continue;
        int id = stoi(fields[0]);
        int parent_id = stoi(fields[1]);
        int to_user_id = stoi(fields[2]);
        int from_user_id = stoi(fields[3]);
        std::string question_text = fields[4];
        std::string answer_text = fields[5];
        bool is_anonymous = stoi(fields[6]);
        Question question(id, std::move(question_text), std::move(answer_text), to_user_id, from_user_id, parent_id, is_anonymous);
        auto [it, inserted] = questions.emplace(question.GetId(), std::move(question));
        if (!inserted) {
            throw std::runtime_error("Question with same ID already exists");
        }
    }
    if (!questions.empty())
        LastId = prev(questions.end())->first;
}

void QuestionsRepository::SaveChanges() {
    auto allQuestions = util::MapValues(questions);
    util::WriteLinesToFile(DATA_FILENAME, PrepareToSave(allQuestions));
}

std::string QuestionsRepository::QuestionToLine(const Question& question) {
    std::ostringstream os;
    os << util::Escape(std::to_string(question.GetId())) << '|';
    os << util::Escape(std::to_string(question.GetParentId())) << '|';
    os << util::Escape(std::to_string(question.GetToUserId())) << '|';
    os << util::Escape(std::to_string(question.GetFromUserId())) << '|';
    os << util::Escape(question.GetQuestionText()) << '|';
    os << util::Escape(question.GetAnswerText()) << '|';
    os << util::Escape(std::to_string(question.IsAnonymous())) << '|';
    return os.str();
}

std::vector<std::string> QuestionsRepository::PrepareToSave(const std::vector<Question>& questions) {
    std::vector<std::string> lines;
    lines.reserve(questions.size());

    for (const Question& q : questions) {
        lines.emplace_back(QuestionToLine(q));
    }
    return lines;
}

QuestionsRepository::QuestionsRepository() {
    LoadQuestions();
}

const std::map<int, Question>& QuestionsRepository::GetAllQuestions() {
    LoadQuestions();
    return questions;
}

std::map<int, Question> QuestionsRepository::GetAllAnsweredQuestions() {
    std::map<int, Question> answered_questions;
    for (auto& [id, question] : questions) {
        if (question.IsAnswered()) {
            answered_questions.emplace(id, question);
        }
    }
    return answered_questions;
}

std::map<int, Question> QuestionsRepository::GetQuestionsFromUser(int user_id) {
    LoadQuestions();
    std::map<int, Question> user_questions;
    for (auto& [id, question] : questions) {
        if (question.GetFromUserId() == user_id) {
            user_questions.emplace(id, question);
        }
    }
    return user_questions;
}

std::map<int, Question> QuestionsRepository::GetQuestionsToUser(int user_id) {
    LoadQuestions();
    std::map<int, Question> user_questions;
    for (auto& [id, question] : questions) {
        if (question.GetToUserId() == user_id) {
            user_questions.emplace(id, question);
        }
    }
    return user_questions;
}

std::optional<Question> QuestionsRepository::FindById(int id) {
    LoadQuestions();
    auto it = questions.find(id);
    if (it == questions.end())
        return std::nullopt;
    return it->second;
}

bool QuestionsRepository::DeleteQuestion(int id) {
    LoadQuestions();
    auto it = questions.find(id);
    if (it == questions.end())
        return false;
    questions.erase(it);
    SaveChanges();
    return true;
}

const Question& QuestionsRepository::AddQuestion(Question question) {
    auto [it, inserted] = questions.emplace(question.GetId(), question);
    util::AddLineToFile(DATA_FILENAME, QuestionToLine(question));
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
    util::AddLineToFile(DATA_FILENAME, QuestionToLine(question));
    return it->second;
}

std::optional<Question> QuestionsRepository::AnswerQuestion(int question_id, std::string answer_text) {
    if (util::IsEmptyOrBlank(answer_text)) {
        throw std::invalid_argument("answer text cannot be empty");
    }
    LoadQuestions();
    auto it = questions.find(question_id);
    if (it == questions.end()) {
        return std::nullopt;
    }
    it->second.SetAnswerText(std::move(answer_text));
    SaveChanges();
    return it->second;
}