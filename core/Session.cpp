#include <optional>
#include "Session.h"

void Session::Login(User user) { CurrentUser = std::move(user); }

void Session::Logout() { CurrentUser = std::nullopt; }

bool Session::IsLoggedIn() const { return CurrentUser != std::nullopt; }

std::optional<User> Session::GetCurrentUser() const { return CurrentUser; }