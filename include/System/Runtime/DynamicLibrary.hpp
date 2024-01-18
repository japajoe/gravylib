#ifndef GRAVY_DYNAMICLIBRARY_HPP
#define GRAVY_DYNAMICLIBRARY_HPP

#include <string>

namespace Gravy::System::Runtime
{
    class DynamicLibrary
    {
    private:
        void *handle;
    public:
        DynamicLibrary();
        ~DynamicLibrary();
        bool Load(const std::string &filePath);
        bool Unload();
        void *GetSymbol(const std::string &name);
    };
};

#endif