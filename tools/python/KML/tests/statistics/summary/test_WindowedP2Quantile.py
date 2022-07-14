import unittest

from KML.statistics.summary.WindowedP2Quantile import PyWindowedP2Quantile


class TestWindowedP2Quantile(unittest.TestCase):

    WINDOW_SIZE = 10
    DATA = [10.0] * 300
    WP2 = None

    def setUp(self):
        self.WP2 = PyWindowedP2Quantile(quantile=0.5, window_size=self.WINDOW_SIZE)

    def tearDown(self):
        self.WP2 = None

    def test_zero_evaluate(self):
        self.assertEqual(self.WP2.evaluate(), 0.0)

    def test_median_evaluate(self):
        self.WP2.update(self.DATA)
        self.assertEqual(self.WP2.evaluate(), 10.0)


if __name__ == "__main__":
    unittest.main()
