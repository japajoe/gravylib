#ifndef GRAVY_GUID_HPP
#define GRAVY_GUID_HPP

#include <string>

namespace Gravy::System
{
    class Guid
    {
    private:
        std::string value;
    public:
        static Guid NewGuid();
        static bool TryParse(const std::string &str, Guid &result);
        std::string ToString() const;
        bool operator==(const Guid& other) const;
        bool operator!=(const Guid& other) const;
    };
};

#endif