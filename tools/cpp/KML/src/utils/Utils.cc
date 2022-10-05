/*!
 * @file Utils.cc
 * @brief Utility functions used across project.
 */
#include "Utils.h"

#include <cmath>  // fabs
#include <stdexcept>

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

        double xlogx(const double& item)
        {
            if (item < 0)
            {
                throw std::runtime_error("Input item must be >= 0!");
            }
            if (0 == item)
            {
                return 0.0;
            }

            return item * std::log2(item);
        }

    }  // namespace Utils
}  // namespace KML

