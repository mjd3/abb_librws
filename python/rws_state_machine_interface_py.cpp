#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "../include/abb_librws/rws_state_machine_interface.h"

using namespace pybind11::literals;
namespace py = pybind11;

namespace abb {
namespace rws {

void init_common(py::module &);
void init_rapid(py::module &);
void init_cfg(py::module &);
void init_interface(py::module &);

using Services = std::decay_t<std::result_of_t<decltype(&RWSStateMachineInterface::services)(RWSStateMachineInterface)>>;
using SG = std::decay_t<std::result_of_t<decltype(&Services::sg)(Services)>>;
using Main = std::decay_t<std::result_of_t<decltype(&Services::main)(Services)>>;
using RAPID = std::decay_t<std::result_of_t<decltype(&Services::rapid)(Services)>>;

PYBIND11_MODULE(abb_librws, m) {
    init_common(m);
    init_rapid(m);
    init_cfg(m);
    init_interface(m);

    py::class_<RWSStateMachineInterface, RWSInterface> sm_iface(m, "RWSStateMachineInterface");

    py::enum_<RWSStateMachineInterface::States>(m, "States")
        .value("IDLE", RWSStateMachineInterface::States::STATE_IDLE)
        .value("INITIALIZE", RWSStateMachineInterface::States::STATE_INITIALIZE)
        .value("RUN_RAPID_ROUTINE", RWSStateMachineInterface::States::STATE_RUN_RAPID_ROUTINE)
        .value("RUN_EGM_ROUTINE", RWSStateMachineInterface::States::STATE_RUN_EGM_ROUTINE)
        .value("UNKNOWN", RWSStateMachineInterface::States::STATE_UNKNOWN)
        .export_values()
    ;

    sm_iface.def(py::init<const std::string &>(), "ip_address"_a = "192.168.125.1")
        .def("services", &RWSStateMachineInterface::services)
    ;

    py::class_<Services>(m, "Services")
        .def("sg", &Services::sg)
        .def("main", &Services::main)
        .def("rapid", &Services::rapid)
    ;

    py::class_<SG>(m, "SmartGripper")
        .def("left_initialize", &SG::leftInitialize)
        .def("left_grip_in", &SG::leftGripIn)
        .def("left_grip_out", &SG::leftGripOut)
        .def("right_initialize", &SG::rightInitialize)
        .def("right_grip_in", &SG::rightGripIn)
        .def("right_grip_out", &SG::rightGripOut)
    ;

    py::class_<Main>(m, "Main")
        .def("get_current_state", &Main::getCurrentState)
        .def("is_state_idle", &Main::isStateIdle)
        .def("is_stationary", &Main::isStationary)
    ;

    py::class_<RAPID>(m, "Rapid")
        .def("run_move_abs_j", &RAPID::runMoveAbsJ)
        .def("run_move_j", &RAPID::runMoveJ)
        .def("run_move_to_calibration_position", &RAPID::runMoveToCalibrationPosition)
        .def("set_move_speed", &RAPID::setMoveSpeed)
    ;

    py::class_<RWSStateMachineInterface::SGSettings, RAPIDRecord>(m, "SGSettings")
        .def(py::init<>())
        .def(py::init(
            [](RAPIDNum& max_speed, RAPIDNum& hold_force, RAPIDNum& physical_limit) {
                RWSStateMachineInterface::SGSettings* sg = new RWSStateMachineInterface::SGSettings();
                sg->max_speed = max_speed;
                sg->hold_force = hold_force;
                sg->physical_limit = physical_limit;
                return sg;
            }),
            "max_speed"_a, "hold_force"_a, "physical_limit"_a
        )
        .def(py::init(
            [](py::array_t<double> arr) {
                auto arr_u = arr.unchecked<1>();
                if (arr_u.size() != 3) {
                    throw std::length_error("Input array is not of length 3!");
                }
                RWSStateMachineInterface::SGSettings* sg = new RWSStateMachineInterface::SGSettings();
                sg->max_speed = arr_u(0);
                sg->hold_force = arr_u(1);
                sg->physical_limit = arr_u(2);
                return sg;
            }),
            "sg_settings"_a
        )
        .def_readwrite("max_speed", &RWSStateMachineInterface::SGSettings::max_speed)
        .def_readwrite("hold_force", &RWSStateMachineInterface::SGSettings::hold_force)
        .def_readwrite("physical_limit", &RWSStateMachineInterface::SGSettings::physical_limit)
    ;

}
} // end namespace rws
} // end namespace abb
