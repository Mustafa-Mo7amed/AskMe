#include "AskMeView.h"

#include <algorithm>
#include <iostream>
#include <format>
#include <map>

int AskMeView::get_int(const std::string& message, int min_value, int max_value) const {
    int value;
    do {
        print(message);
        std::cin >> value;
        if (value < min_value || value > max_value)
            print("ERROR: invalid number...try again", 0, true);
    } while (value < min_value || value > max_value);
    return value;
}

std::string AskMeView::get_string(const std::string& message, int max_size) const {
    std::string input;
    do {
        print(message);
        std::getline(std::cin, input);
        if (input.size() > max_size)
            print("ERROR: invalid input...try again");
    } while (input.size() > max_size);
    return input;
}

void AskMeView::print(const std::string& message, int depth, bool newLine) const {
    while (depth--)
        std::cout << '\t';
    std::cout << message << " ";
    if (newLine)
        std::cout << '\n';
}

void AskMeView::printQuestionThread(int node, int parent, const std::map<int, Question>& questions,
                                    const std::map<int, std::vector<int>>& adj, int depth) const {
    print(format_question(questions.at(node), true), depth, true);
    for (int child : adj.at(node)) {
        printQuestionThread(child, node, questions, adj, depth + 1);
    }
}

void AskMeView::printQuestionsList(const std::map<int, Question>& questions) const {
    std::map<int, std::vector<int>> adj;
    int root = -1;
    for (const auto& [id, question] : questions) {
        adj[question.GetParentId()].emplace_back(id);
        if (root == -1 && question.GetParentId() == -1)
            root = id;
    }
    printQuestionThread(root, -1, questions, adj, 0);
}

std::string AskMeView::format_question(const Question& question, bool include_answer) const {
    std::string from_user;
    if (!question.IsAnonymous()) {
        from_user = std::format(" from user id({})", question.GetFromUserId());
    }
    std::string ret;
    if (question.GetParentId() == -1) {
        ret = std::format("Question id({}){}", question.GetId(), from_user);
    }
    else {
        ret = std::format("Thread id({}) for Question id({}){}", question.GetId(), question.GetParentId(), from_user);
    }
    ret += std::format("\nQuestion: {}", question.GetQuestionText());
    if (include_answer)
        ret += std::format("\nAnswer: {}", question.GetAnswerText());
    return ret;
}

int AskMeView::ShowAuthMenu() const {
    print("Menu:", 0, true);
    print("1: Login", 1, true);
    print("2: Sign Up", 1, true);
    return get_int("Enter a number in range 1 - 2:", 1, 2);
}

UserSignUpData AskMeView::ShowSignUpFrom() const {
    print("Welcome to AskMe:", 0, true);

    print("Enter your name:");
    std::string name = get_string();

    print("Enter your email:");
    std::string email = get_string();

    print("Enter your password (choose a strong one):");
    std::string password = get_string();

    auto checkAnswer = [&](std::string answer) -> bool {
        for (char& c : answer)
            c = (char) std::tolower(c);
        return answer == "y" || answer == "yes";
    };
    print("Would you like to allow people to ask anonymously ? (yes/no)");
    bool allow_anonymous_questions = checkAnswer(std::move(get_string()));

    return {std::move(name), std::move(email), std::move(password), allow_anonymous_questions};
}

void AskMeView::ShowUserIdAfterSignUp(int id) const {
    std::string message = "Your id is: " + std::to_string(id) +
                          ", next time you should login using it with the password you specified!";
    print(message, 0, true);
}

UserLoginData AskMeView::ShowLoginForm() const {
    print("Welcome back!", 0, true);

    print("Enter your id:");
    int id = get_int();

    print("Enter your password:");
    std::string password = get_string();

    return {id, std::move(password)};
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

    print("Enter a number in range 1 - 8:");
    return get_int();
}

void AskMeView::ShowQuestionsToMe(const std::map<int, Question>& questions) const {
    printQuestionsList(questions);
}

// TODO: implement showing which questions were sent anonymously
void AskMeView::ShowQuestionsFromMe(const std::map<int, Question>& questions) const {
    printQuestionsList(questions);
}

int AskMeView::ShowAnswerQuestion() const {
    print("Enter Question id or -1 to cancel:");
    return get_int();
}

std::string AskMeView::ShowQuestionToAnswer(const Question& question) const {
    print(format_question(question, question.IsAnswered()), 0, true);
    std::string answered_warning;
    if (question.IsAnswered()) {
        answered_warning = "WARNING: already answered. Answer will be updated!\n";
    }
    print(std::format("{}Answer:", answered_warning));
    return get_string();
}

int AskMeView::ShowDeleteQuestion() const {
    print("Enter Question id or -1 to cancel:");
    return get_int();
}

int AskMeView::ShowRequestUserIdToAskQuestion() const {
    print("Enter User id or -1 to cancel:");
    return get_int();
}

int AskMeView::ShowRequestQuestionIdForThread(const User& user) const {
    if (!user.IsAnonymousQuestionsAllowed()) {
        print("NOTE: anonymous questions are not allowed for this user.");
    }
    print("For thread question enter Question id or -1 for a new question:");
    return get_int();
}

std::string AskMeView::ShowRequestQuestionText() const {
    print("Enter question text:");
    return get_string();
}

void AskMeView::ShowSystemUsers(const std::vector<User>& users) const {
    for (const auto& user : users) {
        print(std::format("ID: {}\t\tName: {}", user.GetId(), user.GetName()), 0, true);
    }
}

void AskMeView::ShowFeed(const std::vector<Question>& questions) const {
    for (auto& question : questions) {
        if (question.IsAnswered()) {
            print(format_question(question, true), 0, true);
        }
    }
}