/*!
 * @file StreamingMAD.h
 * @brief
 */
#include "IMetric.h"
#include "WindowedFame.h"

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
                StreamingMAD(const size_t& windowSize);

                /*!
                 * @brief
                 */
                ~StreamingMAD();

                /*!
                 * @copydoc IMetric::update()
                 */
                virtual void update(const double& observation) override;

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
