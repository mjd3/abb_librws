from abb_librws import RWSStateMachineInterface, JointTarget, RobJoint, ExtJoint, States, SpeedData
import numpy as np

iface = RWSStateMachineInterface("192.168.125.1")
r_task, l_task = iface.get_rapid_tasks()
r_rob, l_rob = iface.get_cfg_robots()
sd = SpeedData(np.array([100, 100, 100, 100]))
iface.services().rapid().set_move_speed(l_task.name, sd)
jt = JointTarget(RobJoint(), ExtJoint())
iface.services().rapid().run_move_abs_j(l_task.name, jt)
while iface.services().main().is_state_idle(l_task.name).is_false():
    print(iface.get_mechanical_unit_joint_target(l_rob.name))
    pass
jt = JointTarget(RobJoint(rax_5=50.0), ExtJoint())
iface.services().rapid().run_move_abs_j(l_task.name, jt)
while iface.services().main().is_state_idle(l_task.name).is_false():
    print(iface.get_mechanical_unit_joint_target(l_rob.name))
    pass
jt = JointTarget(RobJoint(), ExtJoint())
iface.services().rapid().run_move_abs_j(l_task.name, jt)
while iface.services().main().is_state_idle(l_task.name).is_false():
    print(iface.get_mechanical_unit_joint_target(l_rob.name))
    pass
jt = JointTarget(RobJoint(rax_5=50.0), ExtJoint())
iface.services().rapid().run_move_abs_j(l_task.name, jt)
while iface.services().main().is_state_idle(l_task.name).is_false():
    print(iface.get_mechanical_unit_joint_target(l_rob.name))
    pass
jt = JointTarget(RobJoint(), ExtJoint())
iface.services().rapid().run_move_abs_j(l_task.name, jt)
while iface.services().main().is_state_idle(l_task.name).is_false():
    print(iface.get_mechanical_unit_joint_target(l_rob.name))
    pass
