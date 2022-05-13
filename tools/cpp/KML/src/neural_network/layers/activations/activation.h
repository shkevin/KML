#ifndef ACTIVATION_H
#define ACTIVATION_H 

#include <vector>

using std::vector;

namespace NeuralNetwork {

    enum Activators {
        SIGMOID,
        SOFTMAX,
        TANH,
        RELU,
        LINEAR
    };

    class Activation {

        public:
            Activation(Activators a_activation = LINEAR);
            ~Activation();

            // Sigmoid activation
            const double sigmoid(double input);
            const double sigmoid(vector<double> input);

            // Relu activation
            
            // Linear activation


        protected:
            const double forward(double input);
            const double backward(double input);
    };
}

#endif // ACTIVATION_H
