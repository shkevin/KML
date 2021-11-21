#include <iostream>

#include "dense.h"
#include "../utils/utils.h"

namespace NeuralNetwork {

    namespace Layer {

        Dense::Dense(int units, Activation activation) : Layer(units, activation) {}

        Dense::~Dense() {}

        void Dense::update() {}

        const vector<double> Dense::forward(vector<double> inputs) {
            return this->weights;
        }

        void Dense::backward() {}
    }
}
