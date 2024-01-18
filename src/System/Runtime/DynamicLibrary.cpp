#include "DynamicLibrary.hpp"
#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <iostream>
#include "File.hpp"

namespace Gravy::System::Runtime
{
    DynamicLibrary::DynamicLibrary()
    {
        handle = nullptr;
    }

    DynamicLibrary::~DynamicLibrary()
    {
        Unload();
    }

    bool DynamicLibrary::Load(const std::string &filePath)
    {
        if(handle)
            return false;

        if(!System::IO::File::Exists(filePath))
        {
            std::cout << "File does not exist: " << filePath;
            return false;
        }
            
    #ifdef _WIN32
        handle = (void*)LoadLibrary(filePath);
        if(!handle) 
        {
            std::cout << "Failed to load plugin: " << filePath << '\n';
            return false;
        }    
    #else
        handle = dlopen(filePath.c_str(), RTLD_LAZY);
        if(!handle) 
        {
            char *error = dlerror();
            std::cout << "Failed to load plugin: " << filePath << ". Error: " << error << '\n';
            return false;
        }
    #endif
        return true;
    }

    bool DynamicLibrary::Unload()
    {
        if(!handle)
            return false;
    #ifdef _WIN32
        FreeLibrary((HINSTANCE)handle);
    #else
        dlclose(handle);
    #endif
        handle = nullptr;
        return true;
    }

    void *DynamicLibrary::GetSymbol(const std::string &name)
    {
        if(!handle)
            return nullptr;

        void *s = nullptr;

    #ifdef _WIN32
        s = (void*)GetProcAddress((HINSTANCE)handle, name.c_str());
        if(s == nullptr) 
        {
            std::cout << "Error: undefined symbol:" << name << '\n';
        }
    #else
        dlerror(); /* clear error code */
        s = dlsym(handle, name.c_str());
        char *error = dlerror();
        if (error != nullptr)
        {
            std::cout << "Error: undefined symbol:" << name << '\n';
        }
    #endif
        return s;
    }    
};