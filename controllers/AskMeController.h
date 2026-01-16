#pragma once
#include "repositories/QuestionsRepository.h"
#include "repositories/UsersRepository.h"
#include "services/QuestionService.h"
#include "services/UserService.h"
#include "views/AskMeView.h"
#include "core/Session.h"

class AskMeController {
    UserService user_service;
    QuestionService question_service;
    Session session;
    AskMeView askme_view;

    [[noreturn]] void AuthMenu();

    void SignUp();

    void Login();

    [[noreturn]] void MainMenu();

    void QuestionsToMe() const;

    void QuestionsFromMe() const;

    void AnswerQuestion() const;

    void DeleteQuestion() const;

    void AskQuestion() const;

    void SystemUsers() const;

    void Feed() const;

    void AnonymousQuestionsConfiguration() const;

    void Logout();

public:
    AskMeController(UsersRepository& user_repo, QuestionsRepository& questions_repo);

    void Run();
};