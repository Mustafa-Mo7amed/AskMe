#include <stdexcept>
#include "Question.h"
#include "core/util.h"

Question::Question(int id, std::string question_text, int to_user_id, int from_user_id, int parent_id,
                   bool is_anonymous): Id(id),
                                       QuestionText(std::move(question_text)),
                                       ToUserId(to_user_id),
                                       FromUserId(from_user_id),
                                       ParentId(parent_id),
                                       IS_ANONYMOUS(is_anonymous) {}

Question::Question(int id, std::string question_text, std::string answer_text, int to_user_id, int from_user_id,
                   int parent_id,
                   bool is_anonymous): Id(id),
                                       QuestionText(std::move(question_text)),
                                       AnswerText(std::move(answer_text)),
                                       ToUserId(to_user_id),
                                       FromUserId(from_user_id),
                                       ParentId(parent_id),
                                       IS_ANONYMOUS(is_anonymous) {}

int Question::GetId() const { return Id; }

int Question::GetParentId() const { return ParentId; }

const std::string& Question::GetQuestionText() const { return QuestionText; }

const std::string& Question::GetAnswerText() const { return AnswerText; }

void Question::SetAnswerText(std::string answer_text) {
    AnswerText = std::move(answer_text);
}

int Question::GetToUserId() const { return ToUserId; }

int Question::GetFromUserId() const { return FromUserId; }

bool Question::IsAnonymous() const { return IS_ANONYMOUS; }

bool Question::IsAnswered() const { return !util::IsEmptyOrBlank(GetAnswerText()); }