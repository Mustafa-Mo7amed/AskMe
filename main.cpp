#include "repositories/QuestionsRepository.h"
#include "repositories/UsersRepository.h"
#include "controllers/AskMeController.h"

int main() {
    UsersRepository users_repository;
    QuestionsRepository questions_repository;
    AskMeController askme_controller(users_repository, questions_repository);
    askme_controller.Run();
}