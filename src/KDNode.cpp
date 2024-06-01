#include "KDNode.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

PYBIND11_MODULE(_kdnode, m) {
    pybind11::class_<KDNode, std::shared_ptr<KDNode>>(m, "KDNode")
        .def(pybind11::init<Point const &, std::size_t, std::shared_ptr<KDNode>, std::shared_ptr<KDNode>>())
        .def(pybind11::init<Point const &, std::size_t>())
        .def(pybind11::init<Point const &>())
        .def(pybind11::init<KDNode const &>())
        .def(pybind11::init<>())
        .def("__eq__", &KDNode::operator==)
        .def_property("point", &KDNode::get_point, &KDNode::set_point)
        .def_property("left", &KDNode::get_left, &KDNode::set_left)
        .def_property("right", &KDNode::get_right, &KDNode::set_right)
        .def_property("axis", &KDNode::get_axis, &KDNode::set_axis)
        .def_property_readonly("is_leaf", &KDNode::is_leaf);
}