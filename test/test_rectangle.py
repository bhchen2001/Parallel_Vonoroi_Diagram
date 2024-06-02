import unittest

import sys
sys.path.append('..')

import _rectangle, _point

class RectangleTest(unittest.TestCase):
    def set_coords(self, dim):
        """
        Set and return the list of coordinates
        """
        min_coords = []
        max_coords = []
        for i in range(dim):
            min_coords.append(i)
            max_coords.append(i + 1)
        
        return min_coords, max_coords
    
    def test_init1(self):
        dim = 3
        min_coords, max_coords = self.set_coords(dim)
        min_point = _point.Point(dim, min_coords)
        max_point = _point.Point(dim, max_coords)

        r = _rectangle.Rectangle(min_point, max_point)
        self.assertEqual(r.dim, dim)
        self.assertEqual(r.min_corner, min_point)
        self.assertEqual(r.max_corner, max_point)

    def test_init2(self):
        dim = 3
        min_coords, max_coords = self.set_coords(dim)
        min_point = _point.Point(dim, min_coords)
        max_point = _point.Point(dim, max_coords)

        r1 = _rectangle.Rectangle(min_point, max_point)
        r2 = _rectangle.Rectangle(r1)
        self.assertEqual(r1.dim, r2.dim)
        self.assertEqual(r1.min_corner, r2.min_corner)
        self.assertEqual(r1.max_corner, r2.max_corner)

    def test_invalid_init(self):
        dim1, dim2 = 2, 4
        min_coords_dim_1, max_coords_dim_1 = self.set_coords(dim1)
        min_coords_dim_2, max_coords_dim_2 = self.set_coords(dim2)
        min_point_dim_1, max_point_dim_1 = _point.Point(dim1, min_coords_dim_1), _point.Point(dim1, max_coords_dim_1)
        min_point_dim_2, max_point_dim_2 = _point.Point(dim2, min_coords_dim_2), _point.Point(dim2, max_coords_dim_2)

        with self.assertRaises(ValueError):
            _rectangle.Rectangle(max_point_dim_1, min_point_dim_1)
        with self.assertRaises(ValueError):
            _rectangle.Rectangle(min_point_dim_1, max_point_dim_2)

    def test_contains(self):
        dim = 3
        min_coords, max_coords = self.set_coords(dim)
        min_point = _point.Point(dim, min_coords)
        max_point = _point.Point(dim, max_coords)

        r = _rectangle.Rectangle(min_point, max_point)
        self.assertTrue(r.contains(min_point))
        self.assertTrue(r.contains(max_point))
        self.assertTrue(r.contains(_point.Point(dim, [i + 0.5 for i in range(dim)])))
        self.assertFalse(r.contains(_point.Point(dim, [i + 1.5 for i in range(dim)])))
        self.assertFalse(r.contains(_point.Point(dim, [i - 0.5 for i in range(dim)])))