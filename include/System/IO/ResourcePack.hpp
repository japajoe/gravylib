// License (OLC-3)

// Copyright 2018-2023 OneLoneCoder.com

// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

//     Redistributions or derivations of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

//     Redistributions or derivative works in binary form must reproduce the above copyright notice. This list of conditions and the following disclaimer must be reproduced in the documentation and/or other materials provided with the distribution.

//     Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef GRAVY_RESOURCEPACK_HPP
#define GRAVY_RESOURCEPACK_HPP

#include <vector>
#include <string>
#include <map>
#include <cstdint>
#include <fstream>

namespace Gravy::System::IO
{
    struct ResourceBuffer : public std::streambuf
    {
        ResourceBuffer(std::ifstream &ifs, uint32_t offset, uint32_t size);
        std::vector<char> vMemory;
        std::string GetString();
        char *GetPointer(size_t &size);
    };

    struct ResourceFile
    {
        uint32_t nSize;
        uint32_t nOffset;
        std::string sFileName;
    };

    class ResourcePack : public std::streambuf
    {
    public:
        ResourcePack();
        ~ResourcePack();
        bool AddFile(const std::string &sFile);
        bool AddFile(const std::string &sFile, const std::string &sFileName);
        bool Load(const std::string &sFile, const std::string &sKey);
        bool Save(const std::string &sFile, const std::string &sKey);
        ResourceBuffer GetFileBuffer(const std::string &sFile);
        std::string GetFileAsString(const std::string &sFile);
        bool Loaded();
        std::map<std::string, ResourceFile> GetFiles() const;
    private:
        std::map<std::string, ResourceFile> mapFiles;
        std::ifstream baseFile;
        std::vector<char> Scramble(const std::vector<char> &data, const std::string &key);
        std::string MakePosix(const std::string &path);
        uint16_t Checksum(const unsigned char* buf, uint16_t length);
    };
};

#endif