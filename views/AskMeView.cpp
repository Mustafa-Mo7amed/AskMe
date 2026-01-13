#include <algorithm>
#include <iostream>
#include <format>
#include <map>
#include <limits>
#include "AskMeView.h"
#include "core/util.h"

int AskMeView::get_int(const std::string& message, int min_value, int max_value) {
    int value;
    do {
        print(message);
        if (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            print("ERROR: please enter a valid number", 0, true);
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (value < min_value || value > max_value)
            print("ERROR: invalid number...try again");
    } while (value < min_value || value > max_value);
    return value;
}

std::string AskMeView::get_string(const std::string& message, int max_size) {
    std::string input;
    do {
        print(message);
        std::getline(std::cin, input);
        if (input.size() > max_size || util::IsEmptyOrBlank(input))
            print("ERROR: invalid input...try again", 0, true);
    } while (input.size() > max_size || util::IsEmptyOrBlank(input));
    return input;
}

void AskMeView::print(const std::string& message, int depth, bool newLine) {
    while (depth--)
        std::cout << '\t';
    std::cout << message << " ";
    if (newLine)
        std::cout << '\n';
}

void AskMeView::printQuestionThread(int node, const std::map<int, Question>& questions,
                                    const std::map<int, std::vector<int>>& adj, int depth, bool only_answered) {
    if (!questions.contains(node)) {
        return;
    }
    if (only_answered && !questions.at(node).IsAnswered()) {
        return;
    }
    print(format_question(questions.at(node), questions.at(node).IsAnswered(), depth), 0, true);
    if (!adj.contains(node)) {
        return;
    }
    for (int child : adj.at(node)) {
        printQuestionThread(child, questions, adj, depth + 1, only_answered);
    }
}

void AskMeView::printQuestionsList(const std::map<int, Question>& questions, bool only_answered) {
    std::map<int, std::vector<int>> adj;
    for (const auto& [id, question] : questions) {
        adj[question.GetParentId()].emplace_back(id);
    }

    for (const auto& [id, question] : questions) {
        if (question.GetParentId() == -1 || !questions.contains(question.GetParentId())) {
            printQuestionThread(id, questions, adj, 0, only_answered);
        }
    }
}

std::string AskMeView::format_question(const Question& question, bool include_answer, int depth) {
    static auto indentation = [&](int d) -> std::string {
        std::string s;
        while (d--)
            s.push_back('\t');
        return s;
    };
    std::string from_user;
    if (!question.IsAnonymous()) {
        from_user = std::format(" from user id({})", question.GetFromUserId());
    }
    std::string ret;
    if (question.GetParentId() == -1) {
        ret = std::format("{}Question id({}){}", indentation(depth), question.GetId(), from_user);
    }
    else {
        ret = std::format("{}Thread id({}) for Question id({}){}", indentation(depth), question.GetId(),
                          question.GetParentId(), from_user);
    }
    ret += std::format("\n{}Question: {}", indentation(depth), question.GetQuestionText());
    if (include_answer)
        ret += std::format("\n{}Answer: {}", indentation(depth), question.GetAnswerText());
    ret += '\n';
    return ret;
}

bool AskMeView::checkAnswerYesNo(std::string answer) {
    for (char& c : answer)
        c = (char) std::tolower(c);
    return answer == "y" || answer == "yes";
}

int AskMeView::ShowAuthMenu() const {
    print("Menu:", 0, true);
    print("1: Login", 1, true);
    print("2: Sign Up", 1, true);
    return get_int("Enter a number in range 1 - 2:", 1, 2);
}

UserSignUpData AskMeView::ShowSignUpFrom() const {
    print("Welcome to AskMe:", 0, true);

    std::string name = get_string("Enter your name:");

    std::string email;
    bool valid_email;
    do {
        email = get_string("Enter your email:");
        valid_email = util::IsValidEmail(email);
        if (!valid_email) {
            print("ERROR: invalid email...try again", 0, true);
        }
    } while (!valid_email);

    std::string password;
    bool valid_password;
    do {
        password = get_string("Enter your password (choose a strong one):");
        valid_password = util::IsValidPassword(password);
        if (!valid_password) {
            print("ERROR: invalid password...try again", 0, true);
        }
    } while (!valid_password);

    bool allow_anonymous_questions = checkAnswerYesNo(std::move(get_string("Would you like to allow people to ask anonymously ? (yes/no)")));

    return {std::move(name), std::move(email), std::move(password), allow_anonymous_questions};
}

void AskMeView::ShowUserIdAfterSignUp(int id) const {
    std::string message = "Your id is: " + std::to_string(id) +
                          ", next time you should login using it with the password you specified!";
    print(message, 0, true);
}

UserLoginData AskMeView::ShowLoginForm() const {
    print("Welcome back!", 0, true);

    int id = get_int("Enter your id:");

    std::string password = get_string("Enter your password:");

    return {id, std::move(password)};
}

void AskMeView::ShowWrongIdOrPassword() const {
    print("incorrect id or password...try again", 0, true);
}

int AskMeView::ShowMainMenu() const {
    print("Menu:", 0, true);

    print("1: Print Question To Me", 1, true);
    print("2: Print Question From Me", 1, true);
    print("3: Answer Question", 1, true);
    print("4: Delete Question", 1, true);
    print("5: Ask Question", 1, true);
    print("6: List System Users", 1, true);
    print("7: Feed", 1, true);
    print("8: Anonymous Questions Configuration", 1, true);
    print("9: Logout", 1, true);

    return get_int("Enter a number in range 1 - 9:", 1, 9);
}

void AskMeView::ShowQuestionsToMe(const std::map<int, Question>& questions) const {
    printQuestionsList(questions);
}

// TODO: implement showing which questions were sent anonymously
void AskMeView::ShowQuestionsFromMe(const std::map<int, Question>& questions) const {
    printQuestionsList(questions);
}

int AskMeView::ShowRequestQuestionIdToAnswer() const {
    return get_int("Enter Question id or -1 to cancel:");
}

std::string AskMeView::ShowQuestionToAnswer(const Question& question) const {
    print(format_question(question, question.IsAnswered()), 0, true);
    std::string answered_warning;
    if (question.IsAnswered()) {
        answered_warning = "WARNING: already answered. Answer will be updated!\n";
    }
    print(answered_warning);
    return get_string("Answer:");
}

int AskMeView::ShowDeleteQuestion() const {
    return get_int("Enter Question id or -1 to cancel:");
}

void AskMeView::ShowDeleteQuestionSuccess() const {
    print("Question delete successfully", 0, true);
}

int AskMeView::ShowRequestUserIdToAskQuestion() const {
    return get_int("Enter User id or -1 to cancel:");
}

bool AskMeView::ShowRequestAnonymousQuestion(const User& user) const {
    if (!user.IsAnonymousQuestionsAllowed()) {
        print("NOTE: anonymous questions are not allowed for this user.", 0, true);
        return false;
    }
    return checkAnswerYesNo(std::move(get_string("Would you like to ask anonymously ? (yes/no):")));
}

int AskMeView::ShowRequestQuestionIdForThread() const {
    return get_int("For thread question enter Question id or -1 for a new question:");
}

std::string AskMeView::ShowRequestQuestionText() const {
    return get_string("Enter question text:");
}

void AskMeView::ShowSystemUsers(const std::vector<User>& users) const {
    for (const auto& user : users) {
        print(std::format("ID: {}\t\tName: {}", user.GetId(), user.GetName()), 0, true);
    }
}

void AskMeView::ShowFeed(const std::map<int, Question>& questions) const {
    printQuestionsList(questions, true);
}

bool AskMeView::AnonymousQuestionsConfiguration() const {
    return checkAnswerYesNo(std::move(get_string("Would you like to allow people to ask anonymously ? (yes/no):")));
}

void AskMeView::ShowAnonymousQuestionsConfigurationSuccess() const {
    print("Settings saved successfully", 0, true);
}

void AskMeView::ShowWrongMainMenuInput() const {
    print("ERROR: invalid number...try again", 0, true);
}

void AskMeView::ShowQuestionNotFound() const {
    print("ERROR: question not found", 0, true);
}

void AskMeView::ShowUserNotFound() const {
    print("ERROR: user not found", 0, true);
}

void AskMeView::ShowAnswerQuestionNotAllowed() const {
    print("ERROR: you cannot answer questions that are not directed to you", 0, true);
}

void AskMeView::ShowDeleteQuestionNotAllowed() const {
    print("ERROR: you cannot delete questions you did not ask", 0, true);
}

void AskMeView::ShowSelfQuestionNotAllowed() const {
    print("ERROR: you cannot ask questions to yourself", 0, true);
}