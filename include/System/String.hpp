#ifndef GRAVY_STRING_HPP
#define GRAVY_STRING_HPP

#include <string>

namespace Gravy::System
{
    class String
    {
    public:
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
};
#endif