#include "Guid.hpp"
#include "Random.hpp"
#include <sstream>
#include <regex>
#include <iomanip>

namespace Gravy::System
{
    Guid Guid::NewGuid()
    {
        std::stringstream ss;
        
        for(size_t i = 0; i < 16; ++i)
        {
            uint8_t rand_byte = Random::GetNextByte();

            if (i == 6)
                rand_byte = (rand_byte & 0x0F) | 0x40; // set the version to 4
            else if (i == 8)
                rand_byte = (rand_byte & 0x3F) | 0x80; // set the variant to RFC 4122
            
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(rand_byte);

            if (i == 3 || i == 5 || i == 7 || i == 9) 
                ss << "-";
        }

        Guid guid;
        guid.value = ss.str();
        return guid;
    }

    bool Guid::TryParse(const std::string &str, Guid &result)
    {
        if (str.size() != 36)
            return false;  // Invalid length for a GUID

        static const std::regex reg("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[4][0-9a-fA-F]{3}-[8-9a-bA-B][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$");

        if(std::regex_match(str, reg))
        {
            result.value = str;
            return true;
        }

        return false;
    }

    std::string Guid::ToString() const
    {
        return value;
    }

    bool Guid::operator==(const Guid& other) const
    {
        return value == other.value;
    }

    bool Guid::operator!=(const Guid& other) const
    {
        return value != other.value;
    }
};