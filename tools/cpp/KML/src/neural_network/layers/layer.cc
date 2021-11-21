#include "layer.h"
#include "initializers/initializers.tcc"

namespace NeuralNetwork {

    namespace Layer {

        Layer::Layer(int units, 
                Activation activation, 
                Initializer kernel_initializer, 
                Initializer bias_initializer)
        {
            // Initialize the weights
            switch (kernel_initializer) {
                case UNIFORM:
                    this->weights = Initializers::uniform(units, 0.0, 1.0);
                case ZEROS:
                    this->weights = Initializers::zeros(units);
                default:
                    this->weights = Initializers::uniform(units, 0.0, 1.0);
            }
  
            // Initialize the bias
            switch (bias_initializer) {
                case ZEROS:
                    this->bias = Initializers::zeros(units);
                case UNIFORM:
                    this->bias = Initializers::uniform(units, 0, 1);
                default:
                    this->bias = Initializers::zeros(units);
            }
        }

        Layer::~Layer() {

        }

        void Layer::update() {

        }

    }
}
