#include "Session.h"

void Session::Login(User* user) { CurrentUser = user; }

void Session::Logout() { CurrentUser = nullptr; }

bool Session::IsLoggedIn() const { return CurrentUser != nullptr; }

const User* Session::GetCurrentUser() const { return CurrentUser; }