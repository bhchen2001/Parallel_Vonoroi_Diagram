#include "KDTree.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

Rectangle KDTree::get_initial_region(size_t dim){

    Point min_corner(dim, std::vector<double>(dim, 0));
    Point max_corner(dim, std::vector<double>(dim, std::numeric_limits<double>::max()));

    return Rectangle(min_corner, max_corner);
}

std::shared_ptr<KDNode> KDTree::build_kd_tree(std::vector<Point> &points, size_t depth, const Rectangle &region){
    if(points.size() == 0){
        return nullptr;
    }

    size_t axis = depth % dimensions;
    size_t median = points.size() / 2;

    std::sort(points.begin(), points.end(), [axis](Point &a, Point &b){
        return a[axis] < b[axis];
    });

    Point median_point = points[median];
    std::shared_ptr<KDNode> node = std::make_shared<KDNode>(median_point, axis, region);

    std::vector<Point> left_points(points.begin(), points.begin() + median);
    Rectangle left_region = region.left_half(axis, median_point[axis]);

    std::vector<Point> right_points(points.begin() + median + 1, points.end());
    Rectangle right_region = region.right_half(axis, median_point[axis]);

    node->set_left(build_kd_tree(left_points, depth + 1, left_region));
    node->set_right(build_kd_tree(right_points, depth + 1, right_region));

    return node;
}

void KDTree::insert_node(Point point){
    std::shared_ptr<KDNode> current = root;
    size_t depth = 0;

    while(true){
        size_t axis = depth % dimensions;

        if(current == nullptr){
            root = std::make_shared<KDNode>(point, axis, get_initial_region(dimensions));
            break;
        }
        if(point[axis] < current->get_point()[axis]){
            if(current->get_left() == nullptr){
                Rectangle region = current->get_region().left_half(axis, current->get_point()[axis]);
                current->set_left(std::make_shared<KDNode>(point, (axis + 1) % dimensions), region);
                break;
            }
            else{
                current = current->get_left();
            }
        }
        else{
            if(current->get_right() == nullptr){
                Rectangle region = current->get_region().right_half(axis, current->get_point()[axis]);
                current->set_right(std::make_shared<KDNode>(point, (axis + 1) % dimensions), region);
                break;
            }
            else{
                current = current->get_right();
            }
        }

        depth++;
    }
}

bool KDTree::delete_node(Point point){
    std::shared_ptr<KDNode> current = root;
    std::shared_ptr<KDNode> parent = nullptr;
    size_t depth = 0;
    bool found = false;

    while(current != nullptr){
        size_t axis = depth % dimensions;

        if(current->get_point() == point){
            found = true;
            if(current->get_left() == nullptr && current->get_right() == nullptr){
                if(parent == nullptr){
                    root = nullptr;
                }
                else{
                    if(parent->get_left() == current){
                        parent->set_left(nullptr);
                    }
                    else{
                        parent->set_right(nullptr);
                    }
                }
                break;
            }
            else{
                std::shared_ptr<KDNode> successor = current->get_right();
                std::shared_ptr<KDNode> successor_parent = current;

                while(successor->get_left() != nullptr){
                    successor_parent = successor;
                    successor = successor->get_left();
                }

                current->set_point(successor->get_point());
                if(successor_parent->get_left() == successor){
                    successor_parent->set_left(successor->get_right());
                }
                else{
                    successor_parent->set_right(successor->get_right());
                }
                break;
            }
        }

        parent = current;
        if(point[axis] < current->get_point()[axis]){
            current = current->get_left();
        }
        else{
            current = current->get_right();
        }

        depth++;
    }
    return found;
}

std::vector<Point> KDTree::search_nearest_neighbors(Point point, size_t k){
    BoundedPriorityQueue bpq(k);
    search_nearest_neighbors_recursive(point, root, bpq, k);
    return bpq.get_points();
}

void KDTree::search_nearest_neighbors_recursive(Point query_point, std::shared_ptr<KDNode> current, BoundedPriorityQueue &bpq, size_t k){
    if(current == nullptr){
        return;
    }

    size_t axis = current->get_axis();
    double distance = point_distance(query_point, current->get_point());
    double diff = fabs(query_point[axis] - current->get_point()[axis]);

    bpq.push(distance, current->get_point());

    if(query_point[axis] < current->get_point()[axis]){
        search_nearest_neighbors_recursive(query_point, current->get_left(), bpq, k);
        if(bpq.get_size() < k || diff < bpq.max_priority()){
            search_nearest_neighbors_recursive(query_point, current->get_right(), bpq, k);
        }
    }
    else{
        search_nearest_neighbors_recursive(query_point, current->get_right(), bpq, k);
        if(bpq.get_size() < k || diff < bpq.max_priority()){
            search_nearest_neighbors_recursive(query_point, current->get_left(), bpq, k);
        }
    }
}

std::vector<Point> KDTree::range_search(Rectangle &range){
    std::vector<Point> points;
    range_search_recursive(range, root, points);
    return points;
}

void KDTree::range_search_recursive(Rectangle &range, std::shared_ptr<KDNode> current, std::vector<Point> &points){
    if(current == nullptr){
        return;
    }

    if(current->is_leaf()){
        if(range.contains(current->get_point())){
            points.push_back(current->get_point());
        }
        return;
    }
    else{
        if(range.contains(current->get_point())){
            points.push_back(current->get_point());
        }
        if(intersects(range, current->get_region())){
            range_search_recursive(range, current->get_left(), points);
            range_search_recursive(range, current->get_right(), points);
        }
        return;
    }
}

PYBIND11_MODULE(_kdtree, m) {
    pybind11::class_<KDTree>(m, "KDTree")
        .def(pybind11::init<std::vector<Point> &, size_t>())
        .def("insert_node", &KDTree::insert_node)
        .def("delete_node", &KDTree::delete_node)
        .def("search_nearest_neighbors", &KDTree::search_nearest_neighbors)
        .def("range_search", &KDTree::range_search)
        .def_property_readonly("size", &KDTree::get_size)
        .def_property_readonly("root", &KDTree::get_root)
        .def_property_readonly("dimensions", &KDTree::get_dimensions)
        .def_property_readonly("depth", &KDTree::get_depth);
}