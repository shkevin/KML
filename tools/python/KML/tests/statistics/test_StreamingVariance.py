import unittest

from KML.statistics.StreamingVariance import PyStreamingVariance


class TestStreamingVariance(unittest.TestCase):

    WINDOW_SIZE = 5
    DATA = [10.0] * WINDOW_SIZE
    SV = None

    @classmethod
    def setUpClass(cls):
        cls.SV = PyStreamingVariance(cls.WINDOW_SIZE)

    @classmethod
    def tearDownClass(cls):
        cls.SV = None

    def test_update(self):
        self.SV.update(self.DATA)

    def test_evaluate(self):
        self.SV.update(self.DATA)
        self.assertEqual(self.SV.evaluate(), 0.0)


if __name__ == "__main__":
    unittest.main()
