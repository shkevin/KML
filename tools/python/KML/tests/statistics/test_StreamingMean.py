import unittest

from KML.statistics.StreamingMean import PyStreamingMean


class TestStreamingMean(unittest.TestCase):

    WINDOW_SIZE = 5
    DATA = [10.0] * WINDOW_SIZE
    sm = None

    @classmethod
    def setUpClass(cls):
        cls.SM = PyStreamingMean(cls.WINDOW_SIZE)

    @classmethod
    def tearDownClass(cls):
        cls.SM = None

    def test_update(self):
        self.SM.update(self.DATA)

    def test_evaluate(self):
        self.SM.update(self.DATA)
        self.assertEqual(self.SM.evaluate(), 10.0)


if __name__ == "__main__":
    unittest.main()
