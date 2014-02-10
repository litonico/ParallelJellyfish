import unittest
from numpy import matrix as npMatrix

from geometry import *

class TestPerspectiveMatrix(unittest.TestCase):
    def setUp(self):
        self.persp_matrix = setPerspectiveMatrix(0.5, 2.0, 45)
        self.point1 = npMatrix([1,1,1,1])
        point2 = npMatrix([2,2,2,1])
        point3 = npMatrix([0.5,1,0.5,1])

    def test_vert_projection(self):
        print project_vert(self.persp_matrix, self.point1)


if __name__ == "__main__":
    unittest.main()