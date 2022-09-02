import unittest

from KML.statistics.summary.WindowedFAME import PyWindowedFAME


class TestWindowedFAME(unittest.TestCase):

    WINDOW_SIZE = 5
    DATA = [10.0] * WINDOW_SIZE
    FM = None

    def setUp(self):
        self.FM = PyWindowedFAME()

    def tearDown(self):
        self.FM = None

    def test_update(self):
        self.FM.update(self.DATA)

    def test_constant_median(self):
        self.FM.update(self.DATA)
        self.assertEqual(self.FM.evaluate(), 10.0)
