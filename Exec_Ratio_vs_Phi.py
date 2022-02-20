# Execution Ratio vs Phi
# Name: Pavan Kumar Paluri

# Plots
import matplotlib.pyplot as plt
import numpy as np

# X Axis
phi = [80, 85, 90, 95, 99, 100]

# Y Axes
sched_exec_ratio_u0 = [46, 49, 61, 79, 84, 0] # For fault rate 2

sched_exec_ratio_u1 = [47, 50, 56, 66, 72, 0] # For fault rate 4

sched_exec_ratio_u2 = [42, 50, 51, 59, 64, 0] # For fault rate 6

# plot lines
plt.plot(phi, sched_exec_ratio_u0, label="Fault Rate:2", marker='o')
plt.plot(phi, sched_exec_ratio_u1, label="Fault Rate:4", marker="v")
plt.plot(phi, sched_exec_ratio_u2, label="Fault Rate:6", marker=">")
# plt.plot(utilization_ratio, sched_exec_ratio_u3, label="Fault Rate:8", marker="^")


plt.xlabel("\u03A6")
plt.ylabel("Exection Ratio (\u03A9)")
plt.legend(loc="lower center", prop={'size': 10})
# plt.show()
plt.savefig('Exec_Ratio_Phi.pdf')
