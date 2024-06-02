import unittest
import pytest
import random
from parameterized import parameterized

from scipy.spatial import KDTree

import sys
sys.path.append('..')

import _kdtree, _point, _rectangle

class KDTreeTest(unittest.TestCase):
    def set_points(self, num_nodes, dim):
        """
        Set and return the list of points
        """
        points = []
        for i in range(num_nodes):
            points.append(_point.Point(dim, [i] * dim))

        return points
    
    def set_random_points(self, num_nodes, dim):
        """
        Set and return the list of random points
        """
        points = []
        for i in range(num_nodes):
            points.append(_point.Point(dim, [random.random() for _ in range(dim)]))

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
    
    def test_build_tree_high_dim(self):
        """
        Build the tree with five points
            - [0, 0, 0], [1, 1, 1], [2, 2, 2], [3, 3, 3], [4, 4, 4]
        """
        num_nodes = 5
        dim = 3
        points = self.set_points(num_nodes, dim)
        tree = _kdtree.KDTree(points, dim)

        self.assertEqual(tree.dimensions, dim)
        self.assertEqual(tree.size, num_nodes)

        self.assertEqual(tree.root.point, points[2])
        self.assertEqual(tree.root.axis, 0)
        for i in range(num_nodes):
            self.assertTrue(tree.root.region.contains(points[i]))

        self.assertEqual(tree.root.left.point, points[1])
        self.assertEqual(tree.root.left.axis, 1)
        self.assertTrue(tree.root.left.region.contains(points[0]))
        self.assertTrue(tree.root.left.region.contains(points[1]))
        self.assertFalse(tree.root.left.region.contains(points[3]))
        self.assertFalse(tree.root.left.region.contains(points[4]))

        self.assertEqual(tree.root.right.point, points[4])
        self.assertEqual(tree.root.right.axis, 1)
        self.assertFalse(tree.root.right.region.contains(points[0]))
        self.assertFalse(tree.root.right.region.contains(points[1]))
        self.assertTrue(tree.root.right.region.contains(points[3]))
        self.assertTrue(tree.root.right.region.contains(points[4]))

        self.assertEqual(tree.root.left.left.point, points[0])
        self.assertEqual(tree.root.left.left.axis, 2)
        self.assertTrue(tree.root.left.left.region.contains(points[0]))
        self.assertFalse(tree.root.left.left.region.contains(points[3]))
        self.assertFalse(tree.root.left.left.region.contains(points[4]))

        self.assertEqual(tree.root.right.left.point, points[3])
        self.assertEqual(tree.root.right.left.axis, 2)
        self.assertFalse(tree.root.right.left.region.contains(points[0]))
        self.assertFalse(tree.root.right.left.region.contains(points[1]))
        self.assertTrue(tree.root.right.left.region.contains(points[3]))
    
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
        self.assertTrue(tree.root.region.contains(points[0]))
        self.assertTrue(tree.root.region.contains(new_point))

        self.assertEqual(tree.root.left.point, points[0])
        self.assertEqual(tree.root.left.axis, 1)
        self.assertFalse(tree.root.left.region.contains(new_point))

        self.assertEqual(tree.root.right.point, new_point)
        self.assertEqual(tree.root.right.axis, 1)
        self.assertFalse(tree.root.right.region.contains(points[0]))

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
        
    @parameterized.expand([
            [10, 2], [20, 3], [30, 4], [40, 5]
    ])
    def test_search_nearest_neighbors_fixed_point(self, num_nodes, dim):
        """
        Search the nearest neighbors from the given points
        compare with scipy.spatial.KDTree
        """
        points = self.set_points(num_nodes, dim)
        tree = _kdtree.KDTree(points, dim)

        query = _point.Point(dim, [1] * dim)
        result = tree.search_nearest_neighbors(query, 3)

        scipy_points = []
        for point in points:
            scipy_points.append(point.coords)

        scipy_tree = KDTree(scipy_points)
        _, scipy_index = scipy_tree.query([query.coords], 3)

        self.assertEqual(len(result), len(scipy_index[0]))

        scipy_result = []
        for index in scipy_index[0]:
            scipy_result.append(points[index])

        result = sorted(result, key=lambda x: x.coords)
        scipy_result = sorted(scipy_result, key=lambda x: x.coords)

        for i in range(len(result)):
            self.assertEqual(result[i], scipy_result[i])

    @parameterized.expand([
            [10, 2, 3], [20, 3, 4], [30, 4, 5], [40, 5, 6]
    ])
    def test_search_nearest_neighbors_random_point(self, num_nodes, dim, k):
        """
        Search the nearest neighbors from the random points
        compare with scipy.spatial.KDTree
        """
        for round in range(1000):
            points = self.set_random_points(num_nodes, dim)
            tree = _kdtree.KDTree(points, dim)

            query = _point.Point(dim, [random.random() for _ in range(dim)])
            result = tree.search_nearest_neighbors(query, k)

            scipy_points = []
            for point in points:
                scipy_points.append(point.coords)

            scipy_tree = KDTree(scipy_points)
            _, scipy_index = scipy_tree.query([query.coords], k)

            self.assertEqual(len(result), len(scipy_index[0]))

            scipy_result = []
            for index in scipy_index[0]:
                scipy_result.append(points[index])

            result = sorted(result, key=lambda x: x.coords)
            scipy_result = sorted(scipy_result, key=lambda x: x.coords)

            for i in range(len(result)):
                self.assertEqual(result[i], scipy_result[i])

    def scipy_range_search(self, points, query_rect):
        """
        Search the points within the given rectangle with scipy.spatial.KDTree.query_ball_point
        """
        scipy_points = []
        for point in points:
            scipy_points.append(point.coords)

        scipy_tree = KDTree(scipy_points)
        min_coords = query_rect.min_corner.coords
        max_coords = query_rect.max_corner.coords

        results = []

        def in_range(point):
            for i in range(len(min_coords)):
                if point[i] < min_coords[i] or point[i] > max_coords[i]:
                    return False
            return True

        for point in scipy_points:
            if in_range(point):
                indices = scipy_tree.query_ball_point(point, 0)
                if len(indices) > 0:
                    results.append(points[indices[0]])

        return results

    def test_range_search(self):
        """
        Test _kdtree.range_search
            - compare with modified scipy.spatial.KDTree.query_ball_point
        """

        num_nodes = 10
        dim = 2
        points = self.set_points(num_nodes, dim)
        tree = _kdtree.KDTree(points, dim)

        min_coords = [0] * dim
        max_coords = [3] * dim
        query_rect = _rectangle.Rectangle(_point.Point(dim, min_coords), _point.Point(dim, max_coords))

        result = tree.range_search(query_rect)

        scipy_result = self.scipy_range_search(points, query_rect)

        result = sorted(result, key=lambda x: x.coords)
        scipy_result = sorted(scipy_result, key=lambda x: x.coords)

        # print the result
        for i in range(len(result)):
            print(result[i].coords, scipy_result[i].coords)

        self.assertEqual(len(result), len(scipy_result))
        for i in range(len(result)):
            self.assertEqual(result[i], scipy_result[i])

    @parameterized.expand([
            [10, 2], [20, 3], [30, 4], [40, 5]
    ])
    def test_range_search_random(self, num_nodes, dim):
        """
        Test _kdtree.range_search with random points
            - compare with modified scipy.spatial.KDTree.query_ball_point
        """
        for round in range(1000):
            points = self.set_random_points(num_nodes, dim)
            tree = _kdtree.KDTree(points, dim)

            min_coords = [random.random() for _ in range(dim)]
            max_coords = [min_coords[i] + random.random() for i in range(dim)]
            query_rect = _rectangle.Rectangle(_point.Point(dim, min_coords), _point.Point(dim, max_coords))

            result = tree.range_search(query_rect)

            scipy_result = self.scipy_range_search(points, query_rect)

            result = sorted(result, key=lambda x: x.coords)
            scipy_result = sorted(scipy_result, key=lambda x: x.coords)

            self.assertEqual(len(result), len(scipy_result))
            for i in range(len(result)):
                self.assertEqual(result[i], scipy_result[i])