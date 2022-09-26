/*!
 * @file KMatrix.h
 * @brief
 */
#ifndef __KMATRIX_H__
#define __KMATRIX_H__

#include <utility>  // pair

#ifndef WITH_EIGEN
#define WITH_EIGEN 0  // Set with build options.
#endif                // ifndef WITH_EIGEN

#ifdef WITH_EIGEN
#include <eigen3/Eigen/Dense>
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> Base;
#else
#include "KSimpleMatrix.h"
typedef KML::DataStructures::KSimpleMatrix Base;
#endif  // ifdef WITH_EIGEN

namespace KML
{
    namespace DataStructures
    {
        class KMatrix : public Base  // Base is either Eigen or KSimpleMatrix
        {
            public:
#ifdef WITH_EIGEN
                KMatrix(void) : Eigen::MatrixXd() {}

                // Inherit the Eigen Constructors.
                using Eigen::MatrixXd::MatrixXd;

                // This constructor allows you to construct KMatrix from Eigen expressions
                template<typename OtherDerived>
                explicit KMatrix(const Eigen::MatrixBase<OtherDerived>& other)
                    : Eigen::MatrixXd(other)
                {
                    // Do nothing.
                }

                // This method allows you to assign Eigen expressions to KMatrix
                template<typename OtherDerived>
                KMatrix& operator=(const Eigen::MatrixBase<OtherDerived>& other)
                {
                    this->Eigen::MatrixXd::operator=(other);
                    return *this;
                }
#else
                using KML::DataStructures::KSimpleMatrix::KSimpleMatrix;
#endif
                // Additional declarations shared across Eigen/KSimpleMatrix here.
        };
    }  // namespace DataStructures
}  // namespace KML

#endif  // __KMATRIX_H__
