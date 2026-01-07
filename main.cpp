#include "services/QuestionService.h"
#include "repositories/QuestionsRepository.h"
#include <iostream>
using namespace std;
int main() {
    QuestionsRepository repo;
    QuestionService service(repo);
    auto question = service.AskQuestion(-1,
                                        "How are you, Ali ?",
                                        1,
                                        2,
                                        false
    );
    auto receivedQuestions = service.GetQuestionsToUser(1);
    for (auto& i : receivedQuestions) {
        cout << i.GetId() << '\n';
        cout << i.GetAnswerText() << '\n';
        cout << i.GetQuestionText() << '\n';
    }
}