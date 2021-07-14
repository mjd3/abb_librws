from abb_librws import RWSStateMachineInterface, JointTarget, RobJoint, ExtJoint
import time

iface = RWSStateMachineInterface("192.168.125.1")
jt = JointTarget(RobJoint(), ExtJoint())
iface.services().rapid().run_move_abs_j("T_ROB_L", jt)
time.sleep(1)
while not iface.services().main().is_state_idle("T_ROB_L"):
    pass
jt = JointTarget(RobJoint(rax_5=50.0), ExtJoint())
iface.services().rapid().run_move_abs_j("T_ROB_L", jt)
time.sleep(1)
while not iface.services().main().is_state_idle("T_ROB_L"):
    pass
jt = JointTarget(RobJoint(rax_5=100.0), ExtJoint())
iface.services().rapid().run_move_abs_j("T_ROB_L", jt)
time.sleep(0.1)
while not iface.services().main().is_state_idle("T_ROB_L"):
    pass
jt = JointTarget(RobJoint(rax_5=50.0), ExtJoint())
iface.services().rapid().run_move_abs_j("T_ROB_L", jt)
time.sleep(0.1)
while not iface.services().main().is_state_idle("T_ROB_L"):
    pass
jt = JointTarget(RobJoint(), ExtJoint())
iface.services().rapid().run_move_abs_j("T_ROB_L", jt)
