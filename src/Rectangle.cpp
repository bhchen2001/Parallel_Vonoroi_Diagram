#include "Rectangle.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

PYBIND11_MODULE(_rectangle, m) {
    pybind11::class_<Rectangle>(m, "Rectangle")
        .def(pybind11::init([](const Point &min_corner, const Point &max_corner) {
            try {
                return Rectangle(min_corner, max_corner);
            } catch (const std::invalid_argument &e) {
                throw pybind11::value_error(e.what());
            }
        }))
        // .def(pybind11::init<Point const &, Point const &>())
        .def(pybind11::init<Rectangle const &>())
        .def(pybind11::init<>())
        .def("__eq__", &Rectangle::operator==)
        .def_property_readonly("dim", &Rectangle::get_dim)
        .def_property_readonly("min_corner", &Rectangle::get_min_corner)
        .def_property_readonly("max_corner", &Rectangle::get_max_corner)
        .def("contains", &Rectangle::contains);
}