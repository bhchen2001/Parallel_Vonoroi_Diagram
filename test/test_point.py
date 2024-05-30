import pytest
import unittest

import sys
sys.path.append('..')

import _point

class PointTest(unittest.TestCase):
    def test_init1(self):
        coords = [1, 2, 3]
        p = _point.Point(len(coords), coords)
        self.assertEqual(p.dim, len(coords))
        for i in range(p.dim):
            self.assertEqual(p[i], coords[i])

    def test_init2(self):
        coords = [1, 2, 3]
        p1 = _point.Point(len(coords), coords)

        p2 = _point.Point(p1)
        self.assertEqual(p1.dim, p2.dim)
        for i in range(p1.dim):
            self.assertEqual(p1[i], p2[i])

    def test_eq(self):
        coords = [1, 2, 3]
        p1 = _point.Point(len(coords), coords)
        p2 = _point.Point(p1)
        self.assertEqual(p1, p2)