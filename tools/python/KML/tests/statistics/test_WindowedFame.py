import unittest

from KML.statistics.WindowedFame import PyWindowedFame


class TestWindowedFame(unittest.TestCase):

    WINDOW_SIZE = 5
    DATA = [10.0] * WINDOW_SIZE
    FM = None

    @classmethod
    def setUpClass(cls):
        cls.FM = PyWindowedFame(0.0, cls.WINDOW_SIZE)

    @classmethod
    def tearDownClass(cls):
        cls.FM = None

    def test_update(self):
        self.FM.update(self.DATA)

    def test_evaluate(self):
        self.FM.update(self.DATA)
        self.assertEqual(self.FM.evaluate(), 10.0)

    def test_drift(self):
        data = [10, 10, 10, 10, 10, 5, 5, 5, 5, 5]
        self.FM.update(data)
        self.assertEqual(self.FM.evaluate(), 5.0)


if __name__ == "__main__":
    unittest.main()
