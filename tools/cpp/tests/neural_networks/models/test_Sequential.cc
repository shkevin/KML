// unittest_sequential

#include <gtest/gtest.h>
#include <vector>

#include "KMatrix.h"
#include "IModel.h"
#include "Sequential.h"
#include "Dense.h"
#include "Tanh.h"
#include "ILayer.h"
#include "MSE.h"
#include "ILoss.h"

using KML::NeuralNetworks::Models::IModel;
using KML::NeuralNetworks::Models::Sequential;
using KML::NeuralNetworks::Activations::Tanh;
using KML::NeuralNetworks::ILayer;
using KML::NeuralNetworks::Dense;
using KML::NeuralNetworks::Losses::ILoss;
using KML::NeuralNetworks::Losses::MSE;

class SequentialTest : public ::testing::Test
{
    public:
        IModel *model;
        KMatrix X;

        SequentialTest()
        {
            // Define data
            X = KMatrix(4, 2);
            X << 0, 0, 1, 1,
                 0, 1, 1, 0;
        }
};

TEST_F(SequentialTest, TestXOR)
{
    // Initalize variables
    std::vector<ILayer *> layers = {
        new Dense(2, 3), // Input Layer
        new Tanh(),      // Activation
        new Dense(3, 1), // Hidden Layer
        new Tanh()       // Output Layer
    };
    /* std::vector<ILayer *> layers = { */
    /*     new Dense(2, 3), // Input Layer */
    /*     new Dense(3, 1), // Hidden Layer */
    /* }; */
    const ILoss *loss = new MSE();
    const size_t num_epochs = 1;

    // Create the model
    model = new Sequential(layers, loss, num_epochs);

    // Create the XOR target
    KMatrix y(4, 1);
    y << 0, 1, 1, 0;

    // Fit XOR model.
    /* model->fit(X, y); */

    /* KMatrix predictions = model->predict(X); */

    /* std::cout << predictions << std::endl; */
}
