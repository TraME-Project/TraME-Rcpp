
rm(list=ls())

library(TraME.Rcpp)

#

nbX = 18
nbY = 5
sigma = 1

n = rep(1,nbX)
m = rep(1,nbY)

alpha = matrix(runif(nbX*nbY),nbX,nbY)
gamma = matrix(runif(nbX*nbY),nbX,nbY)

lambda = 1 + matrix(runif(nbX*nbY),nbX,nbY)
zeta = 1 + matrix(runif(nbX*nbY),nbX,nbY)

phi = alpha + gamma

lambda_LTU = lambda/(lambda + zeta)
phi_LTU = (lambda*alpha + zeta*gamma) / (lambda + zeta)

#

mfe_geo_obj <- new(mfe_geo)
mfe_geo_obj$build(n,m,phi,sigma,FALSE)

mfe_cd_obj <- new(mfe_cd)
mfe_cd_obj$build(n,m,lambda_LTU,phi_LTU,sigma,FALSE)

mfe_min_obj <- new(mfe_min)
mfe_min_obj$build(n,m,alpha,gamma,sigma,FALSE)

#

ptm = proc.time()

sol_geo <- mfe_geo_obj$solve("ipfp")
sol_cd <- mfe_cd_obj$solve("ipfp")
sol_min <- mfe_min_obj$solve("ipfp")

time =  proc.time()  - ptm

message(paste0('\nTime taken = ', time["elapsed"], 's.\n'))

sol_cd <- mfe_cd_obj$solve("i")
