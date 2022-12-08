import unittest

from kml.metrics.StreamingMAD import PyStreamingMAD


class TestStreamingMAD(unittest.TestCase):

    DATA = list(range(1, 11))
    WINDOW_SIZE = len(DATA)
    MAD = None

    def setUp(self):
        self.MAD = PyStreamingMAD()

    def tearDown(self):
        self.MAD = None

    def test_update(self):
        self.MAD.update(self.DATA)

    def test_empty_evaluate(self):
        self.assertEqual(self.MAD.evaluate(), 0.0)
