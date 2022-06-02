import unittest

from KML.statistics.StreamingP2Quantile import PyStreamingP2Quantile


class TestStreamingP2Quantile(unittest.TestCase):

    DATA = [10.0] * 5
    P2 = None

    def setUp(self):
        self.P2 = PyStreamingP2Quantile(quantile=0.5)

    def tearDown(self):
        self.P2 = None

    def test_zero_evaluate(self):
        self.assertEqual(self.P2.evaluate(), 0.0)

    def test_median_evaluate(self):
        self.P2.update(self.DATA)
        self.assertAlmostEqual(self.P2.evaluate(), 10.0)


if __name__ == "__main__":
    unittest.main()
