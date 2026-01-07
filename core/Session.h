#pragma once

#include "models/User.h"

class Session {
    User* CurrentUser = nullptr;

public:
    void Login(User* user);

    void Logout();

    [[nodiscard]] bool IsLoggedIn() const;

    [[nodiscard]] const User* GetCurrentUser() const;
};