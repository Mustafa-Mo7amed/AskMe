#include "AskMeController.h"

AskMeController::AskMeController(UsersRepository& user_repo,
                                 QuestionsRepository& questions_repo): user_service(user_repo),
                                                                       question_service(questions_repo) {}

void AskMeController::Run() {
    AuthMenu();
}

void AskMeController::AuthMenu() {
    int choice = askme_view.ShowAuthMenu();
    if (choice == 1) {
        Login();
    }
    else {
        SignUp();
    }
}

void AskMeController::SignUp() {
    UserSignUpData signup_data = askme_view.ShowSignUpFrom();
    const User& user = user_service.AddUser(signup_data.name, signup_data.password, signup_data.email,
                                            signup_data.allow_anonymous_questions);
    session.Login(user);
    askme_view.ShowUserIdAfterSignUp(user.GetId());
    MainMenu();
}

void AskMeController::Login() {
    UserLoginData login_data = askme_view.ShowLoginForm();
    auto user = user_service.FindUser(login_data.id);
    while (true) {
        if (user.has_value() && user.value().GetPassword() == login_data.password) {
            break;
        }
        askme_view.ShowWrongIdOrPassword();
        login_data = askme_view.ShowLoginForm();
        user = user_service.FindUser(login_data.id);
    }
    session.Login(user.value());
    MainMenu();
}

void AskMeController::MainMenu() {
    while (true) {
        int choice = askme_view.ShowMainMenu();
        switch (choice) {
            case 1:
                QuestionsToMe();
                break;
            case 2:
                QuestionsFromMe();
                break;
            case 3:
                AnswerQuestion();
                break;
            case 4:
                DeleteQuestion();
                break;
            case 5:
                AskQuestion();
                break;
            case 6:
                SystemUsers();
                break;
            case 7:
                Feed();
                break;
            case 8:
                AnonymousQuestionsConfiguration();
                break;
            case 9:
                Logout();
                break;
            default:
                askme_view.ShowWrongMainMenuInput();
        }
    }
}

void AskMeController::QuestionsToMe() const {
    int current_userid = session.GetCurrentUser().value().GetId();
    auto questions = question_service.GetQuestionsToUser(current_userid);
    askme_view.ShowQuestionsToMe(questions);
}

void AskMeController::QuestionsFromMe() const {
    int current_userid = session.GetCurrentUser().value().GetId();
    auto questions = question_service.GetQuestionsFromUser(current_userid);
    askme_view.ShowQuestionsFromMe(questions);
}

void AskMeController::AnswerQuestion() const {
    int question_id = askme_view.ShowRequestQuestionIdToAnswer();
    if (question_id == -1) {
        return;
    }
    auto question = question_service.FindQuestion(question_id);
    if (!question) {
        askme_view.ShowQuestionNotFound();
        return;
    }
    if (session.GetCurrentUser().value().GetId() != question.value().GetToUserId()) {
        askme_view.ShowAnswerQuestionNotAllowed();
        return;
    }
    std::string answer = askme_view.ShowQuestionToAnswer(question.value());
    question_service.AnswerQuestion(question_id, answer);
}

void AskMeController::DeleteQuestion() const {
    int question_id = askme_view.ShowDeleteQuestion();
    auto question = question_service.FindQuestion(question_id);
    if (!question) {
        askme_view.ShowQuestionNotFound();
        return;
    }
    if (session.GetCurrentUser().value().GetId() != question.value().GetFromUserId()) {
        askme_view.ShowDeleteQuestionNotAllowed();
        return;
    }
    if (!question_service.DeleteQuestion(question_id)) {
        askme_view.ShowQuestionNotFound();
    }
    else {
        askme_view.ShowDeleteQuestionSuccess();
    }
}

void AskMeController::AskQuestion() const {
    int user_id = askme_view.ShowRequestUserIdToAskQuestion();
    if (user_id == -1) {
        return;
    }
    auto user = user_service.FindUser(user_id);
    if (!user) {
        askme_view.ShowUserNotFound();
        return;
    }
    if (session.GetCurrentUser().value().GetId() == user.value().GetId()) {
        askme_view.ShowSelfQuestionNotAllowed();
        return;
    }
    bool is_anonymous = askme_view.ShowRequestAnonymousQuestion(user.value());
    int parent_id = askme_view.ShowRequestQuestionIdToAnswer();
    if (parent_id != -1 && !question_service.FindQuestion(parent_id)) {
        askme_view.ShowQuestionNotFound();
        return;
    }
    std::string question_text = askme_view.ShowRequestQuestionText();
    question_service.AskQuestion(parent_id,
                                 question_text,
                                 user_id,
                                 session.GetCurrentUser().value().GetId(),
                                 is_anonymous);
}

void AskMeController::SystemUsers() const {
    auto users = user_service.UserMapValues(user_service.GetAllUsers());
    askme_view.ShowSystemUsers(users);
}

void AskMeController::Feed() const {
    auto questions = question_service.GetFeed();
    askme_view.ShowFeed(questions);
}

void AskMeController::AnonymousQuestionsConfiguration() const {
    int current_userid = session.GetCurrentUser().value().GetId();
    bool allow_anonymous_questions = askme_view.AnonymousQuestionsConfiguration();
    bool done = user_service.SetAllowAnonymousQuestions(current_userid, allow_anonymous_questions);
    if (!done) {
        askme_view.ShowUserNotFound();
    }
    else {
        askme_view.ShowAnonymousQuestionsConfigurationSuccess();
    }
}

void AskMeController::Logout() {
    session.Logout();
    AuthMenu();
}