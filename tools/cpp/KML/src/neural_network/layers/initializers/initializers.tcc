#include <iostream>
#include <random>
#include <vector>

using std::vector;

namespace NeuralNetwork {

    namespace Initializers {

        template<typename T>
        vector<double> uniform(int num_inputs, T a, T b) {
            vector<double> values(num_inputs, 0.0);

            if (b <= 1.0) {

                for (auto it = values.begin(); it != values.end(); ++it) {
                    *it = a + (float)(rand()) / ((float)(RAND_MAX/(b - a)));
                }
            }
            else {
                std::random_device rd;
                std::default_random_engine eng(rd());
                std::uniform_real_distribution<float> distr(a, b);

                for (auto it = values.begin(); it != values.end(); ++it) {
                    *it = distr(eng);
                }
          }

            return values;
        }

        template<typename T>
        vector<double> glorot(int num_inputs) {
            // Not Implemented
            vector<double> values(num_inputs, 0.0);
            return values;
        }

        vector<double> zeros(int num_inputs) {
            vector<double> values(num_inputs, 0.0);
            return values;
        }

    }
}
