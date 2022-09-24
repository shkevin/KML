/*!
 * @file StreamingMAD.h
 * @brief
 */
#ifndef __STREAMING_MAD_H__
#define __STREAMING_MAD_H__

#include "IMetric.h"
#include "WindowedFAME.h"

namespace KML
{
    namespace Metrics
    {
        using KML::Statistics::WindowedFAME;
        class StreamingMAD : public IMetric<double>
        {
            public:
                /*!
                 * @brief
                 */
                StreamingMAD();

                /*!
                 * Copy Constructor.
                 */
                StreamingMAD(const StreamingMAD&) = delete;

                /*!
                 * Copy Assignment Operator.
                 */
                StreamingMAD& operator=(const StreamingMAD&) = delete;

                /*!
                 * @brief Move Constructor.
                 */
                StreamingMAD(StreamingMAD&& other);

                /*!
                 * @brief Move Assignment.
                 */
                StreamingMAD& operator=(StreamingMAD&& rhs);

                /*!
                 * @brief
                 */
                ~StreamingMAD() override;

                /*!
                 * @copydoc IMetric::update()
                 */
                using IMetric<double>::update;
                void update(const double& observation) override;

                /*!
                 * @copydoc IMetric::evaluate()
                 */
                using IMetric<double>::evaluate;
                double evaluate() const override;

            private:
                /*!
                 * @brief
                 */
                WindowedFAME* m_scoreMedian = nullptr;

                /*!
                 * @brief
                 */
                WindowedFAME* m_errorMedian = nullptr;
        };
    }  // namespace Metrics
}  // namespace KML

#endif  // __STREAMING_MAD_H__
