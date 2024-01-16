#ifndef GRAVY_CONSOLE_HPP
#define GRAVY_CONSOLE_HPP

#include <string>

namespace Gravy::System
{
    enum class ConsoleColor
    {
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White,
        Reset
    };

    class Console
    {
    public:
        static void WriteLine(const std::string &text, ConsoleColor color = ConsoleColor::White);
        static void Write(const std::string &text, ConsoleColor color = ConsoleColor::White);
        static void WriteLog(const std::string &text);
        static void WriteError(const std::string &text);
    };
};

#endif