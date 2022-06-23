import unittest

from KML.DataStructures.RingBuffer import PyRingBuffer


class TestRingBuffer(unittest.TestCase):

    DATA = list(range(1, 11))
    WINDOW_SIZE = len(DATA)
    RB = None

    # def setUp(self):
    #     self.RB = PyRingBuffer[float](window_size=self.WINDOW_SIZE)

    # def tearDown(self):
    #     self.RB = None


if __name__ == "__main__":
    unittest.main()
