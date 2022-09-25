import unittest

from KML.statistics.summary.StreamingVariance import PyStreamingVariance


class TestStreamingVariance(unittest.TestCase):

    WINDOW_SIZE = 5
    DATA = [10.0] * WINDOW_SIZE
    SV = None

    def setUp(self):
        self.SV = PyStreamingVariance(self.WINDOW_SIZE)

    def tearDown(self):
        self.SV = None

    def test_update(self):
        self.SV.update(self.DATA)

    def test_evaluate(self):
        self.SV.update(self.DATA)
        self.assertEqual(self.SV.evaluate(), 0.0)
