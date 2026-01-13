#include <fstream>
#include <regex>
#include <algorithm>
#include <bits/ranges_algo.h>
#include "util.h"

namespace util {
    bool IsEmptyOrBlank(const std::string& str) {
        return str.empty() || std::ranges::all_of(str.begin(), str.end(), [](const char c) {
            return std::isspace(c);
        });
    }

    bool IsValidEmail(const std::string& email) {
        static const std::regex pattern(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
        return std::regex_match(email, pattern);
    }

    bool IsValidPassword(const std::string& password) {
        for (char c : password) {
            if (c <= 32 || c >= 127)
                return false;
        }
        return true;
    }

    std::string Escape(const std::string& s) {
        std::string out;
        out.reserve(s.size());
        for (char i : s) {
            if (i == '|' || i == '\\')
                out += '\\';
            out += i;
        }
        return out;
    }

    std::string Unescape(const std::string& s) {
        std::string out;
        out.reserve(s.size());
        bool escaped = false;
        for (char i : s) {
            if (escaped) {
                out += i;
                escaped = false;
            }
            else if (i == '\\') {
                escaped = true;
            }
            else {
                out += i;
            }
        }
        return out;
    }

    std::vector<std::string> SplitEscaped(const std::string& s) {
        std::vector<std::string> fields;
        std::string cur;
        bool escaped = false;
        for (char i : s) {
            if (escaped) {
                cur += i;
                escaped = false;
            }
            else if (i == '\\') {
                escaped = true;
            }
            else if (i == '|') {
                fields.emplace_back(cur);
                cur.clear();
            }
            else {
                cur += i;
            }
        }
        return fields;
    }

    std::vector<std::string> LoadFile(const std::string& filename) {
        // creates the file if it doesn't exist
        std::ofstream out("users.txt", std::ios::app);
        out.close();

        std::ifstream in(filename);
        if (!in) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        std::string input;
        std::vector<std::string> lines;
        while (std::getline(in, input)) {
            lines.emplace_back(input);
        }
        in.close();
        return lines;
    }

    void ClearFile(const std::string& filename) {
        std::ofstream out(filename, std::ios::trunc);
        if (!out) {
            throw std::runtime_error("Failed to clear file: " + filename);
        }
    }

    void WriteLinesToFile(const std::string& filename, const std::vector<std::string>& lines) {
        ClearFile(filename);

        std::ofstream out(filename);
        if (!out) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        for (const std::string& i : lines) {
            out << i << '\n';
        }
        out.close();
    }

    void AddLineToFile(const std::string& filename, const std::string& line) {
        std::ofstream out(filename, std::ios::app);
        if (!out) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        out << line << '\n';
        out.close();
    }
}