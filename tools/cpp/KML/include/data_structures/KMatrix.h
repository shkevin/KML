/*!
 * @file KMatrix.h
 * @brief
 */
#ifndef __KMATRIX_H__
#define __KMATRIX_H__

// This is so that I could potentially create my own matrix class.
/* #ifdef EIGEN */
/* #include <eigen3/Eigen/Dense> */
/* /1* #define KMatrix Eigen::MatrixXd *1/ */
/* typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> Base; */

/* #else */
/* #include "KSimpleMatrix.h" */
/* typedef KML::DataStructures::KSimpleMatrix Base; */
/* /1* #define KMatrix KSimpleMatrix *1/ */
/* #endif //if defined(BUILD_EIGEN) */

#include <eigen3/Eigen/Dense>

namespace KML
{
    namespace DataStructures
    {
        class KMatrix : public Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>
        {
            public:
            	KMatrix(void) : Eigen::MatrixXd() {}

				// Inherit the Eigen Constructors.
				using Eigen::MatrixXd::MatrixXd;
 
    			// This constructor allows you to construct KMatrix from Eigen expressions
    			template<typename OtherDerived>
    			KMatrix(const Eigen::MatrixBase<OtherDerived>& other)
    			    : Eigen::MatrixXd(other)
    			{ }
 
    			// This method allows you to assign Eigen expressions to KMatrix
    			template<typename OtherDerived>
    			KMatrix& operator=(const Eigen::MatrixBase <OtherDerived>& other)
    			{
    			    this->Eigen::MatrixXd::operator=(other);
    			    return *this;
    			}
        };
    } // DataStructures
} // KML

#endif // __KMATRIX_H__
