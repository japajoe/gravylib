#ifndef GRAVY_FILE_HPP
#define GRAVY_FILE_HPP

#include <string>
#include <vector>

namespace Gravy::System::IO
{
    class File
    {
    private:
        std::string path;
        std::string name;
        std::string extension;
        size_t size;
    public:
        File();
        File(const std::string &path);
        std::string GetPath() const;
        std::string GetName() const;
        std::string GetExtension() const;
        size_t GetSize() const;

        static std::string ReadAllText(const std::string& filepath);
        static std::vector<std::string> ReadAllLines(const std::string &filepath);
        static std::vector<unsigned char> ReadAllBytes(const std::string &filepath);
        static void WriteAllText(const std::string& filepath, const std::string& text);
        static void WriteLine(const std::string& filepath, const std::string& text);
        static void WriteAllBytes(const std::string& filepath, unsigned char* bytes, size_t size);
        static size_t GetSize(const std::string& filepath);
        static bool Exists(const std::string& filepath);
        static bool IsWithinDirectory(const std::string &path, const std::string &directory);
        static std::string GetName(const std::string &filepath);
        static std::string GetExtension(const std::string &filepath);
    };
};

#endif