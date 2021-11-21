from scipy.sparse import hstack, csr_matrix
import numpy as np


def gradient_descent(X: list, y: list, alpha: float, _lambda: float, iterations: int):
    """Gradient descent algorithm for logistic regression.
    This will compute the weights needed in order to calculate
    the predicted classes y_hat.

    Args:
        X (list): Training examples.
        y (list): Example classes.
        alpha (float): Learning rate for gradient descent.
        _labmda (float): Penalty term for regularization.
        iterations (int): Number of iterations to run gradient descent.

    Returns:
        theta (list): Learned weights.
    """
    X = hstack((np.ones(X.shape[0])[:, None], X)).tocsr()
    # X = feature_normalize(X)
    history = np.zeros(iterations + 1)
    unique_classes = np.unique(y)
    theta = csr_matrix(np.zeros((len(unique_classes), X.shape[1]), dtype=np.float16))
    Y = delta_y(y, unique_classes)

    # compute cost doesn't work yet.
    history[0] = compute_cost(X, Y, theta)
    for i in range(iterations):
        h = sigmoid(theta.dot(X.T))
        # h = feature_normalize(h)
        gradient = ((h - Y) * X) + (_lambda * theta)
        theta -= alpha * gradient
        history[i] = compute_cost(X, Y, theta)

    return theta, history


def compute_cost(X, y, theta):
    return 0


def delta_y(y: list, unique_classes: list) -> list:
    """Create the dirac delta matrix of unique classes in y.
    Args:
        y (list): Training example classes.
        unique_classes (list): unique classes in training examples.
    Returns:
        Dirac Delta of unique classes.
    """
    output = np.zeros((len(unique_classes), y.shape[0]), dtype=np.float16)
    for c in unique_classes:
        output[c - 1, :] = np.where(y == c, 1.0, 0.0).transpose()
    return csr_matrix(output)


def sigmoid(z):
    return z.expm1()
