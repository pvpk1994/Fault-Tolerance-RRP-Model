# Execution Ratio vs Utilization when Redundancy Partition is ignored
# Name: Pavan Kumar Paluri
# Plots
import matplotlib.pyplot as plt
import numpy as np

# X Axis
utilization_ratio = [40, 50, 60, 70, 80, 90, 100]

# Y Axes
sched_exec_ratio_u0 = [100, 100, 100, 100, 100, 85, 0]

sched_exec_ratio_u = [67.6, 67.6, 70.26, 64.0172, 56.82, 46.69, 0] # For fault rate 2

sched_exec_ratio_u1 = [62.8, 62.88, 60.86, 56.332, 48.9, 37.16, 0] # For fault rate 4

sched_exec_ratio_u2 = [44.5, 60.63, 49.64, 45.532, 38.328, 27.25, 0] # For fault rate 6

sched_exec_ratio_u3 = [45.29, 59.2, 49.32, 44.53, 37.90, 23.77, 0] # for fault rate 8

sched_exec_ratio_u4 = [33.28, 45.7, 43.60, 39.01, 32.39, 20.73, 0] # fir fault rate 10


# plot lines
plt.plot(utilization_ratio, sched_exec_ratio_u0, label="Fault Rate:0", marker='o')
plt.plot(utilization_ratio, sched_exec_ratio_u, label="Fault Rate:2", marker="v")
plt.plot(utilization_ratio, sched_exec_ratio_u1, label="Fault Rate:4", marker=">")
plt.plot(utilization_ratio, sched_exec_ratio_u2, label="Fault Rate:6", marker="<")
plt.plot(utilization_ratio, sched_exec_ratio_u3, label="Fault Rate:8", marker="^")
plt.plot(utilization_ratio, sched_exec_ratio_u4, label="Fault Rate:10", marker="x")

plt.xlabel("Utilization")
plt.ylabel("Exection Ratio (\u03A9)")
plt.legend(loc="lower center", prop={'size': 8})
# plt.show()
plt.savefig('Exec_Ratio_Utilization.pdf')