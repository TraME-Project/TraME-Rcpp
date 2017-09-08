library(TraME)
rm(list=ls())
#library(gurobi)
nbX=5
nbY=3

n=rep(1,nbX)
m=rep(1,nbY)  

phi =  matrix(runif(nbX*nbY),nrow=nbX)

zetaG = matrix(1,nbX,1) %*% matrix(runif(nbY+1),1,nbY+1)
zetaH = matrix(1,nbY,1) %*% matrix(runif(nbX+1),1,nbX+1)
#
rscG = new(rsc)
rscH = new(rsc)

rscG$build_beta(zetaG,2,2)
rscH$build_beta(zetaH,2,2)

dse_rsc_obj_TU <- new(dse_rsc)
dse_rsc_obj_TU$build_TU(n,m,phi,rscG,rscH,FALSE)

dse_emp_obj_TU <- new(dse_empirical)
dse_emp_obj_TU$build_TU(n,m,phi,rscG,rscH,FALSE)

dse_rsc_obj_TU$solve("maxWelfare")
dse_emp_obj_TU$solve("cupidsLP")
