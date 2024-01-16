#ifndef GRAVY_FILETIMEINFO_HPP
#define GRAVY_FILETIMEINFO_HPP

#include "FileInfo.hpp"

namespace Gravy::System::IO
{
    class FileTimeInfo
    {
    public:
        DateTime creationTime;
        DateTime lastWriteTime;
        FileTimeInfo();
        FileTimeInfo(const FileInfo &info);
        DateTime GetCreationTime() const;
        DateTime GetLastWriteTime() const;
    };
};

#endif