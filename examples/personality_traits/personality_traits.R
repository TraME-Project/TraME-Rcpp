
rm(list=ls())

library(TraME.Rcpp)

load("formatted_data/XYvals.RData")

#

nbSelection = dim(Xvals)[1]

Xvals = Xvals[1:nbSelection,]
Yvals = Yvals[1:nbSelection,]

sdX = apply(Xvals,2,sd)
sdY = apply(Yvals,2,sd)
mX = apply(Xvals,2,mean)
mY = apply(Yvals,2,mean)

Xvals = t( (t(Xvals)-mX) / sdX)
Yvals = t( (t(Yvals)-mY) / sdY)

nobs = dim(Xvals)[1]

muhatxy = diag(x=1,nobs)

#

model_obj = new(model_mfe_geo)
model_obj$build(Xvals,Yvals)

res_mme = model_obj$mme(muhatxy,0.3)

ptm = proc.time()

res_mme = model_obj$mme(muhatxy)

A_mme = matrix(res_mme$theta_hat,nrow=dim(Xvals)[2])

time =  proc.time()  - ptm
message(paste0('\nTime taken (Affinity) = ', time["elapsed"], 's.\n'))

print(A_mme)
