#include "Console.hpp"
#include "DateTime.hpp"
#include "Environment.hpp"
#include <iostream>
#include <map>
#include <mutex>

namespace Gravy::System
{
    static std::map<ConsoleColor, std::string> consoleColorMap;
    static std::mutex consoleColorMapMutex;

    static void InitializeConsoleColors()
    {
        if (consoleColorMap.size() == 0)
        {
            std::lock_guard<std::mutex> lock(consoleColorMapMutex); // Lock the mutex
            if (consoleColorMap.size() == 0) // Check again within the locked section
            {
                consoleColorMap[ConsoleColor::Red] = "\x1B[31m";
                consoleColorMap[ConsoleColor::Green] = "\x1B[32m";
                consoleColorMap[ConsoleColor::Yellow] = "\x1B[33m";
                consoleColorMap[ConsoleColor::Blue] = "\x1B[34m";
                consoleColorMap[ConsoleColor::Magenta] = "\x1B[35m";
                consoleColorMap[ConsoleColor::Cyan] = "\x1B[36m";
                consoleColorMap[ConsoleColor::White] = "\x1B[37m";
                consoleColorMap[ConsoleColor::Reset] = "\x1B[0m";
            }
        }
    }

    void Console::WriteLine(const std::string &text, ConsoleColor color)
    {
        #ifdef _WIN32
            std::cout << text << Environment::NewLine();
        #else
            InitializeConsoleColors();
            std::lock_guard<std::mutex> lock(consoleColorMapMutex);
            std::cout << consoleColorMap[color] << text << consoleColorMap[ConsoleColor::Reset] << Environment::NewLine();
        #endif
    }

    void Console::Write(const std::string &text, ConsoleColor color)
    {
        #ifdef _WIN32
            std::cout << text;
        #else
            InitializeConsoleColors();
            std::lock_guard<std::mutex> lock(consoleColorMapMutex);
            std::cout << consoleColorMap[color] << text << consoleColorMap[ConsoleColor::Reset];
        #endif
    }

    void Console::WriteLog(const std::string &text)
    {
        std::string timestamp = DateTime::Now().FormattedTimestamp();
        #ifdef _WIN32
            std::cout << timestamp << ' ' << text << Environment::NewLine();
        #else
            InitializeConsoleColors();
            std::lock_guard<std::mutex> lock(consoleColorMapMutex);
            std::cout << consoleColorMap[ConsoleColor::Green] << timestamp << consoleColorMap[ConsoleColor::Reset] << ' ' << text << Environment::NewLine();
        #endif
    }

    void Console::WriteError(const std::string &text)
    {
        std::string timestamp = DateTime::Now().FormattedTimestamp();
        #ifdef _WIN32
            std::cout << timestamp << ' ' << text << Environment::NewLine();
        #else
            InitializeConsoleColors();
            std::lock_guard<std::mutex> lock(consoleColorMapMutex);
            std::cout << consoleColorMap[ConsoleColor::Green] << timestamp << consoleColorMap[ConsoleColor::Red] << ' ' << text << consoleColorMap[ConsoleColor::Reset] << Environment::NewLine();
        #endif
    }
};