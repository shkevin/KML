#ifndef LAYER_H
#define LAYER_H

#include <eigen3/Eigen/Dense>

#include "../utils/utils.h"

using namespace Eigen;

namespace NeuralNetwork {

    namespace Layer {

        enum Activation {
            SIGMOID,
            SOFTMAX,
            TANH,
            RELU,
        };

        enum Initializer {
            UNIFORM,
            GLOROT,
            ZEROS
        };

        class Layer {

            public:

                Layer(int units,
                    Activation activation,
                    Initializer kernel_initializer = UNIFORM,
                    Initializer bias_initializer = ZEROS);

                ~Layer();
                virtual void update() = 0;

            protected:

                template<typename T>
                const vector<T> forward(vector<T> inputs);

                virtual void backward() = 0;

            private:

                vector<double> weights;
                vector<double> bias;
        };
    }
}

#endif // LAYER_H
