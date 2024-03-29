#include "FileStream.hpp"

namespace Gravy::System::IO
{
    FileStream::FileStream(const std::string &filepath, FileMode mode, FileAccess access)
    {
        // Convert FileAccess and FileMode to std::ios_base::openmode
        std::ios_base::openmode fileMode = std::ios_base::binary;

        if (access == FileAccess::Read)
        {
            fileMode |= std::ios_base::in;
        }
        else if (access == FileAccess::Write)
        {
            fileMode |= std::ios_base::out;
        }
        else if (access == FileAccess::ReadWrite)
        {
            fileMode |= std::ios_base::in | std::ios_base::out;
        }

        if (mode == FileMode::CreateNew)
        {
            fileMode |= std::ios_base::trunc;
        }
        else if (mode == FileMode::Create)
        {
            fileMode |= std::ios_base::out | std::ios_base::trunc;
        }
        else if (mode == FileMode::Open)
        {
            fileMode |= std::ios_base::in;
        }
        else if (mode == FileMode::OpenOrCreate)
        {
            fileMode |= std::ios_base::in | std::ios_base::out;
        }
        else if (mode == FileMode::Truncate)
        {
            fileMode |= std::ios_base::out | std::ios_base::trunc;
        }
        else if (mode == FileMode::Append)
        {
            fileMode |= std::ios_base::out | std::ios_base::app;
        }

        file.open(filepath, fileMode);

        if (!file.is_open())
        {
            // Handle file opening failure
            throw std::runtime_error("Failed to open file: " + filepath);
        }

        // Initialize stream properties based on the file's size
        file.seekg(0, std::ios_base::end);
        size = file.tellg();
        file.seekg(0, std::ios_base::beg);
        readPosition = 0;
        writePosition = (mode == FileMode::Append) ? size : 0;
    }

    FileStream::~FileStream()
    {
        Close();
    }

    size_t FileStream::Read(void *buffer, size_t size)
    {
        // Check if the file is at the end before attempting to read
        if (file.peek() == EOF)
        {
            readPosition = file.tellg();
            return 0;
        }

        file.read(static_cast<char *>(buffer), size);
        readPosition = file.tellg();
        return file.gcount();
    }

    size_t FileStream::Write(const void *buffer, size_t size)
    {
        file.write(static_cast<const char *>(buffer), size);
        writePosition = file.tellp();
        return size;
    }

    ssize_t FileStream::Seek(ssize_t offset, SeekOrigin origin)
    {
        if(!file.good())
            return -1;

        std::ios_base::seekdir seekDir;

        switch (origin)
        {
        case SeekOrigin::Begin:
            seekDir = std::ios_base::beg;
            break;
        case SeekOrigin::Current:
            seekDir = std::ios_base::cur;
            break;
        case SeekOrigin::End:
            seekDir = std::ios_base::end;
            break;
        default:
            // Invalid seek origin
            return -1;
        }

        file.seekg(offset, seekDir);
        readPosition = file.tellg();
        writePosition = file.tellp();

        return readPosition;
    }

    void FileStream::Close()
    {
        if (file.is_open())
        {
            file.close();
        }
    }
};