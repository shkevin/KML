import math
import unittest

from KML.statistics.summary.StreamingEntropy import PyStreamingEntropy


class TestStreamingEntropy(unittest.TestCase):

    WINDOW_SIZE = 10
    NUM_BINS = 10
    SE = None

    def setUp(self):
        self.SE = PyStreamingEntropy(self.WINDOW_SIZE, self.NUM_BINS)

    def tearDown(self):
        self.SE = None

    def test_empty_evaluate(self):
        self.assertEqual(self.SE.evaluate(), 0.0)

    def test_uniform_entropy_with_decrement(self):
        data = list(range(1, 12))
        self.SE.update(data)
        self.assertAlmostEqual(math.log(self.NUM_BINS, 2), self.SE.evaluate())

    def test_uniform_entropy_without_decrement(self):
        data = list(range(1, 6))
        self.SE.update(data)
        self.assertAlmostEqual(math.log(5, 2), self.SE.evaluate())

    def test_uniform_entropy_double_bins(self):
        data = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5]
        self.SE.update(data)
        self.assertAlmostEqual(math.log(5, 2), self.SE.evaluate())
