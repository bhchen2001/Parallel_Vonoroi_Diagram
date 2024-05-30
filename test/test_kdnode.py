import pytest
import unittest

import sys
sys.path.append('..')

import _point, _kdnode

class KDNodeTest(unittest.TestCase):
    def set_point(self):
        coords = [1, 2, 3]
        p = _point.Point(len(coords), coords)
        return p
    
    def test_init1(self):
        """
        init(point)
        init(point, axis, left=node1, right=node2)
        """
        p1 = self.set_point()
        p2 = self.set_point()
        p3 = self.set_point()

        n1 = _kdnode.KDNode(p1)
        self.assertEqual(n1.point, p1)
        self.assertEqual(n1.point.dim, p1.dim)
        self.assertEqual(n1.left, None)
        self.assertEqual(n1.right, None)

        n2 = _kdnode.KDNode(p2)
        self.assertEqual(n2.point, p2)
        self.assertEqual(n2.point.dim, p2.dim)
        self.assertEqual(n2.left, None)
        self.assertEqual(n2.right, None)

        n3 = _kdnode.KDNode(p3, 1, n1, n2)
        self.assertEqual(n3.point, p3)
        self.assertEqual(n3.point.dim, p3.dim)
        self.assertEqual(n3.axis, 1)
        self.assertEqual(n3.left, n1)
        self.assertEqual(n3.right, n2)

    def test_init2(self):
        """
        init(point, axis)
        init(node)
        """

        p1 = self.set_point()

        n1 = _kdnode.KDNode(p1, 1)
        self.assertEqual(n1.point, p1)
        self.assertEqual(n1.point.dim, p1.dim)
        self.assertEqual(n1.axis, 1)
        self.assertEqual(n1.left, None)
        self.assertEqual(n1.right, None)

        n2 = _kdnode.KDNode(n1)
        self.assertEqual(n2.point, p1)
        self.assertEqual(n2.point.dim, p1.dim)
        self.assertEqual(n2.axis, 1)
        self.assertEqual(n2.left, None)
        self.assertEqual(n2.right, None)

    def test_eq(self):
        p1 = self.set_point()
        p2 = self.set_point()
        p3 = self.set_point()

        n1 = _kdnode.KDNode(p1, 1)
        n2 = _kdnode.KDNode(p2, 1)
        n3 = _kdnode.KDNode(p3, 2)

        self.assertEqual(n1, n2)
        self.assertNotEqual(n1, n3)
        self.assertNotEqual(n2, n3)