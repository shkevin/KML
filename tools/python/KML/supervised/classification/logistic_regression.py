from utils import gradient_descent, sigmoid
from base_classifier import BaseClassifier
from scipy.sparse import hstack
import numpy as np


class LogisticRegression(BaseClassifier):
    def __init__(self, alpha=0.01, C=1.0, max_iter=100, tol=1e-4):
        self.alpha = alpha
        self.C = C
        self.max_iter = max_iter
        self.tol = tol

    def fit(self, X, y=None):
        return self

    def predict(self, X, y=None):
        theta = gradient_descent(X, y, self.alpha, self.C, self.max_iter)
        X = hstack((np.ones(X.shape[0])[:, None], X)).tocsr()
        y_hat = sigmoid(theta.dot(X.T)).argmax(axis=0).tolist()[0]
        return np.add(y_hat, 1)

    def fit_predict(self, X, y=None):
        return self.fit(X, y).self.predict(X, y)
