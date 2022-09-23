import unittest

from KML.statistics.summary.StreamingP2Quantile import PyStreamingP2Quantile


class TestStreamingP2Quantile(unittest.TestCase):

    DATA = list(range(1, 11))
    P2 = None

    def setUp(self):
        self.P2 = PyStreamingP2Quantile(quantile=0.5)

    def tearDown(self):
        self.P2 = None

    def test_zero_evaluate(self):
        self.assertEqual(self.P2.evaluate(), 0.0)

    def test_median_evaluate(self):
        self.P2.update(self.DATA)
        self.assertAlmostEqual(self.P2.evaluate(), 5.0)

    def test_q1(self):
        self.P2 = PyStreamingP2Quantile(quantile=0.25)
        self.P2.update(self.DATA)
        self.assertAlmostEqual(self.P2.evaluate(), 3.0)

    def test_q3(self):
        self.P2 = PyStreamingP2Quantile(quantile=0.75)
        self.P2.update(self.DATA)
        self.assertAlmostEqual(self.P2.evaluate(), 7.0)
