#include <string>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include "Color.hpp"

namespace Gravy::System::Drawing
{
    class Image
    {
    private:
        std::vector<uint8_t> data;
        uint32_t width;
        uint32_t height;
        uint32_t channels;
    public:
        Image();
        Image(const std::string &filepath);
        Image(const uint8_t *uncompressedData, size_t size, uint32_t width, uint32_t height, uint32_t channels);
        std::vector<uint8_t> &GetData();
        uint32_t GetWidth() const;
        uint32_t GetHeight() const;
        uint32_t GetChannels() const;
        void Clear();
        bool LoadFromFile(const std::string &filepath);
        bool LoadFromMemory(const uint8_t *data, size_t size);
        bool Load(uint32_t width, uint32_t height, uint32_t channels, const Color &color);
    };
}