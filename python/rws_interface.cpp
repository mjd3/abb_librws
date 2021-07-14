#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>


// #include "../include/abb_librws/rws_interface.h"
#include "../include/abb_librws/rws_state_machine_interface.h"
// #include "../include/abb_librws/rws_common.h"
// #include "../include/abb_librws/rws_rapid.h"

namespace py = pybind11;

namespace abb {
namespace rws {

using Services = std::decay_t<std::result_of_t<decltype(&RWSStateMachineInterface::services)(RWSStateMachineInterface)>>;
using SG = std::decay_t<std::result_of_t<decltype(&Services::sg)(Services)>>;
using Main = std::decay_t<std::result_of_t<decltype(&Services::main)(Services)>>;
using RAPID = std::decay_t<std::result_of_t<decltype(&Services::rapid)(Services)>>;

PYBIND11_MODULE(abb_librws, m) {
    
    py::class_<RAPIDBool>(m, "RAPIDBool")
        .def(py::init<const bool>(), py::arg("bool") = false)
        .def_readwrite("value", &RAPIDBool::value)
    ;
    py::implicitly_convertible<bool, RAPIDBool>();

    py::class_<RAPIDNum>(m, "RAPIDNum")
        .def(py::init<const float>(), py::arg("float") = 0.0)
        .def_readwrite("value", &RAPIDNum::value)
    ;
    py::implicitly_convertible<float, RAPIDNum>();

    py::class_<RAPIDDnum>(m, "RAPIDDnum")
        .def(py::init<const double>(), py::arg("float") = 0.0)
        .def_readwrite("value", &RAPIDDnum::value)
    ;
    py::implicitly_convertible<float, RAPIDDnum>();

    py::class_<RAPIDString>(m, "RAPIDString")
        .def(py::init<const std::string&>(), py::arg("string") = "")
        .def_readwrite("value", &RAPIDString::value)
    ;
    py::implicitly_convertible<std::string, RAPIDString>();

    py::class_<RAPIDSymbolDataAbstract>(m, "RAPIDSymbolDataAbstract");
    py::class_<RAPIDRecord, RAPIDSymbolDataAbstract>(m, "RAPIDRecord")
        .def(py::init<const std::string&>(), py::arg("record_type_name"))
    ;

    py::class_<RWSInterface> iface(m, "RWSInterface");
    py::class_<RWSStateMachineInterface, RWSInterface> sm_iface(m, "RWSStateMachineInterface");

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

    py::enum_<RWSStateMachineInterface::States>(m, "States")
        .value("IDLE", RWSStateMachineInterface::States::STATE_IDLE)
        .value("INITIALIZE", RWSStateMachineInterface::States::STATE_INITIALIZE)
        .value("RUN_RAPID_ROUTINE", RWSStateMachineInterface::States::STATE_RUN_RAPID_ROUTINE)
        .value("RUN_EGM_ROUTINE", RWSStateMachineInterface::States::STATE_RUN_EGM_ROUTINE)
        .value("UNKNOWN", RWSStateMachineInterface::States::STATE_UNKNOWN)
        .export_values()
    ;
    
    py::enum_<RWSStateMachineInterface::SGCommands>(m, "SGCommands")
        .value("NONE", RWSStateMachineInterface::SGCommands::SG_COMMAND_NONE)
        .value("INITIALIZE", RWSStateMachineInterface::SGCommands::SG_COMMAND_INITIALIZE)
        .value("CALIBRATE", RWSStateMachineInterface::SGCommands::SG_COMMAND_CALIBRATE)
        .value("MOVE_TO", RWSStateMachineInterface::SGCommands::SG_COMMAND_MOVE_TO)
        .value("GRIP_IN", RWSStateMachineInterface::SGCommands::SG_COMMAND_GRIP_IN)
        .value("GRIP_OUT", RWSStateMachineInterface::SGCommands::SG_COMMAND_GRIP_OUT)
        .export_values()
    ;

    py::class_<RWSInterface::MechanicalUnitStaticInfo>(m, "MechanicalUnitStaticInfo")
        .def(py::init<>())
        .def_readonly("type", &RWSInterface::MechanicalUnitStaticInfo::type)
        .def_readonly("task_name", &RWSInterface::MechanicalUnitStaticInfo::task_name)
        .def_readonly("axes", &RWSInterface::MechanicalUnitStaticInfo::axes)
        .def_readonly("axes_total", &RWSInterface::MechanicalUnitStaticInfo::axes_total)
        .def_readonly("is_integrated_unit", &RWSInterface::MechanicalUnitStaticInfo::is_integrated_unit)
        .def_readonly("has_integrated_unit", &RWSInterface::MechanicalUnitStaticInfo::has_integrated_unit)
    ;

    py::class_<RWSInterface::MechanicalUnitDynamicInfo>(m, "MechanicalUnitDynamicInfo")
        .def(py::init<>())
        .def_readonly("tool_name", &RWSInterface::MechanicalUnitDynamicInfo::tool_name)
        .def_readonly("wobj_name", &RWSInterface::MechanicalUnitDynamicInfo::wobj_name)
        .def_readonly("payload_name", &RWSInterface::MechanicalUnitDynamicInfo::payload_name)
        .def_readonly("total_payload_name", &RWSInterface::MechanicalUnitDynamicInfo::total_payload_name)
        .def_readonly("status", &RWSInterface::MechanicalUnitDynamicInfo::status)
        .def_readonly("mode", &RWSInterface::MechanicalUnitDynamicInfo::mode)
        .def_readonly("jog_mode", &RWSInterface::MechanicalUnitDynamicInfo::jog_mode)
    ;

    py::class_<RWSInterface::SystemInfo>(m, "SystemInfo")
        .def(py::init<>())
        .def_readonly("robot_ware_version", &RWSInterface::SystemInfo::robot_ware_version)
        .def_readonly("system_name", &RWSInterface::SystemInfo::system_name)
        .def_readonly("system_type", &RWSInterface::SystemInfo::system_type)
        .def_readonly("system_options", &RWSInterface::SystemInfo::system_options)
    ;
    
    py::class_<RWSInterface::RuntimeInfo>(m, "RuntimeInfo")
        .def(py::init<>())
        .def_readonly("auto_mode", &RWSInterface::RuntimeInfo::auto_mode)
        .def_readonly("motors_on", &RWSInterface::RuntimeInfo::motors_on)
        .def_readonly("rapid_running", &RWSInterface::RuntimeInfo::rapid_running)
        .def_readonly("rws_connected", &RWSInterface::RuntimeInfo::rws_connected)
    ;
    
    iface.def(py::init<const std::string &>(), py::arg("ip_address") = "192.168.125.1")
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
        .def("is_rapid_running", &RWSInterface::isRAPIDRunning)
    ;

    sm_iface.def(py::init<const std::string &>(), py::arg("ip_address") = "192.168.125.1")
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
        .def("run_move_to_calibration_position", &RAPID::runMoveToCalibrationPosition)
        .def("run_move_j", &RAPID::runMoveJ)
        .def("run_move_abs_j", &RAPID::runMoveAbsJ)
    ;

    py::class_<RobJoint, RAPIDRecord>(m, "RobJoint")
        .def(py::init<>())
        .def(py::init([](RAPIDNum& rax_1, RAPIDNum& rax_2, RAPIDNum& rax_3, RAPIDNum& rax_4, RAPIDNum& rax_5, RAPIDNum& rax_6) {RobJoint* r = new RobJoint(); r->rax_1 = rax_1; r->rax_2 = rax_2; r->rax_3 = rax_3; r->rax_4 = rax_4; r->rax_5 = rax_5; r->rax_6 = rax_6; return r;}), py::arg("rax_1") = 0.0, py::arg("rax_2") = 0.0, py::arg("rax_3") = 0.0, py::arg("rax_4") = 0.0, py::arg("rax_5") = 0.0, py::arg("rax_6") = 0.0)
        .def(py::init([](py::array_t<double> arr) {RobJoint* r = new RobJoint(); auto arr_u = arr.mutable_unchecked<1>(); r->rax_1 = arr_u(0); r->rax_2 = arr_u(1); r->rax_3 = arr_u(2); r->rax_4 = arr_u(3); r->rax_5 = arr_u(4); r->rax_6 = arr_u(5); return r;}))
        .def_readwrite("rax_1", &RobJoint::rax_1)
        .def_readwrite("rax_2", &RobJoint::rax_2)
        .def_readwrite("rax_3", &RobJoint::rax_3)
        .def_readwrite("rax_4", &RobJoint::rax_4)
        .def_readwrite("rax_5", &RobJoint::rax_5)
        .def_readwrite("rax_6", &RobJoint::rax_6)
        .def("__repr__", &RobJoint::constructString)
 ;

    py::class_<ExtJoint, RAPIDRecord>(m, "ExtJoint")
        .def(py::init<>())
        .def(py::init([](RAPIDNum& eax_a, RAPIDNum& eax_b, RAPIDNum& eax_c, RAPIDNum& eax_d, RAPIDNum& eax_e, RAPIDNum& eax_f) {ExtJoint* e = new ExtJoint(); e->eax_a = eax_a; e->eax_b = eax_b; e->eax_c = eax_c; e->eax_d = eax_d; e->eax_e = eax_e; e->eax_f = eax_f; return e;}), py::arg("eax_a") = 0.0, py::arg("eax_b") = 0.0, py::arg("eax_c") = 0.0, py::arg("eax_d") = 0.0, py::arg("eax_e") = 0.0, py::arg("eax_f") = 0.0)
        .def(py::init([](py::array_t<double> arr) {ExtJoint* e = new ExtJoint(); auto arr_u = arr.mutable_unchecked<1>(); e->eax_a = arr_u(0); e->eax_b = arr_u(1); e->eax_c = arr_u(2); e->eax_d = arr_u(3); e->eax_e = arr_u(4); e->eax_f = arr_u(5); return e;}))
        .def_readwrite("eax_a", &ExtJoint::eax_a)
        .def_readwrite("eax_b", &ExtJoint::eax_b)
        .def_readwrite("eax_c", &ExtJoint::eax_c)
        .def_readwrite("eax_d", &ExtJoint::eax_d)
        .def_readwrite("eax_e", &ExtJoint::eax_e)
        .def_readwrite("eax_f", &ExtJoint::eax_f)
        .def("__repr__", &ExtJoint::constructString)
    ;

    py::class_<Pos, RAPIDRecord>(m, "Pos")
        .def(py::init<>())
        .def_readwrite("x", &Pos::x)
        .def_readwrite("y", &Pos::y)
        .def_readwrite("z", &Pos::z)
    ;

    py::class_<Orient, RAPIDRecord>(m, "Orient")
        .def(py::init<>())
        // .def(py::init([](RAPIDNum& q1, RAPIDNum& q2, RAPIDNum& q3, RAPIDNum& q4) { Orient* o = new Orient(); o->q1 = q1; o->q2 = q2; o->q3 = q3; o->q4 = q4; return o;}))
        .def_readwrite("q1", &Orient::q1)
        .def_readwrite("q2", &Orient::q2)
        .def_readwrite("q3", &Orient::q3)
        .def_readwrite("q4", &Orient::q4)
    ;

    py::class_<Pose, RAPIDRecord>(m, "Pose")
        .def(py::init<>())
        .def(py::init<const Pose&>())
        // .def(py::init<const Pos&, const Orient&>([](Pos& pos, Orient& rot) { Pose* pose = new Pose(); pose->pos = pos; pose->rot = rot; return pose; }))
        .def_readwrite("pos", &Pose::pos)
        .def_readwrite("rot", &Pose::rot)
    ;

    py::class_<ConfData, RAPIDRecord>(m, "ConfData")
        .def(py::init<>())
        .def_readwrite("cf1", &ConfData::cf1)
        .def_readwrite("cf4", &ConfData::cf4)
        .def_readwrite("cf6", &ConfData::cf6)
        .def_readwrite("cfx", &ConfData::cfx)
    ;

    py::class_<RobTarget, RAPIDRecord>(m, "RobTarget")
        .def(py::init<>())
        .def(py::init<const RobTarget&>())
        .def_readwrite("pos", &RobTarget::pos)
        .def_readwrite("orient", &RobTarget::orient)
        .def_readwrite("robconf", &RobTarget::robconf)
        .def_readwrite("extax", &RobTarget::extax)
    ;

    py::class_<JointTarget, RAPIDRecord>(m, "JointTarget")
        .def(py::init<>())
        .def(py::init<const JointTarget&>())
        .def(py::init([](RobJoint& robax, ExtJoint& extax) {JointTarget* jt = new JointTarget(); jt->robax = robax; jt->extax = extax; return jt;}), py::arg("robax"), py::arg("extax"))
        .def_readwrite("robax", &JointTarget::robax)
        .def_readwrite("extax", &JointTarget::extax)
        .def("__repr__", &JointTarget::constructString)
    ;

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
