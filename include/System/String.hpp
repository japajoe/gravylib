#ifndef GRAVY_STRING_HPP
#define GRAVY_STRING_HPP

#include <string>
#include <vector>
#include <iostream>

namespace Gravy::System
{
    class String
    {
    private:
        std::string value;
    public:
        String();
        String(const std::string &str);
        String(const char *str);
        String& operator=(const char* str);
        String& operator=(const String& other);
        String operator+(const String& other) const;
        String& operator+=(const String& other);
        bool operator==(const String& other) const;
        bool operator!=(const String& other) const;
        std::string GetValue() const;
        size_t GetLength() const;

        std::vector<String> Split(char separator);
        String Trim();
        String TrimStart();
        String TrimEnd();
        bool StartsWith(const std::string &suffix);
        bool EndsWith(const std::string &suffix);
        bool Contains(const std::string &needle);
        void Replace(const std::string &target, const std::string &replacement);
        String ToLower();
        String ToUpper();

        static std::vector<std::string> Split(const std::string &str, char separator);
        static std::string Trim(const std::string &str);
        static std::string TrimStart(const std::string &str);
        static std::string TrimEnd(const std::string &str);
        static bool StartsWith(const std::string &str, const std::string &suffix);
        static bool EndsWith(const std::string &str, const std::string &suffix);
        static bool Contains(const std::string &haystack, const std::string &needle);
        static void Replace(std::string &str, const std::string &target, const std::string &replacement);
        static std::string ToLower(const std::string &str);
        static std::string ToUpper(const std::string &str);
    };

    std::ostream& operator<<(std::ostream& os, const String& str);
};
#endif