import unittest

from KML.statistics.summary.StreamingIQR import PyStreamingIQR


class TestStreamingIQR(unittest.TestCase):

    DATA = list(range(1, 11))
    WINDOW_SIZE = len(DATA)
    IQR = None

    def setUp(self):
        self.IQR = PyStreamingIQR(window_size=self.WINDOW_SIZE)

    def tearDown(self):
        self.IQR = None

    def test_update(self):
        self.IQR.update(self.DATA)

    def test_empty_evaluate(self):
        self.assertEqual(self.IQR.evaluate(), 0.0)

    def test_simple_iqr(self):
        self.IQR.update(self.DATA)
        self.assertEqual(self.IQR.evaluate(), 4.0)


if __name__ == "__main__":
    unittest.main()
