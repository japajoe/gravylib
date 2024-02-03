#include "AudioClip.hpp"
#include "System/IO/File.hpp"

namespace Gravy::Audio
{
    AudioClip::AudioClip(const std::string &filePath, bool streamFromDisk)
    {
        this->filePath = filePath;
        this->streamFromDisk = streamFromDisk;
        this->fileName = System::IO::File::GetName(filePath);
    }

    AudioClip::AudioClip(const std::vector<char> data, const std::string &name)
    {
        this->filePath = "";
        this->streamFromDisk = false;
        this->data = data;
        this->fileName = System::IO::File::GetName(name);
    }

    std::string AudioClip::GetPilePath() const
    {
        return filePath;
    }

    std::string AudioClip::GetFileName() const
    {
        return fileName;
    }

    bool AudioClip::GetStreamFromDisk() const
    {
        return streamFromDisk;
    }

    size_t AudioClip::GetDataSize() const
    {
        return data.size();
    }

    char *AudioClip::GetData()
    {
        return &data[0];
    }
};