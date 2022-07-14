/*!
 * @file StreamingMAD.h
 * @brief
 */
#ifndef __STREAMING_MAD_H__
#define __STREAMING_MAD_H__

#include "IMetric.h"
#include "WindowedFAME.h"

using KML::Statistics::WindowedFAME;

namespace KML
{
    namespace Metrics
    {
        class StreamingMAD : public IMetric<double>
        {
            public:
                /*!
                 * @brief
                 */
                StreamingMAD();

                /*!
                 * @brief
                 */
                ~StreamingMAD();

                /*!
                 * Copy Constructor.
                 */
                StreamingMAD(const StreamingMAD&) = delete; // No copy

                /*!
                 * Copy Assignment Operator.
                 */
                StreamingMAD& operator=(const StreamingMAD&) = delete; // No copy

                /*!
                 * @copydoc IMetric::update()
                 */
                using IMetric<double>::update;
                virtual void update(const double& observation) override;

                /*!
                 * @copydoc IMetric::evaluate()
                 */
                using IMetric<double>::evaluate;
                virtual double evaluate() const override;

            private:
                /*!
                 * @brief
                 */
                WindowedFAME *m_scoreMedian = nullptr;

                /*!
                 * @brief
                 */
                WindowedFAME *m_errorMedian = nullptr;
        };
    }
}

#endif // __STREAMING_MAD_H__
