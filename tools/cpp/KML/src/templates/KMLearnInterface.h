#include "SimpleKMLearn.h"

namespace KML {

    class KMLearnInterface : Estimator {

        public:
            virtual Estimator fit() = 0;
            virtual Estimator predict() = 0;
            virtual Estimator fit_predict() = 0;
    };
}
