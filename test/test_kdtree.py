import unittest
import pytest

import sys
sys.path.append('..')

import _kdtree, _point

class KDTreeTest(unittest.TestCase):
    def set_points(self, num_nodes, dim):
        """
        Set and return the list of points
        """
        points = []
        for i in range(num_nodes):
            points.append(_point.Point(dim, [i] * dim))

        return points
    
    """
    Traverse the tree and check if the node's information is correct
        - dim
        - point
        - axis
    """
    def traverse(self, node, axis, dim, points):
        if node is None:
            return
        self.assertEqual(node.point.dim, dim)
        self.assertIn(node.point, points)
        self.assertEqual(node.axis, axis)
        self.traverse(node.left, (axis + 1) % dim, dim, points)
        self.traverse(node.right, (axis + 1) % dim, dim, points)
    
    def test_build_tree_three_nodes(self):
        """
        Build the tree with three nodes
            - [0, 0], [1, 1], [2, 2]
        Test the following info
            - tree's dimensions
            - tree's size
            - each nodes' point and dimension
        """
        num_nodes = 3
        dim = 2
        points = self.set_points(num_nodes, dim)
        tree = _kdtree.KDTree(points, dim)

        self.assertEqual(tree.dimensions, dim)
        self.assertEqual(tree.size, num_nodes)

        self.assertEqual(tree.root.point, points[1])
        self.assertEqual(tree.root.axis, 0)
        self.assertEqual(tree.root.left.point, points[0])
        self.assertEqual(tree.root.left.axis, 1)
        self.assertEqual(tree.root.right.point, points[2])
        self.assertEqual(tree.root.right.axis, 1)
    
    def test_build_tree_multiple_nodes(self):
        """
        Build the tree with given points and dims
        """
        num_nodes = 10
        dim = 2
        points = self.set_points(num_nodes, dim)
        tree = _kdtree.KDTree(points, dim)

        self.assertEqual(tree.dimensions, dim)
        self.assertEqual(tree.size, num_nodes)

        self.traverse(tree.root, 0, dim, points)

    def test_insert_node_empty_tree(self):
        """
        Insert a new node to the empty tree
        """
        dim = 2
        tree = _kdtree.KDTree([], dim)

        new_point = _point.Point(dim, [3] * dim)
        tree.insert_node(new_point)

        self.assertEqual(tree.size, 1)
        self.assertEqual(tree.root.point, new_point)
        self.assertEqual(tree.root.axis, 0)
        self.assertEqual(tree.root.left, None)
        self.assertEqual(tree.root.right, None)

    def test_insert_node_built_tree(self):
        """
        Insert a new node to the built tree
        """
        num_nodes = 2
        dim = 2
        points = self.set_points(num_nodes, dim)
        tree = _kdtree.KDTree(points, dim)

        new_point = _point.Point(dim, [num_nodes + 1] * dim)
        tree.insert_node(new_point)

        self.assertEqual(tree.size, num_nodes + 1)

        self.assertEqual(tree.root.point, points[1])
        self.assertEqual(tree.root.axis, 0)
        self.assertEqual(tree.root.left.point, points[0])
        self.assertEqual(tree.root.left.axis, 1)
        self.assertEqual(tree.root.right.point, new_point)
        self.assertEqual(tree.root.right.axis, 1)

    def test_insert_multiple_nodes(self):
        """
        Insert multiple nodes to the tree
        """
        num_nodes = 10
        dim = 2
        points = self.set_points(num_nodes, dim)
        tree = _kdtree.KDTree([], dim)

        for point in points:
            tree.insert_node(point)

        self.assertEqual(tree.size, num_nodes)

        self.traverse(tree.root, 0, dim, points)

    def test_delete_node_built(self):
        """
        Delete a node from the built tree
        """
        num_nodes = 3
        dim = 2
        points = self.set_points(num_nodes, dim)
        tree = _kdtree.KDTree(points, dim)

        result = tree.delete_node(points[1])
        self.assertTrue(result)

        self.assertEqual(tree.size, num_nodes - 1)

        self.assertEqual(tree.root.point, points[2])
        self.assertEqual(tree.root.axis, 0)
        self.assertEqual(tree.root.left.point, points[0])
        self.assertEqual(tree.root.left.axis, 1)
        self.assertEqual(tree.root.right, None)

        result = tree.delete_node(points[0])
        self.assertTrue(result)

        self.assertEqual(tree.size, num_nodes - 2)
        self.assertEqual(tree.depth, 1)

        self.assertEqual(tree.root.point, points[2])
        self.assertEqual(tree.root.axis, 0)
        self.assertEqual(tree.root.left, None)
        self.assertEqual(tree.root.right, None)

    def test_delete_all_node(self):
        """
        Delete all nodes from the tree
        """
        num_nodes = 10
        dim = 2
        points = self.set_points(num_nodes, dim)
        tree = _kdtree.KDTree(points, dim)

        for i in range(num_nodes):
            result = tree.delete_node(points[i])
            self.assertTrue(result)

            self.assertEqual(tree.size, num_nodes - i - 1)

        self.assertEqual(tree.size, 0)
        self.assertEqual(tree.depth, 0)
        self.assertEqual(tree.root, None)

    def test_delete_node_invalid(self):
        """
        Delete a node that is not in the tree
        """
        num_nodes = 3
        dim = 2
        points = self.set_points(num_nodes, dim)
        tree = _kdtree.KDTree(points, dim)

        new_point = _point.Point(dim, [3] * dim)
        result = tree.delete_node(new_point)
        self.assertFalse(result)

        self.assertEqual(tree.size, num_nodes)