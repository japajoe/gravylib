// License (OLC-3)

// Copyright 2018-2023 OneLoneCoder.com

// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

//     Redistributions or derivations of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

//     Redistributions or derivative works in binary form must reproduce the above copyright notice. This list of conditions and the following disclaimer must be reproduced in the documentation and/or other materials provided with the distribution.

//     Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "ResourcePack.hpp"
#include "File.hpp"
#include <cstring>
#include <iostream>

namespace Gravy::System::IO
{
    ResourceBuffer::ResourceBuffer(std::ifstream &ifs, uint32_t offset, uint32_t size)
    {
        vMemory.resize(size);
        ifs.seekg(offset);
        ifs.read(vMemory.data(), vMemory.size());
        setg(vMemory.data(), vMemory.data(), vMemory.data() + size);
    }

    ResourcePack::ResourcePack() {}
    ResourcePack::~ResourcePack() { baseFile.close(); }

    bool ResourcePack::AddFile(const std::string &sFile)
    {
        const std::string file = MakePosix(sFile);

        if (File::Exists(file))
        {            
            ResourceFile e;
            e.nSize = static_cast<uint32_t>(File::GetSize(file));
            e.nOffset = 0; // Unknown at this stage
            e.sFileName = file;
            mapFiles[sFile] = e;
            return true;
        }
        return false;
    }

    bool ResourcePack::AddFile(const std::string &sFile, const std::string &sFileName)
    {
        const std::string file = MakePosix(sFile);
        const std::string fileName = MakePosix(sFileName);

        if (File::Exists(file))
        {
            ResourceFile e;
            e.nSize = static_cast<uint32_t>(File::GetSize(file));
            e.nOffset = 0; // Unknown at this stage
            e.sFileName = fileName;
            mapFiles[file] = e;
            return true;
        }
        return false;
    }

    bool ResourcePack::Load(const std::string &sFile, const std::string &sKey)
    {
        // Open the resource file
        baseFile.open(sFile, std::ifstream::binary);
        if (!baseFile.is_open())
            return false;

        // Read checksum and compare. If the check fails, the provided key is incorrect
        uint16_t checksum = 0;
        baseFile.read((char *)&checksum, sizeof(uint16_t));
        unsigned char *ptrKey = reinterpret_cast<unsigned char*>(const_cast<char*>(sKey.data()));
        uint16_t crc = Checksum(ptrKey, sKey.size());

        if(crc != checksum)
        {
            baseFile.close();
            return false;
        }

        // 1) Read Scrambled index
        uint32_t nIndexSize = 0;
        baseFile.read((char *)&nIndexSize, sizeof(uint32_t));

        std::vector<char> buffer(nIndexSize);
        for (uint32_t j = 0; j < nIndexSize; j++)
            buffer[j] = baseFile.get();

        std::vector<char> decoded = Scramble(buffer, sKey);
        size_t pos = 0;
        auto read = [&decoded, &pos](char *dst, size_t size)
        {
            memcpy((void *)dst, (const void *)(decoded.data() + pos), size);
            pos += size;
        };

        auto readSingleByte = [&read]() -> int
        { char c; read(&c, 1); return c; };

        // 2) Read Map
        uint32_t nMapEntries = 0;
        read((char *)&nMapEntries, sizeof(uint32_t));
        for (uint32_t i = 0; i < nMapEntries; i++)
        {
            uint32_t nFilePathSize = 0;
            read((char *)&nFilePathSize, sizeof(uint32_t));

            std::string sFileName(nFilePathSize, ' ');
            for (uint32_t j = 0; j < nFilePathSize; j++)
                sFileName[j] = readSingleByte();

            ResourceFile e;
            read((char *)&e.nSize, sizeof(uint32_t));
            read((char *)&e.nOffset, sizeof(uint32_t));
            e.sFileName = sFileName;
            mapFiles[sFileName] = e;
        }

        // Don't close base file! we will provide a stream
        // pointer when the file is requested
        return true;
    }

    bool ResourcePack::Save(const std::string &sFile, const std::string &sKey)
    {
        // Create/Overwrite the resource file
        std::ofstream ofs(sFile, std::ofstream::binary);
        if (!ofs.is_open())
            return false;

        unsigned char *ptrKey = reinterpret_cast<unsigned char*>(const_cast<char*>(sKey.data()));

        uint16_t crc = Checksum(ptrKey, sKey.size());

        ofs.write((char *)&crc, sizeof(uint16_t));

        // Iterate through map
        uint32_t nIndexSize = 0; // Unknown for now
        ofs.write((char *)&nIndexSize, sizeof(uint32_t));
        uint32_t nMapSize = uint32_t(mapFiles.size());
        ofs.write((char *)&nMapSize, sizeof(uint32_t));
        for (auto &e : mapFiles)
        {
            // Write the path of the file
            size_t nPathSize = e.second.sFileName.size();
            ofs.write((char *)&nPathSize, sizeof(uint32_t));
            ofs.write(e.second.sFileName.c_str(), nPathSize);

            // Write the file entry properties
            ofs.write((char *)&e.second.nSize, sizeof(uint32_t));
            ofs.write((char *)&e.second.nOffset, sizeof(uint32_t));
        }

        // 2) Write the individual Data
        std::streampos offset = ofs.tellp();
        nIndexSize = (uint32_t)offset;
        for (auto &e : mapFiles)
        {
            // Store beginning of file offset within resource pack file
            e.second.nOffset = (uint32_t)offset;

            // Load the file to be added
            std::vector<uint8_t> vBuffer(e.second.nSize);
            std::ifstream i(e.first, std::ifstream::binary);
            i.read((char *)vBuffer.data(), e.second.nSize);
            i.close();

            // Write the loaded file into resource pack file
            ofs.write((char *)vBuffer.data(), e.second.nSize);
            offset += e.second.nSize;
        }

        // 3) Scramble Index
        std::vector<char> stream;
        auto write = [&stream](const char *data, size_t size)
        {
            size_t sizeNow = stream.size();
            stream.resize(sizeNow + size);
            memcpy(stream.data() + sizeNow, data, size);
        };

        // Iterate through map
        write((char *)&nMapSize, sizeof(uint32_t));
        for (auto &e : mapFiles)
        {
            // Write the path of the file
            size_t nPathSize = e.second.sFileName.size();
            write((char *)&nPathSize, sizeof(uint32_t));
            write(e.second.sFileName.c_str(), nPathSize);

            // Write the file entry properties
            write((char *)&e.second.nSize, sizeof(uint32_t));
            write((char *)&e.second.nOffset, sizeof(uint32_t));
        }
        std::vector<char> sIndexString = Scramble(stream, sKey);
        uint32_t nIndexStringLen = uint32_t(sIndexString.size());
        // 4) Rewrite Map (it has been updated with offsets now)
        // at start of file
        ofs.seekp(sizeof(uint16_t), std::ios::beg); //Beginning is after checksum
        ofs.write((char *)&nIndexStringLen, sizeof(uint32_t));
        ofs.write(sIndexString.data(), nIndexStringLen);
        ofs.close();
        return true;
    }

    ResourceBuffer ResourcePack::GetFileBuffer(const std::string &sFile)
    {
        return ResourceBuffer(baseFile, mapFiles[sFile].nOffset, mapFiles[sFile].nSize);
    }

    bool ResourcePack::Loaded()
    {
        return baseFile.is_open();
    }

    std::vector<char> ResourcePack::Scramble(const std::vector<char> &data, const std::string &key)
    {
        if (key.empty())
            return data;
        std::vector<char> o;
        size_t c = 0;
        for (auto s : data)
            o.push_back(s ^ key[(c++) % key.size()]);
        return o;
    };

    std::string ResourcePack::MakePosix(const std::string &path)
    {
        std::string o;
        for (auto s : path)
            o += std::string(1, s == '\\' ? '/' : s);
        return o;
    };

    std::map<std::string, ResourceFile> ResourcePack::GetFiles() const
    {
        return mapFiles;
    }

    uint16_t ResourcePack::Checksum(const unsigned char* buf, uint16_t length)
    {
        uint32_t sum = 0;

        sum += length;

        // build the sum of 16bit words
        while (length > 1)
        {
            sum += static_cast<uint32_t>(0xFFFF & (*buf << 8 | *(buf + 1)));
            buf += 2;
            length -= 2;
        }

        // if there is a byte left then add it (padded with zero)
        if (length != 0)
        {
            //--- made by SKA ---                sum += (0xFF & *buf)<<8;
            sum += static_cast<uint32_t>(0xFFFF & (*buf << 8 | 0x00));
        }

        // now calculate the sum over the bytes in the sum
        // until the result is only 16bit long
        while ((sum >> 16) != 0)
        {
            sum = (sum & 0xFFFF) + (sum >> 16);
        }

        // build 1's complement:
        return static_cast<uint16_t>(sum ^ 0xFFFF);
    }
};