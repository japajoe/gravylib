#ifndef GRAVY_DIRECTORY_HPP
#define GRAVY_DIRECTORY_HPP

#include <string>

namespace Gravy::System::IO
{
    class Directory
    {
    public:
        static bool Exists(const std::string &path);
        static bool Create(const std::string &path);
    };
};

#endif