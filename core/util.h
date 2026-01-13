#pragma once

#include <string>
#include <vector>
#include <map>

namespace util {
    bool IsEmptyOrBlank(const std::string& str);

    bool IsValidEmail(const std::string& email);

    bool IsValidPassword(const std::string& password);

    std::string Escape(const std::string& s);

    std::string Unescape(const std::string& s);

    std::vector<std::string> SplitEscaped(const std::string& s);

    std::vector<std::string> LoadFile(const std::string& filename);

    void ClearFile(const std::string& filename);

    void WriteLinesToFile(const std::string& filename, const std::vector<std::string>& lines);

    void AddLineToFile(const std::string& filename, const std::string& line);

    template<typename K, typename V>
    std::vector<V> MapValues(const std::map<K, V>& map) {
        const std::map<K, V>& users_map = map;
        std::vector<V> users;
        users.reserve(users_map.size());
        for (auto& [id, user] : users_map) {
            users.emplace_back(user);
        }
        return users;
    }
};