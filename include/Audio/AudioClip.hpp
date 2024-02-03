#ifndef GRAVY_AUDIOCLIP_HPP
#define GRAVY_AUDIOCLIP_HPP

#include <string>
#include <vector>

namespace Gravy::Audio
{
    class AudioClip 
    {
    private:
        std::string filePath;
        std::string fileName;
        std::vector<char> data;
        bool streamFromDisk;
    public:
        AudioClip(const std::string &filePath, bool streamFromDisk = true);
        AudioClip(const std::vector<char> data, const std::string &name);
        std::string GetPilePath() const;
        std::string GetFileName() const;
        bool GetStreamFromDisk() const;
        size_t GetDataSize() const;
        char *GetData();
    };
};
#endif