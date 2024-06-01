#include "Point.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

PYBIND11_MODULE(_point, m) {
    pybind11::class_<Point>(m, "Point")
        .def(pybind11::init<size_t, std::vector<double> const &>())
        .def(pybind11::init<Point const &>())
        .def(pybind11::init<>())
        .def("__getitem__", [](Point &p, size_t i) { return p[i]; })
        .def("__eq__", &Point::operator==)
        .def_property_readonly("dim", &Point::get_dim)
        .def_property_readonly("coords", &Point::get_coords);
    m.def("point_distance", &point_distance);
}