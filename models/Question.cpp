#include <stdexcept>
#include "Question.h";
#include "../core/Validator.h";

Question::Question(int id, std::string question_text, int to_user_id, int from_user_id, int parent_id,
                   bool is_anonymous): Id(id), QuestionText(std::move(question_text)), ToUserId(to_user_id),
                                       FromUserId(from_user_id), ParentId(parent_id), IS_ANONYMOUS(is_anonymous) {}

[[nodiscard]] const std::string& Question::GetQuestionText() const { return QuestionText; }

[[nodiscard]] const std::string& Question::GetAnswerText() const { return AnswerText; }

void Question::SetAnswerText(std::string answer_text) {
    if (Validator::IsEmptyOrBlank(answer_text)) {
        throw std::invalid_argument("Answer Text cannot be empty or blank");
    }
    AnswerText = std::move(answer_text);
}

[[nodiscard]] const int Question::GetToUserId() const { return ToUserId; }

[[nodiscard]] const int Question::GetFromUserId() const { return ToUserId; }

[[nodiscard]] const bool Question::IsAnonymous() const { return IS_ANONYMOUS; }