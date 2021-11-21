#include "utils.h"

namespace NeuralNetwork {

    namespace Utils {

        template<typename T>
        vector<T> dot_product(vector<T> &a, vector<T> &b) {
            T product = (T)0;

            for (size_t i = 0; i < a.size; ++i) {
                product += a[i] * b[i];
            }

            return product;
        }
    }
}
