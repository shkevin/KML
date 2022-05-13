#include "layer.h"
#include "initializers/initializers.tcc"

namespace NeuralNetwork {

    namespace Layer {

        Layer::Layer(const int a_units, 
                Activators activation, 
                Initializer kernel_initializer, 
                Initializer bias_initializer) : m_units(a_units)
        {
            // Initialize the weights
            switch (kernel_initializer) {
                case UNIFORM:
                    this->m_weights = Initializers::uniform(a_units, 0.0, 1.0);
                case ZEROS:
                    this->m_weights = Initializers::zeros(a_units);
                default:
                    this->m_weights = Initializers::uniform(a_units, 0.0, 1.0);
            }
  
            // Initialize the bias
            switch (bias_initializer) {
                case ZEROS:
                    this->m_bias = Initializers::zeros(a_units);
                case UNIFORM:
                    this->m_bias = Initializers::uniform(a_units, 0, 1);
                default:
                    this->m_bias = Initializers::zeros(a_units);
            }

        }

        Layer::~Layer() {

        }

        template<typename T>
        void Layer::update(vector<T> inputs) {
        }

        template<typename T>
        const vector<T> forward(vector<T> inputs) {
        }

        void backward() {

        }
    }
}
