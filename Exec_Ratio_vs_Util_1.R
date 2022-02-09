# Execution Ratio vs Utilization (With Redundancy Area)
# Pavan Kumar Paluri

library(latex2exp)

utilization <- c(40,50,60,70,80,90, 100)
sched_exec_ratio_u0 <- c(100, 100, 100, 100, 100, 85, 0) # For Fault rate 0
sched_exec_ratio_u1 <- c(100, 100, 79, 74, 67, 50, 0) # For Fault rate 2
sched_exec_ratio_u2 <- c(100, 100, 78, 66, 50, 37, 0) # For Fault rate 4
sched_exec_ratio_u3 <- c(100, 100, 55, 41, 36, 21, 0) # For Fault rate 8

# sched_exec_ratio_u <- c(67.6,67.6,70.26,64.0172,56.82,46.69) # for faut rate 2,u:40,50,60,70,80,90
# sched_exec_ratio_u1 <- c(62.8,62.88,60.86,56.332,48.9,37.16) # for fault rate 4,u:40,50,60,70,80,90
# sched_exec_ratio_u2 <- c(44.5,60.63,49.64,45.532,38.328,27.25) # for fault rate 6
# sched_exec_ratio_u3 <- c(45.29,59.2,49.32,44.53,37.90,23.77) # for fault rate 8
# sched_exec_ratio_u4 <- c(33.28,45.7,43.60,39.01,32.39,20.73) # for fault rate 10

# sched_exec_ratio_u40 <- c(67.6,62.8,44.5,45.29,33.28)#fr:2,4,6,8,10
# sched_exec_ratio_u50 <- c(67.6,62.88,60.63,59.2,45.7)#fr:2,4,6,8,10
# sched_exec_ratio_u60 <- c(70.26,60.86,49.64,49.32,43.60)#fr:2,4,6,8,10

par(pty="s")
plot(utilization,sched_exec_ratio_u0,type="o",col="blue",xlab = "Utilization",ylab=TeX("Execution Ratio $(\\Omega)$"),xlim=c(40,100),ylim=c(0,100),las=1,pch=1)
lines(utilization,sched_exec_ratio_u1,col="red",type="o",pch=2)
lines(utilization,sched_exec_ratio_u2,col="black",type="o",pch=3)
lines(utilization,sched_exec_ratio_u3,col="dark green",type="o",pch=4)
# lines(utilization,sched_exec_ratio_u4,col="orange",type="o",pch=5)
grid()
legend("bottomleft",legend=c("FaultRate:0","FaultRate:2","FaultRate:4","FaultRate:8"),col=c("blue","red","black","dark green"),lty=1:2,cex=0.9,pch=c(1,2,4),pt.cex=1,merge=TRUE)


