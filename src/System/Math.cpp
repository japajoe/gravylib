#include "System/Math.hpp"
#include <algorithm>

namespace Gravy::System
{
    double Math::Min(double a, double b)
    {
        return std::min(a, b);
    }

    double Math::Max(double a, double b)
    {
        return std::max(a, b);
    }
}