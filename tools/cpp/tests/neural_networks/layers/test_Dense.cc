// unittest_dense_layer

#include <gtest/gtest.h>
#include <vector>

#include "Dense.h"
#include "KMatrix.h"

using KML::NeuralNetworks::Dense;

class DenseTest : public ::testing::Test
{
    public:
        Dense* dl;
        size_t inputSize = 4;
        size_t outputSize = 2;

        DenseTest()
        {
            dl = new Dense(inputSize, outputSize);
        }
};

TEST_F(DenseTest, TestInitialization)
{    
    KMatrix X(4, 2);
    X << 0, 0,
         0, 1,
         1, 0,
         1, 1;
    KMatrix y(4, 1);
    y << 0,
         1,
         1,
         0;

    /* dl->forward(X); */
    /* dl->backward(km); */
}
