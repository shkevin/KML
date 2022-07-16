import unittest

from KML.data_structures.LinkedList import PyLinkedList


class TestLinkedList(unittest.TestCase):

    DATA = [1, 2, 3, 4, 5]
    WINDOW_SIZE = len(DATA)
    LL = None

    def setUp(self):
        self.LL = PyLinkedList(window_size=self.WINDOW_SIZE)

    def tearDown(self):
        self.LL = None

    def test_update(self):
        self.LL.update(self.DATA)

    # def test_empty(self):
    #     self.assertEqual(self.LL.empty(), True)

    def test_full(self):
        self.LL.update(self.DATA)
        self.assertEqual(self.LL.full(), True)

    def test_size(self):
        self.LL.update(self.DATA)
        self.assertEqual(self.LL.size(), self.WINDOW_SIZE)

    def test_pop(self):
        self.LL.update(self.DATA)
        for i in self.DATA:
            print(i)
            self.assertEqual(i, self.LL.pop())

    def test_reset(self):
        self.LL.update(self.DATA)
        self.LL.reset()
        self.assertEqual(self.LL.empty(), True)


if __name__ == "__main__":
    unittest.main()
