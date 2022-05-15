import unittest

from KML.statistics.StreamingMean import PyStreamingMean

# import KML.statistics.StreamingMean as StreamingMean
# from KML.statistics.StreamingMean import PyStreamingMean


class TestStreamingMean(unittest.TestCase):

    WINDOW_SIZE = 5
    DATA = [10.0] * WINDOW_SIZE
    SM = None

    @classmethod
    def setUpClass(cls):
        cls.sm = PyStreamingMean(cls.WINDOW_SIZE)

    @classmethod
    def tearDownClass(cls):
        cls.sm = None

    def test_update(self):
        self.sm.update(self.DATA)

    def test_evaluate(self):
        self.sm.update(self.DATA)
        self.assertEqual(self.sm.evaluate(), 10.0)


if __name__ == "__main__":
    unittest.main()
