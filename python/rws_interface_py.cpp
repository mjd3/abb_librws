#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "../include/abb_librws/rws_interface.h"

using namespace pybind11::literals;
namespace py = pybind11;

namespace abb {
namespace rws {

void init_interface(py::module &m){
    py::class_<RWSInterface> iface(m, "RWSInterface");

    py::enum_<RWSInterface::RAPIDTaskExecutionState>(m, "RAPIDTaskExecutionState")
        .value("UNKNOWN", RWSInterface::RAPIDTaskExecutionState::UNKNOWN)
        .value("READY", RWSInterface::RAPIDTaskExecutionState::READY)
        .value("STOPPED", RWSInterface::RAPIDTaskExecutionState::STOPPED)
        .value("STARTED", RWSInterface::RAPIDTaskExecutionState::STARTED)
        .value("UNINITIALIZED", RWSInterface::RAPIDTaskExecutionState::UNINITIALIZED)
        .export_values()
    ;

    py::enum_<RWSInterface::MechanicalUnitType>(m, "MechanicalUnitType")
        .value("NONE", RWSInterface::MechanicalUnitType::NONE)
        .value("TCP_ROBOT", RWSInterface::MechanicalUnitType::TCP_ROBOT)
        .value("ROBOT", RWSInterface::MechanicalUnitType::ROBOT)
        .value("SINGLE", RWSInterface::MechanicalUnitType::SINGLE)
        .value("UNDEFINED", RWSInterface::MechanicalUnitType::UNDEFINED)
        .export_values()
    ;

    py::enum_<RWSInterface::MechanicalUnitMode>(m, "MechanicalUnitMode")
        .value("UNKNOWN_MODE", RWSInterface::MechanicalUnitMode::UNKNOWN_MODE)
        .value("ACTIVATED", RWSInterface::MechanicalUnitMode::ACTIVATED)
        .value("DEACTIVATED", RWSInterface::MechanicalUnitMode::DEACTIVATED)
        .export_values()
    ;

    py::class_<RWSInterface::MechanicalUnitStaticInfo>(m, "MechanicalUnitStaticInfo")
        .def_readonly("type", &RWSInterface::MechanicalUnitStaticInfo::type)
        .def_readonly("task_name", &RWSInterface::MechanicalUnitStaticInfo::task_name)
        .def_readonly("axes", &RWSInterface::MechanicalUnitStaticInfo::axes)
        .def_readonly("axes_total", &RWSInterface::MechanicalUnitStaticInfo::axes_total)
        .def_readonly("is_integrated_unit", &RWSInterface::MechanicalUnitStaticInfo::is_integrated_unit)
        .def_readonly("has_integrated_unit", &RWSInterface::MechanicalUnitStaticInfo::has_integrated_unit)
    ;

    py::class_<RWSInterface::MechanicalUnitDynamicInfo>(m, "MechanicalUnitDynamicInfo")
        .def_readonly("tool_name", &RWSInterface::MechanicalUnitDynamicInfo::tool_name)
        .def_readonly("wobj_name", &RWSInterface::MechanicalUnitDynamicInfo::wobj_name)
        .def_readonly("payload_name", &RWSInterface::MechanicalUnitDynamicInfo::payload_name)
        .def_readonly("total_payload_name", &RWSInterface::MechanicalUnitDynamicInfo::total_payload_name)
        .def_readonly("status", &RWSInterface::MechanicalUnitDynamicInfo::status)
        .def_readonly("mode", &RWSInterface::MechanicalUnitDynamicInfo::mode)
        .def_readonly("jog_mode", &RWSInterface::MechanicalUnitDynamicInfo::jog_mode)
    ;

    py::class_<RWSInterface::SystemInfo>(m, "SystemInfo")
        .def_readonly("robot_ware_version", &RWSInterface::SystemInfo::robot_ware_version)
        .def_readonly("system_name", &RWSInterface::SystemInfo::system_name)
        .def_readonly("system_type", &RWSInterface::SystemInfo::system_type)
        .def_readonly("system_options", &RWSInterface::SystemInfo::system_options)
    ;

    py::class_<RWSInterface::RAPIDModuleInfo>(m, "RAPIDModuleInfo")
        .def_readonly("name", &RWSInterface::RAPIDModuleInfo::name)
        .def_readonly("type", &RWSInterface::RAPIDModuleInfo::type)
    ;

    py::class_<RWSInterface::RAPIDTaskInfo>(m, "RAPIDTaskInfo")
        .def_readonly("name", &RWSInterface::RAPIDTaskInfo::name)
        .def_readonly("motion_task", &RWSInterface::RAPIDTaskInfo::is_motion_task)
        .def_readonly("active", &RWSInterface::RAPIDTaskInfo::is_active)
        .def_readonly("execution_state", &RWSInterface::RAPIDTaskInfo::execution_state)
    ;

    py::class_<RWSInterface::StaticInfo>(m, "StaticInfo")
        .def_readonly("rapid_tasks", &RWSInterface::StaticInfo::rapid_tasks)
        .def_readonly("system_info", &RWSInterface::StaticInfo::system_info)
    ;

    py::class_<RWSInterface::RuntimeInfo>(m, "RuntimeInfo")
        .def_readonly("auto_mode", &RWSInterface::RuntimeInfo::auto_mode)
        .def_readonly("motors_on", &RWSInterface::RuntimeInfo::motors_on)
        .def_readonly("rapid_running", &RWSInterface::RuntimeInfo::rapid_running)
        .def_readonly("rws_connected", &RWSInterface::RuntimeInfo::rws_connected)
    ;

    iface.def(py::init<const std::string &>(), "ip_address"_a = "192.168.125.1")
        .def_property_readonly("runtime_info", &RWSInterface::collectRuntimeInfo)
        .def_property_readonly("static_info", &RWSInterface::collectStaticInfo)
        .def("get_cfg_arms", &RWSInterface::getCFGArms)
        .def("get_cfg_joints", &RWSInterface::getCFGJoints)
        .def("get_cfg_mechanical_units", &RWSInterface::getCFGMechanicalUnits)
        .def("get_cfg_mechanical_unit_groups", &RWSInterface::getCFGMechanicalUnitGroups)
        .def("get_cfg_present_options", &RWSInterface::getCFGPresentOptions)
        .def("get_cfg_robots", &RWSInterface::getCFGRobots)
        .def("get_cfg_singles", &RWSInterface::getCFGSingles)
        .def("get_cfg_transmission", &RWSInterface::getCFGTransmission)
        .def("get_io_signal", &RWSInterface::getIOSignal)
        .def("get_mechanical_unit_static_info",
            [](RWSInterface &self, const std::string& mechunit) {
                RWSInterface::MechanicalUnitStaticInfo* musi = new RWSInterface::MechanicalUnitStaticInfo(); 
                bool res = self.getMechanicalUnitStaticInfo(mechunit, *musi);
                return res ? py::cast(musi) : py::none();
            }
        )
        .def("get_mechanical_unit_dynamic_info",
            [](RWSInterface &self, const std::string& mechunit) {
                RWSInterface::MechanicalUnitDynamicInfo* mudi = new RWSInterface::MechanicalUnitDynamicInfo(); 
                bool res = self.getMechanicalUnitDynamicInfo(mechunit, *mudi);
                return res ? py::cast(mudi) : py::none();
            }
        )
        .def("get_mechanical_unit_joint_target",
            [](RWSInterface &self, const std::string& mechunit) {
                JointTarget* jt = new JointTarget(); 
                bool res = self.getMechanicalUnitJointTarget(mechunit, jt);
                return res ? py::cast(jt) : py::none();
            }
        )
        .def("get_mechanical_unit_rob_target",
            [](RWSInterface &self, const std::string& mechunit) {
                RobTarget* rt = new RobTarget(); 
                bool res = self.getMechanicalUnitRobTarget(mechunit, rt);
                return res ? py::cast(rt) : py::none();
            }
        )
        .def("get_rapid_modules_info", &RWSInterface::getRAPIDModulesInfo)
        .def("get_rapid_tasks", &RWSInterface::getRAPIDTasks)
        .def("get_speed_ratio", &RWSInterface::getSpeedRatio)
        .def("get_system_info", &RWSInterface::getSystemInfo)
        .def_property_readonly("auto_mode", &RWSInterface::isAutoMode)
        .def_property_readonly("motors_on", &RWSInterface::isMotorsOn)
        .def_property_readonly("rapid_running", &RWSInterface::isRAPIDRunning)
        .def("set_io_signal", &RWSInterface::setIOSignal)
        .def("start_rapid_execution", &RWSInterface::startRAPIDExecution)
        .def("stop_rapid_execution", &RWSInterface::stopRAPIDExecution)
        .def("reset_rapid_program_pointer", &RWSInterface::resetRAPIDProgramPointer)
        .def("set_motors_on", &RWSInterface::setMotorsOn)
        .def("set_motors_off", &RWSInterface::setMotorsOff)
        .def("set_speed_ratio", &RWSInterface::setSpeedRatio)
        .def("get_log_text", &RWSInterface::getLogText, "verbose"_a = false)
        .def("get_log_text_latest_event", &RWSInterface::getLogTextLatestEvent, "verbose"_a = false)
    ;

}
} // end namespace rws
} // end namespace abb
