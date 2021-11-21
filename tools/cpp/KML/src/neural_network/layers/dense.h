#ifndef DENSE_H
#define DENSE_H

#include "layer.h"

namespace NeuralNetwork {

    namespace Layer {

        class Dense : Layer {

            public:

                Dense(int units, Activation activation);
                ~Dense();
                void update();

            protected:

                const vector<double> forward(vector<double> inputs);
                void backward();

            private:

                vector<double> weights;
                vector<double> bias;
        };
    }
}

#endif // DENSE_H
