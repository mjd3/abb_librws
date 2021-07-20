from abb_librws import RWSStateMachineInterface, JointTarget, RobJoint, ExtJoint, States
import time

iface = RWSStateMachineInterface("192.168.125.1")
iface.services().rapid().set_move_speed(100)
jt = JointTarget(RobJoint(), ExtJoint())
iface.services().rapid().run_move_abs_j("T_ROB_L", jt)
while iface.services().main().is_state_idle("T_ROB_L").is_false():
    print(iface.get_mechanical_unit_joint_target(iface.get_cfg_mechanical_unit_groups()[1].robot))
    pass
jt = JointTarget(RobJoint(rax_5=50.0), ExtJoint())
iface.services().rapid().run_move_abs_j("T_ROB_L", jt)
while iface.services().main().is_state_idle("T_ROB_L").is_false():
    print(iface.get_mechanical_unit_joint_target(iface.get_cfg_mechanical_unit_groups()[1].robot))
    pass
jt = JointTarget(RobJoint(), ExtJoint())
iface.services().rapid().run_move_abs_j("T_ROB_L", jt)
while iface.services().main().is_state_idle("T_ROB_L").is_false():
    print(iface.get_mechanical_unit_joint_target(iface.get_cfg_mechanical_unit_groups()[1].robot))
    pass
jt = JointTarget(RobJoint(rax_5=50.0), ExtJoint())
iface.services().rapid().run_move_abs_j("T_ROB_L", jt)
while iface.services().main().is_state_idle("T_ROB_L").is_false():
    print(iface.get_mechanical_unit_joint_target(iface.get_cfg_mechanical_unit_groups()[1].robot))
    pass
jt = JointTarget(RobJoint(), ExtJoint())
iface.services().rapid().run_move_abs_j("T_ROB_L", jt)
