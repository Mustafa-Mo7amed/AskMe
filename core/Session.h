#pragma once
#include <optional>
#include "models/User.h"

class Session {
    std::optional<User> CurrentUser;

public:
    void Login(User user);

    void Logout();

    [[nodiscard]] bool IsLoggedIn() const;

    [[nodiscard]] std::optional<User> GetCurrentUser() const;
};