# Execution Ratio vs Utilization with Redundancy partition
# Name: Pavan Kumar Paluri

# Plots
import matplotlib.pyplot as plt
import numpy as np

# X Axis
utilization_ratio = [40, 50, 60, 70, 80, 90, 100]

# Y Axes
sched_exec_ratio_u0 = [100, 100, 100, 100, 100, 85, 0]

sched_exec_ratio_u1 = [100, 100, 79, 74, 67, 50, 0] # For fault rate 2

sched_exec_ratio_u2 = [100, 100, 78, 66, 50, 37, 0] # For fault rate 4

sched_exec_ratio_u3 = [100, 100, 55, 41, 36, 21, 0] # For fault rate 8

# plot lines
plt.plot(utilization_ratio, sched_exec_ratio_u0, label="Fault Rate:0", marker='o')
plt.plot(utilization_ratio, sched_exec_ratio_u1, label="Fault Rate:2", marker="v")
plt.plot(utilization_ratio, sched_exec_ratio_u2, label="Fault Rate:4", marker=">")
plt.plot(utilization_ratio, sched_exec_ratio_u3, label="Fault Rate:8", marker="^")


plt.xlabel("Utilization")
plt.ylabel("Exection Ratio (\u03A9)")
plt.legend(loc="lower center", prop={'size': 10})
# plt.show()
plt.savefig('Exec_Ratio_Utilization_WithR.pdf')
