
#include "Utils.h"

#include <cmath>  // fabs

namespace KML
{
    namespace Utils
    {

        bool approximatelyEqual(const double& a, const double& b, const double& epsilon)
        {
            return std::fabs(a - b) <=
                   ((std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
        }

        bool essentiallyEqual(const double& a, const double& b, const double& epsilon)
        {
            return std::fabs(a - b) <=
                   ((std::fabs(a) > std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
        }

        bool definitelyGreaterThan(const double& a, const double& b, const double& epsilon)
        {
            return (a - b) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
        }

        bool definitelyLessThan(const double& a, const double& b, const double& epsilon)
        {
            return (b - a) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
        }

    }  // namespace Utils
}  // namespace KML

