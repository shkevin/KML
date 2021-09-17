class BaseClassifier:
    def __init__(self):
        print("Not Implemented")

    def set_params(self, **params):
        return None

    def get_params(self, deep=True):
        return None

    def fit(self, X, y=None):
        pass

    def predict(self, X, y=None):
        pass
