# TraME-Rcpp &nbsp; [![Build Status](https://travis-ci.org/TraME-Project/TraME-Rcpp.svg?branch=master)](https://travis-ci.org/TraME-Project/TraME-Rcpp) [![Build status](https://ci.appveyor.com/api/projects/status/github/TraME-Project/TraME-Rcpp?branch=master)](https://ci.appveyor.com/project/kthohr/trame-rcpp/branch/master)

**Tra**nsportation **M**ethods for **E**conometrics via **Rcpp** modules

## Overview

TraME (**Tra**nsportation **M**ethods for **E**conometrics) is a C++ library for solving problems of equilibrium computation and estimation in consumer demand and matching frameworks via the Mass Transportation Approach.

TraME-Rcpp is a package of Rcpp modules that allows seamless integration of the TraME C++ library with R.

## Installation and Testing

The quickest way to install TraME-Rcpp is via the devtools package.
```
install.packages("devtools")
library(devtools)
install_github("TraME-Project/TraME-Rcpp")
```
The TraME test routines are invoked as follows:
```
library(TraME.Rcpp)
tests_TraME()
```

Note that TraME requires compilation, and so an appropriate development environment is necessary to install the package.
* Windows users should get [Rtools](https://cran.r-project.org/bin/windows/Rtools/).
* Mac uses should check [here](https://cran.r-project.org/bin/macosx/tools/).

## Example

The following code replicates the example from [here](https://github.com/TraME-Project/TraME).

``` R

rm(list=ls())
library(TraME.Rcpp)

#

nbX = 18   # number of x types
nbY = 5    # number of y types
sigma = 1  # scaling value

n = rep(1,nbX)  # number of agents of each type
m = rep(1,nbY)

# systematic utilities

alpha = matrix(runif(nbX*nbY),nbX,nbY)
gamma = matrix(runif(nbX*nbY),nbX,nbY)

lambda = 1 + matrix(runif(nbX*nbY),nbX,nbY)
zeta = 1 + matrix(runif(nbX*nbY),nbX,nbY)

phi = alpha + gamma

lambda_LTU = lambda/(lambda + zeta)
phi_LTU = (lambda*alpha + zeta*gamma) / (lambda + zeta)

# build markets

mfe_geo_obj <- new(mfe_geo) # geometric matching function <=> perfectly transferable utility
mfe_geo_obj$build(n,m,phi,sigma,FALSE)

mfe_cd_obj <- new(mfe_cd)   # CD matching function <=> linearly transferable utility
mfe_cd_obj$build(n,m,lambda_LTU,phi_LTU,sigma,FALSE)

mfe_min_obj <- new(mfe_min) # min matching function <=> non-transferable utility
mfe_min_obj$build(n,m,alpha,gamma,sigma,FALSE)

# run IPFP

ptm = proc.time()

sol_geo <- mfe_geo_obj$solve("ipfp")
sol_cd <- mfe_cd_obj$solve("ipfp")
sol_min <- mfe_min_obj$solve("ipfp")

time =  proc.time()  - ptm

message(paste0('\nTime taken = ', time["elapsed"], 's.\n'))

sol_cd <- mfe_cd_obj$solve("ipfp",1E-04,1000) # direct control over tolerance values
```

## Authors

Alfred Galichon and Keith O'Hara

## License

GPL (>= 2) 

## Acknowledgements

Work on TraME is supported by NSF Grant DMS-1716489
