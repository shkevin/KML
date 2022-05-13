#ifndef LAYER_H
#define LAYER_H

#include <eigen3/Eigen/Dense>

#include "../utils/utils.h"
#include "activations/activation.h"

using namespace Eigen;

namespace NeuralNetwork {

    namespace Layer {

        enum Initializer {
            UNIFORM,
            GLOROT,
            ZEROS
        };

        class Layer {

            public:

                Layer(const int a_units,
                    Activators a_activation,
                    Initializer a_kernel_initializer = UNIFORM,
                    Initializer a_bias_initializer = ZEROS);

                ~Layer();

                template<typename T>
                void update(vector<T> inputs);

            protected:

                template<typename T>
                const vector<T> forward(vector<T> inputs);

                virtual void backward() = 0;

                const int m_units;
                vector<double> m_weights;
                vector<double> m_bias;
        };
    }
}

#endif // LAYER_H
