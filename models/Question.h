#include <string>

class Question {
    int Id;
    int ParentId;
    std::string QuestionText;
    std::string AnswerText;
    int ToUserId;
    int FromUserId;
    const bool IS_ANONYMOUS;

public:
    Question(int id, std::string question_text, int to_user_id, int from_user_id, int parent_id,
             bool is_anonymous);

    [[nodiscard]] const std::string& GetQuestionText() const;

    void SetQuestionText(std::string question_text);

    [[nodiscard]] const std::string& GetAnswerText() const;

    void SetAnswerText(std::string answer_text);

    [[nodiscard]] const int GetToUserId() const;

    [[nodiscard]] const int GetFromUserId() const;

    [[nodiscard]] const bool IsAnonymous() const;
};