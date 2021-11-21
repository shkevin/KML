#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <numeric>

using std::vector;

namespace NeuralNetwork {

    namespace Utils {

        template<typename T>
        vector<T> dot_product(vector<T> &a, vector<T> &b);

    }
}

#endif // UTILS_H
