import unittest

from KML.data_structures.RingBuffer import PyRingBuffer


class TestRingBuffer(unittest.TestCase):

    DATA = [1, 2, 3, 4, 5]
    WINDOW_SIZE = len(DATA)
    RB = None

    def setUp(self):
        self.RB = PyRingBuffer(window_size=self.WINDOW_SIZE)

    def tearDown(self):
        self.RB = None

    def test_update(self):
        self.RB.update(self.DATA)

    def test_empty(self):
        self.assertEqual(self.RB.empty(), True)

    def test_full(self):
        self.RB.update(self.DATA)
        self.assertEqual(self.RB.full(), True)

    def test_size(self):
        self.RB.update(self.DATA)
        self.assertEqual(self.RB.size(), self.WINDOW_SIZE)

    def test_reset(self):
        self.RB.update(self.DATA)
        self.RB.reset()
        self.assertEqual(self.RB.empty(), True)


if __name__ == "__main__":
    unittest.main()
