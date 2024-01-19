#ifndef GRAVY_STRINGBUILDER_HPP
#define GRAVY_STRINGBUILDER_HPP

#include <sstream>

namespace Gravy::System::Text
{
    class StringBuilder
    {
    private:
        std::stringstream ss;
    public:
        void Append(const std::string &value);
        void Append(int64_t value);
        void Append(uint64_t value);
        void Append(double value);
        void AppendLine(const std::string &value);
        void AppendLine(int64_t value);
        void AppendLine(uint64_t value);
        void AppendLine(double value);
        void Clear();
        std::string ToString() const;
    };
};

#endif