#include "System/String.hpp"
#include <sstream>
#include <cctype> // For std::isspace
#include <algorithm> // For std::transform

namespace Gravy::System
{
    String::String()
    {

    }

    String::String(const std::string &str)
    {
        this->value = str;
    }

    String::String(const char *str)
    {
        this->value = std::string(str);
    }

    String& String::operator=(const char* str) 
    {
        value = str;
        return *this;
    }

    String& String::operator=(const String& other) 
    {
        if (this != &other)
            value = other.value;
        return *this;
    }

    // Concatenation operator overload
    String String::operator+(const String& other) const 
    {
        String result = *this;
        result.value += other.value;
        return result;
    }

    String& String::operator+=(const String& other)
    {
        value += other.value;
        return *this;        
    }

    bool String::operator==(const String& other) const 
    {
        return value == other.value;
    }

    bool String::operator!=(const String& other) const 
    {
        return value != other.value;
    }

    std::string String::GetValue() const
    {
        return value;
    }

    size_t String::GetLength() const
    {
        return value.size();
    }

    std::vector<String> String::Split(char separator)
    {
        std::vector<String> substrings;
        std::istringstream ss(value);
        std::string token;

        while (std::getline(ss, token, separator)) 
        {
            substrings.push_back(token);
        }

        return substrings;
    }

    String String::Trim()
    {
        return String::Trim(value);
    }

    String String::TrimStart()
    {
        return String::TrimStart(value);
    }

    String String::TrimEnd()
    {
        return String::TrimEnd(value);
    }

    bool String::StartsWith(const std::string &suffix)
    {
        return String::StartsWith(value, suffix);
    }

    bool String::EndsWith(const std::string &suffix)
    {
        return String::EndsWith(value, suffix);
    }

    bool String::Contains(const std::string &needle)
    {
        return String::Contains(value, needle);
    }

    void String::Replace(const std::string &target, const std::string &replacement)
    {
        String::Replace(value, target, replacement);
    }

    String String::ToLower()
    {
        return String::ToLower(value);
    }

    String String::ToUpper()
    {
        return String::ToUpper(value);
    }

    std::vector<std::string> String::Split(const std::string &str, char separator)
    {
        std::vector<std::string> substrings;
        std::istringstream ss(str);
        std::string token;

        while (std::getline(ss, token, separator)) 
        {
            substrings.push_back(token);
        }

        return substrings;
    }

    std::string String::Trim(const std::string &str)
    {
        // Find the first non-whitespace character from the beginning
        size_t start = str.find_first_not_of(" \t\n\r\f\v");

        // Find the last non-whitespace character from the end
        size_t end = str.find_last_not_of(" \t\n\r\f\v");

        // Handle the case where the string is all whitespace
        if (start == std::string::npos)
            return "";

        // Extract the substring between start and end
        return str.substr(start, end - start + 1);
    }

    std::string String::TrimStart(const std::string &str)
    {
        size_t start = str.find_first_not_of(" \t\n\r\f\v");

        if (start == std::string::npos)
            return "";

        // Extract the substring starting from the first non-whitespace character
        return str.substr(start);
    }

    std::string String::TrimEnd(const std::string &str)
    {
        size_t end = str.find_last_not_of(" \t\n\r\f\v");

        if (end == std::string::npos)
            return "";

        // Extract the substring from the beginning to the last non-whitespace character
        return str.substr(0, end + 1);
    }

    bool String::StartsWith(const std::string &str, const std::string &suffix)
    {
        if (str.length() >= suffix.length()) 
            return (0 == str.compare(0, suffix.length(), suffix));
        return false;
    }

    bool String::EndsWith(const std::string &str, const std::string &suffix)
    {
        if (str.length() >= suffix.length()) 
            return (0 == str.compare(str.length() - suffix.length(), suffix.length(), suffix));
        return false;
    }

    bool String::Contains(const std::string &haystack, const std::string &needle)
    {
        return haystack.find(needle) != std::string::npos;
    }

    void String::Replace(std::string &str, const std::string &target, const std::string &replacement)
    {
        size_t startPos = 0;

        while ((startPos = str.find(target, startPos)) != std::string::npos)
        {
            str.replace(startPos, target.length(), replacement);
            startPos += replacement.length();
        }
    }

    std::string String::ToLower(const std::string &str)
    {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    std::string String::ToUpper(const std::string &str)
    {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    std::ostream& operator<<(std::ostream& os, const String& str)
    {
        os << str.GetValue();
        return os;
    }
};