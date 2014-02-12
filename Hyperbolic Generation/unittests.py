import unittest
from generation_pseudocode import *

class TestGeneration(unittest.TestCase):

    def setUp(self):
        self.initial_vertlist = generate_vertlist(0)

    def test_vertlist_generation(self):
        #null list test
        
        self.assertEqual(self.initial_vertlist, ([],[]))

        self.initial_vertlist = generate_vertlist(5)
        self.assertEqual(len(self.initial_vertlist[0]), 5)
        self.assertEqual(len(self.initial_vertlist[0]), (len(self.initial_vertlist[1]) + 1))
        
    def test_make_hyperbolic(self):
        self.trivial_hyperbolic = make_hyperbolic(5, [0])
        self.assertEqual(len(self.trivial_hyperbolic[0]), 10)        

if __name__ == "__main__":
    unittest.main()