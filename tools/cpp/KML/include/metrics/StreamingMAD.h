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

        /*!
         * @brief Streaming Median Absolute Deviation (MAD) declarations.
         */
        class StreamingMAD : public IMetric<double>
        {
            public:
                /*!
                 * @brief Default Constructor.
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
                 * @brief Default Destructor.
                 */
                ~StreamingMAD() override;

                /*!
                 * @copydoc IMetric::update()
                 */
                void update(const double& observation) override;
                using IMetric<double>::update;

                /*!
                 * @copydoc IMetric::evaluate()
                 */
                double evaluate() const override;
                using IMetric<double>::evaluate;

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
