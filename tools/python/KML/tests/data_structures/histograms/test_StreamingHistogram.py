import unittest

from KML.data_structures.histograms.StreamingHistogram import \
    PyStreamingHistogram


class TestStreamingHistogram(unittest.TestCase):

    DATA = list(range(1, 11))
    NUM_BINS = 5
    WINDOW_SIZE = 5
    SH = None

    def setUp(self):
        self.SH = PyStreamingHistogram(
            num_bins=self.NUM_BINS, window_size=self.WINDOW_SIZE
        )

    def tearDown(self):
        self.SH = None

    def test_update(self):
        self.SH.update(self.DATA)

    def test_counts(self):
        self.SH.update(self.DATA)
        counts = self.SH.bin_counts()

        for c in counts:
            self.assertEqual(1, c)

    def test_pdf(self):
        self.SH.update(self.DATA)
        pdf = self.SH.pdf()
        even_bin_width = 1 / self.NUM_BINS

        for p in pdf:
            self.assertEqual(p, even_bin_width)

    def test_cdf(self):
        self.SH.update(self.DATA)
        cdf = self.SH.cdf()
        even_bin_width = 1 / self.NUM_BINS

        for i, c in enumerate(cdf):
            self.assertEqual(c, (i + 1) * even_bin_width)

    def test_windowed_quantile(self):
        self.SH.update(self.DATA)
        q = self.SH.quantile(0.8)
        self.assertEqual(q, 9.2)

    def test_empty(self):
        self.assertEqual(self.SH.empty(), True)

    def test_full(self):
        self.SH.update(self.DATA)
        self.assertEqual(self.SH.full(), True)

    def test_size(self):
        self.SH.update(self.DATA)
        self.assertEqual(self.SH.size(), self.WINDOW_SIZE)

    def test_reset(self):
        self.SH.update(self.DATA)
        self.SH.reset()
        self.assertEqual(self.SH.empty(), True)
