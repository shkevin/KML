import unittest

from KML.statistics.WindowedP2Quantile import PyWindowedP2Quantile


class TestWindowedP2Quantile(unittest.TestCase):

    WINDOW_SIZE = 10
    DATA = [10.0] * 300
    WP2 = None

    @classmethod
    def setUpClass(cls):
        cls.WP2 = PyWindowedP2Quantile(quantile=0.5, window_size=cls.WINDOW_SIZE)

    @classmethod
    def tearDownClass(cls):
        cls.WP2 = None

    # def test_zero_evaluate(self):
    #     self.assertEqual(self.WP2.evaluate(), 0.0)

    # def test_median_evaluate(self):
    #     self.WP2.update(self.DATA)
    #     self.assertEqual(self.WP2.evaluate(), 10.0)


if __name__ == "__main__":
    unittest.main()
