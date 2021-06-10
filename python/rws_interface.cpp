#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include "../include/abb_librws/rws_interface.h"
#include "../include/abb_librws/rws_common.h"

namespace py = pybind11;

namespace abb {
namespace rws {

PYBIND11_MODULE(abb_librws, m) {
 
    py::class_<RWSInterface> iface(m, "RWSInterface");
    
    py::enum_<RWSInterface::RAPIDTaskExecutionState>(m, "RAPIDTaskExecutionState")
        .value("UNKNOWN", RWSInterface::RAPIDTaskExecutionState::UNKNOWN)
        .value("READY", RWSInterface::RAPIDTaskExecutionState::READY)
        .value("STOPPED", RWSInterface::RAPIDTaskExecutionState::STOPPED)
        .value("STARTED", RWSInterface::RAPIDTaskExecutionState::STARTED)
        .value("UNINITIALIZED", RWSInterface::RAPIDTaskExecutionState::UNINITIALIZED)
        .export_values();

    py::enum_<RWSInterface::MechanicalUnitType>(m, "MechanicalUnitType")
        .value("NONE", RWSInterface::MechanicalUnitType::NONE)
        .value("TCP_ROBOT", RWSInterface::MechanicalUnitType::TCP_ROBOT)
        .value("ROBOT", RWSInterface::MechanicalUnitType::ROBOT)
        .value("SINGLE", RWSInterface::MechanicalUnitType::SINGLE)
        .value("UNDEFINED", RWSInterface::MechanicalUnitType::UNDEFINED)
        .export_values();
    
    py::enum_<RWSInterface::MechanicalUnitMode>(m, "MechanicalUnitMode")
        .value("UNKNOWN_MODE", RWSInterface::MechanicalUnitMode::UNKNOWN_MODE)
        .value("ACTIVATED", RWSInterface::MechanicalUnitMode::ACTIVATED)
        .value("DEACTIVATED", RWSInterface::MechanicalUnitMode::DEACTIVATED)
        .export_values();

    py::class_<RWSInterface::MechanicalUnitStaticInfo>(m, "MechanicalUnitStaticInfo")
        .def(py::init<>())
        .def_readonly("type", &RWSInterface::MechanicalUnitStaticInfo::type)
        .def_readonly("task_name", &RWSInterface::MechanicalUnitStaticInfo::task_name)
        .def_readonly("axes", &RWSInterface::MechanicalUnitStaticInfo::axes)
        .def_readonly("axes_total", &RWSInterface::MechanicalUnitStaticInfo::axes_total)
        .def_readonly("is_integrated_unit", &RWSInterface::MechanicalUnitStaticInfo::is_integrated_unit)
        .def_readonly("has_integrated_unit", &RWSInterface::MechanicalUnitStaticInfo::has_integrated_unit);

    py::class_<RWSInterface::MechanicalUnitDynamicInfo>(m, "MechanicalUnitDynamicInfo")
        .def(py::init<>())
        .def_readonly("tool_name", &RWSInterface::MechanicalUnitDynamicInfo::tool_name)
        .def_readonly("wobj_name", &RWSInterface::MechanicalUnitDynamicInfo::wobj_name)
        .def_readonly("payload_name", &RWSInterface::MechanicalUnitDynamicInfo::payload_name)
        .def_readonly("total_payload_name", &RWSInterface::MechanicalUnitDynamicInfo::total_payload_name)
        .def_readonly("status", &RWSInterface::MechanicalUnitDynamicInfo::status)
        .def_readonly("mode", &RWSInterface::MechanicalUnitDynamicInfo::mode)
        .def_readonly("jog_mode", &RWSInterface::MechanicalUnitDynamicInfo::jog_mode);

    py::class_<RWSInterface::SystemInfo>(m, "SystemInfo")
        .def(py::init<>())
        .def_readonly("robot_ware_version", &RWSInterface::SystemInfo::robot_ware_version)
        .def_readonly("system_name", &RWSInterface::SystemInfo::system_name)
        .def_readonly("system_type", &RWSInterface::SystemInfo::system_type)
        .def_readonly("system_options", &RWSInterface::SystemInfo::system_options);
    
    py::class_<RWSInterface::RuntimeInfo>(m, "RuntimeInfo")
        .def(py::init<>())
        .def_readonly("auto_mode", &RWSInterface::RuntimeInfo::auto_mode)
        .def_readonly("motors_on", &RWSInterface::RuntimeInfo::motors_on)
        .def_readonly("rapid_running", &RWSInterface::RuntimeInfo::rapid_running)
        .def_readonly("rws_connected", &RWSInterface::RuntimeInfo::rws_connected);
    
    
    iface.def(py::init<const std::string &>(), py::arg("ip_address"))
        .def("collect_runtime_info", &RWSInterface::collectRuntimeInfo)
        .def("set_motors_on", &RWSInterface::setMotorsOn)
        .def("set_motors_off", &RWSInterface::setMotorsOff)
        .def("start_rapid_execution", &RWSInterface::startRAPIDExecution)
        .def("stop_rapid_execution", &RWSInterface::stopRAPIDExecution)
        .def("reset_rapid_program_pointer", &RWSInterface::resetRAPIDProgramPointer)
        .def("get_system_info", &RWSInterface::getSystemInfo)
        .def("get_speed_ratio", &RWSInterface::getSpeedRatio)
        .def("set_speed_ratio", &RWSInterface::setSpeedRatio)
        .def("get_log_text", &RWSInterface::getLogText, py::arg("verbose") = false)
        .def("get_log_text_latest_event", &RWSInterface::getLogTextLatestEvent, py::arg("verbose") = false)
        .def("set_io_signal", &RWSInterface::setIOSignal)
        .def("get_io_signal", &RWSInterface::getIOSignal)
        .def("is_auto_mode", &RWSInterface::isAutoMode)
        .def("is_motors_on", &RWSInterface::isMotorsOn)
        .def("is_rapid_running", &RWSInterface::isRAPIDRunning);

    py::class_<TriBool> tribool(m, "TriBool");
    py::enum_<TriBool::Values>(tribool, "Values")
        .value("UNKNOWN", TriBool::Values::UNKNOWN_VALUE)
        .value("FALSE", TriBool::Values::FALSE_VALUE)
        .value("TRUE", TriBool::Values::TRUE_VALUE)
        .export_values();

    tribool.def(py::init<const TriBool::Values>(), py::arg("value") = TriBool::Values::UNKNOWN_VALUE)
        .def("is_true", &TriBool::isTrue)
        .def("is_false", &TriBool::isFalse)
        .def("is_unknown", &TriBool::isUnknown)
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("__repr__", &TriBool::toString);

}   
}
}
