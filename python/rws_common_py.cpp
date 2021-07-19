#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "../include/abb_librws/rws_common.h"

using namespace pybind11::literals;
namespace py = pybind11;

namespace abb {
namespace rws {

void init_common(py::module &m){

    py::class_<TriBool> tribool(m, "TriBool");
    py::enum_<TriBool::Values>(tribool, "Values")
        .value("UNKNOWN", TriBool::Values::UNKNOWN_VALUE)
        .value("FALSE", TriBool::Values::FALSE_VALUE)
        .value("TRUE", TriBool::Values::TRUE_VALUE)
        .export_values();

    tribool.def(py::init<const TriBool::Values>(), "value"_a = TriBool::Values::UNKNOWN_VALUE)
        .def("is_true", &TriBool::isTrue)
        .def("is_false", &TriBool::isFalse)
        .def("is_unknown", &TriBool::isUnknown)
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("__repr__", &TriBool::toString);

}
} // end namespace rws
} // end namespace abb
