
rm(list=ls())

library(TraME.Rcpp)

#

mydataX <- read.csv("formatted_data/male.csv")
mydataY <- read.csv("formatted_data/female.csv")

Xvals = mydataX[,c(5,6,7,8)]
Yvals = mydataY[,c(5,6,7)]

meanX = apply(Xvals,2,mean)
meanY = apply(Yvals,2,mean)
sdX = apply(Xvals,2,sd)
sdY = apply(Yvals,2,sd)

Xvals = t( t(Xvals) - meanX )
Yvals = t( t(Yvals) - meanY )
Xvals = t( t(Xvals) / sdX)
Yvals = t( t(Yvals) / sdY)

nobs = dim(Xvals)[1]
muhatxy = diag(x=1,nobs)

#

model_obj = new(model_mfe_geo)
model_obj$build(Xvals,Yvals)

ptm = proc.time()

res_mme = model_obj$mme(muhatxy)

A_mme = matrix(res_mme$theta_hat,nrow=dim(Xvals)[2])

time =  proc.time()  - ptm
message(paste0('\nTime taken (Affinity) = ', time["elapsed"], 's.\n'))

print(A_mme)

#mmeaffinityWithRegul(affinityModel, muhatxy, 0, xtol_rel=1e-4, maxeval=1e5, tolIpfp=1E-14, maxiterIpfp = 1e5, print_level=0)
