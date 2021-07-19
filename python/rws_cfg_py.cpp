#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "../include/abb_librws/rws_cfg.h"

using namespace pybind11::literals;
namespace py = pybind11;

namespace abb {
namespace rws {
namespace cfg {
namespace moc {

void init_cfg(py::module &m){

    py::class_<Arm>(m, "Arm")
        .def(py::init<const std::string&, double, double>(), "name"_a, "lower_joint_bound"_a, "upper_joint_bound"_a)
    ;

    py::class_<Joint>(m, "Joint")
        .def(py::init<const std::string&, int, int, const std::string&, const std::string&>(), "name"_a, "logical_axis"_a, "kinematic_axis_number"_a, "use_arm"_a, "use_transmission"_a)
    ;
    
    py::class_<MechanicalUnit>(m, "MechanicalUnit")
        .def(py::init<const std::string&, const std::string&, const std::vector<std::string>&>())
    ;

}
} // end namespace rws
} // end namespace abb
