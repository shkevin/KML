#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>

namespace KML
{
    namespace Utils
    {
        /*!
         * @brief Compare two doubles and determine if they are approximately equal.
         */
        bool approximatelyEqual(const double& a, const double& b, const double& epsilon = 0.0001);

        /*!
         * @brief Compare two doubles and determine if they are essentially equal.
         */
        bool essentiallyEqual(const double& a, const double& b, const double& epsilon = 0.0001);

        /*!
         * @brief Compare two doubles and determine if the first input is greater than the second.
         */
        bool definitelyGreaterThan(const double& a, const double& b,
                                   const double& epsilon = 0.0001);

        /*!
         * @brief Compare two doubles and determine if the first input is less than the second.
         */
        bool definitelyLessThan(const double& a, const double& b, const double& epsilon = 0.0001);

        /*!
         * @brief Calculate the x * log(x) value safely. If the value of x is equal to 0,
         *        safely output 0 instead.
         */
        double xlogx(const double& item);
    }  // namespace Utils
}  // namespace KML

#endif  // __UTILS_H__
