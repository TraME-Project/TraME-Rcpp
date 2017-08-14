rm(list=ls())

library(TraME.R)

#library(gurobi)

alpha = matrix(c(1.6, 3.2, 1.1, 2.9, 1.0, 3.1),nrow=2,byrow=T)
gamma = matrix(c(1.6, 3.2, 1.1, 2.9, 1.0, 3.1),nrow=2,byrow=T)
muhat = matrix(c(1, 3, 1, 2, 1, 3), nrow=2, byrow=T)

n = c(1.2*apply(muhat,1,sum))
m = c(1.3*apply(t(muhat),1,sum))

nbX = length(n)
nbY = length(m)

lambda = 1 + alpha
zeta = 1 + gamma

phi = alpha + gamma

lambda_LTU = lambda/(lambda + zeta)
phi_LTU = (lambda*alpha + zeta*gamma) / (lambda + zeta)
#
dse_logit_obj_TU <- new(dse_logit_tu_R)
dse_logit_obj_TU$build(n,m,phi,FALSE)

dse_logit_obj_LTU <- new(dse_logit_ltu_R)
dse_logit_obj_LTU$build(n,m,lambda_LTU,phi_LTU,FALSE)

dse_logit_obj_NTU <- new(dse_logit_ntu_R)
dse_logit_obj_NTU$build(n,m,alpha,gamma,FALSE)
#
dse_logit_obj_TU$solve("jacobi")
dse_logit_obj_LTU$solve("jacobi")
dse_logit_obj_NTU$solve("darum")
#
arums_G = dse_logit_obj_NTU$get_arums_G()
arums_H = dse_logit_obj_NTU$get_arums_H()

arums_G$U = matrix(0,nbX,nbY)
dse_logit_obj_NTU$set_arums_G(arums_G)

arums_G2 = dse_logit_obj_NTU$get_arums_G()
arums_G2$U

#
# get transfers object

trans_obj = dse_logit_obj_TU$get_transfers()
trans_obj$Psi(phi,phi)

#
# test empirical object

dse_emp_obj_TU <- new(dse_empirical_tu_R)
dse_emp_obj_TU$build(n,m,phi,arums_G,arums_H,FALSE)
dse_emp_obj_TU$solve("cupidsLP")
