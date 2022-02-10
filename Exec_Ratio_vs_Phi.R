# Execution Ratio vs Phi
# Pavan Kumar Paluri

library(latex2exp)

phi <- c(80, 85, 90, 95, 99, 100) # Phi

sched_exec_ratio_u0 <- c(46, 49, 61, 79, 84, 0) # Fault rate 2
sched_exec_ratio_u1 <- c(47, 50, 56, 66, 72, 0) # Fault rate 4
sched_exec_ratio_u2 <- c(42, 50, 51, 59, 64, 0) # Fault rate 6

par(pty="s")
plot(phi,sched_exec_ratio_u0,type="o",col="blue",xlab = TeX("$\\Phi$"),ylab=TeX("Execution Ratio $(\\Omega)$"),xlim=c(80,100),ylim=c(0,100),las=1,pch=1)
lines(phi,sched_exec_ratio_u1,col="red",type="o",pch=2)
lines(phi,sched_exec_ratio_u2,col="black",type="o",pch=3)

grid()
legend("bottomleft",legend=c("FaultRate:2","FaultRate:4","FaultRate:6"),col=c("blue","red","black"),lty=1:2,cex=0.9,pch=c(1,2,4),pt.cex=1,merge=TRUE)
