#include "KDNode.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

PYBIND11_MODULE(_kdnode, m) {
    pybind11::class_<KDNode, std::shared_ptr<KDNode>>(m, "KDNode")
        .def(pybind11::init<Point const &, std::size_t, Rectangle const &, std::shared_ptr<KDNode>, std::shared_ptr<KDNode>>())
        .def(pybind11::init<Point const &, std::size_t, std::shared_ptr<KDNode>, std::shared_ptr<KDNode>>())
        .def(pybind11::init<Point const &, std::size_t>())
        .def(pybind11::init<Point const &>())
        .def(pybind11::init<KDNode const &>())
        .def(pybind11::init<>())
        .def("__eq__", &KDNode::operator==)
        .def_property("point", &KDNode::get_point, &KDNode::set_point)
        .def_property("left", &KDNode::get_left, [](KDNode &node, pybind11::args args) {
            if (args.size() == 1) {
                node.set_left(args[0].cast<std::shared_ptr<KDNode>>());
            } else if (args.size() == 2) {
                node.set_left(args[0].cast<std::shared_ptr<KDNode>>(), args[1].cast<Rectangle>());
            } else {
                throw std::runtime_error("Invalid number of arguments");
            }
        })
        .def_property("right", &KDNode::get_right, [](KDNode &node, pybind11::args args) {
            if (args.size() == 1) {
                node.set_right(args[0].cast<std::shared_ptr<KDNode>>());
            } else if (args.size() == 2) {
                node.set_right(args[0].cast<std::shared_ptr<KDNode>>(), args[1].cast<Rectangle>());
            } else {
                throw std::runtime_error("Invalid number of arguments");
            }
        })
        .def_property("axis", &KDNode::get_axis, &KDNode::set_axis)
        .def_property("region", &KDNode::get_region, &KDNode::set_region)
        .def_property_readonly("is_leaf", &KDNode::is_leaf);
}